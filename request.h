#ifndef REQUEST_H_
#define REQUEST_H_

#include "macros.h"

typedef struct{
    int client_id;
    int num_wanted_seats;
    int prefered_seats[MAX_CLI_SEATS];
    int array_size;

    //TODO


} Request;

void initRequest(Request* req, int client_id, int num_wanted_seats,int array_size);

#endif