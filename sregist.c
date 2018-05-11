#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int slog,sbook;

void writeFile(char * msg, int fd){
    //TODO semaphore
    write(fd,msg,strlen(msg));
}


void openFiles(){
    slog=open("slog.txt",O_WRONLY|O_APPEND|O_CREAT,0644);
    sbook=open("sbook.txt",O_WRONLY|O_APPEND|O_CREAT,0644);
}

void BoothMsg(int boothNum,char * msg){
    char tmp[100];
    sprintf(tmp,"%02d-%s",boothNum,msg);
    writeFile(tmp,slog);
}
