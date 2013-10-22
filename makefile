.SUFFIXES: .c .o 
CC = gcc
CFLAGS = -g

.c.o:  
	$(CC) $(CFLAGS) -c $<

p1: p1.o hash_one.o hash_two.o
	gcc p1.o hash_one.o hash_two.o -o p1

clean:
	rm -f *.o core
