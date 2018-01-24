main () {
    int sum_of_squares ;
    sum_of_squares = 0 ;
    int num ;
    num = 1 ;
    int max ;
    max = 5 ;
    bool flag ;
    flag = true ;

    while (flag) {
      sum_of_squares = sum_of_squares + num * num ;
      num = num + 1 ;
      if (num > max) {
      flag = false ;
      }
    }
    print(sum_of_squares) ;
    print ("\n") ;
}
