/* Program Hoovi*/
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

//using struct to define a state representation

typedef struct
{
	char ra;     	//rooms label alphabet
	int fn;      	//rooms label number
	int rn;      	//parent index 
	int pi;			//the floor number
}state;

//Variable used in the global scope
int vfront= -1; //next position in the visited list
int front = 0;	//front position of the queue
int rear = -1;	//rear position of the queue
int wt =0; 		//amount of state in the waiting list
int scost=0;	//a counter to measure the number search iteration done
state queue[1000]= {}; //This is FIFO waiting queuw; we put all unchecked states in here. 
state visited[1000]={};// This is the visited stated list; we put all checked states in here.

//Function Prototype
void addToQueue(char,int,int,int); 
int equalStates(state, state);		
int addToVisited(state);
void generateSuccessors(state,int);
int hasBeenVisited(state);
int isGoalState(state);
void printSolution(state);
void push(state);
state pop();
state popdfs();


int main()
{
	//defining variables with their data type
	char initstate_ra; //variable to hold the room alphabet entered by the user
	char be;			//variable to hold the option of choosing if the user wants update on Hoovi's location
	int initstate_fn;	//variable to hold the floor number
	int initstate_rn;	//variable to hold the room number
	state s;			//variable to hold the current state that we want to explore
	int parentIndex=0;	//array index of the current state in the visited list
	int accept;			//variable to hold the option of choosing between BFS and DFS
	
	
	printf("\n\n.......Enter to Search.........\n\n");
	printf("Enter Room Alphabet from A to N: ");
	scanf("%c",&initstate_ra);
	printf("Enter Floor Number from 1-3: ");
	scanf("%d",&initstate_fn);
	printf("Enter Room Number between 1 & 2: ");
	scanf("%d",&initstate_rn);
	
	printf("\nHere is the room you entered %c%d.%d\n\n",initstate_ra,initstate_fn,initstate_rn);
	
	state initialState={initstate_ra, initstate_fn, initstate_rn, -1};	//initializing all states and setting a state to start from
	
	printf("Enter 0 for BFS: \nEnter 1 for DFS:\n\n");
	scanf("%d",&accept);
	
	printf("\nDo you want to know about Hoovi's search activity? [Y/N]: \n\n");	//To ask if the user wants details update on where Hoovi is.
	scanf(" %c",&be);
	
	if(initstate_ra<65 || initstate_ra>78 || initstate_fn<1 || initstate_fn>3 || initstate_rn<1 || initstate_rn>2) //condition to check if the input entered by the user is valid for execution
	{
		printf("\nInvalid Input, Try again!!!!");
		return 0;
	}
	
	push(initialState);	// add initial state to the "waiting" queue
	
	if(accept==0) //if the user enters 0 it calls the dfs funcion
	{
			printf("\n->You have selected the BFS Algorithm!!!\n");
	
	while(wt>0)
	{
		//Get Next State
		if(be=='Y') 			//condition to check if the input entered by the user is valid for execution
		{
				s= pop(); 		//to get a state from the queue
				//conditions to show what room and where the Hoovi is in the building
				if(s.rn==1)
				{
					printf("->Exploring The Reception %c%d.%d, Floor No.%d\n",s.ra,s.fn,s.rn,s.fn);
				}
				if(s.rn==2)
				{
					printf("->Exploring The Office %c%d.%d, Floor No.%d\n",s.ra,s.fn,s.rn,s.fn);
				}
				if(s.ra=='I')
				{
					printf("->Exploring The Lobby %c%d.%d, Floor No.%d\n",s.ra,s.fn,s.rn,s.fn);
				}
				if(s.ra=='J')
				{
					printf("->Exploring The Elevator %c%d.%d, Floor No.%d\n",s.ra,s.fn,s.rn,s.fn);
				}
				if(s.ra=='Q')
				{
					printf("->Charging Station, Charging Back to 100!!");
				}
		
				parentIndex = addToVisited(s);				//add this state to the visited list and retrieve storage index
				if(isGoalState(s))
				//if the current state is the goal state, print the solution to the goal state
				{
					printf("\n->Currently at the charging station......\n->(%d rooms explored):\n\n ",scost);
					printf("Printing the solution path: \n\n");
					printSolution(s);
					getchar();		//function to wait for a key press
					return 0;
				}
				else		//if current state is not the goal state, then run successor fucntion.
				{
				generateSuccessors(s,parentIndex);	//generate the children of s and make them remember s as their parent
				getchar();
				}
			
		}
		if(be=='N')	//condition to check if the input entered by the user is valid for execution
		{
			while(wt>0)
			{
				s= pop(); 		//to get a state from the queue
				parentIndex = addToVisited(s);				//add this state to the visited list and retrieve storage index
				if(isGoalState(s))
				//if the current state is the goal state, print the solution to the goal state
				{
					printf("\n->Currently at The charging station.......,\n->(%d rooms explored):\n \n",scost);
					printf("->Printing the solution path: \n\n");
					printSolution(s);
				}
				else		//if current state is not the goal state, then run successor fucntion.
				{
				generateSuccessors(s,parentIndex);	//generate the children of s and make them remember s as their parent
				}
			scost++;
			}
			
  		}
  	//increment search iterations counter
	scost++;	
	}
	printf("\n\nNo Further Rooma to Explore\n\n");
	getchar();
	}
	
	if(accept==1)		//if the user enters 1 it calls the dfs funcion
	{
			printf("->You Have Selected The DFS Algorithm");
	
			while(wt>0)
			{
				if(be=='Y')
				{
					s= popdfs(); 		//calls the dfs fucntion from where it is defined
					if(s.rn==1)
					{
						printf("->\nExploring The Reception %c%d.%d, Floor No.%d\n\n", s.ra,s.fn,s.rn,s.fn);
					}
					if(s.rn==2)
					{
						printf("->\nExploring The Office, Floor No.%d\n\n",s.fn);
					}
					if(s.ra=='I')
					{
						printf("->\nExploring The Lobby, Floor No.%d\n\n",s.fn);
					}
					if(s.ra=='J')
					{
						printf("->\nExploring The Elevator, Floor No.%d\n\n",s.fn);
					}
					if(s.ra=='Q')
					{
						printf("->\nCharging Station, Charging Back to 100!!");
					}
		
					parentIndex = addToVisited(s);
					if(isGoalState(s))
					{
						printf("\n->Currently at The charging station.......,\n->(%d rooms explored):\n \n",scost);
						printf("\n->Printing the solution path: \n\n");
						printSolution(s);
						getchar();
					}
					else
					{
						generateSuccessors(s,parentIndex);
					}
				}
				if(be=='N')	//condition to check if the input entered by the user is valid for execution
				{
					while(wt>0)
					{
						s= popdfs(); 		//to get a state from the queue
						parentIndex = addToVisited(s);				//add this state to the visited list and retrieve storage index
						if(isGoalState(s))
						//if the current state is the goal state, print the solution to the goal state
						{
							printf("\n->Currently at The charging station.......,\n->(%d rooms explored):\n \n ",scost);
							printf("->Printing the solution path: \n\n");
							printSolution(s);
						}
						else		//if current state is not the goal state, then run successor fucntion.
						{
							generateSuccessors(s,parentIndex);	//generate the children of s and make them remember s as their parent
						}
						scost++;
					}
				}
			scost++;
			}
			printf("\n\n->No Further rooms to Explore\n\n");
			getchar();
			return 0;
	}
	
}

