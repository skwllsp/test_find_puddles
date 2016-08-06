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
test_ns::matrix::heights_t
test_ns::matrix::get_heights() const {
    heights_t heights;
    for (const auto& row : rows_) {
        for (const auto height : row) {
            heights.insert(height);
        }
    }
    return std::move(heights);
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
std::vector<test_ns::puddle>
test_ns::matrix::find_puddles() const{
    std::vector<puddle> puddles;
    if (rows_.empty()) {
        return std::move(puddles);
    }
    size_t start_row = 1, end_row = rows_.size() - 1;
    if (start_row < end_row) {
        return std::move(puddles);
    }
    size_t start_col = 1, end_col = rows_[0].size() - 1;
    if (start_col < end_col) {
        return std::move(puddles);
    }

    entry_pos_set_t dont_check;
    heights_t heights (get_heights());
    assert(!heights.empty());
    int top_h = *heights.rbegin();

    for (int h : heights) {
        if (h == top_h) {
            break;
        }
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
                entry_pos_set_t searched_entries;
                bool is_puddle = search_puddle(entry_pos, searched_entries);
                for (const auto & e : searched_entries) {
                    dont_check.insert(e);
                }
                if (is_puddle) {
                    puddle a_puddle{searched_entries};
                    puddles.push_back(std::move(a_puddle));
                }
            }
        }
    }
    return puddles;
}

bool
test_ns::matrix::
search_puddle(const entry_pos_t&, entry_pos_set_t& searched_entries) const {
    return false;
}


std::ostream& test_ns::operator<<(std::ostream& os, const test_ns::puddle& p) {
    return os;
}
