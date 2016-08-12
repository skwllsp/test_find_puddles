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

TEST(Matrix, Two6) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,2},
        {3,4},
        {5,6},
        {7,8}
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
    test_ns::sorted_entry_positions_t expected{ {1,1} };
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
    test_ns::sorted_entry_positions_t expected{ {1,1} };
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
    test_ns::sorted_entry_positions_t expected{ {1,1} };
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
    test_ns::sorted_entry_positions_t expected{ {1,1}, {1,2 } };
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
    test_ns::sorted_entry_positions_t expected{ {1,1}, {1,2 }, {2,1}, {2,2} };
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
    test_ns::sorted_entry_positions_t expected{ {1,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
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
    test_ns::sorted_entry_positions_t expected{ {1,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
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
    test_ns::sorted_entry_positions_t expected{ {1,2}, {2,1}, {2,2} };
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
    test_ns::sorted_entry_positions_t expected{ {1,1}, {1,2}, {2,1}, {2,2} };
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
    test_ns::sorted_entry_positions_t expected{ {1,1}, {1,2}, {2,1}, {2,2},
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
    test_ns::sorted_entry_positions_t expected{ {1,1}, {1,2} };
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
    test_ns::sorted_entry_positions_t expected { {1,1}, {1,2} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = { {3,1}, {3,2} };
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
    ASSERT_TRUE( (puddles[0].entries_ ==
            test_ns::sorted_entry_positions_t{ {1,1}, {1,2} }) );
    ASSERT_TRUE( (puddles[1].entries_ ==
            test_ns::sorted_entry_positions_t { {3,1}, {3,2} }) );
    ASSERT_TRUE( (puddles[2].entries_ ==
            test_ns::sorted_entry_positions_t{ {5,1} }) );
    ASSERT_TRUE( (puddles[3].entries_ ==
            test_ns::sorted_entry_positions_t{ {7,2} }) );
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
    test_ns::sorted_entry_positions_t expected{
        {1,1}, {1,2},
        {2,1},
        {3,1}, {3,2},
        {4,2},
        {5,1}, {5,2},
        {6,1},
        {7,1}, {7,2}
    };
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
    test_ns::sorted_entry_positions_t expected{ {1,1}, {2,1}, {3,1} };
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
    test_ns::sorted_entry_positions_t expected{ {1,1}, {1,2}, {1,3},
        {2,1}, {2,3}, {3,1}, {3,2}, {3,3} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Five5) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,2,4,0,0},
        {5,5,5,5,5},
        {1,2,5,0,5},
        {1,1,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    test_ns::sorted_entry_positions_t expected = { {1,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = { {3,3} };
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
    test_ns::sorted_entry_positions_t expected{ {1,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = { {3,3} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}

TEST(Matrix, Five7) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,0,0,0,5},
        {5,0,0,0,5},
        {1,0,0,0,5},
        {1,1,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    test_ns::sorted_entry_positions_t expected{ {1,1}, {1,2}, {1,3},
    {2,1}, {2,2}, {2,3}, {3,1}, {3,2}, {3,3} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Five8) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,0,5,5,5},
        {5,5,5,5,5},
        {5,5,5,1,5},
        {5,5,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    test_ns::sorted_entry_positions_t expected{ {1,1}};
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = { {3,3} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}

TEST(Matrix, Five9) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,0,5,5,5},
        {5,5,0,5,5},
        {5,5,5,1,5},
        {5,5,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 3);
    test_ns::sorted_entry_positions_t expected{ {1,1}};
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = { {2,2} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
    expected = { {3,3} };
    ASSERT_TRUE( (puddles[2].entries_ == expected) );
}

TEST(Matrix, Five10) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,0,5,5,5},
        {5,3,5,5,5},
        {5,3,3,1,5},
        {5,5,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    test_ns::sorted_entry_positions_t expected{ {1,1}, {2,1}, {3,1}, {3,2}, {3,3}};
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Five11) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,0,5,5,5},
        {5,3,5,5,5},
        {5,3,3,1,5},
        {5,5,0,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    test_ns::sorted_entry_positions_t expected{ {1,1}};
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = { {3,3} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}

TEST(Matrix, Five12) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,0,5,5,5},
        {5,3,5,5,5},
        {5,3,3,1,5},
        {5,5,1,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    test_ns::sorted_entry_positions_t expected{ {1,1}};
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = { {3,3} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}

TEST(Matrix, Five13) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,0,5,5,5},
        {5,3,5,5,5},
        {5,3,3,1,5},
        {5,5,2,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    test_ns::sorted_entry_positions_t expected{ {1,1}};
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = { {3,3} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}

TEST(Matrix, Five14) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,0,5,5,5},
        {5,3,5,5,5},
        {5,3,3,1,5},
        {5,5,3,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    test_ns::sorted_entry_positions_t expected{ {1,1}};
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = { {3,3} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}

TEST(Matrix, Five15) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,0,5,5,5},
        {5,3,5,5,5},
        {5,3,3,1,5},
        {5,5,4,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    test_ns::sorted_entry_positions_t expected{ {1,1}, {2,1}, {3,1}, {3,2}, {3,3}};
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Five16) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {1,2,5,5,5},
        {3,3,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five17) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {1,2,3,4,5,6,7,8,9,10},
        {11,12,13,14,15,16,17,18,19,20},
        {21,22,23,24,25,26,27,28,29,30},
        {31,32,33,34,35,36,37,38,39,40},
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five18) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {3,2,5,5,5},
        {3,1,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five19) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,5,5,1,1},
        {5,5,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five20) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,5,5,1,5},
        {5,5,5,1,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five21) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,1,5},
        {5,5,5,1,5},
        {5,5,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five22) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {5,5,5,1,1},
        {5,5,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five23) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,5,5,5,5},
        {1,1,5,5,5},
        {5,5,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five24) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {5,1,5,5,5},
        {5,1,5,5,5},
        {5,5,5,5,5}
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 0);
}

