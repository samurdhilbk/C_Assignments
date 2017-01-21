#include <stdlib.h>
#include <string.h>

#define MAX 100000	//maximum size of the stack or queue

typedef struct _{	//struct for Stack
	int size;	//variable to hold the size of the Stack
	int * array;	//Array to keep the elements of the Stack
}Stack;

typedef struct __{	//struct for Queue
	int size;	//variable to hold the size of the Queue
	int * array;	//Array to keep the elements of the Queue
}Queue;

Stack* CreateStack(){
	static Stack* stack;		
	stack=(Stack*)malloc(sizeof(Stack));	//allocate memory to stack
	stack->size=0;	//ininitialize stack size to zero
	stack->array=(int*)malloc(sizeof(int)*MAX);	//allocate the maximum expected size of the Stack to the underlying array
	return stack;
}
int DeleteStack(Stack* stack){
	if(stack==NULL) return -1;
	free(stack); //free the memory allocated to the stack pointer
	return  0;
}

Queue* CreateQueue(){
	static Queue* Q;	//create a static Queue pointer(because we need to return it, if it was not static it would vanish after this function terminates)
	Q=(Queue*)malloc(sizeof(Queue));	//allocate memory to queue
	Q->size=0;	//ininitialize queue size to zero
	Q->array=(int*)malloc(sizeof(int)*MAX);	//allocate the maximum expected size of the Queue to the underlying array
	return Q;
}
int DeleteQueue(Queue* queue){
	if(queue==NULL) return -1;
	free(queue);	//free the memory allocated to the queue pointer
	return  0;
}

int StackPush(Stack* stack, int value){
	stack->size++;
	stack->array[stack->size-1]=value;	//assign 'value' to the next position in the array
	return 0;
}

int StackPop(Stack* stack, int* value){
	if(stack==NULL||stack->size==0) return -1;
	*value=stack->array[stack->size-1];	//copy the value at the top of the stack to 'value'
	stack->size--;	//decrement the stack size, effectively popping the value
	return 0;
}

int StackPeek(const Stack* stack, int* value){
	if(stack==NULL||stack->size==0) return -1;
	*value=stack->array[stack->size-1];	//copy the value at the top of the stack to 'value'
	return 0;
}

int QueueEnqueue(Queue* queue, int value){
	queue->size++;
	queue->array[queue->size-1]=value; //assign 'value' to the next position in the array
	return 0;
}
int QueueDequeue(Queue* queue, int* value){
	if(queue==NULL||queue->size==0) return -1;
	*value=queue->array[0];		//copy the value at the front of the array to 'value'
	memcpy(queue->array,queue->array+1,sizeof(int)*(queue->size-1));	//copy the entire memory block after the first element of the array, to the front of the array
	queue->size--;
	return 0;
}
int QueuePeek(const Queue* queue, int* value){
	if(queue==NULL||queue->size==0) return -1;
	*value=queue->array[0];	//copy the value at the front of the queue to 'value'
	return 0;
}
