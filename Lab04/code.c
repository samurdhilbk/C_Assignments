#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure to store details of a student
typedef struct _{
	int batch;
	int regNo;
	char firstName[20];
	char lastName[20];
	float cGPA;
}student;

student students[1000];	//declare an array of 1000 variables of type student
int size=0;	//variable which keeps track of the current size of the students register(array)

//function to add students to the array
void addStudent(student st){
	students[size]=st;	//add st next to the last occupied position in the array
	size++;	//increment the array size
	return;
}

void removeStudent(int batch,int regNo){	//function to remove a student with a specified regiatation number
	int i;
	
	int index=-1;	//varibale to store the index of the student in the array if such a student exists

	for(i=0;i<size;i++){	//find whether there is such a student in the current register
		student st=students[i];
		if(st.batch==batch && st.regNo==regNo){
			index=i;	//set the index to current index
			break;	//break the loop since the respective student has been found
		}
	}

	if(index==-1){ //if the index variable hasn't been changed
		printf("Error: There is no such student in the register\n");	//it means that there is no such student, so terminate function after an error message
		return;
	}
 
    for(i=index;i<size;i++) {	//if there is such student, then move each student in the array after the specified student, to the previous place in the array
    	students[i]=students[i+1];	
    }
    size--;	//decrement the array size
    return;
}

void printStudent(int batch,int regNo){	//function to print the details of a given student
	int i;
	for(i=0;i<size;i++){	//search for the specified student
		student st=students[i];
		if(st.batch==batch && st.regNo==regNo){
			printf("The student %s %s(E/%d/%d) has a cumulative GPA of %f\n",st.firstName,st.lastName,st.batch,st.regNo,st.cGPA); //if student is found display his/her details
			return;
		}
	}
	printf("Error: There is no such student in the register\n");	//if not found display an error message and terminate function
	return;
}

void printAll(){	//a function to print the details of all the students in the current register, one by one
	int i;
	if(size==0){	//if  the array is empty
		printf("Error: There are no students in the register\n");	//print error message and terminate function
		return;
	}
	for(i=0;i<size;i++){	//iterate through each student
		student st=students[i];
		printf("The student %s %s(E/%d/%d) has a cumulative GPA of %f\n",st.firstName,st.lastName,st.batch,st.regNo,st.cGPA);	//print the details of current student
	}
	return;
}

int* checkReg(char * reg){	//function to extract batch and ENO from input and also detect any errors in the input format
	int i;
	static int st[2];
	if(reg[0]!='E' && reg[0]!='e'){	//if the first character is not either 'E' or 'e' print error message and terminate the function
		printf("Please Enter a Valid Registration Number 1\n");
		st[1]=0;
		return st;
	}
	int slashCount=0,slash1,slash2;	//varibales to keep the number of slashes, and the location of the first and second slashes
	for(i=0;i<strlen(reg);i++){
		if(reg[i]=='/'){
			slashCount++;
			if(slashCount==1) slash1=i;
			if(slashCount==2) slash2=i;
		}
		if(slashCount>2){	//if the number of slashes is more than 2, then there is an error in the input format
			printf("Please Enter a Valid Registration Number 2\n");
			st[1]=0;
			return st;
		}
	}
	char batchStr[10],regNoStr[10];	//char buffers to keep the batch and number as strings
	for(i=slash1+1;i<slash2;i++) batchStr[i-slash1-1]=reg[i];
	batchStr[slash2-slash1-1]='\0';
	for(i=slash2+1;i<strlen(reg);i++) regNoStr[i-slash2-1]=reg[i];
	regNoStr[strlen(reg)-slash2-1]='\0';
	//convert the strings to numbers
	st[0]=atoi(batchStr);	
	st[1]=atoi(regNoStr);
	return st;
}

int main(){
	int command=1;	//variable to store the current command
	while(command!=0){	//if command is not zero continue otherwise stop program
		printf("------------------------------------------\n");
		printf("VOLATILE STUDENT RECORD MAINTENANCE SYSTEM\n");
		printf("------------------------------------------\n");
		printf("0. Quit\n");
		printf("1. Insert a Student Record\n");
		printf("2. Print a Student Record\n");
		printf("3. Print All Student Records\n");
		printf("4. Delete a Student Record\n");

		scanf("%d",&command);

		if(command==1){	//if command is 1 then request for student details, store them in a student variable and thar variale to the array
			student st;
			printf("Enter the batch(11/12/13/14): ");
			scanf("%d",&st.batch);
			printf("Enter the registration number: ");
			scanf("%d",&st.regNo);
			printf("Enter the first name: ");
			scanf("%s",st.firstName);
			printf("Enter the last name: ");
			scanf("%s",st.lastName);
			printf("Enter the cumulative GPA: ");
			scanf("%f",&st.cGPA);
			addStudent(st);
		}
		else if(command==2){	//if the command is 2, request the required registration number and print the details of that student
			char reg[10];
			printf("Enter the registration number: ");
			scanf("%s",reg);
			int* st=checkReg(reg);
			if(!st[1]) continue;
			printStudent(st[0],st[1]);
		}
		else if(command==3){	//if the command is 3, print the details of all the students in the current register
			printAll();
		}
		else if(command==4){	//if the command is 4, request for the required registration number and remove that student's record from the array
			char reg[10];
			printf("Enter the registration number: ");
			scanf("%s",reg);
			int* st=checkReg(reg);
			if(!st[1]) continue;
			removeStudent(st[0],st[1]);
		}
		else if(command!=0){	//if the command is not either of 0,1,2,3,4 print error message
			printf("Error: Please Enter a Valid Command\n");
		}
	}
	return 0;
}