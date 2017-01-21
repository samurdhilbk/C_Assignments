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
struct _* next;
}student;

int size=0;	//variable which keeps track of the current size of the students register
student * students;
student * current;

//function to add students to the linked list
void addStudent(student st){
	current=(student*)malloc(sizeof(student));
	current->batch=st.batch;
	current->regNo=st.regNo;
	strcpy(current->firstName,st.firstName);
	strcpy(current->lastName,st.lastName);
	current->cGPA=st.cGPA;
	current->next=students;
	students=current;
	size++;	//increment the linked list size
	return;
}

void removeStudent(int batch,int regNo){	//function to remove a student with a specified regiatation number
	current=students;

	for(current=students;current!=NULL;current=current->next){
		if(current->next->batch==batch && current->next->regNo==regNo){		//if the next element in the linked list is the one to be deleted
			student * temp=current->next;	//temporary pointer to keep the address of the variable to be removed
			current->next=current->next->next;	//assign the address pointed to by the element to be deleted to the next pointer of the previous element
			free(temp);		//free the memory in the location currently occupied by the element to be removed
			return;
		}
	}

    size--;	//decrement the linked list size
    return;
}

void printStudent(int batch,int regNo){	//function to print the details of a given student

	current=students;

	for(current=students;current!=NULL;current=current->next){	//search for the specified student
		if(current->batch==batch && current->regNo==regNo){		//if the next element in the linked list is the one to be printed
			printf("The student %s %s(E/%d/%d) has a cumulative GPA of %f\n",current->firstName,current->lastName,current->batch,current->regNo,current->cGPA); //if student is found display his/her details
			return;
		}
	}
	printf("Error: There is no such student in the register\n");	//if not found display an error message and terminate function
	return;
}

void printAll(){	//a function to print the details of all the students in the current register, one by one

	if(size==0){	//if the register is empty
		printf("Error: There are no students in the register\n");	//print error message and terminate function
		return;
	}

	for(current=students;current!=NULL;current=current->next){	//iterate through each student
		printf("The student %s %s(E/%d/%d) has a cumulative GPA of %f\n",current->firstName,current->lastName,current->batch,current->regNo,current->cGPA); //if student is found display his/her details
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
	//convert the strings to students
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

		if(command==1){	//if command is 1 then request for student details, store them in a student variable and add it to the linked list
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
		else if(command==4){	//if the command is 4, request for the required registration number and remove that student's record from the linked list
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

	//free the linked list to prevent any memory leaks
	current=students;
	while(current!=NULL){	//iterate through each student
		student * temp=current;
		current=current->next;
		free(temp);	//free all the dynamically allocated memory to prevent any memory leaks
	}
	return 0;
}