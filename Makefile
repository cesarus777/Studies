# compiler
CC=gcc

# compilation flags
CFLAGS=-g -c

all: lexem clean

lexem: problem_lx_main.o problem_lx.o
	$(CC) problem_lx_main.o problem_lx.o -g -o lexem.out

problem_lx_main.o: problem_lx_main.c
	$(CC) $(CFLAGS) problem_lx_main.c

problem_lx.o: problem_lx.c
	$(CC) $(CFLAGS) problem_lx.c

clean:
	rm -f problem_lx_main.o problem_lx.o
