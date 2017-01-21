#include <stdio.h>	//import standard I/O library
#include <stdlib.h>	//import standard library

int main(){
    int n;  //declare input as n
    int special=0;	//boolean variable to store whether n is special or not
    printf("Enter a number: ");     //prompt for input
    scanf("%d",&n);     //scan input to variable n
    printf("%d is ",n);       
    if(n%15==0){    //check if special
        printf("special");
        special=1;	//set special to true
    }
    else printf("not special ");
    if(n>999 || (n%5==0 && n%6==0 && n%18!=0)){     //check if scary
        if(n>999 && !(n%5==0 && n%6==0 && n%18!=0)) printf(", big and scary but not weird.\n");     //check if scary but not weird
        if(n<=999 && (n%5==0 && n%6==0 && n%18!=0)) printf(", weird and scary but not big.\n");     //check if scary but not big
        if(n>999 && (n%5==0 && n%6==0 && n%18!=0)){     //check if both weird and scary
            if(special)  printf(" , big, weird and scary.\n");    
            else printf(", big, weird and scary.\n");
        }
    }
    else{   //check if not scary
        if(special) printf(" but not scary.\n");   
        else printf("or not scary.\n");   
    } 
    
    return 0;
}

