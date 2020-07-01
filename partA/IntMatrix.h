#ifndef EX3_INTMATRIX_H
#define EX3_INTMATRIX_H
#include "Auxiliaries.h"
#include <iostream>

namespace mtm {
    /**
     * Class for Integer base matrices
     */
    class IntMatrix {
    private:
        mtm::Dimensions dimensions; //dimensions of the matrix
        int* data; //int array to store matrix entry data.
    public:
        /**
         * Constructor.
         * @param dims the deimensions of the Matrix.
         * @param num default value for every entry of the matrix. 
         *              Set to 0 of no other value is passed.
         * @return new IntMatrix instance.
         */
        IntMatrix(Dimensions dims, int num = 0);

        /**
         * Copy constructor.
         * @param intMatrix matrix to copy.
         * @return new IntMatrix instance identical to mat.
         */
        IntMatrix(const IntMatrix& intMatrix);

        /**
         * Destructor.
         * Clean IntMatrix resources.
         */
        ~IntMatrix();

        /**
         * @param dim positive size of a square matrix.
         * @return Identity matrix of size dim x dim.
         */
        static IntMatrix Identity(int num);

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
         * @return the transpose matrix of the matrix
         */
        IntMatrix transpose() const;

        /**
         * = operator
         * @param other matrix to be equal to.
         * @return refreance to this IntMatrix instance now identical to other.
         */
        IntMatrix& operator=(const IntMatrix& intMatrix); 

        /**
         * @param intMatrix matrix to add.
         * @return this matrix after addition of these 2 matrices.
         */
        IntMatrix& operator+=(const IntMatrix& intMatrix);

        /**
         * @param num scalar to add to the matrix.
         * @return sum of the matrix and the scalar.
         */
        IntMatrix& operator+=(int num);

        /**
         * @return negative matrix of the matrix.
         */
        IntMatrix operator-() const;

        //friend declartion. real declartion outside the class.
        friend std::ostream& operator<<(std::ostream& os, const IntMatrix& intMatrix);

        /**
         * @param row row index of the non-const matrix.
         * @param col ocolumn index of the non-const matrix.
         * @return the element of the non-const matrix in the row and column index.
         */
        int& operator()(int row, int column);

        /**
         * @param row row index of the const matrix.
         * @param col ocolumn index of the const matrix.
         * @return the element of the const matrix in the row and column index.
         */
        const int& operator()(int row, int column) const;

        /**
         * @param num number to compare with matrix entries.
         * @return IntMatrix the same size as the matrix with 1 at the entries that
         * not equal to num, and 0 for the entry that doesn't.
         */
        IntMatrix operator!=(int num) const;
        
        /**
         * @param num number to compare with matrix entries.
         * @return IntMatrix the same size as the matrix with 1 at the entries that
         * equal to num, and 0 for the entry that doesn't.
         */
        IntMatrix operator==(int num) const;
        
        /**
         * @param num number to compare with matrix entries.
         * @return IntMatrix the same size as the matrix with 1 at the entries that smaller
         * than num, and 0 for the entry that doesn't.
         */
        IntMatrix operator<(int num) const;
        
        /**
         * @param num number to compare with matrix entries.
         * @return IntMatrix the same size as the matrix with 1 at the entries that bigger
         * than num, and 0 for the entry that doesn't.
         */
        IntMatrix operator>(int num) const;

        /**
         * @param num number to compare with matrix entries.
         * @return IntMatrix the same size as the matrix with 1 at the entries that
         * smaller or equal to num, and 0 for the entry that doesn't.
         */
        IntMatrix operator<=(int num) const;

        /**
         * @param num number to compare with matrix entries.
         * @return IntMatrix the same size as the matrix with 1 at the entries that
         * bigger or equal to num, and 0 for the entry that doesn't.
         */
        IntMatrix operator>=(int num) const;

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
    };
    /**
     * @param intMatrixA first matrix to add.
     * @param intMatrixB first matrix to add.
     * @return sum of these 2 matrices.
     */
    IntMatrix operator+(const IntMatrix intMatrixA , const IntMatrix intMatrixB);

    /**
     * Symmetry definition
     * @param num number to add to all the matrix elements.
     * @param intMatrix matrix to add the scalar to.
     * @return sum of the scalar to all matrix elements.
     */
    IntMatrix operator+(int num , const IntMatrix intMatrix);

    /**
     * Symmetry definition
     * @param intMatrix matrix to add the scalar to.
     * @param num number to add to all the matrix elements.
     * @return sum of the scalar to all matrix elements.
     */
    IntMatrix operator+(const IntMatrix intMatrix, int num);

    /**
     * @param intMatrixA matrix to subtract from.
     * @param intMatrixB matrix to subtract.
     * @return subtraction of these 2 matrices.
     */
    IntMatrix operator-(const IntMatrix intMatrixA , const IntMatrix intMatrixB);

    /**
     * @param os output stream.
     * @param intMatrix matrix to print.
     * @return print the matrix.
     */
    std::ostream& operator<<(std::ostream& os, const IntMatrix& intMatrix);

    /**
     * @return True if every entry of the matrix is different than 0,
     * False otherwise.
     */
    bool all(const IntMatrix intMatrix);

    /**
     * @return True if one entry of the matrix is different than 0,
     * False otherwise.
     */
    bool any(const IntMatrix intMatrix);

    /**
     * Iterator Class for iterating non-const int matrices
     */
    class IntMatrix::iterator {
        private:
            IntMatrix* intMatrix; //pointer to the IntMatrix instance.
            int index; //current index of iteration.

            /**
             * Constructor.
             * @param intMatrix pointer to the matrix to iterate.
             * @param index starting index of iterating. Set to 0 by default.
             * @return new iterator instance for a certain matrix.
             */
            iterator(IntMatrix* intMatrix, int index);
            friend class IntMatrix;
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
            int& operator*() const;

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
     * Iterator Class for iterating const int matrices
     */
    class IntMatrix::const_iterator {
        private:
            const IntMatrix* intMatrix; // a pointer to the matrix that is about to get iterated
            int index; // current index of iteration 
            
            /**
             * Constructor.
             * @param int_matrix pointer to the const matrix to iterate.
             * @param index starting index of iterating.
             * @return new iterator instance for a certain const matrix.
             */
            const_iterator(const IntMatrix* intMatrix, int index);
            friend class IntMatrix;
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
            const int& operator*() const;

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
}

#endif //EX3_INTMATRIX_H
