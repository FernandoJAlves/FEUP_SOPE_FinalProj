#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#include "server.h"
#include "TicketBooth.h"
#include "Seat.h"

int requests;
int wasPicked = 1; // 0 if wasn't picked, otherwise 1
sem_t semRequest;
Request buffer[1];
Seat* seatsArray;
pthread_t * threadArray;
int terminateServer = 0; // 0 if continue, otherwise 1

int isOpen(time_t start_time, int interval);
void readFIFO();
int initFIFOs();
int initSemaphores();
int initAllSeats(int n_seats);
int initTicketBooths(int n_bilheteiras);

int main(int argc, char *argv[]) {
  printf("** Running Server **\n");

  if (argc == 4){
    printf("ARGS: %s | %s | %s\n", argv[1], argv[2],argv[3]);
  }
  else {
    exit(0);
  }
  printf("1\n");
  int num_room_seats = atoi(argv[1]);
  int num_ticket_offices = atoi(argv[2]);
  int open_time = atoi(argv[3]);

  sleep(1);
  
  initFIFOs();
  initSemaphores();
  initAllSeats(num_room_seats);
  initTicketBooths(num_ticket_offices);

  time_t start_time = time(NULL);

  while(isOpen(start_time, open_time)){
    readFIFO();
  }

  printf("The server will close.\nThank You for using our services.\n");
  return 0;
}


int initFIFOs(){
  mkfifo("requests",0660);
  printf("2\n");
  requests = open("requests",O_RDONLY | O_NONBLOCK);
  printf("3\n");
  return 0;
}

int initSemaphores(){
  sem_init(&semRequest,0,1);
  return 0;
}

int initAllSeats(int n_seats){
  seatsArray = (Seat*) malloc(sizeof(Seat) * n_seats);
  for(int i = 0; i < n_seats; i++){
    initSeat(&(seatsArray[i]));
  }
  return 0;
}

int initTicketBooths(int n_bilheteiras){
  threadArray = (pthread_t*) malloc(sizeof(pthread_t) * n_bilheteiras);
  for(int i = 0; i < n_bilheteiras; i++){
    pthread_create(&(threadArray[i]),NULL,ticket_booth,NULL);
  }
  return 0;
}

int isOpen(time_t start_time, int interval){

  if(interval > difftime(time(NULL),start_time)){
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

sem_t * getSemaphore(){
  return &semRequest;
}

Request * getReqBuffer(){
  return buffer;
}

int * getWasPicked(){
  return &wasPicked;
}