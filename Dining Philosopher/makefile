CC = gcc -pthread
//CFLAGS = -I. -Wall
LFLAGS = -lm
PROG = Dining_Phil

all: Dining_Philosophers.o 
	$(CC) Dining_Philosophers.o -o $(PROG) $(CFLAGS)

Dining_Philosophers.o: Dining_Philosophers.c
	$(CC) $(CFLAGS) -c Dining_Philosophers.c


clean:
	rm *.o 
	rm *~
