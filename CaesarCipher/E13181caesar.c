#include <stdio.h>
#include <limits.h>
#include <string.h>

int rotateLeft(int ch){
    if((ch<='Z' && ch>='A')||(ch<='z' && ch>='a')){ //check whether the character is alphabetical
        if(ch=='A') return 'Z'; //if it's A return Z
        else if(ch=='a') return 'z';    //if it's a return z
        else return ch-1; //else return previous character
    } 
    return ch;  //if not alphabeical just return the same character
}

int rotateRight(int ch){
    if((ch<='Z' && ch>='A')||(ch<='z' && ch>='a')){     //check whether the character is alphabetical
        if(ch=='Z') return 'A'; //if it's Z return A
        else if(ch=='z') return 'a';    //if it's z return a
        else return ch+1;   //else return next character
    } 
    return ch;  //if not alphabeical just return the same character
}

int encode(int ch,int shift){
    int i,j;
    //if shift is positive or zero rotate the character right "shift" number of times
    if(shift>=0){
        for(i=0;i<shift;i++) ch=rotateRight(ch);
        return ch;
    }
    //if shift is negative rotate the character left "shift" number of times
    for(j=0;j<(-1*shift);j++) ch=rotateLeft(ch);
    return ch;
}


int main() {
    int i,j;
    int shift;
    printf("Enter shift:");
    scanf("%d",&shift);
    char b;
    scanf("%c",&b);
    printf("Enter text:\n");
    char s[1000][1000]; //array of strings to store the inputs
    int count=0;
    while (1 == scanf("%[^\n]%*c", s[count])){  //scan till the scanf function returns an error
        count++;
    }
    printf("Here is the encoded text: \n");
    for(i=0;i<count;i++){
        int len=strlen(s[i]);   //get the length of the string
        for(j=0;j<len;j++) {
            printf("%c",encode(s[i][j],shift)); //for each character return its encoded value
        }
        if(i<count-1) printf("\n"); //for each string before the last print an endline(the last string will have an endline)
    }
    return 0;
}