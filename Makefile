CC = gcc-9

CFLAGS = -O0 -g -Wall -fopenmp -fsanitize=address

INC = -Iinc/

LIBS = 

LDFLAGS = 

test: test.c rcm.o 
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) $^ -o $@
	rm -rf *.o

time: time.c rcm.o 
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) $^ -o $@
	rm -rf *.o


%.o: %.c
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) -c $< -o $@

clean:
	rm -rf main *.dSYM *.o test time
