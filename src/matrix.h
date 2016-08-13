#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <set>
#include <map>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <ostream>
#include <functional>

namespace test_ns {

/*
 *
 */
using row_t = std::vector<int>;
using rows_t = std::vector<row_t>;

/*
 *
 */
struct entry_pos_t {
    size_t row;
    size_t col;
    bool operator<(const entry_pos_t& rhs) const {
        return std::tie(row, col) < std::tie(rhs.row, rhs.col);
    }
    bool operator==(const entry_pos_t& rhs) const {
        return std::tie(row, col) == std::tie(rhs.row, rhs.col);
    }
    bool operator!=(const entry_pos_t& rhs) const {
        return !operator==(rhs);
    }
};

template <class T> struct my_hash_t;
template<> struct my_hash_t<entry_pos_t> {
    std::size_t operator()(entry_pos_t const& s) const {
        std::size_t h1 = std::hash<size_t>()(s.row);
        std::size_t h2 = std::hash<size_t>()(s.col);
        return h1 ^ (h2 << 1);
    }
};

using entry_pos_set_t = std::unordered_set<entry_pos_t, my_hash_t<entry_pos_t>>;
using entry_positions_t = entry_pos_set_t;
using sorted_entry_positions_t = std::set<entry_pos_t>;

/*
 *
 */
struct puddle {
    sorted_entry_positions_t entries_;
};
std::ostream& operator<<(std::ostream&, const puddle&);

/*
 *
 */
class matrix {
 public:
    matrix(rows_t);
    std::vector<puddle> find_puddles();

 private:
    rows_t rows_;
    size_t max_row;
    size_t max_col;

    using heights_t = std::multimap<int, entry_pos_t>;
    heights_t heights;

    struct found_area_t {
        int index;
        sorted_entry_positions_t perimeter_entries;
        sorted_entry_positions_t area_entries;
        sorted_entry_positions_t puddle_points;
        int puddle_h;
    };
    using found_areas_t = std::map<int, found_area_t>;
    found_areas_t found_areas;
    int found_areas_index;

    using visited_t = std::unordered_map<entry_pos_t, found_areas_t::iterator,
        my_hash_t<entry_pos_t>>;
    visited_t visited;

    void get_heights();
    int get_height(const entry_pos_t&) const;
    void call_neighbours(const entry_pos_t& curr_pos,
            std::function<void(const entry_pos_t&, const entry_pos_t&)>) const;
    void find_connected_area(const entry_pos_t& curr_pos, visited_t& visited,
            int h, sorted_entry_positions_t& area, std::set<int>& neighbours);
    int get_perimeter_h(const sorted_entry_positions_t& perimeter);
    void find_uncovered_entries(const sorted_entry_positions_t& perimeter,
            sorted_entry_positions_t& area, const visited_t& visited);
};


}  // namespace test_ns

#endif
