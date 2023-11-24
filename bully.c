#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
     
#define MAX_PROC 100
     
typedef struct {
	int id;
	int priority;
	bool alive;
	bool isCoordinator;
	bool inElection;
}Process;
 
void life_status(Process* processes, int n)
{
	int i;
	for (i=0;i<n;i++);
	{
		printf("id: %d, status: %d\n", processes[i].id, processes[i].alive);
	}
}
 
int num_of_processes_in_election(Process* processes, int n)
{
	int i;
	int count = 0;
	for (i = 0; i < n; i++)
	{
		if (processes[i].inElection == true && processes[i].alive == true)
    	{
    		count++;
   		}
   	}
    	
   	return count;
}
 
Process coordinatorReveal(Process* processes, int n)
{
	int i;
	Process retval;
	for (i=0;i<n;i++)
	{
		if (processes[i].inElection == true && processes[i].alive == true)
		{
			retval = processes[i];
		}
	}
	return retval;
}
 
void election_message(Process initiator, Process contender)
{
	printf("%d sent election message to %d\n", initiator.id, contender.id);
	if(contender.inElection == true && contender.alive == true)
	{
		printf("%d sent ok message to %d\n", contender.id, initiator.id);
	}
}
 
int new_initiator_inducer(Process* processes, int n)
{
	int elec_count = 0,i;
	int min_val, new_initiator;
	for (i=0;i<n;i++)
	{
		if(processes[i].inElection == true && processes[i].alive == true)
		{
			if (elec_count == 0)
			{
				min_val = processes[i].priority;
				new_initiator = processes[i].id;
				elec_count++;
			}
			if (min_val > processes[i].priority)
			{
				min_val = processes[i].priority;
				new_initiator = processes[i].id;
			}
		}
	}
	return new_initiator;
}
 
Process f_Bully_Election(int initiator, int n, Process* processes)
{
	bool proceedWithElection = true;
	int i;
	int elec_count=0;
	Process winner;
	while (proceedWithElection)
	{
		elec_count = 0;
		// finding election candidates
		printf("\n------------New Round!!------------\n");
		for (i=0;i<n;i++)
		{
			processes[i].inElection = false;
			if (processes[initiator].priority < processes[i].priority && processes[initiator].alive == true)
			{
				processes[i].inElection = true;
				//printf()
				elec_count++;
			}
		}
		// case when initiator is the highest
		if (elec_count == 0)
		{
			winner = processes[initiator];
			break;
		}
		
		for (i=0;i<n;i++)
		{
			if (processes[i].inElection)
			{
				election_message(processes[initiator], processes[i]); // message passing receival
			}
		}
		
		initiator = new_initiator_inducer(processes, n);
		printf("\n---%d---\n", num_of_processes_in_election(processes,n));
		if (num_of_processes_in_election(processes,n) == 1)
		{
			proceedWithElection = false;
			winner = coordinatorReveal(processes, n);
		}
	}
	
	return winner;
}
 
 
int main()
{
    int n; // this is the number of processes
   	printf("Enter the number of processes: ");
   	scanf("%d", &n);
    	
   	//int* dynamicArray = (int*)malloc(size * sizeof(int));
   	Process* processes = (Process*)malloc(n*sizeof(Process));
    	
    int i;
   	for (i = 0; i < n; i++){
    	processes[i].id = i;
    	processes[i].priority = n-i;
   		processes[i].alive = true;
   		processes[i].isCoordinator = false;
   		processes[i].inElection = false;
   	}
    printf("id\tpriority\talive\tisCoordinator\tinElection \n");
    for (i=0;i<n;i++)
    {
    	printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id,processes[i].priority,processes[i].alive,processes[i].isCoordinator,processes[i].inElection);
    }
    
    int val;
   	printf("Enter any random process id to turn off between 0 and %d: ", n-1);
   	scanf("%d", &val);
   	// switching off the above random process
   	processes[val].alive = false;
   	
   	//life_status(processes, n);
   	//int i;
    	
   	// making a random initiator
   	int initiator;
   	printf("Enter any random process id to be the initiator between 0 and %d except %d: ", n-1, val);
   	scanf("%d", &initiator);
   	if (processes[initiator].alive != true){
   		printf("Initiator is not alive!!\n");
   		exit(0);
   	}
    	
   	//printf("\n----New Contest!!----\n");
   	printf("Process with id: %d is the initiator!!\n", processes[initiator].id);
   	
   	Process coordinator = f_Bully_Election(initiator, n, processes);
   	
   	printf("\nProcess : %d was elected!!\n", coordinator.id);
    	
    return 0;
}
