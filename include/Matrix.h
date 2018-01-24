/*******************************************************************************
 * Name            : Matrix.h
 * Project         : fcal
 * Module          : Codegeneration
 * Copyright       : 2017 CSCI3081W Students. All rights reserved.
 * Original Author : Himanshu Jain, Clement Tan
 *
 ******************************************************************************/
#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

class matrix {
 public:
    matrix(int i, int j);
    matrix(const matrix& m);

    int n_rows();
    int n_cols();

    float *access(const int i, const int j) const;
    friend std::ostream& operator<<(std::ostream &os, matrix &m);
    matrix& operator=(const matrix&m);
    matrix operator*(const matrix& m2);

    static matrix matrix_read(std::string filename);

 private:
    matrix() { }
    int rows;
    int cols;

    /* Your implementation of "data" may vary.  There are ways in
       which data can be an array of arrays and thus simplify the
       access method, at the cost of complicating the process of
       allocating space for data.  The choice is entirely up to
       you. */
    float **data;
};

#endif  // PROJECT_INCLUDE_MATRIX_H_
