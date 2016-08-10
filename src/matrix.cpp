#include <algorithm>
#include <tuple>
#include <cassert>
#include <iostream>
#include <queue>
#include <functional>

#include "matrix.h"

#include <stddef.h>
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
/*
 *
 */
int test_ns::matrix::find_puddle_height(const entry_pos_t& initial_point,
        const sorted_entry_positions_t& outer_leak_points) const {
    std::queue<entry_pos_t> to_search;
    entry_positions_t traversed_positions;
    to_search.push(initial_point);
    traversed_positions.insert(initial_point);
    int lowest_leak_point = -1;
    auto find_lowest_leak_point =
            [this, &to_search, &outer_leak_points,
             &lowest_leak_point, &traversed_positions]
            (const entry_pos_t&, const entry_pos_t& next_entry) {
        if (outer_leak_points.find(next_entry) == outer_leak_points.end() ) {
            if (traversed_positions.find(next_entry) ==
                    traversed_positions.end()) {
                to_search.push(next_entry);
            }
        } else{
            auto leak_point_h = this->get_height(next_entry);
            if (lowest_leak_point == -1 || leak_point_h < lowest_leak_point) {
                lowest_leak_point = leak_point_h;
            }
        }
        traversed_positions.insert(next_entry);
    };
    while(!to_search.empty()) {
        auto an_entry = to_search.front();
        to_search.pop();
        call_neighbours(an_entry, find_lowest_leak_point);
    }
    return lowest_leak_point;
}

void test_ns::matrix::find_puddle_with_islands(const entry_pos_t& initial_point,
        const sorted_entry_positions_t& outer_leak_points,
        sorted_entry_positions_t& possible_puddle_points,
        sorted_entry_positions_t& puddle_with_islands_points) const {
    std::queue<entry_pos_t> to_search;
    to_search.push(initial_point);

    puddle_with_islands_points.insert(initial_point);
    possible_puddle_points.erase(initial_point);
    auto find_puddle_point =
        [this, &possible_puddle_points, &to_search,
         &puddle_with_islands_points, &outer_leak_points]
        (const entry_pos_t&, const entry_pos_t& next_entry) {
        if (outer_leak_points.find(next_entry) != outer_leak_points.end()) {
            return;
        }
        if (puddle_with_islands_points.find(next_entry) !=
                puddle_with_islands_points.end()) {
            return;
        }
        puddle_with_islands_points.insert(next_entry);
        to_search.push(next_entry);
        possible_puddle_points.erase(next_entry);
    };
    while(!to_search.empty()) {
        auto an_entry = to_search.front();
        to_search.pop();
        call_neighbours(an_entry, find_puddle_point);
    }
}


/*
 *
 */
void test_ns::matrix::find_puddle_area(const entry_pos_t& initial_point,
        const sorted_entry_positions_t&,
        sorted_entry_positions_t& possible_puddle_points,
        sorted_entry_positions_t& other_points,
        sorted_entry_positions_t& this_puddle_points,
        int puddle_h) const {
    std::queue<entry_pos_t> to_search;
    to_search.push(initial_point);

    this_puddle_points.insert(initial_point);
    possible_puddle_points.erase(initial_point);
    auto find_puddle_point =
        [this, puddle_h, &possible_puddle_points, &to_search,
         &this_puddle_points, &other_points]
        (const entry_pos_t&, const entry_pos_t& next_entry) {
        if (possible_puddle_points.find(next_entry) ==
                possible_puddle_points.end()) {
            return;
        }
        if (this_puddle_points.find(next_entry) != this_puddle_points.end()) {
            return;
        }
        if (other_points.find(next_entry) != other_points.end()) {
            return;
        }
        auto next_point_h = this->get_height(next_entry);
        if (next_point_h < puddle_h) {
            this_puddle_points.insert(next_entry);
            to_search.push(next_entry);
        } else {
            other_points.insert(next_entry);
        }
        possible_puddle_points.erase(next_entry);
    };
    while(!to_search.empty()) {
        auto an_entry = to_search.front();
        to_search.pop();
        call_neighbours(an_entry, find_puddle_point);
    }
}

/*
 *
 */
