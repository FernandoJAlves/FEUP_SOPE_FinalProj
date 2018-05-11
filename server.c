#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>


#include "server.h"

int requests;

int isOpen(time_t start_time, int interval);

int main(int argc, char *argv[]) {
  printf("** Running Server **\n");

  if (argc == 4){
    printf("ARGS: %s | %s | %s\n", argv[1], argv[2],argv[3]);
  }

  sleep(1);

  int num_room_seats = atoi(argv[1]);
  int num_ticket_offices = atoi(argv[2]);
  int open_time = atoi(argv[3]);


  time_t start_time = time(NULL); // use C function to get the start time of the program

  while(isOpen(start_time, open_time)){

  	//All the code will be in here

  	



  }




  return 0;
}


int initFIFOs(){
  mkfifo("requests",0660);
  requests = open("requests",O_RDONLY);
  return 0;
}


int isOpen(time_t start_time, int interval){

  if(interval < difftime(time(NULL),start_time)){
    return 1;
  }
  else return 0;
}
