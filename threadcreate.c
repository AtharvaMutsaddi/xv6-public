#include "types.h"
#include "stat.h"
#include "user.h"


void f(void * arg){
  printf(1,"I am a thread:%d created from proc:%d\n",gettid(),getpid());
  sleep(1000);
}
int
main(int argc, char *argv[])
{
  int arg=0;
  for(int i=0;i<5;i++){
    thread_create(&f,(void*)&arg);
  }
  for(int i=0;i<5;i++){
    thread_join();
  }  
  
  exit();
}
