#ifndef SERVER_H_
#define SERVER_H_

#include "request.h"
#include "Seat.h"

sem_t * getSemaphore();
Request * getReqBuffer();
int * getWasPicked();
int getTerminateServer();
Seat* getSeatsArray();
int getSeatsArraySize();

#endif