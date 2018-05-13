#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "macros.h"

int clientlog,cbook;

void writeFile(char * msg, int fd){
    write(fd,msg,strlen(msg));
}

void writeClog(char *msg)
{
    writeFile(msg, clientlog);
}


void writeCbook(char *msg)
{
    writeFile(msg, cbook);
}

void openFiles(){
    clientlog=open("clog.txt",O_WRONLY|O_APPEND|O_CREAT,0644);
    cbook=open("cbook.txt",O_WRONLY|O_APPEND|O_CREAT,0644);
}

void closeFiles()
{
    close(clientlog);
    close(cbook);
}


void writeSeats(int *seatsReserved, int ansNum){
    char temp[16];
    if(ansNum < 0){
        return;
    }
    for(int i = 0; i < ansNum; i++){
      if(seatsReserved[i] == 0)
        break;

      sprintf(temp,"%0*d\n",WIDTH_SEAT,seatsReserved[i]);
      writeCbook(temp);
    }
}
