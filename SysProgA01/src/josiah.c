#include "josiah.h"
#include "rodrigo.h"

#pragma warning(disable:4996)

int mainProgram(void) {
    bool run = true;
    int choice = 0;
    Party party;
    InitParty(&party);

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
        
        if (AddClient(&party, &client) == 0){
            printf("Client added to party: %s %s\n", client.firstName, client.lastName);
        }else {
            printf("Failed to add client (party full?)\n");
            }
        break;
    }
    case kMenuOptionTwo : {
        if (AddDestination(&party) != 0) {
        printf("Could not set destination, make sure you have at least one client in the party!!\n");
    }
    break;
    }
    case kMenuOptionThree: {
        run = false;
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
void displayMenu() {
    printf("***************\n");
    printf("1. Enter a client\n"); //If user types "party", that a list of struct of clients and this list ends when the first word of the input is "end"
    printf("2. Enter a destination\n");
    printf("3. Exit\n");
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