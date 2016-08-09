#include <algorithm>
#include <tuple>
#include <cassert>
#include <iostream>
#include <queue>
#include <functional>

#include "matrix.h"

/*
 *
 */
test_ns::matrix::matrix(rows_t rows)
: rows_(std::move(rows)) {
}


/*
 *
 */
int test_ns::matrix::get_height(const entry_pos_t& p) const {
    return rows_[p.row][p.col];
}
/*
bool find_one_puddle(int entry_h, const entry_pos_t&,
        const entry_pos_set_t& leaks_pos, const puddle_pos_t&,
        entry_pos_set_t& searched_entries,
        entry_pos_set_t& below_level_entries) const;
*/
/*
 *
 */
/*
bool
test_ns::matrix::
find_one_puddle(const int entry_h, const entry_pos_t& initial_pos,
        const entry_pos_set_t& leaks_pos,
        const puddle_pos_t& puddle_pos,
        entry_pos_set_t& searched_entries,
        entry_pos_set_t& below_level_entries) const {
    size_t max_row = rows_.size() - 1;
    size_t max_col = rows_[0].size() - 1;
    std::set<entry_pos_t> to_search_positions;
    to_search_positions.insert(initial_pos);
    searched_entries.clear();
    bool edge_found = false;
    auto check_one_position =
            [entry_h, &leaks_pos, &puddle_pos, &to_search_positions,
             &searched_entries,
             this, &below_level_entries, &edge_found]
            (const entry_pos_t& next_pos) {
        int next_pos_height = this->get_height(next_pos);
        if (next_pos_height < entry_h) {
            if (leaks_pos.find(next_pos) != leaks_pos.end()) {
                edge_found = true;
                return;
            }
            puddle_pos_t::const_iterator puddle_itr =
                    puddle_pos.find(next_pos);
            if (puddle_itr != puddle_pos.end()) {
                const puddle& a_puddle = *(puddle_itr->second);
                entry_pos_set_t puddle_inner_positions, puddle_outer_positions;
                //a_puddle.get_inner_and_outer_positions(puddle_inner_positions,
                //        puddle_outer_positions);
                searched_entries.insert(puddle_inner_positions.begin(),
                    puddle_inner_positions.end());
                below_level_entries.insert(*puddle_outer_positions.begin());
                for (auto i = puddle_outer_positions.begin();
                        i != puddle_outer_positions.end(); ++i) {
                    if (searched_entries.find(*i) == searched_entries.end()) {
                        to_search_positions.insert(*i);
                    }
                }
            }
        }
        if (next_pos_height <= entry_h) {
            if (searched_entries.find(next_pos) == searched_entries.end()) {
                to_search_positions.insert(next_pos);
            }
        }
    };
    while (!to_search_positions.empty()) {
        entry_pos_t curr_pos = *to_search_positions.begin();
        to_search_positions.erase(to_search_positions.begin());
        searched_entries.insert(curr_pos);
        if (curr_pos.row == 0 && curr_pos.col == 0) {
            edge_found = true;
            check_one_position({0,1});
            check_one_position({1,0});
        } else if (curr_pos.row == 0 && curr_pos.col == max_col) {
            edge_found = true;
            check_one_position({0,curr_pos.col-1});
            check_one_position({1,curr_pos.col});
        } else if (curr_pos.row == max_row && curr_pos.col == max_col) {
            edge_found = true;
            check_one_position({curr_pos.row,curr_pos.col-1});
            check_one_position({curr_pos.row-1,curr_pos.col});
        } else if (curr_pos.row == max_row && curr_pos.col == 0) {
            edge_found = true;
            check_one_position({curr_pos.row-1,0});
            check_one_position({curr_pos.row,1});
        } else if (curr_pos.row == 0) {
            edge_found = true;
            check_one_position({0,curr_pos.col-1});
            check_one_position({0,curr_pos.col+1});
            check_one_position({1,curr_pos.col});
        } else if (curr_pos.row == max_row) {
            edge_found = true;
            check_one_position({curr_pos.row,curr_pos.col-1});
            check_one_position({curr_pos.row,curr_pos.col+1});
            check_one_position({curr_pos.row-1,curr_pos.col});
        } else if (curr_pos.col == 0) {
            edge_found = true;
            check_one_position({curr_pos.row-1,0});
            check_one_position({curr_pos.row+1,0});
            check_one_position({curr_pos.row,1});
        } else if (curr_pos.col == max_col) {
            edge_found = true;
            check_one_position({curr_pos.row-1,curr_pos.col});
            check_one_position({curr_pos.row+1,curr_pos.col});
            check_one_position({curr_pos.row,curr_pos.col-1});
        } else {
            check_one_position({curr_pos.row-1,curr_pos.col});
            check_one_position({curr_pos.row,curr_pos.col+1});
            check_one_position({curr_pos.row+1,curr_pos.col});
            check_one_position({curr_pos.row,curr_pos.col-1});
        }
    }
    return !edge_found;
}

*/

