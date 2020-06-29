#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H
#include "Auxiliaries.h"
#include "Exceptions.h"
#include <iostream>
#include <string>

namespace mtm {
    /**
     * Generic Class for matrices
     */
    template <class T>
    class Matrix {
    private:
        mtm::Dimensions dimensions; //dimensions of the matrix
        T* data; //generic array to store matrix entry data.
    public:
        /**
         * Constructor.
         * @note T must have default and copy constructor and opeartor =
         * @throw IllegalInitialization if dims is not positive
         * @throw std::bad_alloc if out of memory
         * @param dims the deimensions of the Matrix.
         * @param t default value for every entry of the matrix. 
         *              Set to 0 of no other value is passed.
         * @return new Matrix instance.
         */
        Matrix(Dimensions dims, T t = T());

        /**
         * Copy constructor.
         * @note T must have copy constructor and opeartor =
         * @throw std::bad_alloc if out of memory
         * @param matrix matrix to copy.
         * @return new Matrix instance identical to mat.
         */
        Matrix(const Matrix& matrix);

        /**
         * Destructor.
         * Clean Matrix resources.
         */
        ~Matrix();

        /**
         * @note T must have opeartor =
         * @throw IllegalInitialization if dims is not positive
         * @throw std::bad_alloc if out of memory
         * @param dims size of a square matrix.
         * @param t default value to put in diagonal entries.
         * @return Diagonal matrix of size dim x dim, with value in the diagonal.
         */
        static Matrix Diagonal(int dims, T t);

        /**
         * @return number of rows in a matrix
         */
        int height() const;

        /**
         * @return number of columns in a matrix
         */
        int width() const;

        /**
         * @return size of a matrix
         */
        int size() const;

        /**
         * @note T must have opeartor =
         * @return the transpose matrix of the matrix
         * 
         */
        Matrix transpose() const;

        /**
         * @note T must have opeartor =
         * @throw std::bad_alloc if out of memory
         * @param matrix to put into this matrix.
         * @return the matrix after operation.
         */
        Matrix& operator=(const Matrix& matrix); 

        /**
         * @note T must have opeartor +=
         * @param matrix to add to the matrix.
         * @return sum of the matrix and the other matrix.
         */
        Matrix& operator+=(const Matrix& matrix);

        /**
         * @note T must have opeartor +=
         * @param t scalar to add to the matrix.
         * @return sum of the matrix and the scalar.
         */
        Matrix& operator+=(T t);

        /**
         * @note T must have opeartor -
         * @return negative matrix of the matrix.
         */
        Matrix operator-() const;

        /**
         * @throw AccessIllegalElement if illegal row and col was sent.
         * @param row row index of the non-const matrix.
         * @param col ocolumn index of the non-const matrix.
         * @return the element of the non-const matrix in the row and column index.
         */
        T& operator()(int row, int column);

        /**
         * @throw AccessIllegalElement if illegal row and col was sent.
         * @param row row index of the const matrix.
         * @param col ocolumn index of the const matrix.
         * @return the element of the const matrix in the row and column index.
         */
        const T& operator()(int row, int column) const;

        /**
         * @note T must have opeartor !=
         * @param t number to compare with matrix entries.
         * @return Matrix the same size as the matrix with 1 at the entries that
         * not equal to num, and 0 for the entry that doesn't.
         */
        Matrix<bool> operator!=(T t) const;

        /**
         * @note T must have opeartor !=
         * @param t object to compare with matrix entries.
         * @return Matrix the same size as the matrix with 1 at the entries that
         * equal to num, and 0 for the entry that doesn't.
         */
        Matrix<bool> operator==(T t) const;

        /**
         * @note T must have opeartor <
         * @param t object to compare with matrix entries.
         * @return Matrix the same size as the matrix with 1 at the entries that smaller
         * than num, and 0 for the entry that doesn't.
         */
        Matrix<bool> operator<(T t) const;

        /**
         * @note T must have opeartor >
         * @param t object to compare with matrix entries.
         * @return Matrix the same size as the matrix with 1 at the entries that bigger
         * than num, and 0 for the entry that doesn't.
         */
        Matrix<bool> operator>(T t) const;

        /**
         * @note T must have opeartor > and oprator 
         * @param t object to compare with matrix entries.
         * @return Matrix the same size as the matrix with 1 at the entries that
         * smaller or equal to num, and 0 for the entry that doesn't.
         */
        Matrix<bool> operator<=(T t) const;

