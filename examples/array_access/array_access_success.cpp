int f(int x){
  int a[10];
  int i = 0;
  int z = 0;
  while (i < 6) {
    a[i] = 2;
    i = i + 1;
    z = z + 3;
  }
  if (z < 10){
    if (z >= 0){
      a[z] = 20;
    }
  }
  return a[3];
}
