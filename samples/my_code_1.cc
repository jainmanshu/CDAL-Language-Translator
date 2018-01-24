#include <iostream>
#include "include/Matrix.h"
#include <math.h>
using namespace std;
int main( ) {
matrix m2 ( matrix::matrix_read ("./samples/matrix_2.data") );
 matrix m1 ( matrix::matrix_read ("./samples/my_code_1.data") );
 int rows;
 rows = m1.n_rows();
;
 int columns;
 columns = m1.n_cols();
;
 int m2columns;
 m2columns = m2.n_cols();
;
 int m2rows;
 m2rows = m2.n_rows();
;
 matrix m3( rows,columns );
for (int i= 0;i< rows;i ++) {
for (int j= 0;j< columns;j ++) {
*(m3.access(i, j)) = (0) ; 
} 
} 
 m3 = ( m1 * m2);
 cout << m3 ;
 }