void test_ns::matrix::call_neighbours(const entry_pos_t& curr_pos,
        std::function<void(const entry_pos_t&,const entry_pos_t&)>
            check_one_position) const {
    size_t max_row = rows_.size() - 1;
    size_t max_col = rows_[0].size() - 1;
    if (curr_pos.row == 0 && curr_pos.col == 0) {
        check_one_position(curr_pos,{0,1});
        check_one_position(curr_pos,{1,0});
    } else if (curr_pos.row == 0 && curr_pos.col == max_col) {
        check_one_position(curr_pos,{0,curr_pos.col-1});
        check_one_position(curr_pos,{1,curr_pos.col});
    } else if (curr_pos.row == max_row && curr_pos.col == max_col) {
        check_one_position(curr_pos,{curr_pos.row,curr_pos.col-1});
        check_one_position(curr_pos,{curr_pos.row-1,curr_pos.col});
    } else if (curr_pos.row == max_row && curr_pos.col == 0) {
        check_one_position(curr_pos,{curr_pos.row-1,0});
        check_one_position(curr_pos,{curr_pos.row,1});
    } else if (curr_pos.row == 0) {
        check_one_position(curr_pos,{0,curr_pos.col-1});
        check_one_position(curr_pos,{0,curr_pos.col+1});
        check_one_position(curr_pos,{1,curr_pos.col});
    } else if (curr_pos.row == max_row) {curr_pos,
        check_one_position(curr_pos,{curr_pos.row,curr_pos.col-1});
        check_one_position(curr_pos,{curr_pos.row,curr_pos.col+1});
        check_one_position(curr_pos,{curr_pos.row-1,curr_pos.col});
    } else if (curr_pos.col == 0) {
        check_one_position(curr_pos,{curr_pos.row-1,0});
        check_one_position(curr_pos,{curr_pos.row+1,0});
        check_one_position(curr_pos,{curr_pos.row,1});
    } else if (curr_pos.col == max_col) {
        check_one_position(curr_pos,{curr_pos.row-1,curr_pos.col});
        check_one_position(curr_pos,{curr_pos.row+1,curr_pos.col});
        check_one_position(curr_pos,{curr_pos.row,curr_pos.col-1});
    } else {
        check_one_position(curr_pos,{curr_pos.row-1,curr_pos.col});
        check_one_position(curr_pos,{curr_pos.row,curr_pos.col+1});
        check_one_position(curr_pos,{curr_pos.row+1,curr_pos.col});
        check_one_position(curr_pos,{curr_pos.row,curr_pos.col-1});
    }
}

/*
 *
 */
