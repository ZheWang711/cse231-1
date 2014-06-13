int f(){
  
  // Purely local
  int a_1 = 10;
  int a_2 = 15;
  int* b_1 = &a_1;
  int* b_2 = &a_2;
  while (a_1 < 100) {
    a_1 = a_1 + 1;
    *b_2 = a_1;
  }
  return a_2;
}