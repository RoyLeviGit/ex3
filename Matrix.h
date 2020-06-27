#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H
#include "Auxiliaries.h"
#include "Exceptions.h"
#include <iostream>
#include <string>

namespace mtm {
    template <class T>
    class Matrix {
    private:
        mtm::Dimensions dimensions;
        T* data;
    public:
        Matrix(Dimensions dims, T t = T());
        Matrix(const Matrix& matrix);
        ~Matrix();
        static Matrix Diagonal(int dims, T t);

        int height() const;
        int width() const;
        int size() const;
        Matrix transpose() const;
        Matrix& operator=(const Matrix& matrix); 
        Matrix& operator+=(const Matrix& matrix);
        Matrix& operator+=(T t);
        Matrix operator-() const;
        T& operator()(int row, int column);
        const T& operator()(int row, int column) const;
        Matrix<bool> operator!=(T t) const;
        Matrix<bool> operator==(T t) const;
        Matrix<bool> operator<(T t) const;
        Matrix<bool> operator>(T t) const;
        Matrix<bool> operator<=(T t) const;
        Matrix<bool> operator>=(T t) const;
        template <class ToApply>
        Matrix apply(ToApply toApply) const;

        class iterator;
        iterator begin();
        iterator end();

        class const_iterator;
        const_iterator begin() const;
        const_iterator end() const;
        
