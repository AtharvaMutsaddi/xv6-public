#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
  if(argc!=2){
    printf(1,"Usage: createdummies priority");
    exit();
  }
  int pri = atoi(argv[1]);
  if (pri <= 1 || pri > 5)
  {
    printf(1, "Please enter priority between 2-5!\n");
    exit();
  }
  int pid = fork();
  if (pid < 0)
  {
    printf(1, "Error on fork!\n");
    exit();
  }
  else
  {
    nice(pid, pri);
    if (pid == 0)
    {
      int x=0;
      for (int z = 0; z < 4000000000; z += 1)
        x = x + 3.14 * 89.64; // Useless calculation to consume CPU Time
    }
    else
    {
      printf(1, "Process number:%d is creating new process:%d with priority:%d\n", getpid(), pid, pri);
      wait();
    }
  }
  exit();
}