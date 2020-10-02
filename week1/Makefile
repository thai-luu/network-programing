CC=gcc
CFLAGS=-I.
main: bttuan1.o list.o
	${CC} -o bttuan1 bttuan1.o list.o
main.o: bttuan1.c list.h
	${CC} -c bttuan1.c
list.o: list.c list.h
	${CC} -c list.c
clean:
	rm -f *.o *~