TEST(Matrix, Five25) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {40,40,40,40,40,40,40,40,40,40},
        {40,12,13,14,15,16,17,18,19,40},
        {40,22,23,24,25,26,27,28,29,40},
        {40,40,40,40,40,40,40,40,40,40},
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    test_ns::sorted_entry_positions_t expected{
        {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}, {1,8},
        {2,1}, {2,2}, {2,3}, {2,4}, {2,5}, {2,6}, {2,7}, {2,8}
    };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Recursive1) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        { 4, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        { 4, 0, 5, 5, 5, 5, 5, 0, 0, 4},
        { 4, 0, 5, 0, 0, 0, 5, 0, 0, 4},
        { 4, 0, 5, 0, 5, 0, 5, 0, 0, 4},
        { 4, 0, 5, 0, 0, 0, 5, 0, 0, 4},
        { 4, 0, 5, 6, 7, 5, 5, 0, 0, 4},
        { 4, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    test_ns::sorted_entry_positions_t expected{
        {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}, {1,8},
        {2,1},                                    {2,7}, {2,8},
        {3,1},                                    {3,7}, {3,8},
        {4,1},                                    {4,7}, {4,8},
        {5,1},                                    {5,7}, {5,8},
        {6,1},                                    {6,7}, {6,8},
        {7,1}, {7,2}, {7,3}, {7,4}, {7,5}, {7,6}, {7,7}, {7,8}
    };
    auto itr1 = puddles[0].entries_.begin();
    auto itr2 = expected.begin();
    while (itr1 != puddles[0].entries_.end() && itr2 != expected.end()) {
        if ( !(*itr1 == *itr2)) {
            ASSERT_TRUE( (*itr1 == *itr2) );
        }
        ++itr1;
        ++itr2;
    }
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = {
        {3,3}, {3,4}, {3,5},
        {4,3},        {4,5},
        {5,3}, {5,4}, {5,5},
    };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}

TEST(Matrix, Recursive2) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4, 4, 3, 3, 4, 4, 4, 4},
        { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        { 4, 0, 5, 5, 5, 0, 6, 6, 6, 0, 0, 4},
        { 4, 0, 5, 0, 5, 0, 5, 2, 4, 0, 0, 4},
        { 4, 0, 5, 4, 5, 0, 5, 5, 5, 0, 0, 4},
        { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        { 4, 4, 4, 4, 4, 4, 3, 3, 4, 4, 4, 4},
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 3);
    test_ns::sorted_entry_positions_t expected{
        {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}, {1,8}, {1,9}, {1,10},
        {2,1},                      {2,5},                      {2,9}, {2,10},
        {3,1},                      {3,5},                      {3,9}, {3,10},
        {4,1},                      {4,5},                      {4,9}, {4,10},
        {5,1}, {5,2}, {5,3}, {5,4}, {5,5}, {5,6}, {5,7}, {5,8}, {5,9}, {5,10}
    };
    auto itr1 = puddles[0].entries_.begin();
    auto itr2 = expected.begin();
    while (itr1 != puddles[0].entries_.end() && itr2 != expected.end()) {
        if ( !(*itr1 == *itr2)) {
            ASSERT_TRUE( (*itr1 == *itr2) );
        }
        ++itr1;
        ++itr2;
    }
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = { {3,3} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
    expected = { {3,7} };
    ASSERT_TRUE( (puddles[2].entries_ == expected) );
}

TEST(Matrix, Recursive3) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        {4, 4, 4, 4, 4, 4, 4, 4, 4},
        {4, 0, 0, 0, 0, 0, 0, 0, 4},
        {4, 0, 5, 5, 5, 5, 5, 0, 4},
        {4, 0, 5, 0, 0, 0, 5, 0, 4},
        {4, 0, 5, 0, 5, 0, 5, 0, 4},
        {4, 0, 5, 0, 0, 0, 5, 0, 4},
        {4, 0, 5, 0, 8, 0, 5, 0, 4},
        {4, 0, 5, 0, 0, 0, 5, 0, 4},
        {4, 0, 5, 6, 7, 5, 5, 0, 4},
        {4, 0, 0, 0, 0, 0, 0, 0, 4},
        {4, 4, 4, 3, 4, 4, 4, 4, 4},
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    test_ns::sorted_entry_positions_t expected{
        {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7},
        {2,1},                                    {2,7},
        {3,1},                                    {3,7},
        {4,1},                                    {4,7},
        {5,1},                                    {5,7},
        {6,1},                                    {6,7},
        {7,1},                                    {7,7},
        {8,1},                                    {8,7},
        {9,1}, {9,2}, {9,3}, {9,4}, {9,5}, {9,6}, {9,7}
    };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    expected = {
        {3,3}, {3,4}, {3,5},
        {4,3},        {4,5},
        {5,3}, {5,4}, {5,5},
        {6,3},        {6,5},
        {7,3}, {7,4}, {7,5},
    };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
}

