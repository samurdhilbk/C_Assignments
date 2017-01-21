#include <stdio.h>	//import standard I/O library
#include <stdlib.h>	//import standard library
#include <math.h>	//import the math.h header file 

int main(){

float a,b,c;	//define the coefficients
printf("Enter the coefficients: ");	//prompt for coefficients
scanf("%f %f %f",&a,&b,&c);	//accept the coefficients as input
float det,one,two;	//declare intermediate variables
det=b*b-4.0*a*c;	//calculate the determinant
if(det>0.0){	//if determinant is positive...
	one=(-1.0*b-sqrt(det))/(2.0*a);		//calculate smaller root	
	two=(-1.0*b+sqrt(det))/(2.0*a);		//calculate larger root
	printf("The solutions are: %.2f and %.2f\n",one,two);	//print the solutions
}
else if(det==0.0){	//if determinant is zero
	one=(-1.0*b)/(2.0*a);		//calculate the only root
	printf("The solution is: %.2f\n",one);	//print solution
}
else{		//if determinant is negative
	one=fabs(sqrt(-1.0*det)/(2.0*a));	//calculate the absolute value of the imaginary part
	two=(-1.0*b)/(2.0*a);			//calculate the real part
if(two==0.0) printf("The solutions are: -%.2fi and %.2fi\n",one,one);	//print solution if real part is zero 
else printf("The solutions are: %.2f-%.2fi and %.2f+%.2fi\n",two,one,two,one);		//print solution if real part is non-zero
}
}

