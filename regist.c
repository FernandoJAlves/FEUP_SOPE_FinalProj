#include <string.h>
#include <unistd.h>

int writeFile(char * msg, int fd){
    //TODO semaphore
    write(fd,msg,strlen(msg));
    return 0;
}