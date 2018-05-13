#ifndef SERVER_H_
#define SERVER_H_

#include "request.h"

sem_t * getSemaphore();
Request * getReqBuffer();
int * getWasPicked();
int getTerminateServer();

#endif