        class AccessIllegalElement : public Exception {
        public:
            const char* what() const noexcept override;
        };
        class IllegalInitialization : public Exception {
        public:
            const char* what() const noexcept override;
        };
        class DimensionMismatch : public Exception {
            int mat1_height;
            int mat1_width;
            int mat2_height;
            int mat2_width;
            explicit DimensionMismatch(int mat1_height, int mat1_width, int mat2_height, int mat2_width);
            friend class Matrix<T>;
        public:
            const char* what() const noexcept override;
        };
    };
    template <class T>
    Matrix<T> operator+(const Matrix<T> matrixA , const Matrix<T> matrixB);
    template <class T>
    Matrix<T> operator+(T t , const Matrix<T> matrix);
    template <class T>
    Matrix<T> operator+(const Matrix<T> matrix, T t);
    template <class T>
    Matrix<T> operator-(const Matrix<T> matrixA , const Matrix<T> matrixB);
    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);
    template <class T>
    bool all(const Matrix<T> matrix);
    template <class T>
    bool any(const Matrix<T> matrix);


    template <class T>
    class Matrix<T>::iterator {
        private:
            Matrix<T>* matrix;
            int index;
            iterator(Matrix<T>* matrix, int index);
            friend class Matrix<T>;
        public:
            iterator(const iterator&) = default;
            iterator& operator=(const iterator&) = default;
            T& operator*() const;
            iterator& operator++();
            iterator operator++(int);
            bool operator==(const iterator& it) const;
            bool operator!=(const iterator& it) const;
    };

    template <class T>
    class Matrix<T>::const_iterator {
        private:
            const Matrix<T>* matrix;
            int index;
            const_iterator(const Matrix<T>* matrix, int index);
            friend class Matrix<T>;
        public:
            const_iterator(const const_iterator&) = default;
            const_iterator& operator=(const const_iterator&) = default;
            const T& operator*() const;
            const_iterator& operator++();
            const_iterator operator++(int);
            bool operator==(const const_iterator& it) const;
            bool operator!=(const const_iterator& it) const;        
    };

    // Assumptions:
    // T has default construtor
    // T has copy construtor
    // T has assignment operator
    template <class T>
    Matrix<T>::Matrix(Dimensions dims, T t) : 
        dimensions(dims.getRow(), dims.getCol()) {
        // error checking
        if (dims.getRow() <= 0 || dims.getCol() <= 0) {
            throw IllegalInitialization();
        }

        data = new T[dims.getRow() * dims.getCol()];
        for (int i = 0 ; i < size() ; i++) {
            data[i] = t;
        }
    }

    // Assumptions:
    // T has default construtor
    // T has assignment operator
    template <class T>
    Matrix<T>::Matrix(const Matrix& matrix) : 
        dimensions(matrix.dimensions.getRow(), matrix.dimensions.getCol()),
        data(new T[matrix.dimensions.getRow() * matrix.dimensions.getCol()]) {
        for (int i = 0 ; i < size() ; i++) {
            data[i] = matrix.data[i];
        }
    }
    // Assumptions:
    // T has destructor 
    template <class T>
    Matrix<T>::~Matrix() {
        delete[] data;
    }

    // Assumptions:
    // T has copy construtor
    // T has assignment operator
    template <class T>
    Matrix<T> Matrix<T>::Diagonal(int dims, T t) {
        // error checking
        if (dims <= 0) {
            throw IllegalInitialization();
        }

        Matrix<T> diagonal(Dimensions(dims, dims));
        for(int i = 0; i < dims; i ++) {
            diagonal(i,i) = t;
        }
        return diagonal;
    }

    template <class T>
    int Matrix<T>::height() const {
        return dimensions.getRow();
    }

    template <class T>
    int Matrix<T>::width() const {
        return dimensions.getCol();
    }

    template <class T>
    int Matrix<T>::size() const {
        return height() * width();
    }

    // Assumptions:
    // T has assignment operator
    template <class T>
    Matrix<T> Matrix<T>::transpose() const {
        Dimensions transposedDimensions = Dimensions(dimensions.getCol(), dimensions.getRow());
        Matrix<T> transposed = Matrix(transposedDimensions);
        
        for (int i = 0; i < height() ; i++) {
            for (int j = 0; j < width() ; j++) {
                transposed(j,i) = (*this)(i,j);
            }
        }
        return transposed;
    }

    // Assumptions:
    // T has assignment operator
    template <class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix) {
        // error checking
        if (dimensions != matrix.dimensions) {
            throw DimensionMismatch(height(), width(), matrix.height(), matrix.width());
        }

        for (int i = 0 ; i < size() ; i++) {
            data[i] = matrix.data[i];
        }
        dimensions = Dimensions(matrix.dimensions.getRow(),matrix.dimensions.getCol());
        return *this;
    }

    // Assumptions:
    // T has += operator
    template <class T>
    Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& matrix) {
        // error checking
        if (dimensions != matrix.dimensions) {
            throw DimensionMismatch(height(), width(), matrix.height(), matrix.width());
        }

        for (int i = 0; i < size() ; i++) {
            data[i] += matrix.data[i];
        }
        return *this;
    }

    // Assumptions:
    // T has += operator
    template <class T>
    Matrix<T>& Matrix<T>::operator+=(T t){
        for (int i = 0; i < size() ; i++) {
            data[i] += t;
        }
        return *this;  
    }

    // Assumptions:
    // T has unary - operator
    template <class T>
    Matrix<T> Matrix<T>::operator-() const {
        Matrix<T> minusMatrix(*this);
        for(int i = 0 ; i < size(); i++) {
            minusMatrix.data[i] = -data[i];
        }
        return minusMatrix;
    }
    
    template <class T>
    T& Matrix<T>::operator()(int row, int column) {
        // error checking
        if (row >= height() || column >= width()) {
            throw AccessIllegalElement();
        }

        return data[(row * width()) + column]; 
    }
    
    template <class T>
    const T& Matrix<T>::operator()(int row, int column) const {
        // error checking
        if (row >= height() || column >= width()) {
            throw AccessIllegalElement();
        }

        return data[(row * width()) + column];
    }
    
    // Assumptions:
    // T has != operator
    template <class T>
    Matrix<bool> Matrix<T>::operator!=(T t) const {
        Matrix<bool> diffMatrix(dimensions, false);
        for (int i = 0; i < height(); ++i) {
            for (int j = 0; j < width(); ++j) {
                if ((*this)(i,j) != t) {
                    diffMatrix(i,j) = true;
                }
            }
        }
        return diffMatrix;
    }
    
    template <class T>
    Matrix<bool> Matrix<T>::operator==(T t) const {
        Matrix<bool> equMatrix = operator!=(t);
        for (Matrix<bool>::iterator it = equMatrix.begin(); it != equMatrix.end() ; ++it) {
            *it = !(*it);
        }
        return equMatrix;
    }
    
    // Assumptions:
    // T has < operator
    template <class T>
    Matrix<bool> Matrix<T>::operator<(T t) const {
        Matrix<bool> smallMatrix(dimensions, false);
        for (int i = 0; i < height(); ++i) {
            for (int j = 0; j < width(); ++j) {
                if ((*this)(i,j) < t) {
                    smallMatrix(i,j) = true;
                }
            }
        }
        return smallMatrix;
    }

    // Assumptions:
    // T has > operator
    template <class T>
    Matrix<bool> Matrix<T>::operator>(T t) const{
        Matrix<bool> bigMatrix(dimensions, false);
        for (int i = 0 ; i < height(); i++) {
            for (int j = 0 ; j < width(); j++) {
               if ((*this)(i,j) > t) {
                   bigMatrix(i,j) = true;
               } 
            }
        }
        return bigMatrix;
    }
    
    template <class T>
    Matrix<bool> Matrix<T>::operator<=(T t) const{
        Matrix<bool> newMatrix = operator>(t);
        for (Matrix<bool>::iterator it = newMatrix.begin(); it != newMatrix.end() ; ++it) {
            *it = !(*it);
        }
        return newMatrix;
    }

    template <class T>
    Matrix<bool> Matrix<T>::operator>=(T t) const{
        Matrix<bool> newMatrix = operator<(t);
        for (Matrix<bool>::iterator it = newMatrix.begin(); it != newMatrix.end() ; ++it) {
            *it = !(*it);
        }
        return newMatrix;
    }
    
    template <class T>
    typename Matrix<T>::iterator Matrix<T>::begin() {
        return Matrix<T>::iterator(this, 0);
    }
    
    template <class T>
    typename Matrix<T>::iterator Matrix<T>::end() {
        return Matrix<T>::iterator(this, size());
    }

    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::begin() const {
        return Matrix<T>::const_iterator(this,0);
    }
    
    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::end() const {
        return Matrix<T>::const_iterator(this,size());
    }
    
    template <class T>
    const char* Matrix<T>::AccessIllegalElement::what() const noexcept {
        return "Mtm matrix error: An attempt to access an illegal element";
    }

    template <class T>
    const char* Matrix<T>::IllegalInitialization::what() const noexcept {
        return "Mtm matrix error: Illegal initialization values";
    }

    template <class T>
    Matrix<T>::DimensionMismatch::DimensionMismatch(int mat1_height, int mat1_width, int mat2_height, int mat2_width) :
        mat1_height(mat1_height), mat1_width(mat1_width),
        mat2_height(mat2_height), mat2_width(mat2_width)
    {}

    template <class T>
    const char* Matrix<T>::DimensionMismatch::what() const noexcept {
        return "Mtm matrix error: Dimension mismatch: (" 
        + std::to_string(mat1_height) + "," + std::to_string(mat1_width) + ") ("
        + std::to_string(mat2_height) + "," + std::to_string(mat2_width) + ")";
    }
    
    template <class T>
    Matrix<T> operator+(Matrix<T> MatrixA , Matrix<T> MatrixB) {
        Matrix<T> newMatrix = MatrixA;
        newMatrix += MatrixB;
        return newMatrix;
    }
    
    template <class T>
    Matrix<T> operator+(T t , const Matrix<T> matrix) {
        Matrix<T> plusMatrix(matrix);
        return plusMatrix += t;    
    }

    template <class T>
    Matrix<T> operator+(const Matrix<T> Matrix, T t) {
        return t + Matrix;
    }

    template <class T>
    Matrix<T> operator-(const Matrix<T> matrixA , const Matrix<T> matrixB) {
        Matrix<T> newMatrix = matrixA;
        newMatrix += -matrixB;
        return newMatrix;
    }

    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
        printMatrix(os, matrix.begin(), matrix.end(), matrix.width());
        return os;
    }
    
    // Assumptions:
    // T has static cast to bool
    template <class T>
    bool all(const Matrix<T> matrix) {
        for (T t : matrix) {
            if (static_cast<bool>(t) == false) {
                return false;
            }
        }
        return true;
    }

    // Assumptions:
    // T has static cast to bool
    template <class T>
    bool any(const Matrix<T> matrix) {
        for (T t : matrix) {
            if (static_cast<bool>(t)) {
                return true;
            }
        }
        return false;
    }

    // iterator

    template <class T>
    Matrix<T>::iterator::iterator(Matrix<T>* matrix, int index) : 
        matrix(matrix), index(index)
    {}

    template <class T>
    T& Matrix<T>::iterator::operator*() const {
        // error checking
        if (index >= matrix->size()) {
            throw AccessIllegalElement();
        }
        
        return matrix->data[index];
    }

    template <class T>
    typename Matrix<T>::iterator& Matrix<T>::iterator::operator++() {
        ++index;
        return *this;
    }

    template <class T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator++(int) {
        iterator result = *this;
        ++*this;
        return result;
    }

    template <class T>
    bool Matrix<T>::iterator::operator==(const iterator& it) const {
        return index == it.index;
    }

    template <class T>
    bool Matrix<T>::iterator::operator!=(const iterator& it) const {
        return !(*this == it);
    }

    // const_iterator

    template <class T>
    Matrix<T>::const_iterator::const_iterator(const Matrix<T>* matrix, int index) : 
         matrix(matrix), index(index)
    {}

    template <class T>
    const T& Matrix<T>::const_iterator::operator*() const {
        // error checking
        if (index >= matrix->size()) {
            throw AccessIllegalElement();
        }
        
        return matrix->data[index];
    }

    template <class T>
    typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++() {
        ++index;
        return *this;
    }

    template <class T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++(int) {
        const_iterator result = *this;
        ++*this;
        return result;
    }

    template <class T>
    bool Matrix<T>::const_iterator::operator==(const const_iterator& it) const {
        return index == it.index;
    }

    template <class T>
    bool Matrix<T>::const_iterator::operator!=(const const_iterator& it) const {
        return !(*this == it);
    }


    // Assumptions:
    // T has assignment operator
    template <class T>
    template <class ToApply>
    Matrix<T> Matrix<T>::apply(ToApply toApply) const {
        Matrix<T> newMatrix(dimensions);
        for(int i = 0 ; i < size(); i++){
            newMatrix.data[i] = toApply(data[i]);
        }
        return newMatrix;
    }
}

#endif //EX3_MATRIX_H