        /**
         * @note T must have opeartor <
         * @param t object to compare with matrix entries.
         * @return Matrix the same size as the matrix with 1 at the entries that
         * bigger or equal to num, and 0 for the entry that doesn't.
         */
        Matrix<bool> operator>=(T t) const;

        /**
         * @tparam ApplyFunction class with opeartor ()
         * @note T must have opeartor =
         * @param toApply function to apply on each entry of the matrix
         * @return new matrix with entries applyed by func
         */
        template <class ToApply>
        Matrix apply(ToApply toApply) const;

        class iterator;

        /**
         * @return iterator instance for a non-const matrix, 
         * pointing to the beginning of the matrix.
         */
        iterator begin();

        /**
         * @return iterator instance for a non-const matrix, 
         * pointing to the end of the matrix.
         */
        iterator end();

        class const_iterator;

        /**
         * @return iterator instance for a const matrix, 
         * pointing to the beginning of the matrix.
         */
        const_iterator begin() const;

        /**
         * @return iterator instance for a const matrix, 
         * pointing to the end of the matrix.
         */
        const_iterator end() const;
        
        class AccessIllegalElement : public Exception {
        public:
            AccessIllegalElement() : Exception("Mtm matrix error: An attempt to access an illegal element") {}
        };
        class IllegalInitialization : public Exception {
        public:
            IllegalInitialization() : Exception("Mtm matrix error: Illegal initialization values") {}
        };
        class DimensionMismatch : public Exception {
        public:
            explicit DimensionMismatch(int mat1_height, int mat1_width, int mat2_height, int mat2_width) :
                Exception("Mtm matrix error: Dimension mismatch: (" 
                + std::to_string(mat1_height) + "," + std::to_string(mat1_width) + ") ("
                + std::to_string(mat2_height) + "," + std::to_string(mat2_width) + ")") {}
        };
    };

    /**
    * Symmetry definition
    * @note T must have opeartor +=
    * @throw DimensionMismatch if dims of the 2 matrices aren't equal.
    * @param matrixA matrix to add.
    * @param matrixB second matrix to add.
    * @return sum of these 2 matrices.
    */
    template <class T>
    Matrix<T> operator+(const Matrix<T> matrixA , const Matrix<T> matrixB);

    /**
     * Symmetry definition
     * @note T must have opeartor +=
     * @param t number to add to all the matrix elements.
     * @param matrix matrix to add the scalar to.
     * @return sum of the scalar to all matrix elements.
     */
    template <class T>
    Matrix<T> operator+(T t , const Matrix<T> matrix);

    /**
     * Symmetry definition
     * @note T must have opeartor +=
     * @param matrix matrix to add the scalar to.
     * @param t number to add to all the matrix elements.
     * @return sum of the scalar to all matrix elements.
     */
    template <class T>
    Matrix<T> operator+(const Matrix<T> matrix, T t);

    /**
     * Symmetry definition
     * @note T must have opeartors - and +=
     * @throw DimensionMismatch if dims of the 2 matrices aren't equal.
     * @param matrixA matrix to add.
     * @param matrixB matrix to add.
     * @return subtraction of these 2 matrices.
     */
    template <class T>
    Matrix<T> operator-(const Matrix<T> matrixA , const Matrix<T> matrixB);
    
    /**
     * @note T must have opeartor <<
     * @param os output stream.
     * @param matrix matrix to print.
     * @return print the matrix.
     */
    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

    /**
     * @return True if every entry of the matrix is different than false,
     * False otherwise.
     */
    template <class T>
    bool all(const Matrix<T> matrix);

     /**
     * @return True if one entry of the matrix is different than false,
     * False otherwise.
     */
    template <class T>
    bool any(const Matrix<T> matrix);

    /**
    * Iterator Class for iterating non-const matrices
    */
    template <class T>
    class Matrix<T>::iterator {
        private:
            Matrix<T>* matrix; //pointer to the matrix instance.
            int index; //current index of iteration.

            /**
             * Constructor.
             * @param matrix pointer to the const matrix to iterate.
             * @param index starting index of iterating.
             * @return new iterator instance for a certain const matrix.
             */
            iterator(Matrix<T>* matrix, int index);
            friend class Matrix<T>;
        public:

            /**
             * Default Copy constructor.
             * Created by the compiler
             */
            iterator(const iterator&) = default;

            /**
             * Default = opeartor.
             * Created by the compiler
             */
            iterator& operator=(const iterator&) = default;

            /**
             * @return refreance to the current entry of the matrix in the iteration. 
             */
            T& operator*() const;
            
            /** 
             * Advance the index by 1.
             * @return refreance to the iterator with advanced index. 
             */
            iterator& operator++();

