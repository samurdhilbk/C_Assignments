CFLAGS=-I./ -Wall
CC=gcc

all:main

%:%.c
	$(CC) $(CFLAGS) $? -o $@

main: helper.o bigint.o main.o
	$(CC) $? -o test

clean: 
	rm -f *~ *.o 

realclean: clean 
	rm -f test

