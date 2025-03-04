CC = gcc
CFLAGS = -Wall -Wextra -O2

all: meu_programa

meu_programa: ordered_list.o
	$(CC) $(CFLAGS) -o meu_programa ordered_list.o

ordered_list.o: ordered_list.c ordered_list.h
	$(CC) $(CFLAGS) -c ordered_list.c

clean:
	rm -f meu_programa ordered_list.o

run: 
	./meu_programa
