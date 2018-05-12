#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int clientlog,cbook;

void writeFile(char * msg, int fd){
    //TODO semaphore
    write(fd,msg,strlen(msg));
}

void openFiles(){
    clientlog=open("clog.txt",O_WRONLY|O_APPEND|O_CREAT,0644);
    cbook=open("cbook.txt",O_WRONLY|O_APPEND|O_CREAT,0644);
}