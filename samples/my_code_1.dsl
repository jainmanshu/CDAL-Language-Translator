
main () {

matrix m2 = matrix_read ( "./samples/matrix_2.data" ) ;

matrix m1 = matrix_read ( "./samples/my_code_1.data" ) ;

int rows;
rows = n_rows(m1);
int columns;
columns = n_cols(m1);
int m2columns;
m2columns = n_cols(m2);
int m2rows;
m2rows = n_rows(m2);

matrix m3 [ rows : columns ] i: j = 0;

m3 = m1 * m2;

print (m3);
}
