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

  int num_room_seats = argv[1];
  int num_ticket_offices = argv[2];
  int open_time = argv[3];


  int start_time = 0; // use C function to get the start time of the program

  while(!time_is_over(start_time, open_time)){

  	//All the code will be in here

  	



  }




  return 0;
}


int initFIFOs(){
  mkfifo("requests",0660);
  requests = open("requests",O_RDONLY);
  return 0;
}


bool time_is_over(int start_time, int interval){

	//use the C function to get current time and see if the dif between that and start_time is greater than the given interval (in seconds)

	return false;
}
