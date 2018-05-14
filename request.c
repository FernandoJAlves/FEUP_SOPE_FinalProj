#include "request.h"

void initRequest(Request* req, int client_id){
    req->client_id = client_id;
    req->error = 0;
}


