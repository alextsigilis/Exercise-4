CC = gcc-7

CFLAGS = -O0 -g -Wall -fsanitize=address

INC = -Iinc/

LIBS = 

LDFLAGS = 

main: main.c lib/rcm.o lib/queue.o
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) $^ -o main
	rm -rf lib/rcm.o lib/queue.o


lib/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) $(LIBS) $(LDFLAGS) -c $< -o $@

clean:
	rm -rf main *.dSYM
