#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

#include "macros.h"

int requests;

int initFIFOs(char * path);
int readAnswer(int ans, int * Seats, int * listSize);
void terminate(char * path, int ans);

int main(int argc, char *argv[]) {
  char path[100];
  int ans;
  int seatsSelected[MAX_CLI_SEATS];
  printf("** Running process %d (PGID %d) **\n", getpid(), getpgrp());

  if (argc == 4)
    printf("ARGS: %s | %s | %s\n", argv[1], argv[2], argv[3]);

  

  sleep(1);
  ans = initFIFOs(path);
  int answerReceived = 0;
  int timeout = atoi(argv[1]);
  int requestNum = argv[2];
  int listSize;
  char * list = argv[3];

  time_t start_time = time(NULL);
  while(timeout > difftime(time(NULL),start_time) && !answerReceived){
  answerReceived = readAnswer(ans,seatsSelected,listSize);
  }
  terminate(path, ans);
  return 0;
}

int initFIFOs(char * path){
  requests = open("requests",O_WRONLY | O_NONBLOCK);
  if(requests == -1){
    perror("Server not found");
    exit(1);
  }
  int ans;
  sprintf(path,"ans%05d",getpid());
  mkfifo(path,0660);
  ans = open(path,O_RDONLY | O_NONBLOCK);
  return ans;
}

int readAnswer(int ans, int * seatsSelected, int * listSize){
  int num;
  int aux = read(ans,&num,sizeof(int));
  if(aux == 0){
    return 0;
  }
  if(num < 0){
    return num;
  }

  for(int i = 0; i < num;i++){
    read(ans,&seatsSelected[i],sizeof(int));
  }

  listSize = num;
  return 1;
}

void terminate(char * path, int ans){
  close(requests);
  close(ans);

  if(unlink(path)<0)
    printf("Error when destroying FIFO '%s0'\n",path);
}

