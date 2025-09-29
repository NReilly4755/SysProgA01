#include "josiah.h"
#pragma warning(disable:4996)
int main(void) {
    bool run = true;
    int choice = 0;
    while (run) {
    displayMenu();
    choice = isANumber();
    Client client = { 0 };
    switch (choice) {
    case kMenuOptionOne: {
        printf("Enter first name: ");
        isAString(client.firstName);
        printf("First name is: %s\n", client.firstName);
        printf("Enter last name: ");
        isAString(client.lastName);
        printf("Enter age: ");
        client.age = isANumber();
        printf("Enter address: ");
        isAddress(client.address);
        printf(" address: %s\n",client.address);
        break;
    }
    case kMenuOptionTwo : {
        char destination[kSizeOfString];
        printf("Enter destination: ");
        isAString(destination);
        printf("Address: %s\n", destination);
        break;
    }
    case kMenuOptionThree: {
        break;
    }
    default:
        printf("Debugging: Error input shouldn't get here\n");
        break;
    }

    }
    return 0;
}

// FUNCTION : displayMenu
// DESCRIPTION :
// This function prints the menu to the user
// PARAMETERS :
// NONE
// RETURNS: 
// NONE
//

void displayMenu() {
    printf("***************\n");
    printf("1. Enter a client\n");
    printf("2. Enter a destination\n");
    printf("3. Third options\n");
    printf("****************\n");
    printf("Enter your choice: ");
}

// FUNCTION : isAString
// DESCRIPTION :
// This function will keep asking the user for a valid string 
// PARAMETERS :
// char* str: the str to validated
// RETURNS: 
// NONE
//

void isAString(char* str) {
    char buffer[100];
    bool run = true;
    while (run) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        run = false;
        if (strlen(buffer) == 0) {
            printf("Input cannot be empty! Please enter letters only: ");
            run = true;
            continue;
        }
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!((buffer[i] >= 'a' && buffer[i] <= 'z') || buffer[i] >= 'A' && buffer[i] <= 'Z')) {
                printf("Invalid input! Please enter letters only:");
                run = true;
                break;
            }
        }
    }
    strncpy(str, buffer, kSizeOfString);
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
    //Declare variables
    int value;
    char buffer[100];
    while (true)
    {
        fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            //Check to see if the function parsed valid input and return it.
            if (sscanf(buffer, "%d", &value) == 1)
            {
                return value;
            }
            printf("Invalid input! Please enter a valid number:");
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
    char buffer[100];
    bool run = true;
    while (run) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        run = false;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!((buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z') || (buffer[i] >= '0' && buffer[i]) <= '9')) {
                printf("Invalid input! Please enter a valid word:");
                run = true;
                break;
            }
        }
    }
    strncpy(str, buffer, kSizeOfString);
}