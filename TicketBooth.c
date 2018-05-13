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

	printf("A\n");
	if(!(r.array_size >= r.num_wanted_seats && r.array_size <= MAX_CLI_SEATS)){
		return -2;
	}
	printf("B\n");
	printf("%d\n",r.array_size);
	for(int i = 0; i < r.array_size; i++){
		printf("C\n");
		seat_n = r.prefered_seats[i];
		if(!(seat_n >= 1 && seat_n <= MAX_CLI_SEATS)){
			return -3;
		}
	}
	printf("D\n");
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

int reserveSeats(int * reservedSeats){
	int counter = 0;
	return counter;
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
		printf("%d\n",req->prefered_seats[0]);
		returnValue = validate_request(*req);
		printf("It didn't work\n");
		if(returnValue > 0){
			returnValue = reserveSeats(reservedSeats);
		}
		
		//enviar resposta
		ans = initAnswers(req->client_id,path);
		sendAnswer(ans,returnValue);
		terminate(ans,path);
		
	}

	

	//sendAnswer(ans);
	return NULL;
}

