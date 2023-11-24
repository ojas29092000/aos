#include <stdio.h>
#include <stdlib.h>
 
// Process struct definition with typedef
typedef struct {
    int processID;
    int timestamp;
} Process;
 
int iInPA(Process* processArray, int ival, int numCS)
{
	int i;
	for (i = 0; i<numCS; i++)
	{
		if(ival == processArray[i].processID)
		{
			return 1;
		}
	}
	return 0;
}
 
int gettimestamp(Process* processArray, int ival, int numCS)
{
	int i;
	int retval;
	for (i = 0; i<numCS; i++)
	{
		if(ival == processArray[i].processID)
		{
			retval = processArray[i].timestamp;
		}
	}
	return retval;
}
 
int main() {
    int numProcesses, numCS;
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);
 
    printf("Enter Number of processes that want to enter CS: ");
    scanf("%d", &numCS);
 
    // Dynamically allocate memory for the processArray
    Process* processArray = (Process*)malloc(numCS * sizeof(Process));
 
    if (processArray == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
 
    for (int i = 0; i < numCS; ++i) {
        printf("Enter the Process ID and Timestamp of process: ");
        scanf("%d %d", &processArray[i].processID, &processArray[i].timestamp);
    }
 
    printf("\n");
 
    // Sort processes based on timestamp in ascending order
    for (int i = 0; i < numCS - 1; ++i) {
        for (int j = 0; j < numCS - i - 1; ++j) {
            if (processArray[j].timestamp > processArray[j + 1].timestamp) {
                // Swap processes
                Process temp = processArray[j];
                processArray[j] = processArray[j + 1];
                processArray[j + 1] = temp;
            }
        }
    }
 
    for (int k = 0; k < numCS; ++k) {
        int time = processArray[k].timestamp;
        int processCS = processArray[k].processID;
 
        for (int i = 0; i < numProcesses; ++i) {
            if (processCS != i) {
                printf("Process %d has requested Process %d\n", processCS, i);
            }
        }
        printf("\n");
    }
    
    for (int i = 0; i < numProcesses; ++i)
    {
    	for (int k = 0; k < numCS; ++k)
    	{
    		if (iInPA(processArray, i, numCS) == 1)
    		{
    			if (processArray[k].timestamp < gettimestamp(processArray, i, numCS))
    			{
    				printf("%d Replys %d request\n", i, processArray[k].processID);
    			}
    		}
    		else
    		{
    			printf("%d Replys %d request\n", i, processArray[k].processID);
    		}
    	}
    }
 
    for (int k = 0; k < numCS; ++k) {
        int time = processArray[k].timestamp;
        int processCS = processArray[k].processID;
 		/*
        for (int i = 0; i < numProcesses; ++i) {
            if (processCS != i) {
                printf("Process %d has Accepted the request of process %d\n", i, processCS);
            }
        }*/
        printf("\n");
        printf("Process %d has now entered the CS\n", processCS);
        printf("Process %d has now exited the CS\n", processCS);
        
        for (int i=1; i<numCS-k; ++i)
        {
        	printf("%d Replys %d request\n", processArray[k].processID, processArray[k+i].processID);
        }
        printf("\n");
    }
 
    // Free dynamically allocated memory
    free(processArray);
    
    printf("Simulation has now ended!!\n");
    
    return 0;
}
