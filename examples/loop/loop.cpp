int f(int x){
  int i = 0;
  while (i < 100){
    x = x + i;
    i = i + 1;
  }
  return x;
}
