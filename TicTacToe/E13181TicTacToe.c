/*
	CO222-2016 Lab05
	Author: E13181

	TicTacToe game
*/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

int i,j;	//counters

//protype the functions required
void scanBoard(int a[SIZE][SIZE]);
void printBoard(int b[SIZE][SIZE]);
int getWinner(int b[SIZE][SIZE]);

int main(){
	int inBoard[SIZE][SIZE];
	printf("Please enter the board:\n");
	scanBoard(inBoard);	//scanBoard
	printf("Here is the board:\n");
	printBoard(inBoard);	//printBoard
	//printing the result
	if(getWinner(inBoard)==0)	
		printf("Noughts win\n");
	else if(getWinner(inBoard)==1)
		printf("Crosses win\n");
	else
		printf("There are no winners\n");
	
	return 0;
}


//scan function
void scanBoard(int board[SIZE][SIZE]){
	
	//check if the input is 0 || 1 || 2
	//else give the error message "Enter valid input." and terminate the program
	int c;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			scanf("%d",&c);
			if(!(c>=0 && c<=2)) { //check whether the input is within the range 0-2
				printf("Enter valid input.");
				exit(1);// if not exit the program with EXIT_FAILURE
			}
			else board[i][j]=c;
		}
	}
}


//print function
void printBoard(int board[SIZE][SIZE]){
	//printing board
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(board[i][j]==0) printf("O ");
			else if(board[i][j]==1) printf("X ");
			else printf(". ");
		}
		printf("\n");
	}
}


//find the winner of the game
//assume both two players can't win the game at the same time. It can't happen in a real game
int getWinner(int board[SIZE][SIZE]){
	
	int winner = 2;		//set winner to 2 so that if neither of the players win then their won't be any winner
	
	//if winner is Noughts, winner = 0
	//if winner is Crosses, winner = 1
	//if there is no winner, winner = 2

	//check for win in row
	for(i=0;i<SIZE;i++){	//for each row
		int c=board[i][0];
		if(c==2) continue;	//if the character is '.' then there is no need to consider it so continue the loop
		j=0;	//counter to keep number characters of the same type
		while(board[i][j]==c && j<=SIZE-1) j++;
		if(j==SIZE) {	//if there are three same of the same type in the same row
			if(c==0) return 0;	//first element in the main diagonal
			else return 1;	//if character is zero, the winner is Crosses
		}
	}
	//check for win in column
	for(j=0;j<SIZE;j++){	//for each column
		int c=board[0][j];
		if(c==2) continue;	//if the character is '.' then there is no need to consider it so continue the loop
		i=0;	//counter to keep number characters of the same type
		while(board[i][j]==c && i<=SIZE-1) i++;
		if(i==SIZE) {	//if there are three same of the same type in the same column
			if(c==0) return 0;	//if character is zero, the winner is Noughts
			else return 1;	//if character is zero, the winner is Crosses
		}
	}
	//check for win in diagonals
	int one=board[0][0];	//first element in the main diagonal
	int two=board[0][SIZE-1];	//first element in the secondary diagonal
	//check for wins in the main diagonal
	j=0;
	if(one!=2){
		for(i=0;i<SIZE;i++){
			if(board[i][i]==one) j++;
			else break;		//if alteast one character is not equal to the first value, there is no point in checking further
		}
		if(j==SIZE){	//if there are three same of the same type in the main diagonal
			if(one==0) return 0;	//if character is zero, the winner is Noughts
			else return 1;	//if character is zero, the winner is Crosses
		}
	}
	//check for wins in the secondary diagonal
	j=0;
	if(two!=2){
		for(i=0;i<SIZE;i++){
			if(board[i][SIZE-1-i]==two) j++;	
			else break;		//if alteast one character is not equal to the first value, there is no point in checking further
		}
		if(j==SIZE){	//if there are three same of the same type in the secondary diagonal
			if(two==0) return 0;	//if character is zero, the winner is Noughts
			else return 1;	//if character is zero, the winner is Crosses
		}
	}
	return  winner;
}