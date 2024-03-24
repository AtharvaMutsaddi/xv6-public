#include "types.h"
#include "stat.h"
#include "user.h"

int c = 0;
int c1 = 0;
int c2 = 0;
int run=1;
threadlock *tlock;
void f1(void *synch_val)
{

    int synch = *((int *)synch_val);
    if (synch)
    {
        acquire_threadlock(tlock);
    }
    while (run==1)
    {
        c++;
        c1++;
    }
    if (synch)
    {
        release_threadlock(tlock);
    }
}
void f2(void *synch_val)
{
    int synch = *((int *)synch_val);
    if (synch)
    {
        acquire_threadlock(tlock);
    }
    while (run==1)
    {
        c++;
        c2++;
    }
    if (synch)
    {
        release_threadlock(tlock);
    }
}
void f3(void *a)
{
    printf(1, "Hello\n");
}
void f4(void *a)
{
    printf(1, "Hi\n");
}
int main(int argc, char *argv[])
{
    threadlock_init(tlock);
    int synch = 0;
    thread_create(&f1, (void *)&synch);
    thread_join();
    thread_create(&f2, (void *)&synch);
    thread_join();
    sleep(2);
    run=0;
    printf(1, "c:%d,c1:%d,c2:%d\n", c, c1, c2);
    exit();
}
