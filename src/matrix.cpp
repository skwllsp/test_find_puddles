#include <algorithm>
#include <tuple>
#include <cassert>
#include <iostream>
#include <queue>
#include <functional>

#include "matrix.h"

#include <stddef.h>

namespace {

enum class direction_t {
    right,
    down,
    left,
    up
};

class perimeter {
 public:
    perimeter(const test_ns::entry_pos_t& initial_user_point,
            const test_ns::sorted_entry_positions_t& area,
            size_t max_row, size_t max_col);
    const test_ns::entry_pos_t& get_start_point() const;
    test_ns::entry_pos_t get_next_point();

 private:
    const test_ns::sorted_entry_positions_t& area;
    size_t max_row;
    size_t max_col;
    test_ns::entry_pos_t initial_user_point;
    direction_t curr_dir;
    test_ns::entry_pos_t initial_point;
    test_ns::entry_pos_t cp;
    bool current_point_valid;
    bool outside(const test_ns::entry_pos_t&) const;
    bool inside(const test_ns::entry_pos_t&) const;
    void move_point();
};

class unknown_area {
 public:
    unknown_area(
            const test_ns::sorted_entry_positions_t& perimeter_points,
            const test_ns::sorted_entry_positions_t& area);
    std::pair<bool, test_ns::entry_pos_t> get_first_unknown_entry();
 private:
    const test_ns::sorted_entry_positions_t& border_points;
    const test_ns::sorted_entry_positions_t& area;
    test_ns::sorted_entry_positions_t::const_iterator border_itr;
    bool is_iterating_row;
    size_t border_row;
    size_t border_start_col;
    size_t border_end_col;
    test_ns::sorted_entry_positions_t::const_iterator border_row_start_itr;
    test_ns::sorted_entry_positions_t::const_iterator border_row_end_itr;
};

}  // namespace

/*
 *
 */
unknown_area::unknown_area(
    const test_ns::sorted_entry_positions_t& perimeter_points,
    const test_ns::sorted_entry_positions_t& area)
    : border_points(perimeter_points), area(area),
      border_itr(border_points.begin()),
      is_iterating_row(false), border_row{0},
      border_start_col(0), border_end_col{0},
      border_row_start_itr (border_itr),  border_row_end_itr (border_itr) {
}

/*
 *
 */
std::pair<bool, test_ns::entry_pos_t>
unknown_area::get_first_unknown_entry() {
  while (border_itr != border_points.end()) {
      if (!is_iterating_row) {
          border_row_start_itr = border_itr;
          border_row_end_itr =  border_itr;
          border_row = border_row_start_itr->row;
          while (border_row_end_itr != border_points.end() &&
                 border_row == border_row_end_itr->row) {
              ++border_row_end_itr;
          }
          border_start_col = border_row_start_itr->col;
          border_end_col = std::prev(border_row_end_itr)->col;
      }
      is_iterating_row = true;
      while (border_start_col <= border_end_col) {
          test_ns::entry_pos_t an_entry = {border_row, border_start_col};
          ++border_start_col;
          if (area.find(an_entry) != area.end()) {
              continue;
          }
          return {true, an_entry};
      }
      is_iterating_row = false;
      border_itr = border_row_end_itr;
  }
  return {false, test_ns::entry_pos_t{0,0}};
}


/*
 *
 */
void pss(const test_ns::sorted_entry_positions_t& s) {
    std::cout << "[ ";
    std::cout.flush();
    for (auto const & e : s) {
        std::cout << "{" << e.row << "," << e.col << "}, ";
        std::cout.flush();
    }
    std::cout << " ]\n";
    std::cout.flush();
}

/*
 *
 */
perimeter::perimeter(const test_ns::entry_pos_t& initial_user_point,
            const test_ns::sorted_entry_positions_t& area,
            size_t max_row, size_t max_col)
    : area(area), max_row{max_row}, max_col{max_col},
    initial_user_point(initial_user_point),
    curr_dir(direction_t::right),
    initial_point(initial_user_point),
    current_point_valid(false) {
    assert(inside(initial_point));
    while (initial_point.row > 0 &&
            inside({initial_point.row-1,initial_point.col})) {
        --initial_point.row;
    }
}

