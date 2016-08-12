#include <algorithm>
#include <tuple>
#include <cassert>
#include <iostream>
#include <queue>
#include <functional>

#include "matrix.h"

#include <stddef.h>

namespace {

class unknown_area {
 public:
    unknown_area(const test_ns::sorted_entry_positions_t& border_points,
            const test_ns::sorted_entry_positions_t& outer_leak_points,
            const test_ns::sorted_entry_positions_t& flooded_points,
            const test_ns::sorted_entry_positions_t& all_perimeter_points);
    std::pair<bool, test_ns::entry_pos_t> get_first_unknown_entry();
 private:
    const test_ns::sorted_entry_positions_t& border_points;
    const test_ns::sorted_entry_positions_t& outer_leak_points;
    const test_ns::sorted_entry_positions_t& flooded_points;
    const test_ns::sorted_entry_positions_t& all_perimeter_points;
    test_ns::sorted_entry_positions_t::const_iterator border_itr;
    bool is_iterating_row;
    size_t border_row;
    size_t border_start_col;
    size_t border_end_col;
    test_ns::sorted_entry_positions_t::const_iterator border_row_start_itr;
    test_ns::sorted_entry_positions_t::const_iterator border_row_end_itr;
};

enum class direction_t {
    right,
    down,
    left,
    up
};

class perimeter {
 public:
    perimeter(const test_ns::entry_pos_t& initial_user_point,
            const test_ns::sorted_entry_positions_t& outer_area,
            const test_ns::sorted_entry_positions_t& flooded_area);
    const test_ns::entry_pos_t& get_start_point() const;
    const test_ns::entry_pos_t& get_start_inside_point() const;
    test_ns::entry_pos_t get_next_point();
    test_ns::entry_pos_t get_next_inside_point();
    std::pair<test_ns::entry_pos_t, test_ns::entry_pos_t>
    get_ext_and_int_points();
    bool no_more_data();

 private:
    const test_ns::sorted_entry_positions_t& outer_area;
    const test_ns::sorted_entry_positions_t& flooded_area;
    test_ns::entry_pos_t initial_user_point;
    direction_t curr_dir;
    test_ns::entry_pos_t initial_point;
    test_ns::entry_pos_t initial_inside_point;
    test_ns::entry_pos_t cp;
    test_ns::entry_pos_t inside_cp;
    bool current_point_valid;
    bool dead_end_;
    test_ns::entry_positions_t visited;
    std::queue<direction_t> initial_directions;
    bool outside(const test_ns::entry_pos_t&) const;
    bool inside(const test_ns::entry_pos_t&) const;
    void move_point();
    bool restart_search();
    bool dead_end() const;
};

}  // namespace

/*
 *
 */
perimeter::perimeter(const test_ns::entry_pos_t& initial_user_point,
            const test_ns::sorted_entry_positions_t& outer_area,
            const test_ns::sorted_entry_positions_t& flooded_area)
    : outer_area(outer_area), flooded_area(flooded_area),
    initial_user_point(initial_user_point),
    curr_dir(direction_t::right),
    initial_point(initial_user_point),
    current_point_valid(false), dead_end_{false},
    initial_directions({direction_t::left,
        direction_t::up, direction_t::down}) {
    if (!outside(initial_point)) {
        while (!outside(initial_point)) {
            --initial_point.row;
        }
    }
    initial_inside_point = {initial_point.row+1, initial_point.col};
}

/*
 *
 */
bool perimeter::outside(const test_ns::entry_pos_t& p) const {
    return outer_area.find(p) != outer_area.end() ||
            flooded_area.find(p) != flooded_area.end();
}

/*
 *
 */
