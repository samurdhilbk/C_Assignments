#include <bigint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main()
{
  int i, f; 
  for(f = 1; f < 50; f++) {
    int a, b, fib; 
    for(i=2, a = 1, b = 1, fib = 1; i < f; i++) { 
      fib = a + b; 
      a = b; 
      b = fib; 
    }

    printf("%d the Fib is %d", f, fib);

  } // end for(fib=10..)

  return 0; 
}
  
  
