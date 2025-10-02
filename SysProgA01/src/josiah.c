#include "josiah.h"
#include "rodrigo.h"
#include "bibi.h"


#pragma warning(disable:4996)


// FUNCTION : isAString
// DESCRIPTION :
// This function will keep asking the user for a valid string 
// PARAMETERS :
// char* str: the str to validated
// RETURNS: 
// NONE
//

void isAString(char* str) {
    char buffer[256]; //more buffer to handle all the the strings
    bool run = true;
    while (run) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Input ERROR, try again: ");
            continue;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        run = false;

        size_t len = strlen(buffer);
        if (len == 0) {
            printf("Input cannot be empty, enter letters only: ");
            run = true;
            continue;
        }
        if (len > 100) {
            printf("Input too long, enter a shorter name: ");
            run = true;
            continue;
        }
        for (size_t i = 0; buffer[i] != '\0'; i++) {
            if (!((buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z'))) {
                printf("Invalid input! Please enter letters only: ");
                run = true;
                break;
            }
        }
    }
    strncpy(str, buffer, kSizeOfString);
    str[kSizeOfString - 1] = '\0';
}

// FUNCTION : isANumber
// DESCRIPTION :
// This function will keep asking the user for a valid number
// PARAMETERS :
// NONE
// RETURNS: the validated number
// NONE
//

int isANumber()
{
    int value;
    char buffer[256];
    while (true)
    {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Invalid input! please enter a normal number: ");
            continue;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        if (sscanf(buffer, "%d", &value) == 1)
        {
            if (value > 999) {
                printf("Age invalid, please enter a valid age: ");
                continue;
            }
            return value;
        }
        printf("Invalid input! Please enter a valid number: ");
    }
}
// FUNCTION : isAStisAddressring
// DESCRIPTION :
// This function will keep asking the user for a valid address string 
// PARAMETERS :
// char* str: the str to validated
// RETURNS: 
// NONE
//

void isAddress(char* str) {
    char buffer[512];
    bool run = true;
    while (run) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Input error. Try again: ");
            continue;
        }
        buffer[strcspn(buffer, "\n")] = '\0';
        run = false;

        size_t len = strlen(buffer);
        if (len == 0) {
            printf("Input cannot be empty! Please enter a valid address: ");
            run = true;
            continue;
        }
        if (len > 150) {
            printf("Address too long (max 150 chars), please enter a shorter address: ");
            run = true;
            continue;
        }
    }
    //Copying safely
    strncpy(str, buffer, kSizeOfString);
    str[kSizeOfString - 1] = '\0';
}