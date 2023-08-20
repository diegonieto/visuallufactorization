#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

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
    virtual bool set(const unsigned int i, const unsigned int j, const T value);
    virtual const unsigned int getRowsCount();
    virtual const unsigned int getColumnsCount();
    void print();
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
bool Matrix<T>::set(const unsigned int i, const unsigned int j, const T value)
{
    if ( i <_nrows && j < _ncols ) {
        _matrix[i*_ncols+j] = value;
        return true;
    } else
        throw INVALID_RANGE;
}

template <typename T>
const unsigned int Matrix<T>::getRowsCount()
{
    return _nrows;
}

template <typename T>
const unsigned int Matrix<T>::getColumnsCount()
{
    return _ncols;
}

template <typename T>
void Matrix<T>::print()
{
    for (unsigned int i = 0; i < _nrows; i++)
    {
        for (unsigned int j = 0; j < _ncols; j++)
        {
            std::cout << _matrix[i*_ncols+j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

#endif // MATRIX_H
