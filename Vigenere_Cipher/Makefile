CC=gcc
CFLAGS=-Wall

EXEC = cipher
CSRC = cipher.c vigenere.c
HSRC = vigenere.h
OBJ = $(CSRC:.c=.o)
DATA = test.dat

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

%.o: %.c HSRC
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean: 
	rm -f $(OBJ)

.PHONY: clobber
clobber: clean
	rm -f $(EXEC)

.PHONY: test
test:
	./$(EXEC)<$(DATA)


