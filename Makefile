CC = gcc-9

CFLAGS = -O3 -Wall -fopenmp #-g -fsanitize=address

INC = -Iinc/

LIBS = 

LDFLAGS = 

all: test time
	rm -rf *.dSYM

test: test.c lib/rcm.o lib/parallel_rcm.o
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) $^ -o $@

time: time.c lib/rcm.o lib/parallel_rcm.o
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) $^ -o $@

lib/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) -c $< -o $@

clean:
	rm -rf *.dSYM *.o test time lib/*.o data.*
