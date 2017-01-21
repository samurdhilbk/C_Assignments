/*
   cipher.c

   Sample program for COMP1917 Lab 8
*/

#include <stdio.h>

#include "vigenere.h"

char key[MAX_KEY];

int main( void )
{
  int ch;

  printf("Enter key: ");
  scanf( "%s",  key );

  printf("Enter text:\n");
  while(( ch = getchar()) != EOF ) {
     encrypt( ch );
  }
  printf( "\n" );

  return 0;
}
