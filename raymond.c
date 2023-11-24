#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 
#define MAX_SIZE 10
 
typedef struct
{
    int parent;
    int id;
    bool cs_access;
    int queue[MAX_SIZE];
} node;
 
int whoHasCS(node *proc, int n)
{
    int val;
    int i;
    for (i = 0; i < n; i++)
    {
        if (proc[i].cs_access)
        {
            val = proc[i].id;
            break;
        }
    }
    return val;
}
 
bool isRoot(node proc)
{
    return (proc.id == proc.parent);
}
 
int shift_queue(node *proc, int val)
{
    int retval = proc[val].queue[0];
    for (int i = 0; i < MAX_SIZE - 1; i++)
    {
        proc[val].queue[i] = proc[val].queue[i + 1];
    }
    proc[val].queue[MAX_SIZE - 1] = -1;
    return retval;
}
 
int main()
{
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
 
    int par;
 
    node *proc = (node *)malloc(n * sizeof(node));
    int i;
    // Tree is being formed
    for (i = 0; i < n; i++)
    {
        printf("Enter parent of %d: ", i);
        scanf("%d", &par);
        proc[i].id = i;
        proc[i].parent = par;
        proc[i].cs_access = false;
        if (proc[i].parent == proc[i].id)
        {
            proc[i].cs_access = true;   
        }
        // Initialize the queue with -1
        for (int j = 0; j < MAX_SIZE; j++)
        {
            proc[i].queue[j] = -1;
        }
    } // Tree formed
 
    int n_cs;
    printf("Enter cs access counts: ");
    scanf("%d", &n_cs);
    int req;
    int child;
 
    // Requesting
    for (i = 0; i < n_cs; i++)
    {
        printf("Enter pid: ");
        scanf("%d", &req);
        // Going till root
        while (!isRoot(proc[req]))
        {
            child = req;
            req = proc[req].parent;
            //printf("%d, %d --\n", child, req);
            proc[req].queue[0] = child;
        }
 
        int root = whoHasCS(proc, n);
        int p_root;
        
        // CS allocations
        while (proc[root].queue[0] != -1)
        {
            printf("Process %d has the critical section!\n", root);
 
            // Release the CS access for the current process
            proc[root].cs_access = false;
            p_root = root;
            root = shift_queue(proc, root);
            proc[p_root].parent = root;
            // Move the first process in the queue to CS
 
            //int root = proc[root].queue[0];
            proc[root].parent = root;
            proc[root].cs_access = true;
            printf("Process %d released the critical section.\n", p_root);
 
            // Grant CS access to the next process
            proc[root].cs_access = true;
 
        }
        printf("Process %d has the critical section!\n", root);
    }
 
    free(proc); // Free the allocated memory
 
    return 0;
}
