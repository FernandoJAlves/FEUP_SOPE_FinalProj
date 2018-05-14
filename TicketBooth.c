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
#include "sregist.h"

int initAnswers(int clientPid,char * path){
	int ans;
    sprintf(path,"ans%05d",clientPid);
    ans = open(path,O_WRONLY);
    return ans;
}

int validate_request(Request r){
	int seat_n;

	if(r.error){
		return -4;
	}

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
	sem_t * semAccess = getReservationSem();

	sem_wait(semAccess);

	int current_res_counter = 0;

	int * toFreeArray = (int*) malloc(sizeof(int)*req.array_size);
	
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
			sem_post(semAccess);
			return current_res_counter;
		}

	}

	//não conseguiu reservar o pedido completo

	for(int i = 0; i < req.array_size; i++){
		if(toFreeArray[i]){
			freeSeat(arraySeats, req.prefered_seats[i]);
		}
	}

	for(int i = 0; i < getSeatsArraySize();i++){
		if(!arraySeats[i].reserved){
			sem_post(semAccess);
			return -5;
		}
	}

	sem_post(semAccess);
	return -6;	
}

void* ticket_booth(void * arg){
	char path[100];
	int boothNum = *((int*)arg);
	int ans,returnValue;
	int reservedSeats[MAX_CLI_SEATS];
	Request * req = NULL;
	boothMsg(boothNum,"OPEN");
	while(!getTerminateServer()){

		//buscar request
		
		req = getRequest();
		
		if(req == NULL)
			continue;

		//tratar
		returnValue = validate_request(*req);
		if(returnValue == 0){
			returnValue = reserveSeats(reservedSeats, *req);
			printf("final size: %d\n",returnValue);
		}
		else{
			printf("error: %d\n",returnValue);
		}

		writeAnswer(boothNum,req,returnValue,reservedSeats);

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

	boothMsg(boothNum,"CLOSED");

	return NULL;
}

