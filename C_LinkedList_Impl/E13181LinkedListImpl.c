#include <stdlib.h>

#define MAX 100000	//maximum size of the stack queue

typedef struct _{	//Struct to hold the nodes
	int val;	//vaue of the node
	struct _ * next;	//pointer to the next node
}node;

typedef struct __{	//Struct to hold the Stack
	node * last;	//Pointer to the last node in the Stack
}Stack;

typedef struct ___{	//Struct to hold the Queue
	node * first;	//Pointer to the element at the front of the Queue
	node * last;	//Pointer to the element at the back of the Queue
}Queue;

Stack* CreateStack(){
	static Stack* stack;	//create a static Stack pointer(because we need to return it, if it was not static it would vanish after this function terminates)
	stack=(Stack*)malloc(sizeof(Stack));	//allocate memory to stack
	stack->last=NULL;	//intitialize the pointer which points to the top of the Stack to NULL(because the Stack is empty right now)
	return stack;
}
int DeleteStack(Stack* stack){
	if(stack==NULL || stack->last==NULL) return -1;
	while(stack->last!=NULL){	//while 'last' points to some non-NULL node
		node *tmp=stack->last;	//copy the memory location of the top node momentarily
		stack->last=stack->last->next;	//point 'last' to the next to last element in the stack 
		free(tmp);	//free the memory location of the top element in the Stack
	}
	free(stack); //free the 'stack' pointer
	return  0;
}

Queue* CreateQueue(){
	static Queue* Q;	//create a static Queue pointer(because we need to return it, if it was not static it would vanish after this function terminates)
	Q=(Queue*)malloc(sizeof(Queue));	//allocate memory to queue
	Q->first=NULL;	//intitialize the pointer which points to the front of the Queue to NULL(because the Queue is empty right now)
	Q->last=NULL;	//intitialize the pointer which points to the back of the Queue to NULL(because the Queue is empty right now)
	return Q;
}
int DeleteQueue(Queue* queue){
	if(queue==NULL || queue->first==NULL) return -1;
	while(queue->first!=NULL){	//while 'first' points to some non-NULL node
		node *tmp=queue->first;	//copy the memory location of the front node momentarily
		queue->first=queue->first->next;	//point 'first' to the next to last element in the stack 
		free(tmp);	//free the memory location of the front element of the Queue
	}
	free(queue);	//free the 'queue' pointer
	return  0;
}

int StackPush(Stack* stack, int value){
	static node *new;	//create new node pointer
	new=(node*)malloc(sizeof(node));	//allocate memory to the node
	new->val=value;	//assign the node it's value
	new->next=stack->last;	//point the new node to the node currently at the top of the Stack
	stack->last=new;	//point 'last' to the new node
	return 0; 
}

int StackPop(Stack* stack, int* value){
	if(stack==NULL || stack->last==NULL) return -1;
	*value=stack->last->val;	//copy the value at the top of the stack to 'value'
	node * tmp=stack->last;		//store the memory location of the node at the top of the stack 
	stack->last=stack->last->next;	//point 'last' to the next-to-last node in the stack
	free(tmp);	//free the memory location of the node at the top of the stack
	return 0;
}

int StackPeek(const Stack* stack, int* value){
	if(stack==NULL || stack->last==NULL) return -1;
	*value=stack->last->val;	//copy the value at the top of the stack to 'value'
	return 0;
}

int QueueEnqueue(Queue* queue, int value){
	static node *new;	//create new node pointer
	new=(node*)malloc(sizeof(node));	//allocate memory to the node
	new->val=value;	//assign the node it's value
	new->next=NULL;	//point the new node to nothing
	if(queue->first==NULL){	//if the Queue is currently empty
		queue->first=new;	//point 'first' to the new node
		queue->last=new;	//point 'last' to the new node(Since there is only one node, the first and last are the same)
	}
	else{
		queue->last->next=new; //point the node at the back of the Queue to the new node
		queue->last=new;	//point 'last' to the new ndoe
	}
	return 0;
}
int QueueDequeue(Queue* queue, int* value){
	if(queue==NULL || queue->first==NULL) return -1;
	*value=queue->first->val;	//copy the value at the top of the queue to 'value'
	node * tmp=queue->first;	//store the memory location of the node at the front of the queue
	queue->first=queue->first->next;	//point 'first' to the next-to-first node in the queue
	free(tmp);	//free the memory location of the node at the front of the queue
	return 0;
}
int QueuePeek(const Queue* queue, int* value){
	if(queue==NULL || queue->first==NULL) return -1;
	*value=queue->first->val;	//copy the value at the top of the queue to 'value'
	return 0;
}