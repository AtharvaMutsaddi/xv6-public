#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
int main(int argc, char * argv[]){
    int offset;
    if(argc < 4){
        printf(1,"Usage: %s filename offset whence\n",argv[0]);
    } 
    int fd=open(argv[1],0);
    if(fd<0){
        printf(1,"Error opening the file\n");
        exit();
    }

    
    if (argv[2][0]=='-')
    {
        int offset_arg_size=strlen(argv[2]);
        char offset_arg[offset_arg_size];
        for (int i = 1; i < offset_arg_size; i++)
        {
            offset_arg[i-1]=argv[2][i];
        }
        offset_arg[offset_arg_size-1]='\0';
        offset=atoi(offset_arg);
        offset*=-1;
    }
    else{
        offset=atoi(argv[2]);
    }
    printf(1,"OFFSET:%d\n",offset);
    int whence=atoi(argv[3]);
    int newoffset=lseek(fd,offset,whence);
    if(newoffset>0){
        printf(1,"lseek worked correctly! New file offset=%d\n",newoffset);
        char buf[1];
        while (read(fd,buf,1)>0)
        {
            write(1,buf,1);
        }
        printf(1,"\n");
    }
    else
    {
        printf(2,"lseek failed!\n");
    }
    
    
    exit();
}
