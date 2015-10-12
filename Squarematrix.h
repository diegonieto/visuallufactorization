#ifndef SQUAREMATRIX
#define SQUAREMATRIX

#include "NumericMatrix.hpp"

template <typename T>
class SquareMatrix : public NumericMatrix<T> {
public:
    SquareMatrix(const int size) : NumericMatrix<T>(size, size) {}
};

#endif // SQUAREMATRIX

