#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Taskin Rahman's State Machine
A B F
B G E
C E B
D H A
E A D
F D G
G F H
H C H 

* Starting state is: D
*/

typedef struct fsm{
	char state;
	int stateNum;
	struct fsm * nextState_0;
	struct fsm * nextState_1;
} stateMachine;

stateMachine fsm[8];
int size = 8;
	
void setState(){
	//State A	
	fsm[0].state = 'A'; fsm[0].stateNum = 0; fsm[0].nextState_0 = fsm + 1; fsm[0].nextState_1 = fsm + 5;

	// State B
	fsm[1].state = 'B'; fsm[1].stateNum = 1; fsm[1].nextState_0 = fsm + 6; fsm[1].nextState_1 = fsm + 4;

	// State C
	fsm[2].state = 'C'; fsm[2].stateNum = 2; fsm[2].nextState_0 = fsm + 4; fsm[2].nextState_1 = fsm + 1;

	// State D
	fsm[3].state = 'D'; fsm[3].stateNum = 3; fsm[3].nextState_0 = fsm + 7; fsm[3].nextState_1 = fsm + 0;

	// State E
	fsm[4].state = 'E'; fsm[4].stateNum = 4; fsm[4].nextState_0 = fsm + 0; fsm[4].nextState_1 = fsm + 3;

	// State F
	fsm[5].state = 'F'; fsm[5].stateNum = 5; fsm[5].nextState_0 = fsm + 3; fsm[5].nextState_1 = fsm + 6;

	// State G	
	fsm[6].state = 'G'; fsm[6].stateNum = 6; fsm[6].nextState_0 = fsm + 5; fsm[6].nextState_1 = fsm + 7;

	// State H
	fsm[7].state = 'H'; fsm[7].stateNum = 7; fsm[7].nextState_0 = fsm + 2; fsm[7].nextState_1 = fsm + 7;
}

void change(int num, int nextState, stateMachine *currState){
	if(fsm[nextState].state != '\0'){
		if(num == 0){
			currState->nextState_0 = &fsm[nextState];
		}else{
			currState->nextState_1 = &fsm[nextState];
		}
	}
}

void print(stateMachine *currState){
	int i = 0;
	printf("\nstate\tnext0\tnext1\n");
	for(i=0;i<size;i++){
		if(fsm[i].state != '\0'){
			printf("  %c\t  %c\t  %c\n", fsm[i].state, fsm[i].nextState_0->state, fsm[i].nextState_1->state);
		}
	}
	printf("\nCurrent State: %c\n\n", currState->state);
}

int find(stateMachine *goal, stateMachine *curr, int visited[])
{
	// Given a node:
	//	Is left unvisited? Then:
	//		Is it the one? Then:
	//			retVal = 1;
	//		else
	//			Is right unvisited? Then:
	//				Is it the one? Then:
	//					retVal = 1;
	//				else
	//					Is find(left) == 1? Then:
	//						retVal = 1;
	//					else
	//						Is find(right) == 1? Then:
	//							retVal = 1;
	//						else
	//							This is GARBAGE!!!
	
	visited[curr->stateNum] = 1;
	
	if(visited[curr->nextState_0->stateNum] == 0){ // Is left unvisited?
		if(curr->nextState_0->stateNum == goal->stateNum){ // Is it the one?
			return 1;
		}else{
			if(find(goal, curr->nextState_0, visited) == 1){
				return 1;
			}
		}
	}
	
	if(visited[curr->nextState_1->stateNum] == 0){ // Is right unvisited?
		if(curr->nextState_1->stateNum == goal->stateNum){ // Is it the one?
			return 1;
		}else{
			if(find(goal, curr->nextState_1, visited) == 1){
				return 1;
			}
		}
	}	

	return 0;
}

char *garbage(stateMachine *currState)
{
	int i;
	int count = 0;
	char *states = (char *)malloc(20*sizeof(char));
	for(i = 0; i < 20; i++){
		states[i] = '\0';
	}
	
	for(i = 0; i < 8; i++){
		if(&fsm[i]!=currState){
			int visited[8] = {0, 0, 0, 0, 0, 0, 0, 0};
			if(find(&fsm[i], currState, visited)==0){
				if(count > 0){ 
					states[count++] = ',';
					states[count++] = ' ';
				}
				states[count++] = fsm[i].state;
			}
		}
	}
	
	return states;
}

void delete(stateMachine *currState){
	// Call garbage
	// Then use garbage to delete (set the states to NULL).
	
	char * states = garbage(currState);
	
	int i;
	for(i = 0; states[i] != '\0'; i++){
		int val = (int)states[i]-65;
		if(val >= 0 && val <= 7){
			if(i>0){
				printf(", ");
			}else{
				printf("\nDeleted: ");
			}
			putchar(fsm[val].state);
			fsm[val].state = '\0';
			fsm[val].nextState_0 = NULL;
			fsm[val].nextState_1 = NULL;
		}
	}
	if(i == 0){
		printf("\nNone deleted");
	}
	putchar('\n');
}

int main(int argc, char * argv[])
{
	setState();
	stateMachine *currState = &fsm[3];

	printf("The starting state is: %c \n", fsm[3].state);
	printf("Enter the following commands:\n");
	printf("no commands : to print the initial state.\n");
	printf("'0'/'1': enter '0' to print the next state for zero, and enter '1' to print the next state for one.\n");
	printf("'c': enter the 'c' command followed by a '0' or '1' and then a state name ex. 'A', to modify the state machine.\n");
	printf("'p': enter the 'p' command to print the state machine configuration.\n");
	printf("'g': enter the 'g' command to print which states are currently unreachable.\n");
	printf("'d': enter the 'd' command to delete all unreachable states\n\n");	

	do{
		char input[100];
		fgets(input, 100, stdin);

		int length;
		for(length = 0; length<100 && input[length]!='\n' && input[length]!='\0'; length++){}

		if (length == 5)
		{
			int check = 1;
			if(input[0] == 'c' && input[1] == ' ' && input[3] == ' '){
				if(input[2] == '0' || input[2] == '1'){
					int letter = input[4];
					if(letter >= 65 && letter <= 72){
						check = 0;
						change((int)input[2]-48, letter-65, currState);
					}
				}
			}
			if(check == 1){printf("Not a valid command.\n");}
		}else if(length == 1)
		{
			if(input[0] == 'q'){
				printf("qutting...");
				break;
			}

			switch (input[0])
			{
				case 'p':
					print(currState);
					break;
				case '0':
					currState = currState->nextState_0;
					printf("%c\n", currState->state);
					break;
				case '1':
					currState = currState->nextState_1;
					printf("%c\n", currState->state);
					break;
				case 'g':
					putchar('\n');
					int i;
					char *states = garbage(currState);
					for(i = 0; states[i] != '\0'; i++){
						if(i == 0){
							printf("Garbage: ");
						}
						putchar(states[i]);
					}
					if(i == 0){
						printf("No Garbage");
					}
					
					putchar('\n');
					break;
				case 'd':
					delete(currState);
					break;
				default:
					printf("Not a valid command.\n");
					break;
			}
		}else
		{
			printf("Not a valid command.\n");
		}
	}
	while(1);


	exit(0);		  
}


