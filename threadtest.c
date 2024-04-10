#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
int c = 0, c1 = 0, c2 = 0, run = 1;
threadlock *tlock;
void thread1(void *arg)
{
  int num = *(int *)arg;
  printf(1, "Thread id:%d.Process Id:%d\n", gettid(), getpid());
  for (int i = 0; i < 50; i++)
  {
    acquire_threadlock(tlock);
    c+=num;
    c1+=num;
    release_threadlock(tlock);
  }
  exit();
}
void thread2(void *arg)
{
  int num = *(int *)arg;
  printf(1, "Thread id:%d.Process Id:%d\n", gettid(), getpid());
  for (int i = 0; i < 50; i++)
  {
    acquire_threadlock(tlock);
    c+=num;
    c2+=num;
    release_threadlock(tlock);
  }
  exit();
}
void threadtest()
{

  init_threadlock(tlock);
  int arg = 1;
  thread_create(&thread1, (void *)&arg);
  thread_create(&thread2, (void *)&arg);
  printf(1,"The print statements are not synchronized and may be subject to not being printed in order\n");
  for (int i = 0; i < 50; i++)
  {
    ;
  }
  // run = 0;
  thread_join();
  thread_join();
  printf(1, "c:%d,c1:%d,c2:%d\n", c, c1, c2);
  if(c==(c1+c2)){
    printf(1,"Thread test pass\n");
  }
  else{
    printf(1,"Thread test failed\n");
  }
  return;
}

int main(){
  threadtest();
  exit();
}