TEST(Matrix, Recursive4) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        { 4, 0, 5, 5, 5, 0, 6, 6, 6, 0, 0, 4},
        { 4, 0, 5, 0, 5, 0, 5, 2, 4, 0, 0, 4},
        { 4, 0, 5, 3, 5, 0, 5, 5, 5, 0, 0, 4},
        { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_TRUE (puddles.size() > 0);
    test_ns::sorted_entry_positions_t expected{
        {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {1,6}, {1,7}, {1,8}, {1,9}, {1,10},
        {2,1},                      {2,5},                      {2,9}, {2,10},
        {3,1},        {3,3},        {3,5},                      {3,9}, {3,10},
        {4,1},        {4,3},        {4,5},                      {4,9}, {4,10},
        {5,1}, {5,2}, {5,3}, {5,4}, {5,5}, {5,6}, {5,7}, {5,8}, {5,9}, {5,10}
    };
    auto itr1 = puddles[0].entries_.begin();
    auto itr2 = expected.begin();
    while (itr1 != puddles[0].entries_.end() && itr2 != expected.end()) {
        if ( !(*itr1 == *itr2)) {
            ASSERT_TRUE( (*itr1 == *itr2) );
        }
        ++itr1;
        ++itr2;
    }
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
    ASSERT_TRUE (puddles.size() > 1);
    expected = { {3,7} };
    ASSERT_TRUE( (puddles[1].entries_ == expected) );
    ASSERT_EQ (puddles.size(), 2);
}

TEST(Matrix, Islands1) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4, 4 },
        { 4, 0, 0, 0, 0, 4 },
        { 4, 0, 5, 5, 0, 4 },
        { 4, 0, 5, 0, 0, 4 },
        { 4, 0, 5, 0, 0, 4 },
        { 4, 0, 0, 0, 0, 4 },
        { 4, 4, 4, 4, 4, 4 }
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    test_ns::sorted_entry_positions_t expected{
        {1,1}, {1,2}, {1,3}, {1,4},
        {2,1},               {2,4},
        {3,1},        {3,3}, {3,4},
        {4,1},        {4,3}, {4,4},
        {5,1}, {5,2}, {5,3}, {5,4}
    };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Islands2) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4, 4 },
        { 4, 0, 0, 0, 0, 4 },
        { 4, 0, 0, 0, 0, 4 },
        { 4, 0, 0, 5, 0, 4 },
        { 4, 0, 5, 5, 0, 4 },
        { 4, 0, 0, 0, 0, 4 },
        { 4, 4, 4, 4, 4, 4 }
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    test_ns::sorted_entry_positions_t expected{
        {1,1}, {1,2}, {1,3}, {1,4},
        {2,1}, {2,2}, {2,3}, {2,4},
        {3,1}, {3,2},        {3,4},
        {4,1},               {4,4},
        {5,1}, {5,2}, {5,3}, {5,4}
    };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Islands3) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4, 4 },
        { 1, 0, 1, 2, 3, 4 },
        { 4, 1, 1, 2, 3, 4 },
        { 4, 1, 1, 2, 3, 4 },
        { 4, 1, 1, 2, 3, 4 },
        { 4, 1, 1, 2, 3, 4 },
        { 4, 4, 4, 4, 4, 4 }
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    test_ns::sorted_entry_positions_t expected{ {1,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Islands4) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4, 4 },
        { 4, 3, 3, 2, 2, 4 },
        { 4, 3, 3, 2, 2, 4 },
        { 4, 2, 2, 2, 2, 4 },
        { 4, 2, 2, 1, 1, 4 },
        { 4, 2, 2, 1, 0, 1 },
        { 4, 4, 4, 4, 4, 4 }
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 1);
    test_ns::sorted_entry_positions_t expected{ {1,1} };
    ASSERT_TRUE( (puddles[0].entries_ == expected) );
}

