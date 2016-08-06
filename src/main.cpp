#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "matrix.h"

/*
 *
 */
int main() {
    try {
        test_ns::rows_t rows;

        size_t first_row_size = 0;
        bool first_row_set = false;
        for (std::string line; std::getline(std::cin, line); ) {
            std::cout << line << '\n';
            std::istringstream line_stream(line);
            int value;
            test_ns::row_t a_row;
            if (first_row_size > 0) {
                a_row.reserve(first_row_size);
            }
            while(line_stream >> value) {
                std::cout << value << '\n';
                a_row.push_back(value);
            }
            if (!first_row_set) {
                first_row_size = a_row.size();
                first_row_set = true;
            } else {
                if (first_row_size != a_row.size()) {
                    std::cerr << "row #" << rows.size() + 1 << ", wrong row size\n";
                    return 1;
                }
            }
            rows.push_back(std::move(a_row));
        }
        if (rows.empty() || first_row_size == 0) {
            return 0;
        }
        test_ns::matrix a_matrix(std::move(rows));
        auto puddles = a_matrix.find_puddles();
        for (auto const & p : puddles) {
            std::cout << p << '\n';
        }
    } catch (std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
}
