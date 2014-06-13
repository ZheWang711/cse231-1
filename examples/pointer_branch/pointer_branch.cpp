int f(int x){
  // Purely local
  int a_1 = 10;
  int a_2 = 15;
  int* b;
  if (a_1 > 4) {
    b = &a_1;
  }
  else{
    b = &a_2;
  }
  int** c = &b;
  **c = 5;
  return a_1;
}