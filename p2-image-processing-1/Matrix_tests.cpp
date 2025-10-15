#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 30;
  const int height = 50;
  const int value = 42;
  Matrix_init(&mat, 30, 50);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

TEST(test_smallest) {
  Matrix mat;
  Matrix_init(&mat, 1, 1);

  ASSERT_EQUAL(Matrix_width(&mat), 1);
  ASSERT_EQUAL(Matrix_height(&mat), 1);

  Matrix_fill(&mat, 7);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 7);
  ASSERT_EQUAL(Matrix_max(&mat), 7);
}

TEST(test_negative) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);

  *Matrix_at(&mat, 0, 0) = -5;
  *Matrix_at(&mat, 0, 1) = -10;
  *Matrix_at(&mat, 1, 0) = -3;
  *Matrix_at(&mat, 1, 1) = -8;

  ASSERT_EQUAL(Matrix_max(&mat), -3); 
}

TEST(test_matrix_width_height) {
  Matrix mat;
  Matrix_init(&mat, 3, 7);  

  ASSERT_EQUAL(Matrix_width(&mat), 3);
  ASSERT_EQUAL(Matrix_height(&mat), 7);
}

TEST(test_matrix_print) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 1, 0) = 3;
  *Matrix_at(&mat, 1, 1) = 4;

  ostringstream out;
  Matrix_print(&mat, out);

  string expected = "2 2\n1 2 \n3 4 \n";
  ASSERT_EQUAL(out.str(), expected);
}

TEST(test_fill_border) {
  Matrix mat;
  Matrix_init(&mat, 4, 3); 
  Matrix_fill(&mat, 0);   

  Matrix_fill_border(&mat, 9);


  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 9);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 3), 9);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 0), 9);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 3), 9);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), 0);
}

TEST(test_fill_border_single_row) {
  Matrix mat;
  Matrix_init(&mat, 5, 1); 
  Matrix_fill(&mat, 0);

  Matrix_fill_border(&mat, 7);

  for (int c = 0; c < 5; ++c) {
    ASSERT_EQUAL(*Matrix_at(&mat, 0, c), 7);
  }
}

TEST(test_fill_border_single_col) {
  Matrix mat;
  Matrix_init(&mat, 1, 4); 
  Matrix_fill(&mat, 0);

  Matrix_fill_border(&mat, 7);

  for (int r = 0; r < 4; ++r) {
    ASSERT_EQUAL(*Matrix_at(&mat, r, 0), 7);
  }
}


TEST(test_fill_border_single_entry) {
  Matrix mat;
  Matrix_init(&mat, 1, 1);
  Matrix_fill_border(&mat, 99);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 99);
}


TEST(test_min_value_in_row) {
  Matrix mat;
  Matrix_init(&mat, 4, 2);
  // row 1 = [10, 2, 5, 7]
  *Matrix_at(&mat, 1, 0) = 10;
  *Matrix_at(&mat, 1, 1) = 2;
  *Matrix_at(&mat, 1, 2) = 5;
  *Matrix_at(&mat, 1, 3) = 7;

  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 4), 2);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 0, 4), 1);
}

TEST(test_min_value_in_smallrange) {
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 9;
  *Matrix_at(&mat, 0, 1) = 8;
  *Matrix_at(&mat, 0, 2) = 3;
  *Matrix_at(&mat, 0, 3) = 4;
  *Matrix_at(&mat, 0, 4) = 7;

  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 1, 4), 3);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 1, 4), 2);
}


// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here