/*
 *
 */
bool perimeter::outside(const test_ns::entry_pos_t& p) const {
    return area.find(p) == area.end();
}

/*
 *
 */
bool perimeter::inside(const test_ns::entry_pos_t& p) const {
    return area.find(p) != area.end();
}

/*
 *
 */
const test_ns::entry_pos_t& perimeter::get_start_point() const {
    return initial_point;
}

/*
 *
 */
test_ns::entry_pos_t perimeter::get_next_point() {
    move_point();
    return cp;
}

/*
 *
 */
void perimeter::move_point() {
    if (!current_point_valid) {
        cp = get_start_point();
        current_point_valid = true;
    }
    if (curr_dir == direction_t::right) {
        if (cp.col == max_col) {
            curr_dir = direction_t::down;
            ++cp.row;
        } else {
            if (inside({cp.row, cp.col+1})) {
                if (cp.row > 0 && inside({cp.row-1, cp.col})) {
                    curr_dir = direction_t::up;
                    --cp.row;
                } else {
                    ++cp.col;
                }
            } else {
                curr_dir = direction_t::down;
                if (inside({cp.row+1, cp.col+1})) {
                    ++cp.col;
                }
                ++cp.row;
            }
        }
    } else if (curr_dir == direction_t::left) {
        if (cp.col == 0) {
            curr_dir = direction_t::up;
            --cp.row;
        } else {
            if (inside({cp.row, cp.col-1})) {
                if (cp.row < max_row && inside({cp.row+1, cp.col})) {
                    curr_dir = direction_t::down;
                    ++cp.row;
                } else {
                    --cp.col;
                }
            } else {
                curr_dir = direction_t::up;
                if (inside({cp.row-1, cp.col-1})) {
                    --cp.col;
                }
                --cp.row;
            }
        }
    } else if (curr_dir == direction_t::down) {
        if (cp.row == max_row) {
            curr_dir = direction_t::left;
            --cp.col;
        } else {
            if (inside({cp.row+1, cp.col})) {
                if (cp.col < max_col && inside({cp.row, cp.col+1})) {
                    curr_dir = direction_t::right;
                    ++cp.col;
                } else {
                    ++cp.row;
                }
            } else {
                curr_dir = direction_t::left;
                if (inside({cp.row+1, cp.col-1})) {
                    ++cp.row;
                }
                --cp.col;
            }
        }
    } else if (curr_dir == direction_t::up) {
        if (cp.row == 0) {
            curr_dir = direction_t::right;
            ++cp.col;
        } else {
            if (inside({cp.row-1, cp.col})) {
                if (cp.col > 0 && inside({cp.row, cp.col-1})) {
                    curr_dir = direction_t::left;
                    --cp.col;
                } else {
                    --cp.row;
                }
            } else {
                curr_dir = direction_t::right;
                if (inside({cp.row-1, cp.col+1})) {
                    --cp.row;
                }
                ++cp.col;
            }
        }
    }
}

/*
 *
 */
test_ns::matrix::matrix(rows_t rows)
: rows_(std::move(rows)) {
    if (rows_.empty()) {
        max_row = 0;
        max_col = 0;
    } else {
        max_row = rows_.size() - 1;
        max_col = rows_[0].size() - 1;
    }
}


/*
 *
 */
int test_ns::matrix::get_height(const entry_pos_t& p) const {
    return rows_[p.row][p.col];
}

/*
 *
 */
