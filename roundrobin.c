#include <stdio.h>

int main()
{
  printf("Algorithm: RoundRobin \n");
  int first = 5;
  int quantum = 3;
  int burstT[] = {10,4,2,7,3};
  int prio[] = {3,1,3,4,2};
  int i;
    
  int wait = 0;
    

  int waitT[first];
  int turnA[first];
    
  //Calculate total Burst Time
  int sum = 0;
  for (i = 0; i < first; i++){
    sum += burstT[i]; 
    waitT[i] = 0; //Declare all waits in 0
  }

  int blocks = 0;
  int process = 0;
  int gant[sum];

  while(sum > 0){

    //Select next process with remaining burstTime
    while (burstT[process] <= 0){  
      process ++;
      if (process == first){
        process = 0;
      }
      
    }

    //Increase waiting time for that process
    wait += quantum;
    turnA[process] = wait;
    
    //Add wait to all other process
    for(i=0; i< first; i++){
      if (i != process){
        if(burstT[i] > 0){
          waitT[i] += quantum;
        }
      }
    }

    //Eliminate quantum time;
    burstT[process] -= quantum;

    //Add process to gant chart
    gant[blocks] = process;
    blocks++;

    //Calculate remaining burstTime for all processes
    sum = 0;
    for (i = 0; i < first; i++){
      if (burstT[i] > 0){
        sum += burstT[i];
      }
    }

    //Move on to the next process
    process ++;
    if (process == first){
      process = 0;
    }     
  }
  
  printf("Blocks: %d \n", blocks);
  for (i = 0; i < blocks ; i++){
    printf("P%d[%d] -> ",gant[i], quantum);
  }
  printf("\nTurnAround Times: ");

  for (i = 0; i < first; i++){
    printf("%d, ",turnA[i]);
  }
  printf("\nWaiting Times: ");
    
  for (i = 0; i < first; i++){
    printf("%d, ",waitT[i]);
  }

  printf("\n");
  float avgT = 0;
  float avgW = 0;
  for (i = 0; i < first; i++){
    avgT += turnA[i];
    avgW += waitT[i];
  }
  avgT = avgT/first;
  avgW = avgW/first;
  printf("Avg. TurnAround Time: %.1f \n", avgT);
  printf("Avg. Waiting Time: %.1f \n", avgW);
}
