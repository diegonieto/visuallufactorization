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

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
