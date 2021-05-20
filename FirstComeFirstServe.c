/*######################################
# University of Information Technology #
# Operating System                     #
# File: FirstComeFirstServe.c          #
# First Come First Serve algorithm     #
######################################*/
//Done

#include <stdio.h>

struct ProcessControlBlock
{
    int processName, arrivalTime, burstTime;
    int waitingTime, turnaroundTime;
};

//for users to input information about PCB (process order, arrival time & burst time)
void Input_PCB(int numberProcess, struct ProcessControlBlock pcb[])
{
    for (int i = 0; i < numberProcess; i++)
    {
        printf("Enter the Process Name: ");
        scanf("%d", &pcb[i].processName);

        printf("Enter the Arrival Time: ");
        scanf("%d", &pcb[i].arrivalTime);
        
        printf("Enter the Burst Time: ");
        scanf("%d", &pcb[i].burstTime);

        printf("\n");
    }
}

//sort all processes according to arrival time (using selection sort algorithm)
void Sorting_ArrivalTime(int numberProcess, struct ProcessControlBlock pcb[])
{
    struct ProcessControlBlock temporary;
    int minimum;
    for (int i = 0; i < numberProcess - 1; i++)
    {
        minimum = i;
        for (int j = i + 1; j < numberProcess; j++)
        {
            if (pcb[j].arrivalTime < pcb[minimum].arrivalTime)
                minimum = j;
        }
        
        //swapping
        temporary = pcb[minimum];
        pcb[minimum] = pcb[i];
        pcb[i] = temporary;
    }
}

//calculate waiting time of all processes
void Calculating_WaitingTime(int numberProcess, struct ProcessControlBlock pcb[])
{
    int serviceTime[numberProcess];
    serviceTime[0] = pcb[0].arrivalTime;
    pcb[0].waitingTime = 0;

    for (int i = 1; i < numberProcess; i++)
    {
        serviceTime[i] = serviceTime[i-1] + pcb[i-1].burstTime;
        pcb[i].waitingTime = serviceTime[i] - pcb[i].arrivalTime;

        if (pcb[i].waitingTime < 0)
            pcb[i].waitingTime = 0;
    }
}

//calculate turnaround time of all processes
void Calculating_TurnaroundTime(int numberProcess, struct ProcessControlBlock pcb[])
{
    for (int i = 0; i < numberProcess; i++)
    {
        pcb[i].turnaroundTime = pcb[i].waitingTime + pcb[i].burstTime;
    }
}

//calculate average time of waiting time or turnaround time (depends on 'which' variable)
double Calculating_Average(int numberProcess, struct ProcessControlBlock pcb[], int which)
{
    //which = 1 will calculate average waiting time
    //which = 2 will calculate average turnaround time
    int sum;
    switch (which)
    {
    case 1: //average waiting time
        sum = 0;
        for (int i = 0; i < numberProcess; i++)
        {
            sum += pcb[i].waitingTime;
        }
        return (float)sum / (float)numberProcess;
        break;
    
    case 2: //average turnaround time
        sum = 0;
        for (int i = 0; i < numberProcess; i++)
        {
            sum += pcb[i].turnaroundTime;
        }
        return (float)sum / (float)numberProcess;
        break;

    default:
        return 0;
        break;
    }
}

//this function will print out the result (PCB info)
void Output_PCB(int numberProcess, struct ProcessControlBlock pcb[])
{
    printf("[*] PCB Before Sorting & Calculating [*] \n");
    printf("---------------------------------------------- \n");
    printf("\t FIRST COME FIRST SERVE \n");
    printf("---------------------------------------------- \n");
    printf("Process Name \t Arrival Time \t Burst Time \n");
    for (int i = 0; i < numberProcess; i++)
    {
        printf("%d \t\t %d \t\t %d", pcb[i].processName, pcb[i].arrivalTime, pcb[i].burstTime);
        printf("\n");
    }
    printf("---------------------------------------------- \n");

    //=============================================================================================

    Sorting_ArrivalTime(numberProcess, pcb);
    Calculating_WaitingTime(numberProcess, pcb);
    Calculating_TurnaroundTime(numberProcess, pcb);

    printf("\n\n[*] PCB After Sorting & Calculating [*] \n");
    printf("---------------------------------------------------------------------------------- \n");
    printf("\t\t\t FIRST COME FIRST SERVE \n");
    printf("---------------------------------------------------------------------------------- \n");
    printf("Process Name \t Arrival Time \t Burst Time \t Waiting Time \t Turnaround Time \n");
    for (int i = 0; i < numberProcess; i++)
    {
        printf("%d \t\t %d \t\t %d \t\t %d \t\t %d", pcb[i].processName, pcb[i].arrivalTime, pcb[i].burstTime, pcb[i].waitingTime, pcb[i].turnaroundTime);
        printf("\n");
    }
    printf("---------------------------------------------------------------------------------- \n");
}

//according to the algorithm, will print the Gantt Chart
void printGanttChart(int numberProcess, struct ProcessControlBlock pcb[])
{
    int i, j;
    // print top bar
    printf(" ");
    for (i = 0; i < numberProcess; i++)
    {
        for (j = 0; j < pcb[i].burstTime; j++) 
            printf("--");
        printf(" ");
    }
    printf("\n|");

    // printing process id in the middle
    for(i = 0; i < numberProcess; i++)
    {
        for(j = 0; j < pcb[i].burstTime - 1; j++) 
            printf(" ");
        printf("P%d", pcb[i].processName);
        for(j = 0; j < pcb[i].burstTime - 1; j++) 
            printf(" ");
        printf("|");
    }
    printf("\n ");
    // printing bottom bar
    for(i = 0; i < numberProcess; i++) 
    {
        for(j = 0; j < pcb[i].burstTime; j++) 
            printf("--");
        printf(" ");
    }
    printf("\n");

    // printing the time line
    printf("0");
    int temp = 0;
    for(i = 0; i < numberProcess; i++) 
    {
        for(j = 0; j < pcb[i].burstTime; j++) 
            printf("  ");
        if(pcb[i].turnaroundTime > 9) 
            printf("\b"); // backspace : remove 1 space
        temp += pcb[i].burstTime;
        printf("%d", temp);
    }
    printf("\n");
} 

void main()
{
    int numberProcess;
    printf("\nPlease enter total number of processes that you want: ");
    scanf("%d", &numberProcess);
    printf("\n");

    struct ProcessControlBlock pcb[numberProcess];

    Input_PCB(numberProcess, pcb);
    printf("\n");
    Output_PCB(numberProcess, pcb);
    printf("\n");

    printf("Average of all Waiting Time is %.2lf \n", Calculating_Average(numberProcess, pcb, 1));
    printf("Average of all Turnaround Time is %.2lf \n\n", Calculating_Average(numberProcess, pcb, 2));

    printf("[*] Gantt Chart [*] \n");
    printGanttChart(numberProcess, pcb);
    printf("\n");
}
