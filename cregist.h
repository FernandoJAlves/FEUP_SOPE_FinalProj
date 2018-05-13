#ifndef REGIST_H_
#define REGIST_H_


//void boothMsg(int boothNum,char * msg);
void writeClog(char * msg);
void writeCbook(char *msg);
//void writeAnswer(int boothNum, Request * req, int ansNum, int * reservedSeats);
void writeSeats(int *seatsReserved, int seatsNum);
void openFiles();
void closeFiles();

#endif
