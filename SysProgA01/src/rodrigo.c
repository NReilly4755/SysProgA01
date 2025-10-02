#include <stdio.h>
#include <string.h>
#include "rodrigo.h"
#include "josiah.h" // para isAString / isAddress

// FUNCTION : InitParty
// DESCRIPTION : Initialize the Party struct with zero clients and empty destination
// PARAMETERS : Party *party - pointer to the Party struct
// RETURNS: void
void InitParty(Party *party) {
    party->client_count = 0;
    party->destination[0] = '\0';
}


// FUNCTION : AddClient
// DESCRIPTION : Add a new client to the Party list if limit not reached
// PARAMETERS : Party *party - pointer to Party struct
//              Client *client - pointer to Client to be added
// RETURNS: int (0 if success, -1 if error)
int AddClient(Party *party, Client *client) {
    if (party->client_count >= MAX_CLIENTS) {
        printf("ERROR: maximum number of clients (10) reached\n");
        return -1;
    }
    party->clients[party->client_count] = *client;
    party->client_count++;
    return 0;
}

// FUNCTION : AddDestination
// DESCRIPTION : Ask user to enter the destination for the party
// PARAMETERS : Party *party - pointer to Party struct
// RETURNS: int (0 if success, -1 if error)
int AddDestination(Party *party) {
    char destination_buffer[MAX_DESTINATION_LEN];
    printf("Enter destination for this party: ");

    if (fgets(destination_buffer, sizeof(destination_buffer), stdin) == NULL) {
        printf("Input error...\n");
        return -1;
    }
    destination_buffer[strcspn(destination_buffer, "\n")] = '\0';

    if (strlen(destination_buffer) == 0) {
        printf("Empty destination not allowed...\n");
        return -1;
    }
    if (strlen(destination_buffer) >= MAX_DESTINATION_LEN) {
        printf("Destination too long (max %d chars)\n", MAX_DESTINATION_LEN - 1);
        return -1;
    }

    strncpy(party->destination, destination_buffer, MAX_DESTINATION_LEN);
    party->destination[MAX_DESTINATION_LEN - 1] = '\0';

    printf("Destination set for this party: %s\n", party->destination);

    return 0;
}

