//
//  main.c
//  Game_of_life
//
//  Created by Diego Gayosso Hernandez on 9/21/24 on Xcode.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define generations 7
#define cell '*'
#define ded '.'
#define collum_size 5
#define row_size 5
#define MAX_INPUT_LENGTH 64 //reason for 64 its the max possible characters of an arary of ints seperated by commas

char board[row_size][collum_size] ;
char board_new[row_size][collum_size];


void clearInputBuffer(void) { //holy shit it works
	 int c;
	 while ((c = getchar()) != '\n' && c != EOF) { }
}

void initalize(void){
// gives empty cells '.' for propper spacing, otherwise it would be all fucked up, like my face
	for (int i = 0; i < row_size; i++) {
		 for (int j = 0; j < collum_size; j++) {
			  board[i][j] = ded;
		 }
	}
}

int* getState(int *count) { // such a pain the ass to learn dynamic memory, i hate it
	 char input[MAX_INPUT_LENGTH];
	 int temp[collum_size * row_size];
	 *count = 0;

	 printf("Enter integers separated by commas 0-24 (e.g., 0,1,12,24): ");
	 scanf("%s", input);

	 for (char* p = strtok(input, ","); p != NULL; p = strtok(NULL, ",")) {
		  temp[(*count)++] = atoi(p);
	 }

	 int *finished = (int *)malloc((*count) * sizeof(int));

	 for (int i = 0; i < *count; i++) {
		  finished[i] = temp[i];
	 }

	 clearInputBuffer();
	 return finished;
}

void fillBoard(void) {
	 initalize();

	 int count = 0;
	 int *test = getState(&count);

	 for (int i = 0; i < count; i++) {
		  int row = test[i] / row_size;
		  int collum = test[i] % collum_size;
		  board[row][collum] = cell;
	 }

	 free(test);
}

void printBorad(void){
	for(int i = 0; i<row_size;i++){
		for(int j =0; j<collum_size;j++){
			printf("%2c", board[i][j]);
			
		}
		printf("\n");
	}
}

int countNeighbord(int x, int y){
	//write a forloop that takes in the corordinates of the current box and iteraters through its neighbors just like the king moveset in chess,
	//and increase count if the neighbor cell is alive, after that return the amount that are alive.
	int count = 0;
	for (int dx = -1; dx <= 1; dx++) {
		 for (int dy = -1; dy <= 1; dy++) {
			  int newX = x + dx;
			  int newY = y + dy;

			  if (dx == 0 && dy == 0) continue; //makes sure it doesnt count itself, lonely fuck

			  // it makes sure were within bounds, i hope
			 if (newX >= 0 && newX < row_size && newY >= 0 && newY < collum_size) {
				  if (board[newX][newY] == cell) { count++; }
			 }
		 }
	}
	return count;
}



void iterate(void){
	//check to see if each element is a cell or ded, and check their conditions if they continue to be ded or alive/cell
	 int count;

	 for (int i = 0; i < row_size; i++) {
		  for (int j = 0; j < collum_size; j++) {
				count = countNeighbord(i, j);
				if (board[i][j] == cell && (count < 2 || count > 3)) {
					 board_new[i][j] = ded;
				} else if (board[i][j] == ded && count == 3) {
					 board_new[i][j] = cell;
				} else {
					 board_new[i][j] = board[i][j];  // i have no idea why this solves my problem but it does so..DONT TOUCH!!!
				}
		  }
	 }

	 // Copy the new board to the main board to reuse it
	 for (int i = 0; i < row_size; i++) {
		  for (int j = 0; j < collum_size; j++) {
				board[i][j] = board_new[i][j];
		  }
	 }
	//i wonder if i can put the known alive cells in a queue, and check only those ones. then houw would i check the others? maybe struct would be better
}

void printGenerations(void){
	for(int i=0;i<generations;i++){
		printf("Generation: %d\n",i);
		printBorad();
		iterate();
	}
}

char toQuit(void){
	char input;
	printf("Welcome! Press 'q' to quit or any other key to continue: ");
	scanf("%c",&input);
	clearInputBuffer();
	return input;
}

int main(int argc, const char * argv[]) {
	char Game = toQuit();

	while(Game != 'q'){
		fillBoard();
		printGenerations();
		Game = toQuit();
	}
	printf("thanks for playing\n");
	
	return 0;
}



