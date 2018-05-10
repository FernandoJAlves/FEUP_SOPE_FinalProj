#include "TicketBooth.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>


int ans;

int initAnswers(int clientPid){
    char path[100];
    sprintf(path,"ans%05d",getpid());
    ans = open(path,O_RDONLY);
    return 0;
}