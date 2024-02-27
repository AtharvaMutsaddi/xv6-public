#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
  int priority, pid;
  if(argc < 3){
    printf(2,"Usage: nice pid priority\n");
    exit();
  }
  pid = atoi(argv[1]);
  priority = atoi(argv[2]);
  if (priority < 0 || priority > 5){
    printf(2,"Enter priority between (0-5)\n");
    exit();
  }
  if(nice(pid,priority)<0){
    printf(2,"PID not found...\n");
  }
  printf(1,"Set priority of %d to %d\n",pid,priority);
  exit();
}