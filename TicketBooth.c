#include "TicketBooth.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

#include "macros.h"
#include "server.h"

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

void sendAnswer(int ans,int num){
	write(ans,&num,sizeof(int));
}

Request getRequest(){
	sem_t * semReq = getSemaphore();
	Request req;
	
	sem_wait(semReq);
	int * picked = getWasPicked();
	if(!(*picked)){
		Request * pedido = getReqBuffer();
		req = *pedido;
		*picked = 1;
	}
	sem_post(semReq);
	return req;
}

int reserveSeats(int * reservedSeats){
	int counter = 0;
	return counter;
}

void* ticket_booth(){
	char path[100];
	int ans,returnValue;
	int reservedSeats[MAX_CLI_SEATS];

	while(0/*!terminateServer*/){
		//buscar request
		Request req = getRequest();
		

		//tratar
		returnValue = validate_request(req);
		if(returnValue > 0){
			returnValue = reserveSeats(reservedSeats);
		}
		
		//enviar resposta
		ans = initAnswers(req.client_id,path);
		sendAnswer(ans,returnValue);
		terminate(ans,path);
	}

	

	//sendAnswer(ans);
	return NULL;
}

