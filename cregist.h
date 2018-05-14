#ifndef REGIST_H_
#define REGIST_H_


//void boothMsg(int boothNum,char * msg);
void writeClog(char * msg);
void writeCbook(char *msg);
void writeReservations(int clientId, int * seatsReserved, int ansNum);
void writeSeats(int *seatsReserved, int seatsNum);
void openFiles();
void closeFiles();

#endif