void test_ns::matrix::find_leak_area(const entry_pos_t& initial_point,
        sorted_entry_positions_t& leak_points) const {
    std::queue<entry_pos_t> to_search;
    if (leak_points.find(initial_point) == leak_points.end() ) {
        return;
    }
    to_search.push(initial_point);
    leak_points.insert(initial_point);
    auto find_higher_neighbours = [this, &to_search, &leak_points](
            const entry_pos_t& curr_entry, const entry_pos_t& next_entry) {
        if (this->get_height(next_entry) >= this->get_height(curr_entry) ) {
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
void test_ns::matrix::find_puddle_area(const entry_pos_t& initial_point,
        sorted_entry_positions_t& possible_puddle_points,
        sorted_entry_positions_t& other_points,
        sorted_entry_positions_t& exact_puddle_points) const {
    std::queue<entry_pos_t> to_search;

}

/*
 *
 */
void test_ns::matrix::find_border_points(const entry_pos_t& initial_point,
        sorted_entry_positions_t& to_investigate_points,
        sorted_entry_positions_t& new_border_points) const {

}

/*
 *
 */
std::vector<test_ns::puddle>
test_ns::matrix::
find_puddles_impl(const sorted_entry_positions_t& border_points,
        std::vector<puddle>& found_puddles,
        std::vector<sorted_entry_positions_t>& to_investigate_border_points
        ) const {
    found_puddles.clear();
    to_investigate_border_points.clear();
    if (border_points.empty()) {
        return std::move(found_puddles);
    }
    sorted_entry_positions_t all_leak_points;
    for (auto const & border_point : border_points) {
        find_leak_area(border_point, all_leak_points);
    }
    auto all_leak_points_end = all_leak_points.end();
    auto border_itr = border_points.begin();
    sorted_entry_positions_t possible_puddle_points;
    while (border_itr != border_points.end()) {
        auto border_row_start_itr = border_itr;
        size_t border_row = border_row_start_itr->row;
        auto border_row_end_itr =  border_itr;
        while (border_row == border_row_end_itr->row &&
                border_row_end_itr != border_points.end()) {
            ++border_row_end_itr;
        }
        size_t border_start_col = border_row_start_itr->col;
        size_t border_end_col = std::prev(border_row_end_itr)->col;
        while (border_start_col <= border_end_col) {
            entry_pos_t an_entry = {border_row, border_start_col};
            if (all_leak_points.find(an_entry) != all_leak_points_end) {
                continue;
            }
            possible_puddle_points.insert(an_entry);
        }
        border_itr = border_row_end_itr;
    }
    sorted_entry_positions_t other_points;
    while (!possible_puddle_points.empty()) {
        const entry_pos_t an_entry = *possible_puddle_points.begin();
        possible_puddle_points.erase(possible_puddle_points.begin());
        sorted_entry_positions_t this_puddle_points;
        find_puddle_area(an_entry, possible_puddle_points,
                other_points, this_puddle_points);
        puddle a_puddle(this_puddle_points);
        found_puddles.push_back(std::move(a_puddle));
    }

    while (!to_investigate_points.empty()) {
        const entry_pos_t & an_entry = *possible_puddle_points.begin();
        sorted_entry_positions_t new_border_points;
        find_border_points(an_entry, to_investigate_points, new_border_points);
        to_investigate_border_points.push_back(std::move(new_border_points));
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

    std::list<puddle> puddles;

    size_t start_row = 0, end_row = rows_.size();
    size_t start_col = 0, end_col = rows_[0].size();
    sorted_entry_positions_t border_points;
    for (auto i = start_col; i != end_col; ++i) {
        border_points.insert({0, i});
    }
    for (auto i = start_row+1; i != end_row-1; ++i) {
        border_points.insert({i, 0});
        border_points.insert({i, end_col-1});
    }
    for (auto i = start_col; i != end_col; ++i) {
        border_points.insert({end_row-1, i});
    }
    std::queue<sorted_entry_positions_t> all_border_points;
    all_border_points.push(std::move(border_points));
    std::vector<puddle> all_puddles;
    while (!all_border_points.empty()) {
        const auto & curr_border_points = all_border_points.front();
        std::vector<puddle> found_puddles;
        std::vector<sorted_entry_positions_t> to_investigate_border_points;
        find_puddles_impl(curr_border_points, found_puddles,
                to_investigate_border_points);

        while (!found_puddles.empty()) {
            auto & found_puddle = *found_puddles.rbegin();
            all_puddles.push_back(std::move(found_puddle));
            found_puddles.pop_back();
        }

        while (!to_investigate_border_points.empty()) {
            auto& one_set_of_border_points =
                    *to_investigate_border_points.rbegin();
            all_border_points.push(std::move(one_set_of_border_points));
            to_investigate_border_points.pop_back();
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
