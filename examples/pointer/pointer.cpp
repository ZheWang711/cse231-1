int f(int x){
  
  // Purely local
  int a = 10;
  int* b = &a;
  *b = 5;
  int c = *b;
  
  
  // Non-local
  int* y = &x;
  int** z = &y;
  int* y_copy = y;
  int k = *y;
  *y_copy = 10;
  return k;
}