# compiler
CC=gcc

# compilation flags
CFLAGS=-c

all: all-in max clean

all-in: all-in.o obsha.o
	$(CC) all-in.o obsha.o -o all-in.out

max: max.o obsha.o
	$(CC) max.o obsha.o -o max.out

all-in.o: all-in.c
	$(CC) $(CFLAGS) all-in.c

max.o: max.c
	$(CC) $(CFLAGS) max.c

obsha.o: obsha.c
	$(CC) $(CFLAGS) obsha.c

clean:
	rm -f *.o
