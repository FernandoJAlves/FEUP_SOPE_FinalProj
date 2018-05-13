#include "Seat.h"
#include <unistd.h>

#define DELAY() sleep(1)

int seat_count = 1;

int isSeatFree(Seat *seats, int seatNum){
    sem_wait(&(seats[seatNum-1].sem_seat));
    DELAY();
    int temp = !(seats[seatNum-1].reserved);
    return temp;
}

void bookSeat(Seat *seats, int seatNum, int clientId){
    seats[seatNum-1].reserved = 1;
    seats[seatNum-1].clientId = clientId;
    DELAY();
}

void freeSeat(Seat *seats, int seatNum){
    seats[seatNum-1].reserved = 0;
    seats[seatNum-1].clientId = 0;
    DELAY();
}

void initSeat(Seat* s){
    s->clientId = 0;
    s->reserved = 0;
    s->seatNum = seat_count;
    sem_init(&(s->sem_seat),0,1);
    seat_count++;
}