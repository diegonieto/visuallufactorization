#ifndef NUMERIC_MATRIX_H
#define NUMERIC_MATRIX_H

#include "Matrix.hpp"

template <typename T>
class NumericMatrix : public Matrix<T>
{
public:
    NumericMatrix(const int nrows, const int ncols) :
       Matrix<T>(nrows,ncols) {}

    void setZero();
};

template <typename T>
void NumericMatrix<T>::setZero()
{
    for ( unsigned int i=0; i<this->_nrows; i++ )
    {
        for ( unsigned int j=0; j<this->_ncols; j++ )
        {
            this->_matrix[i*this->_ncols+j] = static_cast<T>(0);
        }
    }
}

#endif // NUMERIC_MATRIX_H