/* CORE SEARCH FUNCTIONS
*
*  push and pop - control the queue operations that implement BFS as our search 
strategy
*  generateSuccessors - creates further states to explore according to the rules of
the problem
*  isGoalState - checks if the current state is a goal state
*
*  Details below
*/

// For pushing the states inside the queue
void push(state s)
{
	rear++;				// increase rear index 
	queue[rear]= s;		// stores s
	wt++;				//increase the count of states in the queue
}

// For popping the states using bfs
state pop()				// pop retrieves a state from the front of the queue
{
	if(wt>0)			// check if there are items in the queue
	{
		state s = queue[front];		// get state at front index	
		front++;					// increase front index to point at the next state
		wt--;						// decrement state counter
		return s;					// pass state back to the point of call
	}
}

// For popping the states using dfs
state popdfs()
{
		if(wt > 0) 
		{
			state s = queue[rear];
			rear--;
			wt--;
			return s;
		}
}

// Takes a single state and that state's storage index in the visited list as input
// It then generates all valid successor states (children) of this state
// The contents of the successor function depend largely on the problem we are trying to solve

// Function to generate the successive room path
void generateSuccessors(state s,int pi)
{
		if(s.rn==2)
		{
			addToQueue(s.ra,s.fn,s.rn-1,pi);
		}
		if(s.rn==1)
		{
			addToQueue(s.ra,s.fn,s.rn+1,pi);
			addToQueue(s.ra=73,s.fn,s.rn-1,pi);
		}
		if((s.ra==73)&& (s.fn==1 || s.fn==2 || s.fn==3) && (s.rn==0))
		{
			for(int i=1; i<9; i++)
			{
				addToQueue(s.ra-i,s.fn,s.rn+1,pi);
			}
			for(int i=2; i<6; i++)
			{
				addToQueue(s.ra+i,s.fn,s.rn+1,pi);
			}
		}
		if((s.ra==73)&& (s.rn==0))
		{
			addToQueue(s.ra+1,s.fn,s.rn,pi);
		}
		if(s.ra==74 && s.fn>1 && s.rn==0)
		{
			addToQueue(s.ra=74,s.fn-1,s.rn=0,pi);
		}
		if(s.ra==74 && s.fn==1)
		{
			addToQueue(s.ra=81,s.fn,s.rn=0,pi);
		}
		if(s.ra==74 && s.rn==0)
		{
			addToQueue(s.ra=73, s.fn,s.rn,pi);
		}
			
}

//// Function to check if the current state is the destination or not
int isGoalState(state s)
{
	
	if((s.ra==81)&& (s.fn==1)&& (s.rn==0))
			return 1;
		else
			return 0;
}

// Function to print the possible potential room
void printSolution(state s)
{
	if(s.pi!=-1)
	{
		printSolution(visited[s.pi]);
		printf("%c%d.%d",s.ra,s.fn,s.rn);
	}
	if(!isGoalState(s))
	{
		printf("->");
		return;
	}
	
}

// Function to add the states in the visited array
int addToVisited(state s)
{
	vfront++;
	visited[vfront]=s;
	return vfront;
}

// Function to check if both the rooms are the same
int equalStates(state s1, state s2)
{
	if(s1.ra==s2.ra && s1.fn==s2.fn && s1.rn == s2.rn)
	{
		return 1;
		
	}
	else 
	{
		return 0;
	}
}

// Function to check if we have visited the rooms or not
int hasBeenVisited(state s)
{
	int i;
	for (i=0; i<vfront; i++)
	{
		if(equalStates(visited[i],s))
		return 1;
	}
	return 0;
}

// Function to check if we have visited the rooms or not
void addToQueue(char ra, int fn,int rn,int pi)
{
	state s = {ra,fn,rn,pi};
	if(!hasBeenVisited(s))
	{
		push(s);
		return;
	}
}





