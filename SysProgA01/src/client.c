/*
 * FILE		    : client.c
 * PROJECT	    : System Programming Assignment 1
 * PROGRAMMER	: Nicholas Reilly, Rodrigo Gomes, Josiah Williams, <fill your name here Bibi as your Teams name is different>
 * FIRST VERSION	: Sept 30 2025
 * DESCRIPTION	: Main client file. C
 * REFERENCING   : Deitel, P., & Deitel, H. (2016). How to Program in C and C++ (8th ed.). Deitel & Associates Inc.
 */

#include "client.h"
#pragma warning(disable : 4996)

int main(void)
{
    const char *fifo = "/tmp/travel_fifo";

    // Open FIFO for writing
    int fd = open(fifo, O_WRONLY);
    if (fd == -1)
    {
        perror("open fifo");
        exit(EXIT_FAILURE);
    }

    // Send a message using LogEvent
    LogEvent(fd, "Server started?\n");

    runClientFlow(fd);

    close(fd);

    return 0;
}

//-------------------------------------------------------Josiah's Code-------------------------------------------------------//

// FUNCTION : isAString
// DESCRIPTION :
// This function will keep asking the user for a valid string
// PARAMETERS :
// char* str: the str to validated
// RETURNS:
// NONE
//

void isAString(char *str, int fd)
{
    bool run = true;
    while (run)
    {
        printf("> ");
        fflush(stdout);

        if (!idleCheck(str, kSizeOfString, TTK))
        {
            printf("No input for 120 seconds. Exiting client creation.\n");
            LogEvent(fd, "Client creation timed out due to inactivity.\n");
            exit(EXIT_FAILURE);
        }

        size_t len = strlen(str);

        if (len == 0)
        {
            printf("Input cannot be empty, enter letters only: ");
            continue;
        }
        if (len > kMaxLengthName)
        {
            printf("Input too long, enter a shorter name: ");
            continue;
        }

        bool valid = true;
        for (size_t i = 0; i < len; i++)
        {
            if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') ||
                  str[i] == ' '))
            {
                valid = false;
                break;
            }
        }
        if (!valid)
        {
            printf("Invalid input! Please enter letters only: ");
            continue;
        }

        // Input is valid
        run = false;
    }
}

// FUNCTION : isAddress
// DESCRIPTION :
// This function will keep asking the user for a valid address string
// PARAMETERS :
// char* str: the str to validated
// RETURNS:
// NONE
//

void isAddress(char *str, int fd)
{
    bool run = true;
    while (run)
    {
        printf("> ");
        fflush(stdout);

        if (!idleCheck(str, kSizeOfString, TTK))
        {
            printf("No input for 120 seconds. Exiting client creation.\n");
            LogEvent(fd, "Client creation timed out due to inactivity.\n");
            exit(EXIT_FAILURE);
        }

        size_t len = strlen(str);

        if (len == 0)
        {
            printf("Input cannot be empty! Please enter a valid address: ");
            continue;
        }
        if (len > kMaxAddressLength)
        {
            printf("Address too long (max %d chars), please enter a shorter address: ", kMaxAddressLength);
            continue;
        }

        run = false; // valid input
    }
}

//--------------------------------------------------------Rodrigo's Code-------------------------------------------------------//
// FUNCTION : InitParty
// DESCRIPTION : Initialize the Party struct with zero clients and empty destination
// PARAMETERS : Party *party - pointer to the Party struct
// RETURNS: void
void InitParty(Party *party)
{
    party->client_count = 0;
    party->destination[0] = '\0';
}

