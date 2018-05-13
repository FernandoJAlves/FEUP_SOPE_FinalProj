#include "TicketBooth.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

#include "macros.h"
#include "server.h"
#include "Seat.h"

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

	if(r.array_size < r.num_wanted_seats || r.array_size > MAX_CLI_SEATS){
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

Request * getRequest(){
	sem_t * semReq = getSemaphore();
	Request * req = NULL;
	
	sem_wait(semReq);
	int * picked = getWasPicked();
	if(!(*picked)){
		req = getReqBuffer();

			
		*picked = 1;
	}
	sem_post(semReq);

	return req;
}

int reserveSeats(int * reservedSeats, Request req){

	Seat * arraySeats = getSeatsArray();

	int current_res_counter = 0;

	int * toFreeArray = (int*) malloc(sizeof(int)*req.array_size);

	//
	
	for(int i = 0; i < req.array_size; i++){

		toFreeArray[i] = 1;

		if(isSeatFree(arraySeats, req.prefered_seats[i])){
			bookSeat(arraySeats, req.prefered_seats[i], req.client_id);
			reservedSeats[current_res_counter] = req.prefered_seats[i];
			current_res_counter++;
		}
		else{
			toFreeArray[i] = 0;
		}


		if(current_res_counter == req.num_wanted_seats){
			for(int j = 0; j <= i; j++){
				sem_post(&(arraySeats[req.prefered_seats[j]-1].sem_seat));
			}
			return current_res_counter;
		}

	}

	//não conseguiu reservar o pedido completo

	for(int i = 0; i < req.array_size; i++){
		if(toFreeArray[i]){
			freeSeat(arraySeats, req.prefered_seats[i]);
		}
		sem_post(&(arraySeats[req.prefered_seats[i]-1].sem_seat));
	}

	return 0;
}

void* ticket_booth(){
	char path[100];
	int ans,returnValue;
	int reservedSeats[MAX_CLI_SEATS];
	Request * req = NULL;

	while(!getTerminateServer()){
		//buscar request
		
		
		req = getRequest();
		
		if(req == NULL)
			continue;

		
		//tratar
		returnValue = validate_request(*req);
		if(returnValue == 0){
			returnValue = reserveSeats(reservedSeats, *req);
			printf("fine: %d\n",returnValue);
		}
		


		//enviar resposta
		ans = initAnswers(req->client_id,path);
		sendAnswer(ans,returnValue);
		if(returnValue > 0){
			for(int i = 0; i < returnValue; i++){
				sendAnswer(ans,reservedSeats[i]);
				printf("sent: %d\n",reservedSeats[i]);
			}
		}


		terminate(ans,path);
		
	}

	

	//sendAnswer(ans);
	return NULL;
}

