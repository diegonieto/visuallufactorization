/**
 * @file Matrix.hpp
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

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>

enum Matrix_Errors {
    INVALID_RANGE = -20
};

template <typename T>
class Matrix
{
protected:
    const unsigned int _nrows;
    const unsigned int _ncols;
    T *_matrix;
public:
    Matrix(const int nrows, const int ncols) :
    _nrows(nrows), _ncols(ncols)
    {
        _matrix = new T[_nrows*_ncols];
    }

    virtual ~Matrix()
    {
        delete[] _matrix;
    }

    virtual T get(const unsigned int i, const unsigned int j) const;
    virtual T* getDataPtr() const;
    virtual bool set(const unsigned int i, const unsigned int j, const T value);
    virtual const unsigned int getRowsCount() const;
    virtual const unsigned int getColumnsCount() const;
    void print() const;
};

template <typename T>
T Matrix<T>::get(const unsigned int i, const unsigned int j) const
{
    if ( i <_nrows && j < _ncols )
        return _matrix[i*_ncols+j];
    else
        throw INVALID_RANGE;
}

template <typename T>
T* Matrix<T>::getDataPtr() const
{
    return _matrix;
}

template <typename T>
bool Matrix<T>::set(const unsigned int i, const unsigned int j, const T value)
{
    if ( i <_nrows && j < _ncols ) {
        _matrix[i*_ncols+j] = value;
        return true;
    } else
        throw INVALID_RANGE;
}

template <typename T>
const unsigned int Matrix<T>::getRowsCount() const
{
    return _nrows;
}

template <typename T>
const unsigned int Matrix<T>::getColumnsCount() const
{
    return _ncols;
}

template <typename T>
void Matrix<T>::print() const
{
    for (unsigned int i = 0; i < _nrows; i++)
    {
        for (unsigned int j = 0; j < _ncols; j++)
        {
            std::cout << std::setprecision(4) << _matrix[i*_ncols+j] << "\t\t\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

#endif // MATRIX_H