// FUNCTION : AddClient
// DESCRIPTION : Add a new client to the Party list if limit not reached
// PARAMETERS : Party *party - pointer to Party struct
//              Client *client - pointer to Client to be added
// RETURNS: int (0 if success, -1 if error)
int AddClient(Party *party, Client *client)
{
    if (party->client_count >= MAX_CLIENTS)
    {
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
int AddDestination(Party *party, int fd)
{

    char destination_buffer[MAX_DESTINATION_LEN];
    printf("Enter destination for this party: ");
    fflush(stdout);

    // Wait for input using idleCheck (with timeout)
    if (!idleCheck(destination_buffer, sizeof(destination_buffer), TTK))
    {
        printf("No input for 120 seconds. Exiting client creation.\n");
        LogEvent(fd, "Client creation timed out due to inactivity.\n");
        exit(EXIT_FAILURE);
    }

    // Check if input is empty
    if (strlen(destination_buffer) == 0)
    {
        printf("Empty destination not allowed...\n");
        return -1;
    }

    strncpy(party->destination, destination_buffer, MAX_DESTINATION_LEN);
    party->destination[MAX_DESTINATION_LEN - 1] = '\0';

    printf("Destination set for this party: %s\n", party->destination);
    printf("Press Enter to go to client menu...\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
    return 0;
}

//--------------------------------------------------------Nick's Code-------------------------------------------------------//

// FUNCTION   : LogEvent
// DESCRIPTION: Logs events to a specified file descriptor. If fd is -1, it does
//              nothing. Otherwise, it writes the message to the fd followed by a newline.
// PARAMETERS : fd - the file descriptor to write to
//              message - the message to log
// RETURNS    : nothing
void LogEvent(int fd, const char *message)
{
    if (fd >= 0)
    {
        write(fd, message, strlen(message));
        write(fd, "\n", 1);
    }
}

///
// FUNCTION   : idleCheck
// DESCRIPTION: Checks if there is input within a specified timeout period.
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
int idleCheck(char *buffer, size_t size, int timeout_sec)
{
    // Initlaize variables
    fd_set set;
    struct timeval timeout;

    // Clear the set and add stdin to it
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    timeout.tv_sec = timeout_sec;
    timeout.tv_usec = 0;

    // Wait for input or timeout
    int ret = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

    // Check the result of select
    if (ret > 0)
    {
        if (fgets(buffer, size, stdin) == NULL)
        {
            return 0;
        }

        // Remove trailing newline if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
        else
        {
            // Input was longer than buffer so clear the rest of the line
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
        }
        return 1;
    }

    // Timed out: return error
    else if (ret == 0)
    {
        // Timeout
        return 0;
    }

    // Show error if something bugged and kill the program.
    else
    {
        perror("select failed");
        return -1;
    }
}

// FUNCTION     : runClientFlow
// DESCRIPTION  : Handles the first part of program so the timeout check can happen properly.
// PARAMETERS   : char pointer for the choice, size_t fir the size of choices buffer and int for the file descriptor.
// RETURNS      : 0 if true, -1 if false.
int modeSelect(char *choice, size_t bufSize, int fd)
{
    while (1)
    {

        // Get prompt from user and use fflush to make sure the message shows (it was not showing on my Linux VM).
        printf("Select mode: 'party' to start a new group, or 'stop' to quit: \n");
        fflush(stdout);

        // Wait for input with timeout
        if (!idleCheck(choice, bufSize, 120))
        {
            printf("No input for 120 seconds. Exiting client creation.\n");
            LogEvent(fd, "Client creation timed out due to inactivity.\n");
            exit(EXIT_FAILURE);
        }

        // Return true if party was selected.
        if (strcmp(choice, "party") == 0)
        {
            return 0;
        }

        // Return false if stop was chosen.
        if (strcmp(choice, "stop") == 0)
        {
            return -1;
        }

        // GIve user an error message if neither option was chosen.
        printf("Invalid input. Please type 'party' or 'stop'.\n");
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
    char buffer[100];
    int value;

    // Be in a loop as long as the inpiut is invalid.
    while (1)
    {
        printf("> ");
        fflush(stdout);

        // Check to see if the user does ot enter anything ehre for 120 seocnds. If longer, kill program.
        if (!idleCheck(buffer, sizeof(buffer), TTK))
        {
            printf("No input for 120 seconds. Exiting client creation.\n");
            LogEvent(fd, "Client creation timed out due to inactivity.\n");
            exit(EXIT_FAILURE);
        }

        // Copy the calue and confirm valid of type int
        if (sscanf(buffer, "%d", &value) == 1)
        {
            LogEvent(fd, "Valid integer input received.\n");
            return value;
        }
        // Trap user until input is valid
        else
        {
            printf("Invalid input! Please enter a valid number:\n");
            LogEvent(fd, "Invalid integer input. Prompting again.\n");
        }
    }
}

// FUNCTION     : clearBuffer
// DESCRIPTION  : Clears out leftover crap in stdin
// PARAMETERS   : nothing
// RETURNS      : nothing
void clearBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

//--------------------------------------------------------Bibi's Code-------------------------------------------------------//

// FUNCTION : runClientFlow
// DESCRIPTION : Handles full sequence: start party -> set destination -> add clients
//               Sends all data to server using FIFO file descriptor.
// PARAMETERS : fd - file descriptor of opened FIFO for writing
// RETURNS : void

void runClientFlow(int fd)
{
    Party party;
    InitParty(&party);

    char input[50];
    char buffer[BUFFER_SIZE];
    char temp[100];

    while (1)
    {

        int response = modeSelect(input, sizeof(input), fd);
        if (response == -1)
        {
            printf("Stopping client input...\n");
            write(fd, "stop\n", 5);
            break;
        }

        printf("Starting new party...\n");
        write(fd, "party\n", 6);

        if (AddDestination(&party, fd) != 0)
        {
            printf("Destination failed, please try again.\n");
            continue;
        }

        snprintf(buffer, sizeof(buffer), "%s\n", party.destination);
        write(fd, buffer, strlen(buffer));

        while (1)
        {
            printf("Type 'client' to add a client or 'end' to finish this party: \n");
            fflush(stdout);

            if (!idleCheck(temp, sizeof(temp), TTK))
            {
                printf("No input for 120 seconds. Exiting client creation.\n");
                LogEvent(fd, "Client creation timed out due to inactivity.\n");
                exit(EXIT_FAILURE);
            }

            if (strcmp(temp, "end") == 0)
            {
                snprintf(buffer, sizeof(buffer),
                         "Party finished. Total clients: %d. Destination: %s\n",
                         party.client_count, party.destination);

                printf("%s", buffer);

                write(fd, buffer, strlen(buffer));

                write(fd, "end\n", 4);
                pid_t server_pid;

                //Call to kill the serrver and client via a signal when end is invoked.
                FILE *pidfile = fopen("/tmp/server.pid", "r");
                if (pidfile)
                {
                    fscanf(pidfile, "%d", &server_pid);
                    fclose(pidfile);
                    kill(server_pid, SIGUSR1);
                }
                else
                {
                    printf("Warning: could not find server PID file.\n");
                }

                break;
            }

            if (strcmp(temp, "client") != 0)
            {
                printf("Invalid. Please type 'client' or 'end'.\n");
                continue;
            }

            Client client = {0};

            printf("Enter first name: ");
            fflush(stdout);
            isAString(client.firstName, fd);

            printf("Enter last name: ");
            fflush(stdout);
            isAString(client.lastName, fd);

            printf("Enter age: ");
            fflush(stdout);
            client.age = GetValidIntegerInput(fd);

            printf("Enter address: ");
            fflush(stdout);
            isAddress(client.address, fd);

            // --- Add client to party ---
            if (AddClient(&party, &client) == 0)
            {
                printf("Added client: %s %s, Age %d, Address %s\n",
                       client.firstName, client.lastName, client.age, client.address);

                snprintf(buffer, sizeof(buffer),
                         "client %s %s %03d %s\n",
                         client.firstName, client.lastName,
                         client.age, client.address);
                write(fd, buffer, strlen(buffer));
            }
            else
            {
                printf("Party full, cannot add more clients.\n");
            }
        }
    }
}
