#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <set>
#include <unordered_set>
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
struct puddle {
    entry_pos_set_t entries_;
};
std::ostream& operator<<(std::ostream&, const puddle&);

/*
 *
 */
class matrix {
 public:
    matrix(rows_t);
    std::vector<puddle> find_puddles() const;

 private:
    rows_t rows_;
    using heights_t = std::set<int>;
    heights_t get_heights() const;
    int get_height(const entry_pos_t&) const;
    bool search_puddle(const entry_pos_t&,
            entry_pos_set_t& searched_entries) const;
};

}  // namespace test_ns

#endif
