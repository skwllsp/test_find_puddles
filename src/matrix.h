#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <set>
#include <map>
#include <list>
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
using entry_positions_t = std::set<entry_pos_t>;
using sorted_entry_positions_t = std::set<entry_pos_t>;

/*
 *
 */
using entry_pos_ordered_t = std::set<entry_pos_t>;
struct puddle {
    explicit puddle(sorted_entry_positions_t&);
    sorted_entry_positions_t entries_;
};
std::ostream& operator<<(std::ostream&, const puddle&);

using list_puddles = std::list<puddle>;
using puddle_pos_t = std::unordered_map<entry_pos_t,
        list_puddles::iterator, my_hash_t<entry_pos_t>>;

/*
 *
 */
class matrix {
 public:
    matrix(rows_t);
    std::vector<puddle> find_puddles() const;

 private:
    rows_t rows_;
    int get_height(const entry_pos_t&) const;
    bool find_one_puddle(int entry_h, const entry_pos_t&,
            const entry_pos_set_t& leaks_pos, const puddle_pos_t&,
            entry_pos_set_t& searched_entries,
            entry_pos_set_t& below_level_entries) const;
    std::vector<puddle>
    find_puddles_impl(const sorted_entry_positions_t& border_points,
            std::vector<puddle>& found_puddles,
            std::vector<sorted_entry_positions_t>& to_investigate_border_points)
            const;
    void find_leak_area(const entry_pos_t& initial_point,
            sorted_entry_positions_t& leak_points) const;
    void find_puddle_area(const entry_pos_t& initial_point,
            sorted_entry_positions_t& possible_puddle_points,
            sorted_entry_positions_t& to_investigate_points,
            sorted_entry_positions_t& exact_puddle_points) const;
    void find_border_points(const entry_pos_t& initial_point,
            sorted_entry_positions_t& to_investigate_points,
            sorted_entry_positions_t& new_border_points) const;
};

}  // namespace test_ns

#endif
