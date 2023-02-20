$(CC) = gcc

all : hanoi

hanoi : hanoi.o

    $(CC) -o hanoi hanoi.o 

hanoi.o : *.c

    $(CC) *.c -o hanoi.o

clean : 

    rm *.o hanoi