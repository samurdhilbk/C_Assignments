/*
Authored by: E/13/181
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
	int N;
	printf("Enter N:\n");
	scanf("%d",&N);
	int i,j;
	for(i=1;i<=N;i++){
		for(j=1;j<=i;j++){
			int y=(j%26==0)?26:j%26;
			printf("%c",'A'+y-1);
		}
		printf("\n");
	}
	for(i=N-1;i>=1;i--){
		for(j=1;j<=i;j++){
			int y=(j%26==0)?26:j%26;
			printf("%c",'A'+y-1);
		}
		printf("\n");
	}
	if(N!=0) printf("\n");
	return 0;
}