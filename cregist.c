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

void writeReservations(int clientId, int * seatsReserved, int ansNum){
    char temp[512];
    char aux[512];
    int width;
    sprintf(temp,"%0*d ",WIDTH_PID,clientId);

    switch (ansNum)
    {
    case -1:
        strcat(temp, "MAX\n");
        writeClog(temp); 
        break;

    case -2:
        strcat(temp, "NST\n");
        writeClog(temp); 
        break;

    case -3:
        strcat(temp, "IID\n");
        writeClog(temp); 
        break;

    case -4:
        strcat(temp, "ERR\n");
        writeClog(temp); 
        break;

    case -5:
        strcat(temp, "NAV\n");
        writeClog(temp); 
        break;

    case -6:
        strcat(temp, "FUL\n");
        writeClog(temp); 
        break;

    default:
        for (int i = 0; i < ansNum; i++)
        {
            width = (WIDTH_XXNN-1)/2;
            sprintf(aux, "%s%0*d.%0*d %0*d\n",temp,width,i+1,width,ansNum,WIDTH_SEAT,seatsReserved[i]);
            writeClog(aux);
            
        }
    } 
      
}
