#ifndef EX3_INTMATRIX_H
#define EX3_INTMATRIX_H
#include "Auxiliaries.h"
#include <iostream>

namespace mtm {
    class IntMatrix {
    private:
        mtm::Dimensions dimensions;
        int* data;
    public:
        IntMatrix(Dimensions dims, int num = 0);
        IntMatrix(const IntMatrix& intMatrix);
        ~IntMatrix();
        static IntMatrix Identity(int num);

    int height() const;
        int width() const;
        int size() const;
        IntMatrix transpose() const;
        IntMatrix& operator=(const IntMatrix& intMatrix); 
        IntMatrix& operator+=(const IntMatrix& intMatrix);
        IntMatrix& operator+=(int num);
        IntMatrix operator-() const;
        friend std::ostream& operator<<(std::ostream& os, const IntMatrix& intMatrix);
        int& operator()(int row, int column);
        const int& operator()(int row, int column) const;
        IntMatrix operator!=(int num) const;
        IntMatrix operator==(int num) const;
        IntMatrix operator<(int num) const;
        IntMatrix operator>(int num) const;
        IntMatrix operator<=(int num) const;
        IntMatrix operator>=(int num) const;

        class iterator;
        iterator begin();
        iterator end();

        class const_iterator;
        const_iterator begin() const;
        const_iterator end() const;
    };
    IntMatrix operator+(const IntMatrix intMatrixA , const IntMatrix intMatrixB);
    IntMatrix operator+(int num , const IntMatrix intMatrix);
    IntMatrix operator+(const IntMatrix intMatrix, int num);
    IntMatrix operator-(const IntMatrix intMatrixA , const IntMatrix intMatrixB);
    std::ostream& operator<<(std::ostream& os, const IntMatrix& intMatrix);
    bool all(const IntMatrix intMatrix);
    bool any(const IntMatrix intMatrix);

    class IntMatrix::iterator {
        private:
            IntMatrix* intMatrix;
            int index;
            iterator(IntMatrix* intMatrix, int index);
            friend class IntMatrix;
        public:
            iterator(const iterator&) = default;
            iterator& operator=(const iterator&) = default;
            int& operator*() const;
            iterator& operator++();
            iterator operator++(int);
            bool operator==(const iterator& it) const;
            bool operator!=(const iterator& it) const;
    };

    class IntMatrix::const_iterator {
        private:
            const IntMatrix* intMatrix;
            int index;
            const_iterator(const IntMatrix* intMatrix, int index);
            friend class IntMatrix;
        public:
            const_iterator(const const_iterator&) = default;
            const_iterator& operator=(const const_iterator&) = default;
            const int& operator*() const;
            const_iterator& operator++();
            const_iterator operator++(int);
            bool operator==(const const_iterator& it) const;
            bool operator!=(const const_iterator& it) const;
    };
}

#endif //EX3_INTMATRIX_H
