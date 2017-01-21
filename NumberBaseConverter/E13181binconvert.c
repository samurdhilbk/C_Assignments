/*
Authored by E/13/181
All 16 possible conversions have been implemented
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef long long ll;

int i;
char bin[32];

int main(int argc,char** argv){
    if(argc<=3){		//print error message if the number of arguments is less than 3
        printf("Error!\n");
        printf("Usage: ./binconvert -<input format> -<output format> <input>\n");
        return 1;
    }
	for(i=0;i<32;i++) bin[i]='0';	//initialize the bin array to all zero characters
	if(argv[1][1]=='H'){		//if first option is -H
		for(i=0;i<8;i++){
			char c=argv[3][i];
			int y;
			if(c>=65){	//if the hexadecimal character is a letter
				y=c-55;	//subtract the ASCII value of 'A' to get the numerical value of the character
			}
			else y=c-48;	//if the hexadecimal character is a number subtract the ASCII value of '0' to get the numerical value of the character
			int j;
			for(j=0;j<4;j++){	//convert the hexadecimal character to its binary value and store in bin
				bin[(i+1)*4-1-j]=y%2+48;
				y=(y-y%2)/2;
			}
		}
	}
	else if(argv[1][1]=='B'){	//if first option is -B
		for(i=0;i<32;i++){	//the equivalent binary value is the same so fill bin with arg[3]
			bin[i]=argv[3][i];
		} 
	}
	else if(argv[1][1]=='I'){	//if first option is -I
		int u=atoi(argv[3]);	//convert the string representing the integer to an int
		if(u>=0){	//if the integer is positive or zero convert to binary in the usual way and store in bin
			for(i=0;i<32;i++){
				bin[31-i]=u%2+48;
				u=(u-u%2)/2;
			}
		}
		else{	//if the integer is negative convert to the two's compliment representation
			int found=0;	//boolean to keep track of whether the rightmost set bit has been considered
			int p=abs(u);	//get the absolute value of the integer
			for(i=0;i<32;i++){	//convert p to its ordinary binary representation and store in bin
				bin[31-i]=p%2+48;
				p=(p-p%2)/2;
			}
			//converting to the two's compliment is equivalent to flipping all the bits and adding 1 to the resulting value. This means that all bits except the rightmost set bit will be flipped.
			for(i=31;i>=0;i--){	
				if(bin[i]=='1' && !found){	//if rightmost set-bit is found
					bin[i]='1';	//don't change that bit
					found=1;	//keep in mind that the rightmost set-bit has been found
				}
				else bin[i]=(bin[i]=='0')?'1':'0';	//flip all other bits
			}
		}
	}
	else {		////if first option is -I
		int one,two,three;
		float f=strtod(argv[3],NULL);	//convert the string to the equivalent float value
		if(argv[3][0]=='-'){
			bin[0]='1';	//if the value is negative first bit is zero
		}
		else {
			bin[0]='0';	//else first bit is one
		}
		if(f!=0.0){	//if value is not zero calculate the other bits
			f=(f>0.0)?f:(-1.0)*f;	//get the absolute value of f, since the sign has been taken care of
			if(f>=1.0) two=(int)floor(log10(f)/log10(2.0f))+127;	//calculate the exponent if number is greater than or equal to 1
			else two=-1*(int)ceil(1.0f/f)+1+127;	//calculate exponent if number is less than 1
			for(i=0;i<8;i++){	//convert the exponent to binary format and stor in the appropriate position 
				bin[8-i]=two%2+48;
				two=(two-two%2)/2;
			}
			two-=127;	//get the original value of two, for further reference
			int j=9;
			int a=(int)floor(f);	//the intger part of f
			float b=f-floor(f);	//the decimal part of f
			if(f>=1.0){	//if number is greater than or equal to 1 calculate the mantissa	
				while(j<24 && a>1){
					bin[j]=a%2+48;
					a=(a-a%2)/2;
					j++;
				}
				for(i=0;i<23-two;i++){
					b*=2;
					bin[j++]=(int)floor(b)+48;
					b=b-floor(b);
				}
			}
			else{	//if number is less than 1 calculate the mantissa
				float f1=b*(int)ceil(1.0f/f);	
				b=f1-floor(f1);
				for(i=0;i<23;i++){
					b*=2;
					bin[j++]=(int)floor(b)+48;
					b=b-floor(b);
				}
			}
		}
	}

	//handle the output

	if(argv[2][1]=='H'){	//if the second argument is -H
		printf("0x");
		for(i=0;i<8;i++){	//consider bin by blocks of 4-bits(8 such blocks) 
			int j=0;
			int val=0;
			for(j=0;j<4;j++){	//calculate the decimal value corresponding to this particular 4-bit block
				val+=(bin[4*i+j]-'0')*(int)pow(2.0f,(float)(3-j));
			}
			if(val<10) printf("%d",val);	//determine the hexadecimal character corresponding to the caluculated value and print it
			else printf("%c",55+val);
		}
		printf("\n");
	}
	else if(argv[2][1]=='B'){	//if the second argument is -B print out the contents of bin as it is
		if(argv[1][1]=='B') printf("%s",argv[3]);
		else for(i=0;i<32;i++) printf("%c",bin[i]);
		printf("\n");
	}
	else if(argv[2][1]=='I'){	//if the second argument is -I
		if(argv[1][1]=='F') printf("%d\n",(int)floor(strtod(argv[3],NULL)));	//if the first argument was F print out the integer as a floating point value
		else{
			ll ans=0L;	//define a long long to hold the raw integral value that the floating point representation corresponds to 
			for(i=0;i<32;i++){	//find this integral value
				ans+=(bin[i]-'0')*(int)pow(2.0f,(31-i));
			}
			if(bin[0]=='0'){	//if the number is positive ans is equal to the desired value
				printf("%lld\n",ans);
			}
			else{	//if the number is negative, then bin corrresponds to its two's compliment representaion so reverse the process of finding the two's compliment to get the integer value
				printf("-");
				printf("%lld\n",~(ans-1));	//substract one and flip all bits
			}
		}
	}
	else{	
		if(argv[1][1]=='I') printf("%f\n",(float)atoi(argv[3]));	//if the second argument is -F
		else{
			if(bin[0]=='1') printf("-");	//	check is the number is negative
			int exp=0;	//exponent	
			for(i=1;i<=8;i++){	//calculate the exponent(plus 127)
				exp+=(bin[i]-'0')*(int)pow(2.0f,(float)(8-i));
			}
			float th=1.0;	
			for(i=9;i<32;i++){	//caluculate the value corresponding to the mantissa
				th+=(bin[i]-'0')*pow(2.0f,(float)(-1-(i-9)));
			}
			printf("%f\n",th*pow(2.0f,(float)(exp-127)));	//calculate final value and print the final answer
		}
	}
	return 0;
}
