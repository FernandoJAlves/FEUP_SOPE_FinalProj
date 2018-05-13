#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "macros.h"
#include "request.h"
#include "Seat.h"

int slog, sbook;

void writeFile(char *msg, int fd)
{
    //TODO semaphore
    write(fd, msg, strlen(msg));
}

void writeSlog(char *msg)
{
    writeFile(msg, slog);
}


void writeSbook(char *msg)
{
    writeFile(msg, sbook);
}

void openFiles()
{
    slog = open("slog.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
    sbook = open("sbook.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

void closeFiles()
{
    close(slog);
    close(sbook);
}

void boothMsg(int boothNum, char *msg)
{
    char tmp[1024];
    sprintf(tmp, "%02d-%s\n", boothNum, msg);
    writeSlog(tmp);
}

void writeAnswer(int boothNum, Request *req, int ansNum, int *reservedSeats)
{
    char temp[512];
    char aux[32];
    sprintf(temp, "%05d-%02d: ", req->client_id, req->num_wanted_seats);

    for (int i = 0; i < 5; i++)
    {

        if (i < req->array_size)
        {
            sprintf(aux, "%0*d ", WIDTH_SEAT, req->prefered_seats[i]);
        }
        else
        {
            sprintf(aux, "%*s ", WIDTH_SEAT, " ");
        }

        strcat(temp, aux);
    }

    strcat(temp, "- ");
    switch (ansNum)
    {
    case -1:
        strcat(temp, "MAX");
        break;

    case -2:
        strcat(temp, "NST");
        break;

    case -3:
        strcat(temp, "IID");
        break;

    case -4:
        strcat(temp, "ERR");
        break;

    case -5:
        strcat(temp, "NAV");
        break;

    case -6:
        strcat(temp, "FUL");
        break;

    default:
        for (int i = 0; i < req->num_wanted_seats; i++)
        {
            sprintf(aux, "%0*d ", WIDTH_SEAT, reservedSeats[i]);
            strcat(temp, aux);
        }
    }

    boothMsg(boothNum, temp);
}

void writeSeats(Seat * reservedSeats, int seatsNum){
    char temp[16];
    for(int i = 0; i < seatsNum; i++){
      if(reservedSeats[i].reserved)
      {
        sprintf(temp,"%0*d\n",WIDTH_SEAT,reservedSeats[i].seatNum);
        writeSbook(temp);
      }
    }
}
