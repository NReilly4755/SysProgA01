/*
* FILE		    : client.c
* PROJECT	    : System Programming Assignment 1
* PROGRAMMER	: Nicholas Reilly, Rodrigo Gomes, Josiah Williams, <fill your name here Bibi as your Teams name is different>
* FIRST VERSION	: Sept 30 2025
* DESCRIPTION	: Main client file. C
* REFERENCING   : Deitel, P., & Deitel, H. (2016). How to Program in C and C++ (8th ed.). Deitel & Associates Inc. 
*/

#include "nick.h"
#include "josiah.h"
#include "bibi.h"
#include "rodrigo.h"



int main(void) {
    const char *fifo = "/tmp/travel_fifo";

    // Open FIFO for writing
    int fd = open(fifo, O_WRONLY);
    if (fd == -1) {
        perror("open fifo");
        exit(EXIT_FAILURE);
    }

    // Send a message using LogEvent
    LogEvent(fd, "Server started?\n");
    
    runClientFlow(fd);

    close(fd);
    
    return 0;
}