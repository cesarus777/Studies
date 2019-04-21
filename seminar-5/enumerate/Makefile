# compiler
CC=gcc

# compilation flags
CFLAGS=

all: lexem.out

lexem.out: problem_lx_main.o problem_lx.o symbol_check.o
	$(CC) $? -o $@

.PHONY: clean
clean:
	rm -f *.o lexem.out
