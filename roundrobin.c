#include <stdio.h>

int main()
{
  printf("Algorithm: RoundRobin \n");
  int first = 5;
  int quantum = 1;
  int burstT[] = {10,1,2,1,5};
  int prio[] = {3,1,3,4,2};
  int i;
    
  int wait = 0;
  int turn = 0;
    

  int waitT[first];
  int turnA[first];
    
  int sum = 0;
  for (i = 0; i < first; i++){
    sum += burstT[i];
  }
  int process = 0;
  int j = 0;
  int gant[sum];

  while(sum > 0){

    //Select next process with remaining burstTime
    while (burstT[process] == 0){  
      process ++;
      if (process == first){
        process = 0;
      }
    }
    //Increase waiting time for that process
    waitT[process] += wait;
    wait += quantum;
    turn += quantum;

    //Eliminate quantum time;
    brustT[process] -= quantum;
    if (burstT[process < 1]){
      turnA[process] = turn;
    }

    gant[j] = process;
    j++;


    //Calculate remaining burstTime for all processes
    int sum = 0;
    for (i = 0; i < first; i++){
      sum += burstT[i];
    }

    //Move on to the next process
    process ++;
    if (process == first){
      process = 0;
    }      
  }

  for (i = 1; i < first+1; i++){
    printf("P%d[%d] -> ",i,gant[i-1]);
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
