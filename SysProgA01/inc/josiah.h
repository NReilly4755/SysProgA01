#ifndef JOSIAH_H
#define JOSIAH_H

//Include necessary headers
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//Constants
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

typedef struct {
	char firstName[kSizeOfString];
	char lastName[kSizeOfString];
	int age;
	char address[kSizeOfString];
}Client;

//Function prototypes
int mainProgram(void);
void displayMenu();
int isANumber();
void isAString(char* str);
void isAddress(char* str);

#endif