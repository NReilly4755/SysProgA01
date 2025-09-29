/*
* FILE		    : nick.c
* PROJECT	    : System Programming Assignment 1
* PROGRAMMER	: Nicholas Reilly
* FIRST VERSION	: Sept 30 2025
* DESCRIPTION	: My code contribution to the project. Contains server initialization, logging, and input validation functions.
*               : Also contains the idleCheck function to monitor user inactivity. I also did the makefile and Linux bash script.
* REFERENCING   : Deitel, P., & Deitel, H. (2016). How to Program in C and C++ (8th ed.). Deitel & Associates Inc. 
*/

#include "nick.h"


// FUNCTION   : LogEvent
// DESCRIPTION: Logs events to a specified file descriptor. If fd is -1, it does
//              nothing. Otherwise, it writes the message to the fd followed by a newline.
// PARAMETERS : fd - the file descriptor to write to
//              message - the message to log
// RETURNS    : nothing
void LogEvent(int fd, const char* message) {
    if (fd >= 0) {
        write(fd, message, strlen(message));
        write(fd, "\n", 1);
    }
}

///
// FUNCTION   : idleCheck
//DESCRIPTION: Checks if there is input within a specified timeout period.
//             If input is received, it reads the input into the provided buffer.
//             If no input is received within the timeout, it returns 0.

//
//
// PARAMETERS : buffer - the buffer to store input
//              size - the size of the buffer
//              timeout_sec - the timeout period in seconds
//
// RETURNS    : 0 if input is received, 1 if timeout occurs
//
int idleCheck(char* buffer, size_t size, int timeout_sec) {
    
    //Declare the file descriptor set and timeout structure.
    fd_set set;
    struct timeval timeout;

    //Initialize the file descriptor set and add stdin to it.
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    //Set the timeout period.
    timeout.tv_sec = timeout_sec;
    timeout.tv_usec = 0;

    //Wait for input on stdin with the specified timeout.
    int ret = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

    //Check the result of select and input is available, read it into the buffer.
    if (ret > 0) {
        if(fgets(buffer, size, stdin) == NULL)
            return 0;
        buffer[strcspn(buffer, "\n")] = '\0';
        return 0;
      
    // No input within the timeout period.
    } else if (ret == 0) {
        return 1;

    // An error occurred.    
    } else {
        perror("No valid input or system error occured.\n");
        return 1;
    }
}


//
// FUNCTION   : GetValidIntegerInput
// DESCRIPTION: Makes sure that the input read from keyboard is a single int only between 1-6 inclusive
//
// PARAMETERS : none
// RETURNS    : value, which is the number isolated and meets the range of 1-6 inclusive.
//
int GetValidIntegerInput(int fd)
{
    //Declare variables
    int value;
    char buffer[100];

    // Log the event of prompting for input.
    LogEvent(fd, "Prompting user for integer input.\n");
    while (1)
    {
        //Call idleCheck to see if the user stalls out the TTK.
        if(!idleCheck(buffer, sizeof(buffer), TTK)){
            printf("No input for 120 seconds. Exiting client creation.\n");
            LogEvent(fd, "Client creation timed out due to inactivity.\n");
            exit(EXIT_FAILURE);
        }
            //Remove the newlne at end of input to have a null terminator.
            char *newline = strchr(buffer, '\n');
            if (newline)
                *newline = '\0';

            //Check to see if the function parsed valid input and return it.
            if (sscanf(buffer, "%d", &value) == 1)
            {
                return value;
                LogEvent(fd, "Valid integer input received.\n");
            }
        
        //Non happy path: bad input detected.
        printf("Invalid input! Please enter a valid number:\n");
        LogEvent(fd, "Invalid integer input. Prompting again.\n");
    }
}