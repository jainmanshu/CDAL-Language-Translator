/*******************************************************************************
 * Name            : Matrix.cc
 * Project         : fcal
 * Module          : Codegeneration
 * Copyright       : 2017 CSCI3081W Students. All rights reserved.
 * Original Author : Himanshu Jain, Clement Tan
 *
 ******************************************************************************/
#include "include/Matrix.h"
#include <stdlib.h>
#include <fstream>

matrix::matrix(int i, int j) {
  rows = i;
  cols = j;
  data = new float *[rows];
  for (int p = 0 ; p < rows ; p++) {
    data[p] = new float[cols];
    for (int q = 0; q < cols; q++) {
     data[p][q] = 0.0;
}
}
}

matrix::matrix(const matrix& m) {
  rows = m.rows;
  cols = m.cols;
  data = new float *[rows];
  for (int p = 0 ; p < rows ; p++) {
      data[p] = new float[cols];
  for (int q = 0; q < cols; q++) {
       data[p][q] = *m.access(p, q);
}
}
}

int matrix::n_rows() {
  return rows;
}

int matrix::n_cols() {
  return cols;
}

float *matrix::access(const int i, const int j) const {
  return &data[i][j];
}

std::ostream& operator<<(std::ostream &os, matrix& m) {
  os << m.rows << " " << m.cols << "\n";
  for (int p = 0 ; p < m.rows ; p++) {
    for (int q = 0; q < m.cols; q++) {
     os << *(m.access(p, q)) << "  ";
}
os << "\n";
}
return os;
}

matrix& matrix::operator=(const matrix& m) {
  if (this->rows == m.rows && this->cols == m.cols) {
    for (int p = 0 ; p < m.rows ; p++) {
    for (int q = 0; q < m.cols; q++) {
         *(this->access(p, q)) = *m.access(p, q);
       }
     }
  } else {
    throw "Matrix cannot be Multiplied !! Must have same diminesion";
  }
  return *this;
}
matrix matrix::operator*(const matrix& m2) {
  matrix mymatrix(this->rows, m2.cols);
  for (int i = 0; i < this->rows ; i++) {
    for (int j = 0; j < m2.cols ; j++) {
      for (int k = 0; k < m2.cols; k++) {
       (*(mymatrix.access(i, j))) = (*(mymatrix.access(i, j)))  +
                (*(this->access(i, k)) * (*(m2.access(k, j))));
      }
    }
  }
  return mymatrix;
}

matrix matrix::matrix_read(std::string filename) {
  const char *fname = filename.c_str();
  std::ifstream infile(fname);
  int m, n;
  infile >> m;
  infile >> n;
  matrix mymatrix(m, n);
  for (int p = 0; p < m; p++) {
    for (int q = 0; q < n; q++) {
       infile >> *(mymatrix.access(p, q));
    }
  }
  infile.close();
  return mymatrix;
}
