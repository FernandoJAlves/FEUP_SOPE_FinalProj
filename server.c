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
#include "sregist.h"

int requests;
int wasPicked = 1; // 0 if wasn't picked, otherwise 1
sem_t semRequest;
sem_t semMakeFullRes;
Request buffer[1];
Seat* seatsArray;
int seatsArraySize;
pthread_t * threadArray;
int terminateServer = 0; // 0 if continue, otherwise 1

int isOpen(time_t start_time, int interval);
void readFIFO();
int initFIFOs();
int initSemaphores();
int initAllSeats(int n_seats);
int initTicketBooths(int n_bilheteiras);
void terminateFIFOs();

int main(int argc, char *argv[]) {
  printf("** Running Server **\n");

  if (argc == 4){
    printf("ARGS: %s | %s | %s\n", argv[1], argv[2],argv[3]);
  }
  else {
    exit(0);
  }
  int num_room_seats = atoi(argv[1]);
  int num_ticket_offices = atoi(argv[2]);
  int open_time = atoi(argv[3]);

  initFIFOs();

  sleep(1);
  
  initSemaphores();
  initAllSeats(num_room_seats);
  seatsArraySize = num_room_seats;
  openFiles();
  initTicketBooths(num_ticket_offices);
  time_t start_time = time(NULL);

  while(isOpen(start_time, open_time)){
    readFIFO();
  }
  
  terminateFIFOs();
  terminateServer = 1;
  for(int i = 0; i < num_ticket_offices;i++){
    pthread_join(threadArray[i], NULL);
  }

  writeSlog("SERVER CLOSED");
  writeSeats(seatsArray,num_room_seats);
  closeFiles();
  printf("The server will close.\nThank You for using our services.\n");
  return 0;
}


int initFIFOs(){
  mkfifo("requests",0660);
  requests = open("requests",O_RDONLY | O_NONBLOCK);
  return 0;
}

int initSemaphores(){
  sem_init(&semRequest,0,1);
  sem_init(&semMakeFullRes,0,1);
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
  int * boothNums = (int*)malloc(sizeof(int)*n_bilheteiras); 
  for(int i = 0; i < n_bilheteiras; i++){
    boothNums[i] = i+1;
    pthread_create(&(threadArray[i]),NULL,ticket_booth,&boothNums[i]);
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
  int n = 0;
  if(wasPicked){
    n = read(requests,&buffer,sizeof(Request));
    if(n > 0){
      wasPicked = 0;
    }
  } 
  sem_post(&semRequest); 
}

void terminateFIFOs(){
  close(requests);
  unlink("requests");
}

sem_t * getSemaphore(){
  return &semRequest;
}

sem_t * getReservationSem(){
  return &semMakeFullRes;
}

Request * getReqBuffer(){
  return buffer;
}

int * getWasPicked(){
  return &wasPicked;
}

int getTerminateServer(){
  return terminateServer;
}

Seat* getSeatsArray(){
  return seatsArray;
}

int getSeatsArraySize(){
  return seatsArraySize;
}
