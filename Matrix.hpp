#ifndef MATRIX_H
#define MATRIX_H

enum Matrix_Errors {
    INVALID_RANGE = -20
};

template <typename T>
class Matrix
{
protected:
    const int _nrows;
    const int _ncols;
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

    virtual T get(const int i, const int j) const;
    virtual bool set(const int i, const int j, const T value);
};

template <typename T>
T Matrix<T>::get(const int i, const int j) const
{
    if ( i <_nrows && j < _ncols )
        return _matrix[i*_ncols+j];
    else
        throw INVALID_RANGE;
}

template <typename T>
bool Matrix<T>::set(const int i, const int j, const T value)
{
    if ( i <_nrows && j < _ncols ) {
        _matrix[i*_ncols+j] = value;
        return true;
    } else
        throw INVALID_RANGE;
}

#endif // MATRIX_H
