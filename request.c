#include "request.h"

void initRequest(Request* req, int client_id, int num_wanted_seats){
    req->client_id = client_id;
    req->num_wanted_seats = num_wanted_seats;

}