TEST(Matrix, Islands5) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4 },
        { 4, 2, 3, 1, 4 },
        { 4, 3, 3, 1, 4 },
        { 4, 1, 1, 0, 1 },
        { 4, 4, 4, 4, 4 },
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    ASSERT_TRUE( (puddles[0].entries_ ==
            test_ns::sorted_entry_positions_t { {1,1} }) );
    ASSERT_TRUE( (puddles[1].entries_ ==
            test_ns::sorted_entry_positions_t { {3,3} }) );
}

TEST(Matrix, DISABLED_Islands6) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4 },
        { 4, 2, 3, 1, 4 },
        { 4, 1, 3, 1, 4 },
        { 4, 1, 1, 0, 1 },
        { 4, 4, 4, 4, 4 },
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    ASSERT_TRUE( (puddles[0].entries_ ==
            test_ns::sorted_entry_positions_t { {3,3} }) );
}


TEST(Matrix, Kone1) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4 },
        { 4, 3, 3, 3, 4 },
        { 4, 3, 1, 3, 4 },
        { 4, 3, 3, 3, 4 },
        { 4, 4, 4, 4, 4 },
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    ASSERT_TRUE( (puddles[0].entries_ ==
            test_ns::sorted_entry_positions_t { {2,2} }) );
}

TEST(Matrix, Kone2) {
    test_ns::matrix a_matrix(test_ns::rows_t{
        { 4, 4, 4, 4, 4 },
        { 4, 3, 4, 4, 4 },
        { 4, 1, 2, 0, 4 },
        { 4, 3, 3, 3, 1 },
        { 4, 4, 4, 4, 4 },
    });
    auto puddles = a_matrix.find_puddles();
    ASSERT_EQ (puddles.size(), 2);
    ASSERT_TRUE( (puddles[0].entries_ ==
            test_ns::sorted_entry_positions_t { {3,3} }) );
}
