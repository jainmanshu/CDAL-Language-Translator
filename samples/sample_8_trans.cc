#include <iostream>
#include "include/Matrix.h"
#include <math.h>
using namespace std;
int main ( ) {
    matrix m ( matrix::matrix_read ("./samples/sample_8.data") ) ;
    cout << m ;
}

