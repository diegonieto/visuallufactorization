#include <gtest/gtest.h>

#include "Squarematrix.hpp"

#include <stddef.h>
#include <math.h>

#include <array>
#include <numeric>
#include <iostream>
#include <memory>

typedef double NumericType;

TEST(NumericMatrix, setZero)
{
  const size_t matrixSize = 3;
  std::unique_ptr<SquareMatrix<NumericType>> matrix = std::make_unique<SquareMatrix<NumericType>>(matrixSize);

  matrix->setZero();

  const unsigned int nrows = matrix->getRowsCount();
  const unsigned int ncols = matrix->getColumnsCount();

  EXPECT_EQ(nrows, 3);
  EXPECT_EQ(ncols, 3);

  for (unsigned int i = 0; i < nrows; i++)
  {
    for (unsigned int j = 0; j < ncols; j++)
    {
      EXPECT_EQ(matrix->get(i, j), 0);
    }
  }
}

TEST(NumericMatrix, checkInit)
{
  const size_t matrixSize = 3;
  std::unique_ptr<SquareMatrix<NumericType>> matrix = std::make_unique<SquareMatrix<NumericType>>(matrixSize);

  const unsigned int nrows = matrix->getRowsCount();
  const unsigned int ncols = matrix->getColumnsCount();
  for (unsigned int i = 0; i < nrows; i++)
  {
    for (unsigned int j = 0; j < ncols; j++)
    {
      matrix->set(i, j, i * ncols + j);
    }
  }

  for (unsigned int i = 0; i < nrows; i++)
  {
    for (unsigned int j = 0; j < ncols; j++)
    {
      EXPECT_EQ(matrix->get(i, j), i * ncols + j);
    }
  }
}

TEST(NumericMatrix, LU1)
{
  const size_t matrixSize = 3;
  std::unique_ptr<SquareMatrix<NumericType>> matrix = std::make_unique<SquareMatrix<NumericType>>(matrixSize);
  matrix->set(0, 0, 1);
  matrix->set(0, 1, 2);
  matrix->set(0, 2, 2);
  matrix->set(1, 0, 4);
  matrix->set(1, 1, 4);
  matrix->set(1, 2, 2);
  matrix->set(2, 0, 4);
  matrix->set(2, 1, 6);
  matrix->set(2, 2, 4);

  matrix->print();

  matrix->lu();

  matrix->print();

  EXPECT_NEAR(4, matrix->get(0, 0), 0.00001);
  EXPECT_NEAR(4, matrix->get(0, 1), 0.00001);
  EXPECT_NEAR(2, matrix->get(0, 2), 0.00001);
  EXPECT_NEAR(1, matrix->get(1, 0), 0.00001);
  EXPECT_NEAR(2, matrix->get(1, 1), 0.00001);
  EXPECT_NEAR(2, matrix->get(1, 2), 0.00001);
  EXPECT_NEAR(0.25, matrix->get(2, 0), 0.00001);
  EXPECT_NEAR(0.5, matrix->get(2, 1), 0.00001);
  EXPECT_NEAR(0.5, matrix->get(2, 2), 0.00001);
}

TEST(NumericMatrix, LU2)
{
  const size_t matrixSize = 3;
  std::unique_ptr<SquareMatrix<NumericType>> matrix = std::make_unique<SquareMatrix<NumericType>>(matrixSize);
  matrix->set(0, 0, 25);
  matrix->set(0, 1, 5);
  matrix->set(0, 2, 1);
  matrix->set(1, 0, 64);
  matrix->set(1, 1, 8);
  matrix->set(1, 2, 1);
  matrix->set(2, 0, 144);
  matrix->set(2, 1, 12);
  matrix->set(2, 2, 1);

  matrix->print();

  matrix->lu();

  matrix->print();

  EXPECT_NEAR(144, matrix->get(0, 0), 0.00001);
  EXPECT_NEAR(12, matrix->get(0, 1), 0.00001);
  EXPECT_NEAR(1, matrix->get(0, 2), 0.00001);
  EXPECT_NEAR(0.17361, matrix->get(1, 0), 0.00001);
  EXPECT_NEAR(2.91667, matrix->get(1, 1), 0.00001);
  EXPECT_NEAR(0.82639, matrix->get(1, 2), 0.00001);
  EXPECT_NEAR(0.44444, matrix->get(2, 0), 0.00001);
  EXPECT_NEAR(0.91429, matrix->get(2, 1), 0.00001);
  EXPECT_NEAR(-0.2, matrix->get(2, 2), 0.00001);
}

