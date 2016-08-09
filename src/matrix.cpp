#include <algorithm>
#include <tuple>
#include <cassert>
#include <iostream>

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
void
test_ns::matrix::get_heights(test_ns::matrix::heights_t& heights) const {
    size_t max_per_level = rows_.size() * rows_[0].size();
    size_t cached_per_level = std::max(5U, (unsigned)(max_per_level * 0.01));

    size_t curr_row = 0, curr_col = 0;
    for (const auto& row : rows_) {
        curr_col = 0;
        for (const auto height : row) {
            auto res = heights.insert(std::make_pair(height,height_data_t()));
            height_data_t & d = res.first->second;
            if (res.second) {
                d.positions = 1;
                d.some_entries.push_back({curr_row, curr_col});
            } else {
                ++d.positions;
                if (d.positions <= cached_per_level) {
                    d.some_entries.push_back({curr_row, curr_col});
                } else {
                    d.some_entries.clear();
                }
            }
            ++curr_col;
        }
        ++curr_row;
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
                a_puddle.get_inner_and_outer_positions(puddle_inner_positions,
                        puddle_outer_positions);
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

/*
 *
 */
void
test_ns::matrix::
find_one_puddle_and_update(int entry_h, const entry_pos_t& entry_pos,
        puddle_pos_t& puddle_pos, entry_pos_set_t& leaks_pos,
        std::list<puddle>& puddles,
        size_t& yet_not_found_positions) const {
    entry_pos_set_t searched_entries;
    entry_pos_set_t below_level_entries;
    bool is_puddle = find_one_puddle(entry_h, entry_pos, leaks_pos,
            puddle_pos, searched_entries, below_level_entries);
    yet_not_found_positions -= searched_entries.size();
    if (is_puddle) {
        if (!below_level_entries.empty()) {
            for (auto const & below_entry : below_level_entries) {
                for (auto i = puddles.begin(); i != puddles.end(); ++i) {
                    const auto & puddle = *i;
                    auto & entries = puddle.entries_;
                    if (entries.find(below_entry) != entries.end()) {
                        puddles.erase(i);
                        break;
                    }
                }
            }
        }
        puddle a_puddle{searched_entries, entry_h};
        auto itr = puddles.insert(puddles.end(), std::move(a_puddle));
        for (const auto & e : searched_entries) {
            auto res = puddle_pos.insert(std::make_pair(e,itr));
            if (!res.second) {
                puddle_pos_t::iterator pitr = res.first;
                pitr->second = itr;
            }
        }
    } else {
        for (const auto & e : searched_entries) {
            leaks_pos.insert(e);
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
    if (rows_.size() < 3) {
        return std::move(empty_puddles);
    }
    if (rows_[0].size() < 3) {
        return std::move(empty_puddles);
    }

    std::list<puddle> puddles;
    size_t start_row = 0, end_row = rows_.size();
    size_t start_col = 0, end_col = rows_[0].size();

    puddle_pos_t puddle_pos;
    entry_pos_set_t leaks_pos;

    heights_t heights;
    get_heights(heights);
    assert(!heights.empty());

    int top_h = heights.rbegin()->first;

    for (auto & h_data_pair : heights) {
        auto h = h_data_pair.first;
        if (h == top_h) {
            break;
        }
        height_data_t & h_data = h_data_pair.second;
        size_t yet_not_found_positions = h_data.positions;
        if (h_data.positions != h_data.some_entries.size()) {
            for (size_t r = start_row; r < end_row; ++r) {
                for (size_t c = start_col; c < end_col; ++c) {
                    entry_pos_t entry_pos{r,c};
                    if (puddle_pos.find(entry_pos) != puddle_pos.end()) {
                        continue;
                    }
                    if (leaks_pos.find(entry_pos) != leaks_pos.end()) {
                        continue;
                    }
                    int entry_h = get_height(entry_pos);
                    if (entry_h != h) {
                        continue;
                    }
                    find_one_puddle_and_update(entry_h, entry_pos,
                            puddle_pos, leaks_pos, puddles,
                            yet_not_found_positions);
                    if (yet_not_found_positions == 0) {
                        break;
                    }
                }
                if (yet_not_found_positions == 0) {
                    break;
                }
            }
        } else {
            // here I know exactly places with this height
            for (auto & entry_pos : h_data.some_entries) {
                int entry_h = h;
                if (puddle_pos.find(entry_pos) != puddle_pos.end()) {
                    continue;
                }
                if (leaks_pos.find(entry_pos) != leaks_pos.end()) {
                    continue;
                }
                find_one_puddle_and_update(entry_h, entry_pos,
                        puddle_pos, leaks_pos, puddles,
                        yet_not_found_positions);
                if (yet_not_found_positions == 0) {
                    break;
                }
            }
        }
    }
    return std::vector<test_ns::puddle>(puddles.begin(), puddles.end());
}

/*
 *
 */
test_ns::puddle::puddle(entry_pos_set_t& entry_pos_set, int height)
 : entries_(entry_pos_set.begin(), entry_pos_set.end()), height_(height) {
}

/*
 *
 */
void
test_ns::puddle::
get_inner_and_outer_positions(entry_pos_set_t& inner_pos,
        entry_pos_set_t& outer_pos) const {
    size_t first_row = entries_.begin()->row;
    size_t last_row = entries_.rbegin()->row;
    for (auto i = entries_.begin(); i != entries_.end(); ++i) {
        auto & e = *i;
        if (e.row == first_row || e.row == last_row) {
            outer_pos.insert(e);
            continue;
        }
        if (std::prev(i)->row != e.row) {
            outer_pos.insert(*std::prev(i));
            outer_pos.insert(e);
            continue;
        }
        inner_pos.insert(e);
    }
}


/*
 *
 */
std::ostream& test_ns::operator<<(std::ostream& os, const test_ns::puddle& p) {
    os << "height: " << p.height_ << ", points: [";
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
