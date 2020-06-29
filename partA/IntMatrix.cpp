#include "IntMatrix.h"
#include <iostream>
using namespace mtm;

IntMatrix::IntMatrix(Dimensions dims, int num) : 
    dimensions(dims.getRow(), dims.getCol()),
    data(new int[dims.getRow() * dims.getCol()]) {
    for (int i = 0 ; i < size() ; i++) {
        data[i] = num;
    }
}

IntMatrix::IntMatrix(const IntMatrix& intMatrix) : 
    dimensions(intMatrix.dimensions.getRow(), intMatrix.dimensions.getCol()),
    data(new int[intMatrix.dimensions.getRow() * intMatrix.dimensions.getCol()]) {
    for (int i = 0 ; i < size() ; i++) {
       data[i] = intMatrix.data[i];
    }
}

IntMatrix::~IntMatrix() {
    delete[] data;
}

IntMatrix IntMatrix::Identity(int num) {
    IntMatrix identity(Dimensions(num, num));
    for(int i = 0; i < num; i ++) {
        identity(i,i) = 1 ;
    }
    return identity;
}

int IntMatrix::height() const {
    return dimensions.getRow();
}

int IntMatrix::width() const {
    return dimensions.getCol();
}

int IntMatrix::size() const {
    return height() * width();
}

IntMatrix IntMatrix::transpose() const {
    Dimensions transposedDimensions = Dimensions(dimensions.getCol(), dimensions.getRow());
    IntMatrix transposed = IntMatrix(transposedDimensions);

    for (int i = 0; i < height() ; i++) {
        for (int j = 0; j < width() ; j++) {
            transposed(j,i) = (*this)(i,j);
        }
    }
    return transposed;
}

IntMatrix& IntMatrix::operator=(const IntMatrix& intMatrix) {
    int* temp = new int[intMatrix.dimensions.getRow() * intMatrix.dimensions.getCol()];
    for (int i = 0 ; i < intMatrix.size() ; i++) {
        temp[i] = intMatrix.data[i];
    }
    delete[] data;
    data = temp;
    dimensions = Dimensions(intMatrix.dimensions.getRow(),intMatrix.dimensions.getCol());
    return *this;
}

IntMatrix& IntMatrix::operator+=(const IntMatrix& intMatrix) {
    for (int i = 0; i < size() ; i++) {
        data[i] += intMatrix.data[i];
    }
    return *this;
}

IntMatrix& IntMatrix::operator+=(int num) {
    for (int i = 0; i < size() ; i++) {
        data[i] += num;
    }
    return *this;
}

IntMatrix IntMatrix::operator-() const {
    IntMatrix minusMatrix(*this);
    for(int i = 0 ; i < size(); i++) {
        minusMatrix.data[i] = -data[i];
    }
    return minusMatrix;
}

int& IntMatrix::operator()(int row, int column) {
    return data[(row * width()) + column];
}

const int& IntMatrix::operator()(int row, int column) const {
    return data[(row * width()) + column];
}

IntMatrix IntMatrix::operator!=(int num) const{
    IntMatrix diffMatrix(dimensions, 0);
    for(int i = 0 ; i < size() ; i++ ){
        if(data[i] != num){
            diffMatrix.data[i]++;
        }
    }
    return diffMatrix;
}

IntMatrix IntMatrix::operator==(int num) const{
    IntMatrix equMatrix = operator!=(num);
    equMatrix = -equMatrix + 1;
    return equMatrix;
}

IntMatrix IntMatrix::operator<(int num) const{
    IntMatrix smallMatrix(dimensions, 0);
    for (int i = 0 ; i < size() ; i++ ) {
        if(data[i] < num){
            smallMatrix.data[i]++;
        }
    }
    return smallMatrix;
}

