CC = gcc
CFLAGS = -g -Wall
MAINOBJS = main.o haizei/test.o

.PHONY: clean

all: $(MAINOBJS)
	$(CC) $(CFLAGS) $(MAINOBJS) -o ./bin/main

haizei/test.o: haizei/test.c haizei/test.h
	$(CC) $(CFLAGS) -I./ -c -o haizei/test.o haizei/test.c
main.o: main.c  
	$(CC) $(CFLAGS) -I./ -c -o main.o main.c
clean:
	rm -f $(MAINOBJS) bin/main
