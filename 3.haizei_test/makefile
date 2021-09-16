.PHONY: clean
all: main.o haizei/test.o
	gcc main.o haizei/test.o -o ./bin/haizei
main.o: main.c
	gcc -c -I./ main.c
haizei/test.o: haizei/test.c haizei/test.h 
	gcc -c -I./ -o haizei/test.o haizei/test.c 
clean:
	rm -rf ./bin/haizei main.o haizei/test.o
