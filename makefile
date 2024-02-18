CC = gcc
CFLAGS = -Wall -Wextra -g

all: mini5main

mini5main: mini5main.o mini5phone.o
	$(CC) $(CFLAGS) mini5main.o mini5phone.o -o mini5main

mini5main.o: mini5main.c mini5phone.h
	$(CC) $(CFLAGS) -c mini5main.c

mini5phone.o: mini5phone.c mini5phone.h
	$(CC) $(CFLAGS) -c mini5phone.c

clean:
	rm -f mini5main.o mini5phone.o mini5main

