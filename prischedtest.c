#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void prischedtest()
{
  printf(1, "Priority Scheduling test...\n");
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
      printf(1, "Number of times proc 1 chosen : %d\n", c1);
      printf(1, "Number of times proc 2 chosen : %d\n", c2);
      int diff = c2 - (c1 * 2);
      if (diff < 0)
      {
        diff *= (-1);
      }
      if (diff <= 5)
      {
        printf(1, "pri sched passed!");
      }
      else
      {
        printf(2, "Pri sched failed!\n");
      }
    }
  }
  exit();
}
int main()
{
  prischedtest();
}