void test_ns::matrix::call_neighbours(const entry_pos_t& curr_pos,
        std::function<void(const entry_pos_t&,const entry_pos_t&)>
            check_one_position) const {
    if (curr_pos.row == 0 && curr_pos.col == 0) {
        if (curr_pos.col < max_col)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col+1});
        if (curr_pos.row < max_row)
            check_one_position(curr_pos,{curr_pos.row+1,curr_pos.col});
    } else if (curr_pos.row == 0 && curr_pos.col == max_col) {
        if (curr_pos.col > 0)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col-1});
        if (curr_pos.row < max_row)
            check_one_position(curr_pos,{curr_pos.row+1,curr_pos.col});
    } else if (curr_pos.row == max_row && curr_pos.col == max_col) {
        if (curr_pos.col > 0)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col-1});
        if (curr_pos.row > 0)
            check_one_position(curr_pos,{curr_pos.row-1,curr_pos.col});
    } else if (curr_pos.row == max_row && curr_pos.col == 0) {
        if (curr_pos.row > 0)
            check_one_position(curr_pos,{curr_pos.row-1,curr_pos.col});
        if (curr_pos.col < max_col)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col+1});
    } else if (curr_pos.row == 0) {
        if (curr_pos.col > 0)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col-1});
        if (curr_pos.col < max_col)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col+1});
        if (curr_pos.row < max_row)
            check_one_position(curr_pos,{curr_pos.row+1,curr_pos.col});
    } else if (curr_pos.row == max_row) {
        if (curr_pos.col > 0)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col-1});
        if (curr_pos.col < max_col)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col+1});
        if (curr_pos.row > 0)
            check_one_position(curr_pos,{curr_pos.row-1,curr_pos.col});
    } else if (curr_pos.col == 0) {
        if (curr_pos.row > 0)
            check_one_position(curr_pos,{curr_pos.row-1,curr_pos.col});
        if (curr_pos.col < max_col)
            check_one_position(curr_pos,{curr_pos.row+1,curr_pos.col});
        if (curr_pos.col < max_col)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col+1});
    } else if (curr_pos.col == max_col) {
        if (curr_pos.row > 0)
            check_one_position(curr_pos,{curr_pos.row-1,curr_pos.col});
        if (curr_pos.row < max_row)
            check_one_position(curr_pos,{curr_pos.row+1,curr_pos.col});
        if (curr_pos.col > 0)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col-1});
    } else {
        if (curr_pos.row > 0)
            check_one_position(curr_pos,{curr_pos.row-1,curr_pos.col});
        if (curr_pos.col < max_col)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col+1});
        if (curr_pos.row < max_row)
            check_one_position(curr_pos,{curr_pos.row+1,curr_pos.col});
        if (curr_pos.col > 0)
            check_one_position(curr_pos,{curr_pos.row,curr_pos.col-1});
    }
}

/*
 *
 */
void
test_ns::matrix::get_heights() {
    size_t curr_row = 0, curr_col = 0;
    for (const auto& row : rows_) {
        curr_col = 0;
        for (const auto height : row) {
            heights.emplace(std::make_pair(height,
                    entry_pos_t{curr_row, curr_col}));
            ++curr_col;
        }
        ++curr_row;
    }
}

/*
 *
 */
void test_ns::matrix::find_uncovered_entries(
    const sorted_entry_positions_t& perimeter,
    sorted_entry_positions_t& area,
    const visited_t& visited) {
    unknown_area an_unknown_area(perimeter, area);
    while (true) {
        auto unknown_element = an_unknown_area.get_first_unknown_entry();
        if (!unknown_element.first) {
            break;
        }
        const entry_pos_t& an_unknown_entry = unknown_element.second;
        assert (visited.find(an_unknown_entry) == visited.end());
        area.insert(an_unknown_entry);
    }
}

/*
 *
 */
int test_ns::matrix::get_perimeter_h(
        const sorted_entry_positions_t& perimeter) {
    assert(!perimeter.empty());
    auto i = perimeter.begin();
    int lowest_perimeter_h = get_height(*i);
    while (++i != perimeter.end()) {
        const auto & curr_entry = *i;
        int curr_entry_h = get_height(curr_entry);
        if (curr_entry_h < lowest_perimeter_h) {
            lowest_perimeter_h = curr_entry_h;
        }
    }
    return lowest_perimeter_h;
}


/*
 *
 */
