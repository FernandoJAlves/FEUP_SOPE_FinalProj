#ifndef SEAT_H_
#define SEAT_H_

#include <semaphore.h>

typedef struct{
    int seatNum;
    int clientId;
    int reserved;
    sem_t sem_seat;
} Seat;

void initSeat(Seat* s);

#endif