IntMatrix IntMatrix::operator>(int num) const{
    IntMatrix bigMatrix(dimensions, 0);
    for (int i = 0 ; i < size() ; i++ ) {
        if(data[i] > num){
            bigMatrix.data[i]++;
        }
    }
    return bigMatrix;
}

 IntMatrix IntMatrix::operator<=(int num) const {
    IntMatrix newMatrix = operator>(num);
    newMatrix = -newMatrix + 1;
    return newMatrix; 
 }

IntMatrix IntMatrix::operator>=(int num) const {
    IntMatrix newMatrix = operator<(num);
    newMatrix = -newMatrix + 1;
    return newMatrix;
}

mtm::IntMatrix::iterator IntMatrix::begin() {
    return mtm::IntMatrix::iterator(this, 0);
}

mtm::IntMatrix::iterator IntMatrix::end() {
    return mtm::IntMatrix::iterator(this, size());
}

IntMatrix::const_iterator IntMatrix::begin() const {
    return IntMatrix::const_iterator(this, 0);
}

IntMatrix::const_iterator IntMatrix::end() const {
    return IntMatrix::const_iterator(this, size());
}

IntMatrix mtm::operator+(IntMatrix intMatrixA , IntMatrix intMatrixB) {
    IntMatrix newIntMatrix = intMatrixA;
    newIntMatrix += intMatrixB;
    return newIntMatrix;
}

IntMatrix mtm::operator+(int num , const IntMatrix intMatrix) {
    IntMatrix plusMatrix(intMatrix);
    return plusMatrix += num;    
}

IntMatrix mtm::operator+(const IntMatrix intMatrix, int num) {
    return num + intMatrix;
}

IntMatrix mtm::operator-(IntMatrix intMatrixA , IntMatrix intMatrixB) {
    IntMatrix newIntMatrix = intMatrixA;
    newIntMatrix += -intMatrixB;
    return newIntMatrix;
}

std::ostream& mtm::operator<<(std::ostream& os, const IntMatrix& intMatrix) {
    os << printMatrix(intMatrix.data, intMatrix.dimensions);
    return os;
}

bool mtm::all(const IntMatrix intMatrix) {
    IntMatrix comparisonMatrix = (intMatrix == 0);
    for (int element : comparisonMatrix) {
        if (element == 1) {
            return false;
        }
    }
    return true;
}

bool mtm::any(const IntMatrix intMatrix) {
    IntMatrix comparisonMatrix = (intMatrix != 0);
    for (int element : comparisonMatrix) {
        if (element == 1) {
            return true;
        }
    }
    return false;
}

// iterator

IntMatrix::iterator::iterator(IntMatrix* intMatrix, int index) : 
    intMatrix(intMatrix), index(index) {}

int& IntMatrix::iterator::operator*() const {
    return intMatrix->data[index];
}

IntMatrix::iterator& IntMatrix::iterator::operator++() {
    ++index;
    return *this;
}

IntMatrix::iterator IntMatrix::iterator::operator++(int) {
    iterator result = *this;
    ++*this;
    return result;
}

bool IntMatrix::iterator::operator==(const iterator& it) const {
    return index == it.index;
}

bool IntMatrix::iterator::operator!=(const iterator& it) const {
    return !(*this == it);
}

// const_iterator

IntMatrix::const_iterator::const_iterator(const IntMatrix* intMatrix, int index) : 
    intMatrix(intMatrix), index(index) {}

const int& IntMatrix::const_iterator::operator*() const {
    return intMatrix->data[index];
}

IntMatrix::const_iterator& IntMatrix::const_iterator::operator++() {
    ++index;
    return *this;
}

IntMatrix::const_iterator IntMatrix::const_iterator::operator++(int) {
    const_iterator result = *this;
    ++*this;
    return result;
}

bool IntMatrix::const_iterator::operator==(const const_iterator& it) const {
    return index == it.index;
}

bool IntMatrix::const_iterator::operator!=(const const_iterator& it) const {
    return !(*this == it);
}
