/*
Authored by E/13/181
*/
#include <stdio.h> //include stdio.h so that fprintf() can be used

#define INT_MAX 2147483647 //maximum value that can be stored in a 32 bit signed integer
#define INT_MIN -2147483648 //minimum value that can be stored in a 32 bit signed integer

typedef long long ll; //define the type long long as ll

int i; //counter to index for loops
int int_32; //32-bit integer store the 32-bit length inputs
ll int_64; //64-bit integer to store the 64-bit length inputs
char bin[64]; //char array to handle the binary ouputs
int bitlength; //variable to store the bitlength assosciated with option 1

int absolute(int index) { //function to return the absolute value of an integer
    if (index >= 0) return index;
    else return (-1) * index;
}

int power(int base, int index) { //function to return the power of an integer to an integer base
    int ret = 1;
    int j;
    for (j = 0; j < index; j++) ret *= base;
    return ret;
}

float fpower(float base, int index) { //function to return the power of a float to an integer base
    float ret = 1.0f;
    int j;
    for (j = 0; j < absolute(index); j++) ret *= base;
    if (index >= 0) return ret;
    return 1.0f / ret;
}

double dpower(double base, int index) { //function to return the power of a double to an integer base
    double ret = 1.0;
    int j;
    for (j = 0; j < absolute(index); j++) ret *= base;
    if (index >= 0) return ret;
    return 1.0 / ret;
}

int strlength(char * buff) { //function to return the length of a string(char array) upto the null terminating character
    int ret = 0; //return valure, the length of the string
    int i = 0;
    while (buff[i++] != '\0') ret++; //until the null terminating character is reached, increment the return value
    return ret;
}

double string_to_double(char * buff) { //function to get the equivalent double value of a string denoting a double value
    double ret = 0.0;
    int i;
    if (buff[0] != '-') { //if the double value is negative
        int y = strlength(buff), u = 0; //u is the length of the whole number part of the floating point value
        for (i = 0; i < y; i++) { //until the decimal point is found, increment u
            if (buff[i] == '.') break;
            u++;
        }
        for (i = 0; i < u; i++) ret += (double)(buff[i] - '0') * dpower(10.0f, u - i - 1); //calculate the whole number part of the floating point value
        for (i = u + 1; i < y; i++) ret += (double)(buff[i] - '0') * dpower(10.0f, u + 1 - i - 1); //calculate the fractional part of the floating point value
    } else { //if the double value is zero or positive
        int y = strlength(buff), u = 0; //u is the length of the whole number part of the floating point value
        for (i = 1; i < y; i++) { //until the decimal point is found, increment u
            u++;
            if (buff[i] == '.') break;
        }
        for (i = 1; i < u; i++) ret += (double)(buff[i] - '0') * dpower(10.0f, u - i - 1); //calculate the whole number part of the floating point value
        for (i = u + 1; i < y; i++) ret += (double)(buff[i] - '0') * dpower(10.0f, u + 1 - i - 1); //calculate the fractional part of the floating point value
        ret = ret * (-1.0f); //multiply by -1 to get the negative value
    }
    return ret;
}

float getFloor(char * buff) { //function to find the floor value of a floating point value
    int j = 0;
    char temp[1000]; //temporary buffer to hold the string representation of the floor value of the floating point number
    while (buff[j] != '.') { //until you reach the decimal point, add the digits to the temporary buffer
        temp[j] = buff[j];
        j++;
    }
    temp[j] = '.'; //add the decimal point
    temp[j + 1] = '0'; //add a zero after the decimal point
    temp[j + 2] = '\0'; //add the null terminating character
    return (float)string_to_double(temp); //get the corresponding floating point number and return it
}

int string_to_int(char * buff) { //function to return the corresonding int value of a string denoting an integer
    int len = strlength(buff); //number of digits in the int
    int j, ret = 0;
    if (buff[0] != '-') { //for non-negative numbers
        for (j = 0; j < len; j++) ret += power(10, (len - 1 - j)) * (buff[j] - '0'); //multiply digit by the appropriate power of 10 and add
    } else { //for negative numbers
        for (j = 1; j < len; j++) ret += power(10, (len - j - 1)) * (buff[j] - '0'); //multiply digit by the appropriate power of 10 and add
        ret = ret * (-1); //multiply by -1 to get the negative value
    }
    return ret;
}

/*
Function to return the bitlength assosciated with option 1 or option 2.

Index is 0 for option 1 and non-zero for option 2.
*/
int getBitLength(char opt, char * * argv, int index) {
    if (opt == 'H') {
        if (index == 0) return strlength(argv[3]) * 4;
        else return bitlength;
    } else if (opt == 'B') {
        if (index == 0) return strlength(argv[3]);
        else return bitlength;
    } else if (opt == 'I' || opt == 'F') return 32;
    else return 64;
}

