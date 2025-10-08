#ifndef CLIENT_H
#define CLIENT_H

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
#include <signal.h>

//Definitions
#define MAX_CLIENTS 10
#define MAX_DESTINATION_LEN 167
#define BUFFER_SIZE 512
#define TTK 120
#define kMenuOptionOne 1
#define kMenuOptionTwo 2
#define kMenuOptionThree 3
#define kSizeOfString 100
#define kSuccess 0
#define kEmpty 0
#define kNegativeAge 0
#define kMaxLengthName 100
#define kMaxAge 999
#define kMaxAddressLength 150

//Structs

typedef struct {
	char firstName[kSizeOfString];
	char lastName[kSizeOfString];
	int age;
	char address[kSizeOfString];
}Client;

typedef struct {
    Client clients[MAX_CLIENTS];
    int client_count;
    char destination[MAX_DESTINATION_LEN];
} Party;

//Prototypes
int mainProgram(void);
void displayMenu();
int isANumber();
void isAString(char* str, int);
void isAddress(char* str, int);
void InitParty(Party *p);
int AddClient(Party *p, Client *c);
int AddDestination(Party *p, int);
void runClientFlow(int fd);
void LogEvent(int fd, const char* message);
int idleCheck(char* buffer, size_t size, int timeout_sec);
int GetValidIntegerInput(int fd);
int modeSelect(char*,size_t, int);
void clearBuffer(void);


#endif /* CLIENT_H */
