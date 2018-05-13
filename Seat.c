#include "Seat.h"

#define DELAY() sleep(1)

int seat_count = 1;

int isSeatFree(Seat *seats, int seatNum){
    DELAY();
    return !(seats[seatNum-1].reserved);   
}

void bookSeat(Seat *seats, int seatNum, int clientId){
    DELAY();
    seats[seatNum-1].reserved = 1;
    seats[seatNum-1].clientId = clientId;
    
}

void freeSeat(Seat *seats, int seatNum){
    DELAY();
    seats[seatNum-1].reserved = 0;
    seats[seatNum-1].clientId = 0;
    
}

void initSeat(Seat* s){
    s->clientId = 0;
    s->reserved = 0;
    s->seatNum = seat_count;
    sem_init(&(s->sem_seat),0,1);
    seat_count++;
}