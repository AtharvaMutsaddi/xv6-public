#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#define TOLERANCE 5
#define F_LIM 1000000000 
#define NUM_PROC 5
void f() {
   for(int i=0;i<F_LIM;i++){
    ;
   }
}

int
throughput(int pri)
{
    int start = uptime();
    for (int i = 0; i < NUM_PROC; i++) {
        int pid = fork();
        if (pid < 0) {
            printf(1, "fork failed\n");
            exit();
        }
        else if (pid == 0) {
            nice(pid,pri);
            f();
            exit();
        }
    }

    for (int i = 0; i < 5; i++) {
        wait();
    }
    int end = uptime();
    int time = (end - start);
    int thru = (NUM_PROC*10)/time;
    return thru;
}
void prischedtest()
{
  printf(1, "priority scheduling working...\n");
  int pid1=-1,pid2=-1;
  pid1 = fork();
  if (pid1 < 0)
  {
    printf(1, "fork failed!\n");
    exit();
  }
  else if (pid1 == 0)
  {
    nice(getpid(), 2);
    while (1)
    {
      ;
    }
    exit();
  }
  else
  {
    pid2 = fork();
    if (pid2 < 0)
    {
      printf(1, "fork failed!\n");
      exit();
    }
    else if (pid2 == 0)
    {
      nice(getpid(), 4);
      while(1)
      {
        ;
      }
      exit();
    }
    else
    {
      sleep(800);
      int c1, c2;
      c1 = getchosen(pid1);
      c2 = getchosen(pid2);
      int diff = c2 - (c1 * 2);
      if (diff < 0)
      {
        diff *= (-1);
      }
      if (diff <= TOLERANCE)
      {
        printf(1, "ok\n");
      }
      else
      {
        printf(2, "failed\n");
      }
    }
  }
  return;
}
int main()
{;
  prischedtest();
  printf(1,"Throughput via priority scheduling is: %d process/sec\n",throughput(4));
  printf(1,"Throughput via round robin scheduling is: %d process/sec\n",throughput(1));
  exit();
}