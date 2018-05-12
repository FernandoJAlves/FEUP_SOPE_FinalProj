#include "TicketBooth.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

#include "request.h"
#include "macros.h"



int initAnswers(int clientPid,char * path){
	int ans;
    sprintf(path,"ans%05d",clientPid);
    ans = open(path,O_WRONLY);
    return ans;
}

int validate_request(Request r){
	int seat_n;
	if(!(r.num_wanted_seats >= 1 && r.num_wanted_seats <= MAX_CLI_SEATS)){
		return -1;
	}


	if(!(r.array_size >= r.num_wanted_seats && r.array_size <= MAX_CLI_SEATS)){
		return -2;
	}

	for(int i = 0; i < r.array_size; i++){
		//seat_n = *(r.prefered_seats + i*sizeof(int)); //Não tenho a certeza se funciona!
		seat_n = r.prefered_seats[i];
		if(!(seat_n >= 1 && seat_n <= MAX_CLI_SEATS)){
			return -3;
		}
	}

	return 0;
}

void terminate(int ans, char * path){
	close(ans);
}


int ticket_booth(){
	char path[100];
	int ans,clientPid;
	ans = initAnswers(clientPid,path);


	

	terminate(ans,path);
	return 0;
}