void test_ns::matrix::find_border_points(const entry_pos_t& initial_point,
        sorted_entry_positions_t& other_points,
        sorted_entry_positions_t& this_puddle_points,
        sorted_entry_positions_t& island_border_points,
        sorted_entry_positions_t& possible_puddle_points,
        const sorted_entry_positions_t& outer_leak_points) const {
    std::queue<entry_pos_t> to_search;
    to_search.push(initial_point);
    entry_positions_t traversed_positions;

    island_border_points.insert(initial_point);
    traversed_positions.insert(initial_point);
    other_points.erase(initial_point);
    possible_puddle_points.erase(initial_point);

    auto find_island_border_point =
            [&other_points, &this_puddle_points,
             &island_border_points, &to_search, &traversed_positions,
             &possible_puddle_points, &outer_leak_points]
            (const entry_pos_t& curr_entry, const entry_pos_t& next_entry)  {
        if (outer_leak_points.find(next_entry) != outer_leak_points.end()) {
            return;
        }
        if (this_puddle_points.find(next_entry) != this_puddle_points.end()) {
            island_border_points.insert(curr_entry);
            other_points.erase(curr_entry);
            possible_puddle_points.erase(curr_entry);
            return;
        }
        if (traversed_positions.find(next_entry) != traversed_positions.end()) {
            return;
        }
        to_search.push(next_entry);
        traversed_positions.insert(curr_entry);
        other_points.erase(curr_entry);
        possible_puddle_points.erase(curr_entry);
    };

    while(!to_search.empty()) {
        auto an_entry = to_search.front();
        to_search.pop();
        call_neighbours(an_entry, find_island_border_point);
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

    // look for all leaking points
    sorted_entry_positions_t outer_leak_points;
    for (auto const & border_point : border_points) {
        find_leak_area(border_point, outer_leak_points);
    }
    auto all_leak_points_end = outer_leak_points.end();

    // look for non leaking points
    auto border_itr = border_points.begin();
    sorted_entry_positions_t possible_puddle_points;
    while (border_itr != border_points.end()) {
        auto border_row_start_itr = border_itr;
        auto border_row_end_itr =  border_itr;
        size_t border_row = border_row_start_itr->row;
        while (border_row_end_itr != border_points.end() &&
               border_row == border_row_end_itr->row) {
            ++border_row_end_itr;
        }
        size_t border_start_col = border_row_start_itr->col;
        size_t border_end_col = std::prev(border_row_end_itr)->col;
        while (border_start_col <= border_end_col) {
            entry_pos_t an_entry = {border_row, border_start_col};
            ++border_start_col;
            if (outer_leak_points.find(an_entry) != all_leak_points_end) {
                continue;
            }
            possible_puddle_points.insert(an_entry);
        }
        border_itr = border_row_end_itr;
    }

    // separate puddle points belonging to different puddles
    std::queue<sorted_entry_positions_t> separate_puddles;
    while (!possible_puddle_points.empty()) {
        const entry_pos_t an_entry = *possible_puddle_points.begin();
        sorted_entry_positions_t puddle_with_islands_points;
        find_puddle_with_islands(an_entry, outer_leak_points,
                possible_puddle_points, puddle_with_islands_points);
        separate_puddles.push(std::move(puddle_with_islands_points));
    }

    // look for pudlles and islands among non leaking points
    while (!separate_puddles.empty()) {
        auto possible_puddle_points (std::move(separate_puddles.front()));
        separate_puddles.pop();
        while (!possible_puddle_points.empty()) {
            const entry_pos_t an_entry = *possible_puddle_points.begin();
            sorted_entry_positions_t this_puddle_points;
            sorted_entry_positions_t other_points;

            // find the height of surface for this puddle
            int puddle_h = find_puddle_height(an_entry, outer_leak_points);

            // find the puddle itself
            find_puddle_area(an_entry, outer_leak_points,
                    possible_puddle_points, other_points, this_puddle_points,
                    puddle_h);

            // find border points for islands inside this puddle
            while (!other_points.empty()) {
                const entry_pos_t & an_entry = *other_points.begin();
                sorted_entry_positions_t new_border_points;
                find_border_points(an_entry, other_points, this_puddle_points,
                        new_border_points, possible_puddle_points,
                        outer_leak_points);
                other_border_points.push(std::move(new_border_points));
            }
            puddle a_puddle(this_puddle_points);
            found_puddles.push(std::move(a_puddle));
        }
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
test_ns::puddle::puddle(sorted_entry_positions_t& entry_pos_set)
 : entries_(entry_pos_set.begin(), entry_pos_set.end()) {
}



/*
 *
 */
std::ostream& test_ns::operator<<(std::ostream& os, const test_ns::puddle& p) {
    os << ", points: [";
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
