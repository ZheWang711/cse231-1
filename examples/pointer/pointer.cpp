int f(){
  
  // Purely local
  int a_1 = 10;
  int a_2 = 15;
  int* b_1 = &a_1;   // b_1 --> a_1
  int* b_2 = &a_2;   // b_1 --> a_1, b_2 --> a_2
  int** c = &b_1;    // b_1 --> a_1, b_2 --> a_2, c --> b_1
  *c = b_2;          // b_1 --> a_1, b_1 --> a_2, b_2 --> a_2, c --> b_1
  
  return a_1;
}