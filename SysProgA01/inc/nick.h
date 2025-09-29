#ifndef NICK_H   
#define NICK_H

//Include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/select.h>
#include <time.h>

//Define TTK in seconds.
#define TTK 120

//Function prototypes
void LogEvent(int fd, const char* message);
int idleCheck(char* buffer, size_t size, int timeout_sec);
int GetValidIntegerInput(int fd);

#endif

