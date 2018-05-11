#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "server.h"

int requests;

int main(int argc, char *argv[]) {
  printf("** Running Server **\n");

  if (argc == 4){
    printf("ARGS: %s | %s | %s\n", argv[1], argv[2],argv[3]);
  }

  sleep(1);

  return 0;
}


int initFIFOs(){
  mkfifo("requests",0660);
  requests = open("requests",O_RDONLY);
  return 0;
}


