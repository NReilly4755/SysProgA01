#ifndef RODRIGO_H
#define RODRIGO_H

#include "josiah.h"

#define MAX_CLIENTS 10
#define MAX_DESTINATION_LEN 167

typedef struct {
    Client clients[MAX_CLIENTS];
    int client_count;
    char destination[MAX_DESTINATION_LEN];
} Party;

//Prototypes
void InitParty(Party *p);
int AddClient(Party *p, Client *c);
int AddDestination(Party *p);

#endif
