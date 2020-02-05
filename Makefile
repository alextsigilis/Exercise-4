CC = gcc-9

CFLAGS = -O0 -g -Wall -fopenmp -fsanitize=address

INC = -Iinc/

LIBS = 

LDFLAGS = 

test: test.c lib/rcm.o 
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) $^ -o $@
	rm -rf lib/*.o

time: time.c lib/rcm.o 
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) $^ -o $@
	rm -rf *.o


lib/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) -c $< -o $@

clean:
	rm -rf *.dSYM *.o test time lib/*.o
