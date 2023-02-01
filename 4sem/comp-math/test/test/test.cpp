#include <gtest/gtest.h>

#include <complib/comp.hpp>

#include <vector>

TEST(test_matrix_solve, matrix_solve) {

  vector<vector<double>> matr1 = {{1, -2, 1, 0}, {2, 2, -1, 3}, {3, -1, 1, 5}};
  vector<double> sol_matr1 = matrix_solution(matr1);
  vector<double> expected1 = {1, 3, 5};
  ASSERT_EQ(expected1, sol_matr1);

  vector<vector<double>> matr2 = {{3, 4, 10}, {5, -7, 3}};
  vector<double> sol_matr2 = matrix_solution(matr2);
  vector<double> expected2 = {2, 1};
  ASSERT_EQ(expected2, sol_matr2);

  //   vector<vector<double>> matr3 = {{1, 2, -3, -4}, {2, 5, -4, 0}, {-3, 1, 3,
  //   5}}; vector<double> sol_matr3 = matrix_solution(matr3); vector<double>
  //   expected3 = {2.05, 1.7, 3.15}; ASSERT_EQ(expected3, sol_matr3);

  vector<vector<double>> matr4 = {
      {1, 2, 3, -2, 6}, {2, 4, -2, -3, 18}, {3, 2, -1, 2, 4}, {2, -3, 2, 1, 8}};
  vector<double> sol_matr4 = matrix_solution(matr4);
  vector<double> expected4 = {1, 3, 5};
  ASSERT_EQ(expected4, sol_matr4);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
