#ifndef SEAT_H_
#define SEAT_H_

#include <semaphore.h>

typedef struct{
    int seatNum;
    int clientId;
    int reserved;
    int waiting;
    //sem_t sem_seat;
} Seat;

void initSeat(Seat* s);

int isSeatFree(Seat *seats, int seatNum);
void bookSeat(Seat *seats, int seatNum, int clientId);
void freeSeat(Seat *seats, int seatNum);

#endif