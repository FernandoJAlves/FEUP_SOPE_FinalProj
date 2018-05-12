#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "macros.h"

int requests;

int initFIFOs(char * path);
void readAnswer(int ans);
void terminate(char * path, int ans);

int main(int argc, char *argv[]) {
  char path[100];
  int ans;
  printf("** Running process %d (PGID %d) **\n", getpid(), getpgrp());

  if (argc == 4)
    printf("ARGS: %s | %s | %s\n", argv[1], argv[2], argv[3]);

  

  sleep(1);
  ans = initFIFOs(path);
  readAnswer(ans);
  terminate(path, ans);
  return 0;
}

int initFIFOs(char * path){
  int ans;
  sprintf(path,"ans%05d",getpid());
  mkfifo(path,0660);
  ans = open(path,O_RDONLY);
  requests = open("requests",O_WRONLY);
  return ans;
}

void readAnswer(int ans){
  int num;
  int answers[MAX_CLI_SEATS];
  read(ans,(unsigned char *)&num,sizeof(int));
}

void terminate(char * path, int ans){
  close(requests);
  close(ans);

  if(unlink(path)<0)
    printf("Error when destroying FIFO '%s0'\n",path);
}

