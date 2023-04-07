all: wish
	rm *.o

wish : wish.o parseCommand.o splitCommand.o
	gcc -o wish wish.o parseCommand.o splitCommand.o

wish.o : wish.c
	gcc -c -o wish.o wish.c
	
parseCommand.o : parseCommand.c
	gcc -c -o parseCommand.o parseCommand.c

splitCommand.o : splitCommand.c
	gcc -c -o splitCommand.o splitCommand.c
clean :
	rm -f *.o