            /**
             * Advance the index by 1.
             * @return Instance of the iterator with the previous index. 
             */
            iterator operator++(int);

            /**
             * @param it iterator to compare with this iterator.
             * @return true if the iterators are of the same matrix and point to the same index,
             * false otherwise.
             */
            bool operator==(const iterator& it) const;

            /**
             * @param it iterator to compare with this iterator.
             * @return true if the iterators are of the same matrix and point to different index,
             * false otherwise.
             */
            bool operator!=(const iterator& it) const;
    };

    /**
    * Iterator Class for iterating const matrices
    */
    template <class T>
    class Matrix<T>::const_iterator {
        private:
            const Matrix<T>* matrix; //pointer to the const matrix instance.
            int index; //current index of iteration.

            /**
             * Constructor.
             * @param matrix pointer to the const matrix to iterate.
             * @param index starting index of iterating.
             * @return new iterator instance for a certain const matrix.
             */
            const_iterator(const Matrix<T>* matrix, int index);
            friend class Matrix<T>;
        public:

            /**
             * Default Copy constructor.
             * Created by the compiler
             */
            const_iterator(const const_iterator&) = default;

            /**
             * Default = opeartor.
             * Created by the compiler
             */
            const_iterator& operator=(const const_iterator&) = default;

            /**
             * @return const refreance to the current entry of the matrix in the iteration. 
             */
            const T& operator*() const;

            /** 
             * Advance the index by 1.
             * @return refreance to the iterator with advanced index. 
             */
            const_iterator& operator++();

            /**
             * Advance the index by 1.
             * @return Instance of the iterator with the previous index. 
             */
            const_iterator operator++(int);

            /**
             * @param it iterator to compare with this iterator.
             * @return true if the iterators are of the same matrix and point to the same index,
             * false otherwise.
             */
            bool operator==(const const_iterator& it) const;

            /**
             * @param it iterator to compare with this iterator.
             * @return true if the iterators are of the same matrix and point to different index,
             * false otherwise.
             */
            bool operator!=(const const_iterator& it) const;        
    };

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

    template <class T>
    Matrix<T>::Matrix(const Matrix& matrix) : 
        dimensions(matrix.dimensions.getRow(), matrix.dimensions.getCol()),
        data(new T[matrix.dimensions.getRow() * matrix.dimensions.getCol()]) {
        for (int i = 0 ; i < size() ; i++) {
            data[i] = matrix.data[i];
        }
    }

    template <class T>
    Matrix<T>::~Matrix() {
        delete[] data;
    }

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

    template <class T>
    Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix) {
        T *temp = new T[matrix.dimensions.getRow() * matrix.dimensions.getCol()];
        for (int i = 0 ; i < matrix.size() ; i++) {
            temp[i] = matrix.data[i];
        }
        delete[] data;
        data = temp;
        dimensions = Dimensions(matrix.dimensions.getRow(),matrix.dimensions.getCol());
        return *this;
    }

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

    template <class T>
    Matrix<T>& Matrix<T>::operator+=(T t){
        for (int i = 0; i < size() ; i++) {
            data[i] += t;
        }
        return *this;  
    }

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
        if (row < 0 || column < 0 ||row >= height() || column >= width()) {
            throw AccessIllegalElement();
        }

        return data[(row * width()) + column]; 
    }
    
    template <class T>
    const T& Matrix<T>::operator()(int row, int column) const {
        // error checking
        if (row < 0 || column < 0 ||row >= height() || column >= width()) {
            throw AccessIllegalElement();
        }

        return data[(row * width()) + column];
    }
    
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
    Matrix<T> operator+(Matrix<T> MatrixA , Matrix<T> MatrixB) {
        Matrix<T> newMatrix = MatrixA;
        newMatrix += MatrixB;
        return newMatrix;
    }
    
    template <class T>
    Matrix<T> operator+(T t , const Matrix<T> matrix) {
        Matrix<T> plusMatrix(Dimensions(matrix.height(), matrix.width()), t);
        return plusMatrix += matrix;  
    }

    template <class T>
    Matrix<T> operator+(const Matrix<T> matrix, T t) {
        Matrix<T> plusMatrix(matrix);
        return plusMatrix += t;
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
    
    template <class T>
    bool all(const Matrix<T> matrix) {
        for (T t : matrix) {
            if (static_cast<bool>(t) == false) {
                return false;
            }
        }
        return true;
    }

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
        if (index < 0 || index >= matrix->size()) {
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
        if (index < 0 || index >= matrix->size()) {
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
