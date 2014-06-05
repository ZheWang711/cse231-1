int f(int x){
  int* y = &x;
  int** z = &y;
  int* y_copy = y;
  int k = *y;
  return k;
}
