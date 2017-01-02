#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

///////////////////////////
//-------------------------
//Dublin Anondson
//-------------------------
///////////////////////////


typedef int buffer_item;
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
//Semaphores
sem_t empty;
sem_t full;
//numbers for circular queue
int size = 0;
int front;
int back = 0;
//Mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Insert an item into the bounded buffer
int insert_item(buffer_item item)
{
  int check; 
 sem_getvalue(&empty, &check);
 if(check <= 5)
   {
     buffer[back] = item;
     back = (back + 1) % BUFFER_SIZE;
     size ++;
     return 0;
   }
 if(check > 5)
   return -1;
 
}

int remove_item(buffer_item *item)
{
 
 int check;
 sem_getvalue(&full, &check);
 if(check >= 0)
   {
    *item = buffer[front];
     front = (front +1) % BUFFER_SIZE;
     size--;
     return 0;
   }
  if(check < 0)
   {
    return -1;
   }
}

void *producer(void *param)
{

 buffer_item item;
 while(1)
 {
//  sem_wait(&empty);
  pthread_mutex_lock(&mutex);
  sem_wait(&empty);
  sleep((rand() % 5) + 1);
  item = rand();
  if(insert_item(item) == -1)
  {
  fprintf(stderr, "Could not insert correctly.");
  }
  else
  { 
  printf("Producer produced %d\n", item);
  }
   sem_post(&full);
    pthread_mutex_unlock(&mutex);
     //sem_post(&full);
  }
}

void *consumer(void *param) 
{

buffer_item item;

      while (1) 
       {
         //Semaphore and Mutex lock
         // sem_wait(&full);
          pthread_mutex_lock(&mutex);
          sem_wait(&full);
	  /* sleep for a random period of time */
	   sleep((rand() % 5) + 1);
           
           if (remove_item(&item) == -1)
	  {
 	   fprintf(stderr, "Could not Remove Correctly.");
          }
	   else
	      {
	       printf("Consumer consumed %d\n",item);
       	      }
          //Semaphore and mutex unlock
           sem_post(&empty);
           pthread_mutex_unlock(&mutex);
          // sem_post(&empty); 
      }
}
int main(int argc, char *argv[])
{
 int sleeptime = atoi(argv[1]);
 int prothread = atoi(argv[2]);
 int conthread = atoi(argv[3]);
 int i, j, k;

 
// int sem_t empty;
// int sem_t full;
  sem_init(&empty, 0, 5);
  sem_init(&full, 0, 0);

//Zero out the buffer
for(k = 0; k < BUFFER_SIZE; k++)
   buffer[k] = 0;

 pthread_t pro[prothread];
 pthread_t con[conthread];
// pthread_attr_t attr;
 for(i = 0; i<prothread;i++)
 {
 // printf("you got to %d\n producers", i);
  pthread_create(&pro[i], NULL, producer, NULL);
 }

 for(i = 0; i<prothread;i++)
 { 
 // printf("you got to %d\n consumers", i);
  pthread_create(&con[i], NULL, consumer, NULL);
 // pthread_join(con[i], NULL);
 }
 
 sleep(sleeptime);
 exit(-1);
}