void test_ns::matrix::find_connected_area(
        const entry_pos_t& initial_point, visited_t& visited,
        int initial_h, sorted_entry_positions_t& area,
        std::set<int>& neighbours) {
    std::queue<entry_pos_t> to_search;

    auto find_higher_or_equal_neighbours =
            [this, initial_h, &to_search, &area, &visited, &neighbours](
            const entry_pos_t& base_entry, const entry_pos_t& curr_entry) {
        if (area.find(curr_entry) != area.end() ) {
            return;
        }
        auto base_entry_h = this->get_height(base_entry);
        auto curr_entry_h = this->get_height(curr_entry);
        if (base_entry_h <= curr_entry_h) {
            if (area.find(curr_entry) == area.end() ) {
                to_search.push(curr_entry);
                area.insert(curr_entry);
            }
        } else {
            // other area
            auto visiter_itr = visited.find(curr_entry);
            if (visiter_itr == visited.end()) {
                return;
            }
            found_area_t& another_area = visiter_itr->second->second;
            if (another_area.puddle_h == 0 ) {
                return;
            }
            neighbours.insert(another_area.index);
        }
    };
    to_search.push(initial_point);
    area.insert(initial_point);
    while(!to_search.empty()) {
        auto an_entry = to_search.front();
        to_search.pop();
        call_neighbours(an_entry, find_higher_or_equal_neighbours);
    }
}

/*
 *
 */
std::vector<test_ns::puddle>
test_ns::matrix::find_puddles() {
    std::vector<puddle> all_puddles;
    if (rows_.empty() || rows_.size() < 3) {
        return std::move(all_puddles);
    }

    get_heights();
    visited_t visited;

    found_areas_index = 0;

    for (auto i = heights.begin(); i != heights.end();) {
        auto initial_entry_h = i->first;
        auto const initial_entry = i->second;
        i = heights.erase(i);
        if (visited.find(initial_entry) != visited.end()) {
            continue;
        }
        sorted_entry_positions_t area_entries;
        std::set<int> neighbours;
        find_connected_area(initial_entry, visited, initial_entry_h,
                area_entries, neighbours);

        perimeter area_perimeter(initial_entry, area_entries, max_row, max_col);
        auto area_perimeter_start = area_perimeter.get_start_point();
        sorted_entry_positions_t area_perimeter_entries;
        area_perimeter_entries.insert(area_perimeter_start);
        while (true) {
            auto curr_entry = area_perimeter.get_next_point();
            if (curr_entry == area_perimeter_start) {
                break;
            }
            area_perimeter_entries.insert(curr_entry);
        }

        int lowest_perimeter_h = get_perimeter_h(area_perimeter_entries);

        if (!neighbours.empty()) {

        } else {
            sorted_entry_positions_t puddle_points;
            if (initial_entry_h < lowest_perimeter_h) {
                for (auto const & area_entry : area_entries) {
                    if (area_perimeter_entries.find(area_entry) ==
                            area_perimeter_entries.end()) {
                        int area_entry_h = get_height(area_entry);
                        if (area_entry_h < lowest_perimeter_h) {
                            puddle_points.insert(area_entry);
                        }
                    }
                }
            }
            found_area_t found_area{found_areas_index,
                std::move(area_perimeter_entries),
                area_entries, std::move(puddle_points),
                lowest_perimeter_h};
            auto found_area_pair = found_areas.insert(
                    std::make_pair(++found_areas_index,std::move(found_area)));
            for (auto const & e : area_entries) {
                visited.insert({e, found_area_pair.first});
            }
        }
    }

    for (auto & found_area_pair : found_areas) {
        if (!found_area_pair.second.puddle_points.empty()) {
            puddle a_puddle{std::move(found_area_pair.second.puddle_points)};
            all_puddles.push_back(std::move(a_puddle));
        }
    }
    return std::move(all_puddles);
}

/*
 *
 */
std::ostream& test_ns::operator<<(std::ostream& os, const test_ns::puddle& p) {
    os << "points: [";
    bool print_comma = false;
    for (auto const & e : p.entries_) {
        if (print_comma) {
            os << ", ";
        } else {
            print_comma = true;
        }
        os << '{'<< e.row << ',' << e.col << '}';
    }
    os << ']';
    return os;
}
