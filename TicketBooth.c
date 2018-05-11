#include "TicketBooth.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

#include "request.h"
#include "server.h"

int ans;

int initAnswers(int clientPid){
    char path[100];
    sprintf(path,"ans%05d",getpid());
    ans = open(path,O_RDONLY);
    return 0;
}

int validate_request(Request r){

	if(!(r.num_wanted_seats >= 1 && r.num_wanted_seats <= MAX_CLI_SEATS)){
		return -1;
	}


	if(!(r.array_size >= r.num_wanted_seats && r.array_size <= MAX_CLI_SEATS)){
		return -2;
	}

	for(int i = 0; i < r.array_size; i++){
		int seat_n = *(r.prefered_seats + i*sizeof(int)); //Não tenho a certeza se funciona!
		if(!(seat_n >= 1 && seat_n <= MAX_CLI_SEATS)){
			return -3;
		}
	}

	return 0;
}


int ticket_booth(){

	// "Recolher" um request
	// Validar o request
	


	return 0;
}