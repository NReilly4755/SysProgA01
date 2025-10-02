# Default target builds both
all: bin/serverProgram bin/clientProgram

# Server executable
bin/serverProgram : dirs obj/server.o obj/nick.o obj/josiah.o obj/bibi.o obj/rodrigo.o
	gcc obj/server.o obj/nick.o obj/josiah.o obj/bibi.o obj/rodrigo.o -o bin/serverProgram

# Client executable
bin/clientProgram : dirs obj/client.o obj/nick.o obj/josiah.o obj/bibi.o obj/rodrigo.o
	gcc obj/client.o obj/nick.o obj/josiah.o obj/bibi.o obj/rodrigo.o -o bin/clientProgram

# Object files
obj/client.o : src/client.c inc/nick.h inc/josiah.h inc/bibi.h inc/rodrigo.h
	gcc -c src/client.c -I inc -o obj/client.o

obj/server.o : src/server.c
	gcc -c src/server.c -I inc -o obj/server.o

obj/nick.o : src/nick.c inc/nick.h
	gcc -c src/nick.c -I inc -o obj/nick.o

obj/josiah.o : src/josiah.c inc/josiah.h
	gcc -c src/josiah.c -I inc -o obj/josiah.o

obj/bibi.o : src/bibi.c inc/bibi.h
	gcc -c src/bibi.c -I inc -o obj/bibi.o

obj/rodrigo.o : src/rodrigo.c inc/rodrigo.h
	gcc -c src/rodrigo.c -I inc -o obj/rodrigo.o


# ensure build directories exist
dirs:
	mkdir -p bin obj
	
# Cleanup
clean:
	rm -f bin/*
	rm -f obj/*