TEST(NumericMatrix, InverseUpper1)
{
  const size_t matrixSize = 3;
  std::unique_ptr<SquareMatrix<NumericType>> matrix = std::make_unique<SquareMatrix<NumericType>>(matrixSize);
  matrix->set(0, 0, 2);
  matrix->set(0, 1, 4);
  matrix->set(0, 2, 6);
  matrix->set(1, 0, 0);
  matrix->set(1, 1, -1);
  matrix->set(1, 2, -8);
  matrix->set(2, 0, 0);
  matrix->set(2, 1, 0);
  matrix->set(2, 2, 96);

  auto inverse = matrix->getInverse();

  EXPECT_NEAR(0.5, inverse.get(0, 0), 0.00001);
  EXPECT_NEAR(2, inverse.get(0, 1), 0.00001);
  EXPECT_NEAR(0.13542, inverse.get(0, 2), 0.00001);
  EXPECT_NEAR(0, inverse.get(1, 0), 0.00001);
  EXPECT_NEAR(-1, inverse.get(1, 1), 0.00001);
  EXPECT_NEAR(-0.08333, inverse.get(1, 2), 0.00001);
  EXPECT_NEAR(0, inverse.get(2, 0), 0.00001);
  EXPECT_NEAR(0, inverse.get(2, 1), 0.00001);
  EXPECT_NEAR(0.01042, inverse.get(2, 2), 0.00001);
}

TEST(NumericMatrix, InverseLower1)
{
  const size_t matrixSize = 3;
  std::unique_ptr<SquareMatrix<NumericType>> matrix = std::make_unique<SquareMatrix<NumericType>>(matrixSize);
  matrix->set(0, 0, 1);
  matrix->set(0, 1, 0);
  matrix->set(0, 2, 0);
  matrix->set(1, 0, 1.5);
  matrix->set(1, 1, 1);
  matrix->set(1, 2, 0);
  matrix->set(2, 0, 3);
  matrix->set(2, 1, 14);
  matrix->set(2, 2, 1);

  auto inverse = matrix->getInverse();

  EXPECT_NEAR(1, inverse.get(0, 0), 0.00001);
  EXPECT_NEAR(0, inverse.get(0, 1), 0.00001);
  EXPECT_NEAR(0, inverse.get(0, 2), 0.00001);
  EXPECT_NEAR(-1.5, inverse.get(1, 0), 0.00001);
  EXPECT_NEAR(1, inverse.get(1, 1), 0.00001);
  EXPECT_NEAR(0, inverse.get(1, 2), 0.00001);
  EXPECT_NEAR(18, inverse.get(2, 0), 0.00001);
  EXPECT_NEAR(-14, inverse.get(2, 1), 0.00001);
  EXPECT_NEAR(1, inverse.get(2, 2), 0.00001);
}

TEST(NumericMatrix, InverseA)
{
  const size_t matrixSize = 3;
  std::unique_ptr<SquareMatrix<NumericType>> matrix = std::make_unique<SquareMatrix<NumericType>>(matrixSize);
  matrix->set(0, 0, 2);
  matrix->set(0, 1, 4);
  matrix->set(0, 2, 6);
  matrix->set(1, 0, 3);
  matrix->set(1, 1, 5);
  matrix->set(1, 2, 1);
  matrix->set(2, 0, 6);
  matrix->set(2, 1, -2);
  matrix->set(2, 2, 2);

  matrix->lu();

  auto inverse = matrix->getInverse();

  EXPECT_NEAR(0.13542, inverse.get(0, 0), 0.00001);
  EXPECT_NEAR(0.10417, inverse.get(0, 1), 0.00001);
  EXPECT_NEAR(-0.06250, inverse.get(0, 2), 0.00001);
  EXPECT_NEAR(-0.08333, inverse.get(1, 0), 0.00001);
  EXPECT_NEAR(0.166667, inverse.get(1, 1), 0.00001);
  EXPECT_NEAR(0, inverse.get(1, 2), 0.00001);
  EXPECT_NEAR(0.01042, inverse.get(2, 0), 0.00001);
  EXPECT_NEAR(-0.14583, inverse.get(2, 1), 0.00001);
  EXPECT_NEAR(0.18750, inverse.get(2, 2), 0.00001);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
