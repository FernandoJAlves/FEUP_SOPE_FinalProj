#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

#define MAX_ROOM_SEATS 9999
#define MAX_CLI_SEATS 99
#define WIDTH_PID 5
#define WIDTH_XXNN 5
#define WIDTH_SEAT 4

int main(int argc, char *argv[]) {
  printf("** Running process %d (PGID %d) **\n", getpid(), getpgrp());

  if (argc == 4)
    printf("ARGS: %s | %s | %s\n", argv[1], argv[2],arg[3]);

  sleep(1);

  return 0;
}