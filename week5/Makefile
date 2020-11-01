CC=gcc
CFLAGS=-I.

main: server.o list.o 
    
	${CC} -o server server.o list.o 
	${CC} -o client client.c
main.o: server.c list.h 
	${CC} -c server.c
list.o: list.c list.h
	${CC} -c list.c
clean:
	rm -f *.o *~