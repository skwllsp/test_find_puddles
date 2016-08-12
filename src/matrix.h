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
    void get_heights();
    int get_height(const entry_pos_t&) const;

    void find_puddles_impl(const sorted_entry_positions_t& border_points,
            std::queue<puddle>& found_puddles,
            std::queue<sorted_entry_positions_t>& other_border_points)
            const;
    void find_leak_area(const entry_pos_t& initial_point,
            sorted_entry_positions_t& leak_points) const;
    int find_surface_height(
            const entry_pos_t& initial_point,
            const sorted_entry_positions_t& outer_leak_points,
            const sorted_entry_positions_t& flooded_points) const;
    void find_puddle_points(const entry_pos_t& initial_point,
            const sorted_entry_positions_t& outer_leak_points,
            sorted_entry_positions_t& this_puddle_points,
            int puddle_h,
            sorted_entry_positions_t& all_flooded_points) const;
    void find_island_borders(const entry_pos_t& initial_point,
            const sorted_entry_positions_t& outer_leak_points,
            const sorted_entry_positions_t& this_puddle_points,
            int puddle_h,
            std::queue<sorted_entry_positions_t>& other_border_points,
            sorted_entry_positions_t& all_perimeter_points) const;
    void call_neighbours(const entry_pos_t& curr_pos,
            std::function<void(const entry_pos_t&, const entry_pos_t&)>) const;
    bool is_perimeter_connected(
            const sorted_entry_positions_t& border_points) const;
    void find_connected_area(const entry_pos_t& curr_pos, int h,
            sorted_entry_positions_t& area);
};


}  // namespace test_ns

#endif
