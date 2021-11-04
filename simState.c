#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
int count = 0, size = sizeof(fsm)/sizeof(fsm[0]);
int list[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

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

void delete(){
	int j, k, counter, outDel = 0, finalCheck = 0;
	char check;
	for (j = 0; j < 8; j++) 
	{
		counter = 0;
		check = fsm[j].state;

		for (k = 0; k < 8; k++)
		{
			if ((k != j) && (((fsm[k].nextState_0->state) == check) || ((fsm[k].nextState_1->state) == check))) 
			{
				counter += 1;
			}
		}

		if (counter == 0)
		{
			if (outDel == 0)
			{
				fprintf(stdout, "Deleted: ");
				outDel += 1;
			}
			fprintf(stdout, "%c ", fsm[j].state);
			finalCheck += 1;
			fsm[j].state = 'Z';
		}
	}		
	if (finalCheck == 0)
	{
		fprintf(stdout, "No states deleted.");	
	}
	fprintf(stdout, "\n");
}

void deleteOne(char optional){
int l, x; 

			for (l = 0; l < 8; l++)
			{
				if (fsm[l].state == optional)
				{
					x = l;
				}
			}

			if (fsm[x].state == 'Z')
			{
				fprintf(stdout, "Not deleted.\n");
			}
			else if ((optional == 'A') || (optional == 'B') || (optional == 'C') || (optional == 'D') || (optional == 'E') || (optional == 'F') || (optional == 'G') || (optional == 'H')) 
			{
				int k, counter = 0;
				char check = optional;

				for (k = 0; k < 8; k++)
				{
					if ((((fsm[k].nextState_0->state) == check) || ((fsm[k].nextState_1->state) == check))) 
					{
						counter += 1;
					}
				}

				if (counter == 0)
				{
					fsm[k].state = 'Z';
					fprintf(stdout, "Deleted.\n");
				}
				else
				{
					fprintf(stdout, "The state you entered is not a garbaged state.");
				}
			}
}

void garbage(int size, stateMachine current){
	int i, j;
	stateMachine Tmp;
	bool g = false, noG = true;

	for (i = 0; i < size; i++){
		Tmp = fsm[i];
		if (i != current.stateNum){g = true;}
		for (j = 0; j < size; j++){ //Checking if any other states point to Tmp
			if (i == current.stateNum){break;}
			if (i != j){
				if ((fsm[j].nextState_0 == fsm + Tmp.stateNum) || (fsm[j].nextState_1 == fsm + Tmp.stateNum)){
					g = false;
				}
			}
		}
		if (g){
			noG = false;
			list[count++] = fsm[i].stateNum;
		}
	}

	if (noG){fprintf(stdout, "\nNo Garbage\n");}
	else {
		fprintf(stdout, "\nGarbage: ");
		for (i = 0; i < count; i++){
			fprintf(stdout, "%c ", fsm[list[i]].state);
		}
		fprintf(stdout, "\n");	
	}
}

int main(int argc, char * argv[])
{
	setState();
	stateMachine current = fsm[3]; 
	bool check = true, confirm = false; 
	int i;
		
	fprintf(stdout, "The starting state is: %c \n", fsm[current.stateNum].state);
	fprintf(stdout, "Enter the following commands:\n");
	fprintf(stdout, "no commands : to print the initial state.\n");
	fprintf(stdout, "'0'/'1': enter '0' to print the next state for zero, and enter '1' to print the next state for one.\n");
	fprintf(stdout, "'c': enter the 'c' command followed by a '0' or '1' and then a state name ex. 'A', to modify the state machine.\n");
	fprintf(stdout, "'p': enter the 'p' command to print the state machine configuration.\n");
	fprintf(stdout, "'g': enter the 'g' command to print which states are currently unreachable.\n");
	fprintf(stdout, "'d': enter the 'd' command to delete all unreachable states\n\n");		 
			
	do{
		char input[] = {'n', 'n', 'n', 'n', 'n'};
		gets(input);
		if (input[0] == 'q') {fprintf(stdout, "Ended program"); check = false; break;}
		else if (input[0] == '0'){
			current = fsm[current.nextState_0->stateNum];
			fprintf(stdout, "%c\n", fsm[current.stateNum].state);
		}
		else if (input[0] == 'd'){
			if (input[2] != 'n'){
				for (i = 0; i < size; i++){
					if (input[2] == fsm[i].state){delete(input[2]);}
				}

			}
			else{
				delete();
			}
		}
		else if (input[0] == '1'){
			current = fsm[current.nextState_0->stateNum];
			fprintf(stdout, "%c\n", fsm[current.stateNum].state);
		}
		else if (input[0] == 'p'){
			for (i = 0; i < size; i++){
				if(fsm[i].state != "Z"){
					fprintf(stdout, "%c %c %c\n", fsm[i].state, fsm[i].nextState_0->state, fsm[i].nextState_1->state);
				}
			}	
		}
		else if (input[0] == 'g'){garbage(size, current);}
		else if (input[0] == 'c'){
			if (input[2] == '0'){
				confirm = false;
				for (i = 0; i < size; i++){
					if (input[4] == fsm[i].state){
						current.nextState_0 = fsm + i;
						fsm[current.stateNum].nextState_0 = fsm + i;
						fprintf(stdout, "State machine changed.\n");
						confirm = true;
						break;
					}
				}
				if (confirm == false){fprintf(stdout, "State not found.\n");}
			}
			else if (input[2] == '1'){
				confirm = false;
				for (i = 0; i < size; i++){
					if (input[4] == fsm[i].state){
						current.nextState_1 = fsm + i;
						fsm[current.stateNum].nextState_1 = fsm + i;
						fprintf(stdout, "State machine changed.\n");
						confirm = true;
						break;
					}	
				}
				if (confirm == false){fprintf(stdout, "State not found.\n");}
			}
		}
		else if (input[0] == '\0'){fprintf(stdout, "The starting state is: %c \n", fsm[current.stateNum].state);}
		else{fprintf(stdout, "Invalid command\n");}		
	}
	while(check);
	exit(0);		  
}


