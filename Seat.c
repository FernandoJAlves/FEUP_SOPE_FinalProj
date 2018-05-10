#include "Seat.h"

#define DELAY() sleep(1)

int isSeatFree(Seat *seats, int seatNum){
    return !(seats[seatNum].reserved);
}

void bookSeat(Seat *seats, int seatNum, int clientId){
    seats[seatNum].reserved = 1;
    seats[seatNum].clientId = clientId;
}

void freeSeat(Seat *seats, int seatNum){
    seats[seatNum].reserved = 0;
    seats[seatNum].clientId = 0;
}