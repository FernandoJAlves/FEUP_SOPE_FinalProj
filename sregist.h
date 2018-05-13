#ifndef REGIST_H_
#define REGIST_H_

void boothMsg(int boothNum,char * msg);
void writeSlog(char * msg);
void writeAnswer(int boothNum, Request * req, int ansNum, int * reservedSeats);
void writeSeats(Seat * reservedSeats, int seatsNum);
void openFiles();
void closeFiles();

#endif