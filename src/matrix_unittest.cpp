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
    ASSERT_EQ(puddles[0].height_, 0);
    test_ns::entry_pos_ordered_t expected{ {1,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Three3) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,1,0},
        {1,0,1},
        {1,1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    ASSERT_EQ(puddles[0].height_, 0);
    test_ns::entry_pos_ordered_t expected{ {1,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
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
    ASSERT_EQ(puddles[0].height_, 1);
    test_ns::entry_pos_ordered_t expected{ {1,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
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
    ASSERT_EQ(puddles[0].height_, 1);
    test_ns::entry_pos_ordered_t expected{ {1,1}, {1,2 } };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
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
        {4,4,4,4},
        {3,1,2,3},
        {4,2,2,4},
        {4,5,4,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    ASSERT_EQ(puddles[0].height_, 2);
    test_ns::entry_pos_ordered_t expected{ {1,1}, {1,2 }, {2,1}, {2,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
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
    ASSERT_EQ(puddles[0].height_, 1);
    test_ns::entry_pos_ordered_t expected{ {1,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    ASSERT_EQ(puddles[1].height_, 1);
    expected = { {2,2} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
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
    ASSERT_EQ(puddles[0].height_, 1);
    test_ns::entry_pos_ordered_t expected{ {1,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    ASSERT_EQ(puddles[1].height_, 1);
    expected = { {2,1} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
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
    ASSERT_EQ(puddles[0].height_, 1);
    test_ns::entry_pos_ordered_t expected{ {1,2}, {2,1}, {2,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Four8) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,0,1,3},
        {2,1,0,2},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    ASSERT_EQ(puddles[0].height_, 1);
    test_ns::entry_pos_ordered_t expected{ {1,1}, {1,2}, {2,1}, {2,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}
TEST(Matrix, Four9) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,0,1,3},
        {2,1,0,2},
        {2,0,1,2},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    ASSERT_EQ(puddles[0].height_, 1);
    test_ns::entry_pos_ordered_t expected{ {1,1}, {1,2}, {2,1}, {2,2},
        {3,1}, {3,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}
TEST(Matrix, Four10) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,1,1,3},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    ASSERT_EQ(puddles[0].height_, 1);
    test_ns::entry_pos_ordered_t expected{ {1,1}, {1,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}
TEST(Matrix, Four11) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,1,1,3},
        {2,2,2,2},
        {2,0,0,2},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    ASSERT_EQ(puddles[0].height_, 0);
    test_ns::entry_pos_ordered_t expected = { {3,1}, {3,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    ASSERT_EQ(puddles[1].height_, 1);
    expected = { {1,1}, {1,2} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}
TEST(Matrix, Four12) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {2,2,2,2},
        {3,1,1,3},
        {2,2,2,2},
        {2,0,0,2},
        {2,2,2,2},
        {2,1,2,2},
        {2,2,2,2},
        {2,2,0,2},
        {2,2,2,2}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 4);
    ASSERT_EQ(puddles[0].height_, 0);
    test_ns::entry_pos_ordered_t expected = { {3,1}, {3,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    ASSERT_EQ(puddles[1].height_, 0);
    expected = { {7,2} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
    ASSERT_EQ(puddles[2].height_, 1);
    expected = { {1,1}, {1,2} };
    ASSERT_TRUE( (puddles[2].entries_ == expected) );
    ASSERT_EQ(puddles[3].height_, 1);
    expected = { {5,1} };
    ASSERT_TRUE( (puddles[3].entries_ == expected) );
}

TEST(Matrix, Four13) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {3,3,3,3},
        {3,1,1,3},
        {3,0,2,3},
        {3,0,0,3},
        {3,2,1,3},
        {3,1,1,3},
        {3,1,2,3},
        {3,1,1,2},
        {3,3,3,3}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    ASSERT_EQ(puddles[0].height_, 1);
    test_ns::entry_pos_ordered_t expected{ {1,1}, {1,2},
        {2,1}, {3,1}, {3,2}, {4,2}, {5,1}, {5,2}, {6,1}, {7,1}, {7,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Four14) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {4,4,4,4},
        {4,0,4,4},
        {4,3,4,4},
        {4,2,4,4},
        {4,4,4,3}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    ASSERT_EQ(puddles[0].height_, 3);
    test_ns::entry_pos_ordered_t expected{ {1,1}, {2,1}, {3,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Five1) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {0,0,0,0,0}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five2) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {0,0,0,0,0},
        {0,0,1,0,0}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five3) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {0,0,0,0,0},
        {0,0,1,0,0},
        {0,0,0,0,0}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five4) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,1,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    ASSERT_EQ (puddles.size(), 1);
    ASSERT_EQ(puddles[0].height_, 0);
    test_ns::entry_pos_ordered_t expected{ {1,1}, {1,2}, {1,3},
        {2,1}, {2,3}, {3,1}, {3,2}, {3,3} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}
TEST(Matrix, Five5) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,2,5,0,0},
        {5,5,5,5,5},
        {1,2,5,0,5},
        {1,1,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    ASSERT_EQ(puddles[0].height_, 0);
    test_ns::entry_pos_ordered_t expected{ {3,3} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    ASSERT_EQ(puddles[1].height_, 2);
    expected = { {1,1} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}
TEST(Matrix, Five6) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,0,5,0,0},
        {5,5,5,5,5},
        {1,2,5,2,5},
        {1,1,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    ASSERT_EQ(puddles[0].height_, 0);
    test_ns::entry_pos_ordered_t expected{ {1,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    ASSERT_EQ(puddles[1].height_, 2);
    expected = { {3,3} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}
