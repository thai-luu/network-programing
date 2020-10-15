CC=gcc
CFLAGS=-I.
main: bttuan3.o list.o 
	${CC} -o bttuan3 bttuan3.o list.o 
main.o: bttuan3.c list.h 
	${CC} -c bttuan3.c
list.o: list.c list.h
	${CC} -c list.c
clean:
	rm -f *.o *~