bool perimeter::inside(const test_ns::entry_pos_t& p) const {
    return outer_area.find(p) == outer_area.end() &&
            flooded_area.find(p) == flooded_area.end();
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
const test_ns::entry_pos_t& perimeter::get_start_inside_point() const {
    return initial_inside_point;
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
std::pair<test_ns::entry_pos_t, test_ns::entry_pos_t>
perimeter::get_ext_and_int_points() {
    move_point();
    return std::make_pair(cp, inside_cp);
}

/*
 *
 */
test_ns::entry_pos_t perimeter::get_next_inside_point() {
    move_point();
    return inside_cp;
}

/*
 *
 */
bool perimeter::dead_end() const {
    return dead_end_;
}

/*
 *
 */
bool perimeter::no_more_data() {
    if (!dead_end_) {
        return false;
    } else {
        while (!restart_search()) {
        }
        return !dead_end_;
    }
}

/*
 *
 */
bool perimeter::restart_search() {
    if (initial_directions.empty()) {
        return false;
    }
    current_point_valid = false;
    dead_end_ = false;
    curr_dir = initial_directions.front();
    initial_directions.pop();
    move_point();
    return !dead_end_;
}

/*
 *
 */
void perimeter::move_point() {
    if (!current_point_valid) {
        cp = get_start_point();
        inside_cp = get_start_inside_point();
        current_point_valid = true;
    }
    if (curr_dir == direction_t::right) {
        if (outside({cp.row, cp.col+1}) || outside({cp.row+1, cp.col+1})) {
            if (inside({cp.row+1, cp.col+1}) ) {
                ++cp.col;
                ++inside_cp.col;
            } else {
                if (outside({cp.row+1, cp.col+1})) {
                    curr_dir = direction_t::down;
                    ++cp.row;
                    ++cp.col;
                    // inside_cp is the same
                } else {
                    dead_end_ = true;
                }
            }
        } else {
            if (outside({cp.row-1, cp.col+1})) {
                curr_dir = direction_t::up;
                --cp.row;
                ++cp.col;
                --inside_cp.row;
                ++inside_cp.col;
            } else if (outside({cp.row-1, cp.col})) {
                curr_dir = direction_t::up;
                --cp.row;
                --inside_cp.row;
                ++inside_cp.col;
            } else {
                dead_end_ = true;
            }
        }
    } else if (curr_dir == direction_t::up) {
        if (outside({cp.row-1, cp.col}) || outside({cp.row-1, cp.col+1})) {
            if (inside({cp.row-1, cp.col+1})) {
                --cp.row;
                --inside_cp.row;
            } else {
                if (outside({cp.row-1, cp.col+1})) {
                    curr_dir = direction_t::right;
                    --cp.row;
                    ++cp.col;
                    // inside_cp is the same
                } else {
                    dead_end_ = true;
                }
            }
        } else {
            if (outside({cp.row-1, cp.col-1})) {
                curr_dir = direction_t::left;
                --cp.row;
                --cp.col;
                --inside_cp.row;
                --inside_cp.col;
            } else if (outside({cp.row, cp.col-1})) {
                curr_dir = direction_t::left;
                --cp.col;
                --inside_cp.row;
                --inside_cp.col;
            } else {
                dead_end_ = true;
            }
        }
    } else if (curr_dir == direction_t::down) {
        if (outside({cp.row+1, cp.col}) || outside({cp.row+1, cp.col-1})) {
            if (inside({cp.row+1, cp.col-1})) {
                ++cp.row;
                ++inside_cp.row;
            } else {
                if (outside({cp.row+1, cp.col-1})) {
                    curr_dir = direction_t::left;
                    ++cp.row;
                    --cp.col;
                } else {
                    dead_end_ = true;
                }
            }
        } else {
            if(outside({cp.row+1, cp.col+1})) {
                curr_dir = direction_t::right;
                ++cp.row;
                ++cp.col;
                ++inside_cp.row;
                ++inside_cp.col;
            } else if(outside({cp.row, cp.col+1})) {
                curr_dir = direction_t::right;
                ++cp.col;
                ++inside_cp.row;
                ++inside_cp.col;
            } else {
                dead_end_ = true;
            }
        }
    } else {
        assert(curr_dir == direction_t::left);
        if (outside({cp.row, cp.col-1}) || outside({cp.row-1, cp.col-1})) {
            if (inside({cp.row-1, cp.col-1})) {
                --cp.col;
                --inside_cp.col;
            } else {
                if (outside({cp.row-1, cp.col-1})) {
                    curr_dir = direction_t::up;
                    --cp.col;
                    --cp.row;
                    // inside_cp is the same
                } else {
                    dead_end_ = true;
                }
            }
        } else {
            if (outside({cp.row+1, cp.col-1})) {
                curr_dir = direction_t::down;
                ++cp.row;
                --cp.col;
                ++inside_cp.row;
                --inside_cp.col;
            } else if (outside({cp.row+1, cp.col})) {
                curr_dir = direction_t::down;
                ++cp.row;
                ++inside_cp.row;
                --inside_cp.col;
            } else {
                dead_end_ = true;
            }
        }
    }
    if (visited.find(cp) == visited.end()) {
        visited.insert(cp);
        return;
    }
}

/*
 *
 */
unknown_area::unknown_area(
    const test_ns::sorted_entry_positions_t& border_points,
    const test_ns::sorted_entry_positions_t& outer_leak_points,
    const test_ns::sorted_entry_positions_t& flooded_points,
    const test_ns::sorted_entry_positions_t& all_perimeter_points)
    : border_points(border_points), outer_leak_points(outer_leak_points),
      flooded_points(flooded_points),
      all_perimeter_points(all_perimeter_points),
      border_itr(border_points.begin()),
      is_iterating_row(false), border_row{0},
      border_start_col(0), border_end_col{0},
      border_row_start_itr (border_itr),  border_row_end_itr (border_itr) {
}

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
            if (outer_leak_points.find(an_entry) != outer_leak_points.end()) {
                continue;
            }
            if (flooded_points.find(an_entry) != flooded_points.end()) {
                continue;
            }
            if (all_perimeter_points.find(an_entry) !=
                    all_perimeter_points.end()) {
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
void test_ns::matrix::find_leak_area(const entry_pos_t& initial_point,
        sorted_entry_positions_t& leak_points) const {
    std::queue<entry_pos_t> to_search;
    if (leak_points.find(initial_point) != leak_points.end() ) {
        return;
    }
    to_search.push(initial_point);
    leak_points.insert(initial_point);
    auto find_higher_neighbours = [this, &to_search, &leak_points](
            const entry_pos_t& curr_entry, const entry_pos_t& next_entry) {
        auto curr_entry_h = this->get_height(curr_entry);
        auto next_entry_h = this->get_height(next_entry);
        if (next_entry_h >= curr_entry_h) {
            if (leak_points.find(next_entry) == leak_points.end() ) {
                to_search.push(next_entry);
                leak_points.insert(next_entry);
            }
        }
    };
    while(!to_search.empty()) {
        auto an_entry = to_search.front();
        to_search.pop();
        call_neighbours(an_entry, find_higher_neighbours);
    }
}

int test_ns::matrix::find_surface_height(
        const entry_pos_t& initial_puddle_point,
        const sorted_entry_positions_t& outer_leak_points,
        const sorted_entry_positions_t& flooded_points) const {
    perimeter a_perimeter(initial_puddle_point, outer_leak_points,
            flooded_points);
    const auto perimeter_start_point = a_perimeter.get_start_point();
    int lowest_leak_point = get_height(a_perimeter.get_start_point());
    while (true) {
        entry_pos_t perimeter_next_point (a_perimeter.get_next_point());
        if (perimeter_next_point == perimeter_start_point ||
                a_perimeter.no_more_data()) {
            break;
        }
        auto leak_point_h = get_height(perimeter_next_point);
        if (leak_point_h < lowest_leak_point) {
            lowest_leak_point = leak_point_h;
        }
    }
    return lowest_leak_point;
}

/*
 *
 */
void test_ns::matrix::find_puddle_points(const entry_pos_t& initial_point,
        const sorted_entry_positions_t& outer_leaks,
        sorted_entry_positions_t& this_puddle_points,
        int puddle_h,
        sorted_entry_positions_t& all_flooded_points) const {
    std::queue<entry_pos_t> to_search;
    std::queue<perimeter> found_perimeters;

    auto find_puddle_point =
        [this, puddle_h, &to_search, &outer_leaks, &this_puddle_points,
         &all_flooded_points]
        (const entry_pos_t&, const entry_pos_t& point_to_consider) {
        if (this_puddle_points.find(point_to_consider) !=
                this_puddle_points.end()) {
            return;
        }
        if (outer_leaks.find(point_to_consider) != outer_leaks.end()) {
            return;
        }
        auto point_to_consider_h = this->get_height(point_to_consider);
        if (point_to_consider_h < puddle_h) {
            this_puddle_points.insert(point_to_consider);
            all_flooded_points.insert(point_to_consider);
            to_search.push(point_to_consider);
        }
    };

    to_search.push(initial_point);
    this_puddle_points.insert(initial_point);
    all_flooded_points.insert(initial_point);
    while(!to_search.empty()) {
        auto an_entry = to_search.front();
        to_search.pop();
        call_neighbours(an_entry, find_puddle_point);
    }
}

/*
 *
 */
void test_ns::matrix::find_island_borders(const entry_pos_t& initial_point,
        const sorted_entry_positions_t& outer_leaks,
        const sorted_entry_positions_t& this_puddle_points,
        int puddle_h,
        std::queue<sorted_entry_positions_t>& other_border_points,
        sorted_entry_positions_t& all_perimeter_points) const {
    std::queue<entry_pos_t> to_search;
    entry_pos_set_t traversed;

    auto find_island =
        [this, puddle_h, &to_search, &outer_leaks, &this_puddle_points,
         &all_perimeter_points, &other_border_points, &traversed]
        (const entry_pos_t&, const entry_pos_t& point_to_consider) {
        if (outer_leaks.find(point_to_consider) != outer_leaks.end()) {
            return;
        }
        if (all_perimeter_points.find(point_to_consider) !=
            all_perimeter_points.end()) {
            return;
        }
        if (traversed.find(point_to_consider) != traversed.end()) {
            return;
        }
        traversed.insert(point_to_consider);
        if (this_puddle_points.find(point_to_consider) !=
                this_puddle_points.end()) {
            to_search.push(point_to_consider);
            return;
        }
        auto point_to_consider_h = this->get_height(point_to_consider);
        if (point_to_consider_h >= puddle_h) {
            perimeter a_perimeter(point_to_consider, outer_leaks,
                    this_puddle_points);
            entry_pos_t perimeter_initial_inside_point =
                a_perimeter.get_start_inside_point();
            entry_pos_t perimeter_initial_point =
                a_perimeter.get_start_point();
            sorted_entry_positions_t perimeter_points;
            perimeter_points.insert(perimeter_initial_inside_point);
            all_perimeter_points.insert(perimeter_initial_inside_point);
            while (true) {
                auto ext_and_int_points = a_perimeter.get_ext_and_int_points();
                if (a_perimeter.no_more_data()) {
                    break;
                }
                if (ext_and_int_points.first == perimeter_initial_point) {
                    break;
                }
                perimeter_points.insert(ext_and_int_points.second);
                all_perimeter_points.insert(ext_and_int_points.second);
            }
            other_border_points.push(std::move(perimeter_points));
            to_search.push(point_to_consider);
        }
    };

    to_search.push(initial_point);
    while(!to_search.empty()) {
        auto an_entry = to_search.front();
        to_search.pop();
        call_neighbours(an_entry, find_island);
    }
}

bool test_ns::matrix::is_perimeter_connected(
        const sorted_entry_positions_t& border_points) const {
    if (border_points.empty() ) {
        return false;
    }
    if (border_points.size() == 1) {
        return true;
    }
    direction_t curr_dir = direction_t::right;
    entry_pos_t initial_position = *border_points.begin();
    entry_pos_t cp = initial_position;
    auto if_exists_update = [&border_points, &cp, &curr_dir]
        (const entry_pos_t& next_hop, direction_t next_hop_dir) -> bool {
        if (border_points.find(next_hop) != border_points.end()) {
            cp = next_hop;
            if (curr_dir != next_hop_dir)
                curr_dir = next_hop_dir;
            return true;
        }
        return false;
    };

    do {
        if (curr_dir == direction_t::right) {
            if (if_exists_update({cp.row, cp.col+1}, direction_t::right))
                continue;
            if (if_exists_update({cp.row+1, cp.col}, direction_t::down))
                continue;
            if (if_exists_update({cp.row+1, cp.col+1}, direction_t::down))
                continue;
            if (if_exists_update({cp.row-1, cp.col}, direction_t::up))
                continue;
            if (if_exists_update({cp.row-1, cp.col+1}, direction_t::up))
                continue;
            break;
        } else if (curr_dir == direction_t::left) {
            if (if_exists_update({cp.row, cp.col-1}, direction_t::left))
                continue;
            if (if_exists_update({cp.row+1, cp.col}, direction_t::down))
                continue;
            if (if_exists_update({cp.row+1, cp.col-1}, direction_t::down))
                continue;
            if (if_exists_update({cp.row-1, cp.col}, direction_t::up))
                continue;
            if (if_exists_update({cp.row-1, cp.col-1}, direction_t::up))
                continue;
            break;
        } else if (curr_dir == direction_t::up) {
            if (if_exists_update({cp.row-1, cp.col}, direction_t::up))
                continue;
            if (if_exists_update({cp.row, cp.col-1}, direction_t::left))
                continue;
            if (if_exists_update({cp.row-1, cp.col-1}, direction_t::left))
                continue;
            if (if_exists_update({cp.row, cp.col+1}, direction_t::right))
                continue;
            if (if_exists_update({cp.row-1, cp.col+1}, direction_t::right))
                continue;
            break;
        } else if (curr_dir == direction_t::down) {
            if (if_exists_update({cp.row+1, cp.col}, direction_t::down))
                continue;
            if (if_exists_update({cp.row, cp.col-1}, direction_t::left))
                continue;
            if (if_exists_update({cp.row+1, cp.col-1}, direction_t::left))
                continue;
            if (if_exists_update({cp.row, cp.col+1}, direction_t::right))
                continue;
            if (if_exists_update({cp.row+1, cp.col+1}, direction_t::right))
                continue;
            break;
        }
    } while (!(cp == initial_position));

    if (cp == initial_position) {
        return true;
    } else {
        return false;
    }
}


/*
 *
 */
void
test_ns::matrix::
find_puddles_impl(const sorted_entry_positions_t& border_points,
        std::queue<puddle>& found_puddles,
        std::queue<sorted_entry_positions_t>& other_border_points
        ) const {
    if (border_points.empty()) {
        return;
    }

    if (!is_perimeter_connected(border_points)) {
        return;
    }

    // look for all leaking points
    sorted_entry_positions_t outer_leak_points;
    sorted_entry_positions_t flooded_points;
    sorted_entry_positions_t all_perimeter_points;

    for (auto const & border_point : border_points) {
        find_leak_area(border_point, outer_leak_points);
    }

    // look for non leaking points
    unknown_area an_unknown_area(border_points,
            outer_leak_points, flooded_points, all_perimeter_points);

    while (true) {
        auto unknown_element = an_unknown_area.get_first_unknown_entry();
        if (!unknown_element.first) {
            break;
        }
        const entry_pos_t& an_unknown_entry = unknown_element.second;

        // find the height of surface for this puddle
        int puddle_h = find_surface_height(an_unknown_entry,
                outer_leak_points, flooded_points);

        if (get_height(an_unknown_entry) >= puddle_h) {
            // it is an island near a higher point and a puddle
            continue;
        }

        // find the puddle itself
        sorted_entry_positions_t this_puddle_points;
        find_puddle_points(an_unknown_entry, outer_leak_points,
                this_puddle_points, puddle_h, flooded_points);

        find_island_borders(an_unknown_entry, outer_leak_points,
                this_puddle_points, puddle_h, other_border_points,
                all_perimeter_points);

        puddle a_puddle{std::move(this_puddle_points)};
        found_puddles.push(std::move(a_puddle));
    }
}

/*
 *
 */
std::vector<test_ns::puddle>
test_ns::matrix::find_puddles() const{
    std::vector<puddle> empty_puddles;
    if (rows_.empty()) {
        return std::move(empty_puddles);
    }

    size_t start_row = 0, end_row = rows_.size();
    size_t start_col = 0, end_col = rows_[0].size();
    sorted_entry_positions_t initial_border_points;
    for (auto i = start_col; i != end_col; ++i) {
        initial_border_points.insert({0, i});
    }
    for (auto i = start_row+1; i < end_row-1; ++i) {
        initial_border_points.insert({i, 0});
        initial_border_points.insert({i, end_col-1});
    }
    for (auto i = start_col; i != end_col; ++i) {
        initial_border_points.insert({end_row-1, i});
    }
    std::queue<sorted_entry_positions_t> all_border_points;
    all_border_points.push(std::move(initial_border_points));
    std::vector<puddle> all_puddles;
    while (!all_border_points.empty()) {
        sorted_entry_positions_t curr_border_points(
                std::move(all_border_points.front()));
        all_border_points.pop();
        std::queue<puddle> found_puddles;
        std::queue<sorted_entry_positions_t> other_border_points;
        find_puddles_impl(curr_border_points, found_puddles,
                other_border_points);

        while (!found_puddles.empty()) {
            auto & found_puddle = found_puddles.front();
            all_puddles.push_back(std::move(found_puddle));
            found_puddles.pop();
        }

        while (!other_border_points.empty()) {
            auto& one_set_of_border_points = other_border_points.front();
            all_border_points.push(std::move(one_set_of_border_points));
            other_border_points.pop();
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
