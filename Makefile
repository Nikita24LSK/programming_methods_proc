all: lab1
	
lab1: main.o interfaces.o
	gcc main.o interfaces.o -o lab1

main.o: main.c
	gcc -c main.c

interfaces.o: interfaces.c
	gcc -c interfaces.c

clean:
	rm -rf *.o