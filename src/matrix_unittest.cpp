#include "gtest/gtest.h"
#include "matrix.h"

TEST(Matrix, Zero1) {
    test_ns::matrix a_matrix(test_ns::rows_t{});
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, One1) {
    test_ns::matrix a_matrix(test_ns::rows_t{{0}});
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, One2) {
    test_ns::matrix a_matrix(test_ns::rows_t{{1}});
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Two1) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {0,0},
        {0,0}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Two2) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {0,0},
        {1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Two3) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,1},
        {1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Two4) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {0,1},
        {0,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Two5) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {3,4},
        {1,7}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Three1) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {0,0,0},
        {0,0,0},
        {0,0,0}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Three2) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,1,1},
        {1,0,1},
        {1,1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
}

TEST(Matrix, Three3) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,1,0},
        {1,0,1},
        {1,1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
}
TEST(Matrix, Three4) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,1,1},
        {1,0,0},
        {1,1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}
TEST(Matrix, Three5) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,1,1},
        {1,0,1},
        {1,1,0}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
}
TEST(Matrix, Three6) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,1,1},
        {1,0,1},
        {1,0,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}
TEST(Matrix, Three7) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,1,1},
        {1,0,1},
        {0,1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
}
TEST(Matrix, Three8) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,1,1},
        {0,0,1},
        {1,1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}
TEST(Matrix, Three9) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {0,1,1},
        {1,0,1},
        {1,1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
}
TEST(Matrix, Three10) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,0,1},
        {1,0,1},
        {1,1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}
TEST(Matrix, Three11) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2},
        {3,1,3},
        {4,4,4}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
}
TEST(Matrix, Three12) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2},
        {3,1,3},
        {4,4,0}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
}
TEST(Matrix, Four1) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,1,1,1},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}
TEST(Matrix, Four2) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,1,1,5},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
}
TEST(Matrix, Four3) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,1,1,3},
        {2,2,1,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}
TEST(Matrix, Four4) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,1,1,3},
        {2,1,1,2},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
}
TEST(Matrix, Four5) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,1,2,3},
        {2,2,1,2},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
}
TEST(Matrix, Four6) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,2,1,3},
        {2,1,2,2},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
}
TEST(Matrix, Four7) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,2,1,3},
        {2,1,0,2},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
}
