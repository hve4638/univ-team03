all: wish
	rm *.o

wish : wish.o parseCommand.o
	gcc -o wish wish.o parseCommand.o

wish.o : wish.c
	gcc -c -o wish.o wish.c
	
parseCommand.o : parseCommand.c
	gcc -c -o parseCommand.o parseCommand.c

clean :
	rm -f *.o