//function to handle some errors in the input
//returns 1 if there's an error and zero otherwise
int error_handle(int argc, char * * argv, int bitlength) {
    if (argc <= 3) { //print error message if the number of arguments is less than 3
        fprintf(stderr, "ERROR: The number of arguments is wrong.\n");
        fprintf(stderr, "Usage: ./binconvert -<input format> -<output format> <input>\n");
        return 1;
    }
    char opt1 = argv[1][1], opt2 = argv[2][1];
    if (!(opt1 == 'B' || opt1 == 'H' || opt1 == 'D' || opt1 == 'F' || opt1 == 'I')) { //chech for invalid input argument
        fprintf(stderr, "ERROR: The input argument is wrong.\n");
        fprintf(stderr, "Possible input arguments are -B, -H, -I, -F and -D.\n");
        return 1;
    }
    if (!(opt2 == 'B' || opt2 == 'H' || opt2 == 'D' || opt2 == 'F' || opt2 == 'I')) { //check for invalid ouput argument
        fprintf(stderr, "ERROR: The output argument is wrong.\n");
        fprintf(stderr, "Possible output arguments are -B, -H, -I, -F and -D.\n");
        return 1;
    }

    if (opt1 == 'B') { //check for format errors in binary inputs
        for (i = 0; i < bitlength; i++) {
            if (!((argv[3][i] == '0') || (argv[3][i] == '1'))) {
                fprintf(stderr, "ERROR: Input format error at location %d.\n", i);
                return 1;
            }
        }
    }
    if (opt1 == 'H') { //check for format errors in hex inputs
        for (i = 0; i < bitlength / 4; i++) {
            char c = argv[3][i];
            if (!((c >= 'A' && c <= 'F') || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) {
                fprintf(stderr, "ERROR: Input format error at location %d.\n", i);
                return 1;
            }
        }
    }
    if (opt1 == 'I') { //check for format errors in int inputs
        for (i = 0; i < strlength(argv[3]); i++) {
            char c = argv[3][i];
            if (!(c >= '0' && c <= '9')) {
                if (c == '-' && i == 0) continue;
                fprintf(stderr, "ERROR: Input format error at location %d.\n", i);
                return 1;
            }
        }
    }
    if (opt1 == 'F' || opt1 == 'D') { //check for format errors in floating point inputs
        int dotcount = 0;
        for (i = 0; i < strlength(argv[3]); i++) {
            char c = argv[3][i];
            if (!(c >= '0' && c <= '9')) {
                if (c == '-' && i == 0) continue;
                if (c == '.' && dotcount == 0) {
                    dotcount++;
                    continue;
                }
                fprintf(stderr, "ERROR: Input format error at location %d.\n", i);
                return 1;
            }
        }
    }

    if (bitlength != 32 && bitlength != 64) { //check whether the input size is not either of 32 or 64 bit length
        fprintf(stderr, "ERROR: The input size is wrong.\n");
        return 1;
    }

    int bitlength2 = getBitLength(opt2, argv, 1); //get the corresponding bit length of the second option
    if (bitlength != bitlength2) { //check if the conversion is intended for unequal bitlengths
        fprintf(stderr, "ERROR: This conversion is not possible.\n");
        return 1;
    }
    return 0;
}

int alphtoint(char c) {
    int y;
    if (c <= 'Z' && c >= 'A') { //if the hexadecimal character is an uppercase letter
        y = c - ('A' - 10); //subtract the ASCII value of 'A' to get the numerical value of the character
    } else if (c <= 'z' && c >= 'a') { //if the hexadecimal character is a lowercase letter
        y = c - ('a' - 10); //subtract the ASCII value of 'a' to get the numerical value of the character
    } else y = c - '0'; //if the hexadecimal character is a number subtract the ASCII value of '0' to get the numerical value of the character
    return y;
}





int main(int argc, char * * argv) {

    char opt1 = argv[1][1], opt2 = argv[2][1];
    bitlength = getBitLength(opt1, argv, 0);
    if (error_handle(argc, argv, bitlength)) return 1;
    for (i = 0; i < 64; i++) bin[i] = '0'; //initialize the bin array to all zero characters


    //handle the input	


    if (opt1 == 'H') { //if first option is -H
        if (bitlength == 64) {
            int_64 = 0LL;
            for (i = 0; i < 16; i++) int_64 += (ll)alphtoint(argv[3][i]) * (ll)dpower(16.0, 15 - i); //multiply numerical value of digit by the appropriate power of 16 and add
        } else {
            int_32 = 0;
            for (i = 0; i < 8; i++) {
                int_32 += alphtoint(argv[3][i]) * power(16, 7 - i); //multiply numerical value of digit by the appropriate power of 16 and add
            }
        }
    } else if (opt1 == 'B') { //if first option is -B
        if (bitlength == 32) {
            int_32 = 0;
            for (i = 0; i < 32; i++) { //find this integral value
                int_32 += (argv[3][i] - '0') * (int)fpower(2.0f, (float)(31 - i)); //multiply digit by the appropriate power of 2 and add
            }
        } else {
            int_64 = 0LL;
            for (i = 0; i < 64; i++) { //find this integral value
                int_64 += (argv[3][i] - '0') * (ll)dpower(2.0, (double)(63 - i)); //multiply digit by the appropriate power of 2 and add
            }
        }
    } else if (opt1 == 'I') { //if first option is -I
        int_32 = string_to_int(argv[3]); //convert the string representing the integer to an int
    } else if (opt1 == 'D') {
        double f = string_to_double(argv[3]); //convert the string to the equivalent double value
        //this first casts the double pointer to a long long pointer and then dereferences that long long pointer
        //what it effectively does is copy the 64-bits in the double variable to a long long variable and then read that long long variable as a long long value
        int_64 = * (ll * ) & f;
    } else { ////if first option is -F
        float f = (float)string_to_double(argv[3]); //convert the string to the equivalent float value
        //this first casts the float pointer to an int pointer and then dereferences that int pointer
        //what it effectively does is copy the 32-bits in the float variable to an int variable and then read that int variable as an int value
        int_32 = * (int * ) & f;
    }


    //handle the output


    if (opt2 == 'H') { //if the second argument is -H
        if (bitlength == 32) {
            fprintf(stdout, "0x%08X\n", int_32); //print out the hex representaion of int_32 set to a field-width of 8 padded with zeros
        } else {
            fprintf(stdout, "0x%016llX\n", int_64); //print out the hex representaion of int_64 set to a field-width of 16 padded with zeros
        }
    } else if (opt2 == 'B') { //if the second argument is -B 
        if (opt1 == 'B') fprintf(stdout, "%s\n", argv[3]); //if the first option is also -B just print out argv[3]
        else {
            if (bitlength == 32) {
                int j;
                for (j = 0; j < 32; j++) { //read the bits of int_32
                    if (((1 << j) & int_32) == 0) bin[31 - j] = '0'; //bitwise AND int_32 with 1 bit-shifted by j(this will give 1 if the jth bit of int_32 from the right is 1 and 0 if not)
                    else bin[31 - j] = '1';
                }
                for (i = 0; i < 32; i++) fprintf(stdout, "%c", bin[i]);
                fprintf(stdout, "\n");
            } else {
                ll j;
                for (j = 0; j < 64; j++) { //read the bits of int_64
                    if (((1LL << j) & int_64) == 0) bin[63 - j] = '0'; //bitwise AND int_64 with 1 bit-shifted by j(this will give 1 if the jth bit of int_64 from the right is 1 and 0 if not)
                    else bin[63 - j] = '1';
                }
                for (i = 0; i < 64; i++) fprintf(stdout, "%c", bin[i]);
                fprintf(stdout, "\n");
            }
        }
    } else if (opt2 == 'I') { //if the second argument is -I
        if (opt1 == 'F') {
            float checkFloat = getFloor(argv[3]); //a temporary float value to check the compatibiltiy of the integral part of the float with the bounds of int
            if (checkFloat > (float)INT_MAX || checkFloat < (float)INT_MIN) { //check whether the integeral part of the floating point value is out of bounds in comparison to the minimum and maximum int values
                fprintf(stderr, "ERROR: This conversion is not possible.\n");
                return 1;
            }
            fprintf(stderr, "WARNING: There is a possibility for a precision loss.\n");
            fprintf(stdout, "%d\n", (int)checkFloat); //if the integeral part is within the bounds of int, print out the integer 
        } else {
            fprintf(stdout, "%d\n", int_32); //if first option is -H,-B or -I just print out int_32
        }
    } else { //if the second argument is -F or -D
        if (opt1 == 'I') {
            fprintf(stdout, "%.2f\n", (float)string_to_int(argv[3])); //	if the first argument was -I, print out the corresponding float value to two decimal places
            return 0;
        } else {
            if (bitlength == 32) {
                //this first casts the int pointer to a float pointer and then dereferences that float pointer
                //what it effectively does is copy the 32-bits in the int variable to a float variable and then read that float variable as a float value
                fprintf(stdout, "%.2f\n", * (float * ) & int_32); //calculate final value and print the final answer to two decimal places
            } else {
                //this first casts the long long pointer to a double pointer and then dereferences that double pointer
                //what it effectively does is copy the 64-bits in the long long variable to a double variable and then read that double variable as a double value
                fprintf(stdout, "%.6lf\n", * (double * ) & int_64); //calculate final value and print the final answer to six decimal places
            }
        }
    }
    return 0;
}