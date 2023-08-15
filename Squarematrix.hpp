#ifndef SQUAREMATRIX
#define SQUAREMATRIX

#include <cmath>
#include "NumericMatrix.hpp"
#include <array>

template <typename T>
class SquareMatrix : public NumericMatrix<T> {
public:
    SquareMatrix(const int size) : NumericMatrix<T>(size, size) {}
    const unsigned int getSize() { return this->getRowsCount(); }
    void permute(const unsigned int startRow);
    void lu();
};

template <typename T>
void SquareMatrix<T>::permute(const unsigned int startRow)
{
  T maxValue = static_cast<double>(std::abs(this->get(startRow, startRow)));
  unsigned int maxValueRow = startRow;

  // Find the absolute max value of a column in a rows range(startRow:nRows)
  for ( unsigned int currRow=startRow+1; currRow<this->getColumnsCount(); currRow++ )
  {
    if ( std::abs(this->get(currRow, startRow)) > maxValue ) {
      maxValue = std::abs(this->get(currRow, startRow));
      maxValueRow = currRow;
    }
  }

  // Interchange row (startRow <-> maxValueRow)
  if ( maxValueRow != startRow ) {
    T tmp;
    for ( unsigned int k=0; k<this->getColumnsCount(); k++ )
    {
      tmp = this->get(startRow, k);
      this->set(startRow, k, this->get(maxValueRow, k));
      this->set(maxValueRow, k, tmp);
    }
  }
}

template <typename T>
void SquareMatrix<T>::lu()
{
  std::vector<T> L;
  L.reserve(this->getColumnsCount()*this->getRowsCount());
  // Iterate through each column
  for ( unsigned int col=0; col<this->getColumnsCount()-1; col++ )
  {
      permute(col);
      // Iterate through each row to do zero
      for ( unsigned int row=col+1; row<this->getRowsCount(); row++ )
      {
          // Compute the pivot
          T p = static_cast<T>(-static_cast<T>(this->get(row, col))/static_cast<T>(this->get(col, col)));
          // Update row
          for ( unsigned int k=col; k<this->getColumnsCount(); k++ )
          {
              this->set(row, k, this->get(row, k)+p*this->get(col, k));
          }
          // Store the pivot for L
          L[row*this->getColumnsCount()+col] = -p;
      }
  }
  for (unsigned int row = 1; row < this->getRowsCount(); row++)
  {
      // Update row
      for (unsigned int col = 0; col < row; col++)
      {
          this->set(row, col, L[row*this->getColumnsCount()+col]);
      }
  }
}

#endif // SQUAREMATRIX
