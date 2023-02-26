CC=gcc
CFLAGS=-Wall -Werror

sonwa:	sonwa.o
	$(CC) -o sonwa sonwa.o -lm

sonwa.o:	sonwa.c
	$(CC) $(CFLAGS) -c sonwa.c -lm

clean:
	rm -f sonwa sonwa.o
