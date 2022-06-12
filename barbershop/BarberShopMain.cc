#include <stdio.h>
#include "BarberShop.h"
#include "thread.h"
#include <vector> 

#define NCUST 6
#define SIMTIME 25

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}



void selectionSort(int p_first[], int n, int cust_time[])
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (cust_time[j] < cust_time[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
        swap(&p_first [min_idx], & p_first [i]);
 	swap(&cust_time[min_idx], &cust_time[i]);
	
    }
}


void *barberMain(void *bsPtr)
{
  BarberShop *bs = (BarberShop *)bsPtr;
  bs->barberDay();
  return NULL;
}

void *custMain(void *bsPtr)
{
  bool ret;
  BarberShop *bs = (BarberShop *)bsPtr;
  while(1){
    ret= bs->getHairCut();
    thread_sleep(1, 0);
    if(ret == true)  return NULL;
  }
  //return NULL;
  
  }


void *clockMain(void *bsPtr)
{
  BarberShop *bs = (BarberShop *)bsPtr;
  thread_sleep(SIMTIME, 0);
  printf("CLOCK: Closing time\n");
  bs->ClosingTime();
  return NULL;
}


int main(int argc, char **argv)
{
  int ii;
  int cust_num [6] = {0, 1, 2, 3, 4, 5};
  int cut_time [6] = {3, 1, 4, 2, 6, 5};
  
  selectionSort(cut_time, NCUST, cust_num);
  
  BarberShop *bs = new BarberShop();
  pthread_t barber;
  pthread_t customers[NCUST];
  pthread_t clock;

  pthread_create(&barber, NULL, barberMain, bs);

  for(ii = 0; ii < NCUST; ii++){
    pthread_create(&customers[cust_num[ii]], NULL, custMain, bs);
  }
  
    pthread_create(&clock,NULL, clockMain, bs);
  thread_join(barber);
}
