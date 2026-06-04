#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, simTime;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int tickets[n];
    int totalTickets = 0;

    // Input tickets
    for(int i = 0; i < n; i++)
    {
        printf("Enter tickets for Task %d: ", i + 1);
        scanf("%d", &tickets[i]);

        totalTickets += tickets[i];
    }

    printf("Enter simulation time: ");
    scanf("%d", &simTime);

    srand(time(NULL)); // Random seed

    printf("\n----- Lottery Scheduling -----\n");

    for(int time = 0; time < simTime; time++)
    {
        // Generate random winning ticket
        int winner = rand() % totalTickets + 1;

        int sum = 0;
        int task = -1;

        // Find which task owns the winning ticket
        for(int i = 0; i < n; i++)
        {
            sum += tickets[i];

            if(winner <= sum)
            {
                task = i;
                break;
            }
        }

        printf("Time %2d : Task %d\n",
               time, task + 1);
    }

    return 0;
}
