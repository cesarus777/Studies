# compiler
CC=gcc

# compilation flags
CFLAGS= -g

all: lexem.out

lexem.out: main.o problem_lx.o problem_st.o symbol_check.o
	$(CC) $? -o $@

.PHONY: clean
clean:
	rm -f *.o lexem.out
