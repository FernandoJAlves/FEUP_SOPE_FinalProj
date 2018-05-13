#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

#include "macros.h"
#include "request.h"

int requests;

void initRequestsFIFO();
int initAnswers(char * path);
int readAnswer(int ans, int * Seats, int * listSize);
void terminate(char * path, int ans);
int * parseArray(int * actualSize, char * list);
int sizeOfArray(char * list);
void sendRequest(Request * r);

int main(int argc, char *argv[]) {
  char path[100];
  int ans;
  int seatsSelected[MAX_CLI_SEATS];
  printf("** Running process %d (PGID %d) **\n", getpid(), getpgrp());

  if (argc == 4)
    printf("ARGS: %s | %s | %s\n", argv[1], argv[2], argv[3]);


  int answerReceived = 0;
  int timeout = atoi(argv[1]);
  int requestNum = atoi(argv[2]);
  char * seatList = argv[3];
  int answerSize;
  int sizeList;
  int * list = parseArray(&sizeList, seatList);
  initRequestsFIFO();
  
  sleep(1);
  
  Request r;
  initRequest(&r,getpid(),requestNum,list,sizeList);
  sendRequest(&r);
  ans = initAnswers(path);




  time_t start_time = time(NULL);
  while(timeout > difftime(time(NULL),start_time) && !answerReceived){
    answerReceived = readAnswer(ans,seatsSelected,&answerSize);
  }
  terminate(path, ans);
  return 0;
}

void initRequestsFIFO(){
  requests = open("requests",O_WRONLY | O_NONBLOCK);
  if(requests == -1){
    perror("Server not found");
    exit(1);
  }

}

int initAnswers(char * path){
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

  *listSize = num;
  return 1;
}

void terminate(char * path, int ans){
  close(requests);
  close(ans);

  if(unlink(path)<0)
    printf("Error when destroying FIFO '%s0'\n",path);
}

int * parseArray(int * actualSize, char * list){
  *actualSize = sizeOfArray(list);
  int * data = (int*) malloc(sizeof(int)*(*actualSize));
  
  int count = 0;
  char* end = list;
  while(*end){
    data[count] = strtol(list, &end,10);
    while(*end == ' '){
      end++;
    }
    list = end;
    count++;
  }
  //printf("size: %d\n",*actualSize);
  //printf("first ele: %d\n",data[0]);
  return data;
}

int sizeOfArray(char * list){
  char* end = list;
  int counter = 0;
  while(*end){
    strtol(list, &end,10);
    counter++;
    while(*end == ' '){
      end++;
    }
    list = end;
  }
  return counter;
}

void sendRequest(Request * r){
  write(requests,r,sizeof(Request));
}