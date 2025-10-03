# Default target builds both
all: bin/serverProgram bin/clientProgram

# Server executable
bin/serverProgram: dirs obj/server.o
	gcc obj/server.o -o bin/serverProgram

# Client executable
bin/clientProgram: dirs obj/client.o
	gcc obj/client.o -o bin/clientProgram

# Object files
obj/server.o: src/server.c
	gcc -c src/server.c -I inc -o obj/server.o

obj/client.o: src/client.c inc/client.h
	gcc -c src/client.c -I inc -o obj/client.o

# Ensure build directories exist
dirs:
	mkdir -p bin obj

# Cleanup
clean:
	rm -f bin/* obj/*

