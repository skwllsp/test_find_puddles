#include <algorithm>
#include <tuple>
#include <cassert>

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
                if (d.positions < 3) {
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
        entry_pos_set_t& searched_entries,
        entry_pos_set_t& below_level_entries) const {
    size_t max_row = rows_.size() - 1;
    size_t max_col = rows_[0].size() - 1;
    std::set<entry_pos_t> to_search_positions;
    to_search_positions.insert(initial_pos);
    searched_entries.clear();
    bool edge_found = false;
    auto check_one_position =
            [entry_h, &to_search_positions, &searched_entries,
             this, &below_level_entries]
            (const entry_pos_t& next_pos) {
        int next_pos_height = this->get_height(next_pos);
        if (next_pos_height <= entry_h) {
            if (searched_entries.find(next_pos) == searched_entries.end()) {
                to_search_positions.insert(next_pos);
                if (next_pos_height < entry_h) {
                    below_level_entries.insert(next_pos);
                }
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
        entry_pos_set_t& dont_check,
        std::list<puddle>& puddles,
        size_t& yet_not_found_positions) const {
    entry_pos_set_t searched_entries;
    entry_pos_set_t below_level_entries;
    bool is_puddle = find_one_puddle(entry_h, entry_pos,
            searched_entries, below_level_entries);
    yet_not_found_positions -= searched_entries.size();
    for (const auto & e : searched_entries) {
        dont_check.insert(e);
    }
    if (is_puddle && !below_level_entries.empty()) {
        for (auto const & below_entry : below_level_entries) {
            for (auto i = puddles.rbegin(); i != puddles.rend(); ++i) {
                const auto & puddle = *i;
                if (puddle.height_ + 1 < entry_h) {
                    break;
                }
                auto & entries = puddle.entries_;
                if (entries.find(below_entry) != entries.end()) {
                    puddles.erase(std::prev (i.base()));
                    break;
                }
            }
        }
    }
    if (is_puddle) {
        puddle a_puddle{searched_entries, entry_h};
        puddles.push_back(std::move(a_puddle));
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
    size_t start_row = 1, end_row = rows_.size() - 1;
    size_t start_col = 1, end_col = rows_[0].size() - 1;

    entry_pos_set_t dont_check;

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
            for (size_t c = start_col; c < end_col; ++c) {
                for (size_t r = start_row; r < end_row; ++r) {
                    entry_pos_t entry_pos{r,c};
                    if (dont_check.find(entry_pos) != dont_check.end()) {
                        continue;
                    }
                    int entry_h = get_height(entry_pos);
                    if (entry_h != h) {
                        continue;
                    }
                    find_one_puddle_and_update(entry_h, entry_pos,
                            dont_check, puddles, yet_not_found_positions);
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
                if (dont_check.find(entry_pos) != dont_check.end()) {
                    continue;
                }
                int entry_h = h;
                find_one_puddle_and_update(entry_h, entry_pos,
                        dont_check, puddles, yet_not_found_positions);
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
std::ostream& test_ns::operator<<(std::ostream& os, const test_ns::puddle& p) {
    return os;
}
