#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
int c = 0, c1 = 0, c2 = 0, run = 1;
threadlock * tlock;
void thread1(void *arg)
{
  int num = *(int *)arg;
  while (run == 1)
  {

    if (num!=0)
      acquire_threadlock(tlock);
    c++;
    c1++;
    printf(1,"Thread id:%d.Process Id:%d\n",gettid(),getpid());
    printf(1,"c:%d,c1:%d\n",c,c1);
    if (num!=0)
      release_threadlock(tlock);
  }
  exit();
}
void thread2(void *arg)
{
  int num = *(int *)arg;
  while (run == 1)
  {

    if (num!=0)
      acquire_threadlock(tlock);
    c++;
    c2++;
    printf(1,"Thread id:%d.Process Id:%d\n",gettid(),getpid());
    printf(1,"c:%d,c2:%d\n",c,c2);
    if (num!=0)
      release_threadlock(tlock);
  }
  exit();
}
int main(int argc, char *argv[])
{
  
  init_threadlock(tlock);
  int arg = atoi(argv[1]);
  thread_create(&thread1, (void *)&arg);
  thread_create(&thread2, (void *)&arg);
  sleep(200);
  run=0;
  thread_join();
  thread_join();
  printf(1,"c:%d,c1:%d,c2:%d\n",c,c1,c2);
  exit();
}