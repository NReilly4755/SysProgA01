# Compiler and flags
CC      ?= cc
CFLAGS  = -Wall -Wextra -I inc

# Default target builds both
all: bin/serverProgram bin/clientProgram

# Server executable
bin/serverProgram: dirs obj/server.o
	$(CC) obj/server.o -o bin/serverProgram

# Client executable
bin/clientProgram: dirs obj/client.o
	$(CC) obj/client.o -o bin/clientProgram

# Object files
obj/server.o: src/server.c
	$(CC) $(CFLAGS) -c src/server.c -o obj/server.o

obj/client.o: src/client.c inc/client.h
	$(CC) $(CFLAGS) -c src/client.c -o obj/client.o

# Ensure build directories exist
dirs:
	mkdir -p bin obj

# Cleanup
clean:
	rm -f bin/* obj/*
