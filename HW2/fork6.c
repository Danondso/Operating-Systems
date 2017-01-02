#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argc, char *argv[])
{
  
 int input = atoi(argv[1]);
   

  pid_t pid;
  int i;
  int fib1 = 0, fib2 = 1;  
  int next;
  
 pid = fork();
 
if(pid < 0)
{
   fprintf(stderr, "Fork Failed\n");
   exit(-1);
}
 else if(pid == 0)
 {
   printf("%d\n", fib1);
   printf("%d\n", fib2);  
   for(i = 0; i < input; i++)
    {
     if(i <= 1) 
        next = i;
     else
     {
     next = fib1 + fib2;
     fib1 = fib2;
     fib2 = next;
     printf("%d\n", next);
    }
    }
  }    
 else
{
  wait(NULL);
  exit(0);
} 
return 0;
}
