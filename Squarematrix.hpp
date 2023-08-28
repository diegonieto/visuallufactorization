/**
 * @file Squarematrix.hpp
 *
 * Copyright 2023 Diego Nieto
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef SQUAREMATRIX
#define SQUAREMATRIX

#include <cmath>
#include <array>

#include <string.h>

#include "NumericMatrix.hpp"


// #define DEBUG
#ifdef DEBUG
#define DBG(x) std::cout << __PRETTY_FUNCTION__ << ":" << __LINE__ << x << std::endl;
#define DBG_CMD(x) x
#else
#define DBG(x)
#define DBG_CMD(x)
#endif

template <typename T>
class SquareMatrix : public NumericMatrix<T> {
public:
    SquareMatrix(const int size) :
      NumericMatrix<T>(size, size)
    {

    }
    const unsigned int getSize() { return this->getRowsCount(); }

    /**
     * @brief Performs an LU decomposition of the given matrix inplace
     *
     */
    void lu();

    /**
     * @brief Get the inverse of the given matrix
     *
     */
    SquareMatrix<T> getInverse();

    /**
     * @brief Set data from a memory pointer
     *
     * @param ptr pointer to data
     * @param size size of the date. Must much cols*rows, i.e., size
     */
    void setData(T *ptr, size_t size);

private:
    /**
     * @brief Given a startRow, it iterates forward looking for the max
     * absolute value of a column in a rows range
     *
     */
    void permute(const unsigned int startRow);

    /**
     * @brief Make the matrix identity by setting ones in the diagonal
     */
    void makeIdentity();

    std::unique_ptr<SquareMatrix<T>> _permutationMatrix;
};

template <typename T>
void SquareMatrix<T>::permute(const unsigned int startRow)
{
  T maxValue = static_cast<double>(std::abs(this->get(startRow, startRow)));
  unsigned int maxValueRow = startRow;

  // Find the absolute max value of a column in a rows range(startRow:nRows)
  for ( unsigned int currRow=startRow+1; currRow<getSize(); currRow++ )
  {
    if ( std::abs(this->get(currRow, startRow)) > maxValue ) {
      maxValue = std::abs(this->get(currRow, startRow));
      maxValueRow = currRow;
    }
  }

  // Interchange row (startRow <-> maxValueRow)
  if ( maxValueRow != startRow ) {
    T tmp;
    for ( unsigned int k=0; k<getSize(); k++ )
    {
      tmp = this->get(startRow, k);
      this->set(startRow, k, this->get(maxValueRow, k));
      this->set(maxValueRow, k, tmp);
      tmp = _permutationMatrix->get(startRow, k);
      _permutationMatrix->set(startRow, k, _permutationMatrix->get(maxValueRow, k));
      _permutationMatrix->set(maxValueRow, k, tmp);
    }
  }
}

/**
 * @brief Make the matrix identity by setting ones in the diagonal
 */
template<typename T>
void SquareMatrix<T>::makeIdentity()
{
  this->setZero();
  for (unsigned rowcol = 0; rowcol < this->getSize(); rowcol++ )
  {
    this->set(rowcol, rowcol, static_cast<T>(1.0f));
  }
}

