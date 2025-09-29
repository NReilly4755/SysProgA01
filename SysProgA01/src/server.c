/*
* FILE          : server.c
* PROJECT       : System Programming Assignment 1
* PROGRAMMER    : Nicholas Reilly
* FIRST VERSION : Sept 30 2025
* DESCRIPTION   : Main server file. Sets up a FIFO for IPC and prints messages from clients.
*/

#include "nick.h"
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Function prototype
void InitializeServer(void);

// Main function
int main(void) {
    InitializeServer();
    return 0;
}

// FUNCTION   : InitializeServer
// DESCRIPTION: Sets up a named pipe (FIFO) for inter-process communication.
//              Listens for messages from clients and prints them to the console.
// PARAMETERS : None
// RETURNS    : void
void InitializeServer(void) {

    //Define the path for where it will live.
    const char *fifo = "/tmp/travel_fifo";
    
    // Create a pipe if one does not already exist.
    if (mkfifo(fifo, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo failed");
            exit(EXIT_FAILURE);
        }
    }

    //Buffers to hold incoming messages
    char buffer[256];
    ssize_t n;

    //Open FIFO for reading (will block until a writer connects)
    int fd = open(fifo, O_RDONLY);
    if (fd == -1) {
        perror("open fifo");
        exit(EXIT_FAILURE);
    }

    printf("Server is running. Waiting for client messages...\n");
    fflush(stdout);

    //Read messages continuously
    while ((n = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[n] = '\0';
        printf("Server received: %s\n", buffer);
        fflush(stdout);    
    }

    //Handle error for a bad message.
    if (n == -1) {
        perror("read failed");
    }
}
