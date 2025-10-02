/*
* FILE        : bibi.c
* PROJECT     : System Programming Assignment 1
* PROGRAMMER  : Bibi Murwared
* FIRST VERSION : Oct 2025
* DESCRIPTION : Implements the main party/client input flow using Party (Rodrigo),
*               input validators (Josiah), and dynamic allocation (Bibi).
*               Sends all messages to the server via FIFO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bibi.h"
#include "rodrigo.h"
#include "josiah.h"

#define BUFFER_SIZE 512

// FUNCTION : runClientFlow
// DESCRIPTION : Handles full sequence: start party -> set destination -> add clients
//               Sends all data to server using FIFO file descriptor.
// PARAMETERS : fd - file descriptor of opened FIFO for writing
// RETURNS : void
void runClientFlow(int fd) {
    
    Party party;
    InitParty(&party);

    char input[50];
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("Type 'party' to start a new group, or 'stop' to quit: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input error, try again\n");
            continue;
        }
        input[strcspn(input, "\n")] = '\0'; // remove newline

        if (strcmp(input, "stop") == 0) {
            printf("Stopping client input...\n");
            write(fd, "stop\n", 5);
            break;
        }

        if (strcmp(input, "party") != 0) {
            printf("Invalid. Please type 'party' or 'stop'.\n");
            continue;
        }

        // Party started
        printf("Starting new party...\n");
        write(fd, "party\n", 6);

        // === Destination ===
        if (AddDestination(&party) != 0) {
            printf("Destination failed, please try again.\n");
            continue;
        }

        // Send destination to server
        snprintf(buffer, sizeof(buffer), "%s\n", party.destination);
        write(fd, buffer, strlen(buffer));

        // === Add clients ===
        while (1) {
            printf("Type 'client' to add a client or 'end' to finish this party: ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("Input error, try again\n");
                continue;
            }
            input[strcspn(input, "\n")] = '\0';

            if (strcmp(input, "end") == 0) {
                printf("Party finished. Total clients: %d. Destination: %s\n",
                       party.client_count, party.destination);
                write(fd, "end\n", 4);
                break;
            }

            if (strcmp(input, "client") != 0) {
                printf("Invalid. Please type 'client' or 'end'.\n");
                continue;
            }

            // Create a new client
            Client client = {0};
            printf("Enter first name: ");
            isAString(client.firstName);

            printf("Enter last name: ");
            isAString(client.lastName);

            printf("Enter age: ");
            client.age = isANumber();

            printf("Enter address: ");
            isAddress(client.address);

            // Add client to the party
            if (AddClient(&party, &client) == 0) {
                printf("Added client: %s %s, Age %d, Address %s\n",
                       client.firstName, client.lastName, client.age, client.address);

                // Send client to server
                snprintf(buffer, sizeof(buffer),
                         "client %s %s %03d %s\n",
                         client.firstName, client.lastName,
                         client.age, client.address);
                write(fd, buffer, strlen(buffer));
            } else {
                printf("Party full, cannot add more clients.\n");
            }
        }
    }
}
