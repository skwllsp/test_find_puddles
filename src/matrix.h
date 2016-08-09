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

using entry_pos_set_t =
        std::unordered_set<entry_pos_t, my_hash_t<entry_pos_t>>;

/*
 *
 */
using entry_pos_ordered_t = std::set<entry_pos_t>;
struct puddle {
    puddle(entry_pos_set_t&, int height);
    entry_pos_ordered_t entries_;
    int height_;
    void get_inner_and_outer_positions(entry_pos_set_t& inner_pos,
            entry_pos_set_t& outer_pos) const;
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
    using entry_positions_t = std::vector<entry_pos_t>;
    struct height_data_t {
        size_t positions;
        entry_positions_t some_entries;
    };
    using heights_t = std::map<int, height_data_t>;
    void get_heights(heights_t&) const;
    int get_height(const entry_pos_t&) const;
    bool find_one_puddle(int entry_h, const entry_pos_t&,
            const entry_pos_set_t& leaks_pos, const puddle_pos_t&,
            entry_pos_set_t& searched_entries,
            entry_pos_set_t& below_level_entries) const;
    void find_one_puddle_and_update(int entry_h, const entry_pos_t&,
            puddle_pos_t& puddle_pos, entry_pos_set_t& leaks_pos,
            list_puddles& puddles,
            size_t& yet_not_found_positions) const;
};

}  // namespace test_ns

#endif
