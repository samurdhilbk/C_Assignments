/*
Authored by: E/13/181
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int occur(char * word, char * text){
	int count=0;
	char S[1000];
	char W[1000];
	int i;
	int curr=-1;
	for(i=0;i<strlen(text);i++){
		if((text[i]<='Z' && text[i]>='A')||(text[i]<='z' && text[i]>='a')||(text[i]==' ')) {
			curr++;
			if(text[i]<='Z' && text[i]>='A'){
				S[curr]=text[i]+'a'-'A';
			}
			else S[curr]=text[i];
		}
	}
	for(i=0;i<strlen(word);i++){
		if(word[i]<='Z' && word[i]>='A'){
			W[i]=word[i]+'a'-'A';
		}
		else W[i]=word[i];
	}
	//printf("%s\n",S);
	//printf("%s\n",W);
	i=0;
	while(i<strlen(S)){
		char u=(i==0)?' ':S[i-1];
		if(S[i]==W[0] && u==' '){
			int j=0;
			while(S[i]==W[j] && j<strlen(W)){
				i++;
				j++;
			}
			if(j==strlen(W) && (S[i]==' ' || i==strlen(S))) count++; 
		}
		i++;
	}
	return count;
}

int main(int argc,char** argv){
	char s[1000];
	char w[1000];
	scanf("%[^\n]%*c", s);
	scanf("%[^\n]%*c", w);
	printf("%d\n",occur(w,s));
	return 0;
}