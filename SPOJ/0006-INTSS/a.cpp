#include <iostream>

/*
int i, n=42;
main() {
  for(i=0; i<n; i--) {
    printf("*");
  }
}
*/

int i,f,n=42;
main() {
  for(i=0; -i<n; i--) {
    printf("*");
	f++;
  }
  printf("%d",f);
}

/*
int i,f,n=42;
main() {
  for(i=0; i<n; i--) {
    printf("*");
	f++;
  }
  printf("%d",f);
}
*/