template <typename T>
void SquareMatrix<T>::lu()
{
  _permutationMatrix = std::make_unique<SquareMatrix<T>>(getSize());
  _permutationMatrix->makeIdentity();

  // Iterate through each column
  for ( unsigned int col=0; col<getSize()-1; col++ )
  {
      permute(col);
      // Iterate through each row to do zero
      for ( unsigned int row=col+1; row<getSize(); row++ )
      {
          // Compute the pivot
          T p = static_cast<T>(-static_cast<T>(this->get(row, col))/static_cast<T>(this->get(col, col)));
          // Update row
          for ( unsigned int k=col; k<getSize(); k++ )
          {
              this->set(row, k, this->get(row, k)+p*this->get(col, k));
          }
          // Store the pivot for L
          this->set(row, col, -p);
      }
  }
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::getInverse()
{
  DBG (" printing original LU: ");
  DBG_CMD (this->print());

  // Perform backward substitution. U will do the following transformation:
  SquareMatrix<T> Uinverse(getSize());
  Uinverse.makeIdentity();
  //   U   |  UInv
  // u u u | 1 0 0      1 0 0 | u-1 u-1 u-1
  // 0 u u | 0 1 0  ->  0 1 0 |  0  u-1 u-1
  // 0 0 u | 0 0 1      0 0 1 |  0   0  u-1
  for ( int row = getSize()-1; row >= 0; row-- )
  {
    T p = static_cast<T>(static_cast<T>(1.0f)/this->get(row, row));
    // Multiply all the row by the pivot in both matrix
    for ( unsigned int col = row; col < this->getSize(); col++ )
    {
      this->set(row, col, this->get(row, col)*p);
      Uinverse.set(row, col, Uinverse.get(row, col)*p);
    }
    DBG (" row is " << row);
    // Make zeros the colum of the row-1 to row=0
    for ( int rowInUpdate = row-1; rowInUpdate >= 0; rowInUpdate-- )
    {
        DBG (" in update " << rowInUpdate );
        const T localPivot = -this->get(rowInUpdate, row);
        // Update all the columns at the right of the(rowInUpdate, row) in both matrix
        for ( unsigned int kcol=row; kcol<getSize(); kcol++)
        {
          this->set(rowInUpdate, kcol, localPivot*this->get(row, kcol)+this->get(rowInUpdate, kcol));
          const auto updatedValue = localPivot*Uinverse.get(row, kcol)+Uinverse.get(rowInUpdate, kcol);
          DBG (
              " BACKWARD row " << row
              << " in update " << rowInUpdate
              << " local pivot " << localPivot
              << " inverse.get(row, row) " << Uinverse.get(row, kcol)
              << " inverse.get(rowInUpdate, row) " << Uinverse.get(rowInUpdate, kcol)
              << " result  " << updatedValue
          );
          Uinverse.set(rowInUpdate, kcol, updatedValue);
        }
    }
  }
  DBG (" printing inverse U-1: " );
  DBG_CMD (Uinverse.print());

  // Perform forward subtitution
  SquareMatrix<T> Linverse(getSize());
  Linverse.makeIdentity();
  //   L   |  LInv
  // 1 0 0 | 1 0 0      1 0 0 |  1  0   0
  // l 1 0 | 0 1 0  ->  0 1 0 | l-1  1  0
  // l l 1 | 0 0 1      0 0 1 | l-1 l-1 1
  for ( unsigned int rowcol = 0; rowcol < getSize(); rowcol++ )
  {
    // Make zeros the colum of the rowcol-1 to rowcol=0
    for ( unsigned int rowcolInUpdate = rowcol+1; rowcolInUpdate < getSize(); rowcolInUpdate++ )
    {
        DBG ( " in update " << rowcolInUpdate );
        const T localPivot = -this->get(rowcolInUpdate, rowcol);
        // Update all the columns at the left of the(rowcolInUpdate, rowcol) in both matrix
        for ( unsigned int kcol=0; kcol<rowcolInUpdate; kcol++)
        {
          this->set(rowcolInUpdate, kcol, localPivot*this->get(rowcol, kcol)+this->get(rowcolInUpdate, kcol));
          const auto updatedValue = localPivot*Linverse.get(rowcol, kcol)+Linverse.get(rowcolInUpdate, kcol);
          DBG (
             " FORWARD rowcol " << rowcol
              << " in update " << rowcolInUpdate
              << " local pivot " << localPivot
              << " inverse.get(rowcol, rowcol) " << Linverse.get(rowcol, kcol)
              << " inverse.get(rowcolInUpdate, rowcol) " << Linverse.get(rowcolInUpdate, kcol)
              << " result  " << updatedValue
          );
          Linverse.set(rowcolInUpdate, kcol, updatedValue);
        }
    }
  }
  DBG (" printing inverse L-1: " );
  DBG_CMD (Linverse.print());

  // Get A-1 => Multiply A-1=U-1*L-1*p (only U-1*L-1 below)
  SquareMatrix<T> Ainverse(getSize());
  for (unsigned int i=0; i<getSize(); i++)
  {
    for (unsigned int j=0; j<getSize(); j++)
    {
      T local = 0;
      for (unsigned int k=0; k<getSize(); k++)
      {
        local += Uinverse.get(i, k) * Linverse.get(k, j);
      }
      Ainverse.set(i, j, local);
    }
  }
  DBG (" printing inverse without permutation: " );
  DBG_CMD (Ainverse.print());

  // Get A-1 => Multiply A-1=(UL)-1 * p (the remaining multiplication)
  SquareMatrix<T> AinversePermuted(getSize());
  if (_permutationMatrix != nullptr)
  {
    DBG (" printing permutation matrix: " );
    DBG_CMD (_permutationMatrix->print());
    for (unsigned int i=0; i<getSize(); i++)
    {
      for (unsigned int j=0; j<getSize(); j++)
      {
        T local = 0;
        for (unsigned int k=0; k<getSize(); k++)
        {
          local += Ainverse.get(i, k) * _permutationMatrix->get(k, j);
        }
        AinversePermuted.set(i, j, local);
      }
    }
    DBG (" printing A inversed and permuted: " );
    DBG_CMD (AinversePermuted.print());
    Ainverse.setData(AinversePermuted.getDataPtr(), getSize()*getSize());
  }

  return Ainverse;
}

template <typename T>
void SquareMatrix<T>::setData(T *ptr, size_t size)
{
    if (size == this->_ncols * this->_nrows) {
        memcpy(this->_matrix, ptr, size*sizeof(T));
    } else {
        throw INVALID_RANGE;
    }
}

#endif // SQUAREMATRIX
