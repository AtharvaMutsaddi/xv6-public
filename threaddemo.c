#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#define SLEEP_TIME 100

lock_t* lk;
int c=0;
void f1(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  if (num) lock_acquire(lk);
  c+=1;
  sleep(SLEEP_TIME);
  if (num) lock_release(lk);
  exit();
}

void f2(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  if (num) lock_acquire(lk);
  c+=2;
  sleep(SLEEP_TIME);
  if (num) lock_release(lk);
  exit();
}

void f3(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  if (num) lock_acquire(lk);
  c=((c/3)  + (c%3));
  sleep(SLEEP_TIME);
  if (num) lock_release(lk);
  exit();
}

int
main(int argc, char *argv[])
{
  lock_init(lk);
  int arg1 = 1, arg2 = 1;

  printf(1, "below should be sequential print statements:\n");
  thread_create(&f1, (void *)&arg1, (void *)&arg2);
  thread_create(&f2, (void *)&arg1, (void *)&arg2);
  thread_create(&f3, (void *)&arg1, (void *)&arg2);
  thread_join();
  thread_join();
  thread_join();
  printf(1,"%d\n",c);
  arg1 = 0;
  printf(1, "below should be a jarbled mess:\n");
  thread_create(&f1, (void *)&arg1, (void *)&arg2);
  thread_create(&f2, (void *)&arg1, (void *)&arg2);
  thread_create(&f3, (void *)&arg1, (void *)&arg2);
  thread_join();
  thread_join();
  thread_join();
  printf(1,"%d\n",c);
  exit();
}