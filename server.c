#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>

#include "server.h"
#include "request.h"

int requests;
int wasPicked = 1; // 0 if wasn't picked, otherwise 1

sem_t semRequest;

Request buffer[1];

int isOpen(time_t start_time, int interval);
void readFIFO();
int initFIFOs();
int initSemaphores();

int main(int argc, char *argv[]) {
  printf("** Running Server **\n");

  if (argc == 4){
    printf("ARGS: %s | %s | %s\n", argv[1], argv[2],argv[3]);
  }

  sleep(1);
  initFIFOs();
  initSemaphores();

  //Initialize bilheteiras

  int num_room_seats = atoi(argv[1]);
  int num_ticket_offices = atoi(argv[2]);
  int open_time = atoi(argv[3]);


  time_t start_time = time(NULL); // use C function to get the start time of the program

  while(isOpen(start_time, open_time)){
    readFIFO();
  }




  return 0;
}


int initFIFOs(){
  mkfifo("requests",0660);
  requests = open("requests",O_RDONLY);
  return 0;
}

int initSemaphores(){
  sem_init(&semRequest,0,1);
  return 0;
}


int isOpen(time_t start_time, int interval){

  if(interval < difftime(time(NULL),start_time)){
    return 1;
  }
  else return 0;
}

void readFIFO(){
  sem_wait(&semRequest);
  if(wasPicked){
    read(requests,&buffer,sizeof(Request));
    wasPicked = 0;
  } 
  sem_post(&semRequest); 
}
