all: wish
	rm *.o

wish : wish.o parseCommand.o splitCommand.o builtInCommand.o runCommand.o freeComandNode.o utils.o main.o
	gcc -o wish wish.o parseCommand.o splitCommand.o builtInCommand.o runCommand.o freeComandNode.o utils.o main.o

main.o : main.c
	gcc -c -o main.o main.c

wish.o : wish.c
	gcc -c -o wish.o wish.c

builtInCommand.o : builtInCommand.c
	gcc -c -o builtInCommand.o builtInCommand.c
	
parseCommand.o : parseCommand.c
	gcc -c -o parseCommand.o parseCommand.c

splitCommand.o : splitCommand.c
	gcc -c -o splitCommand.o splitCommand.c

runCommand.o : runCommand.c
	gcc -c -o runCommand.o runCommand.c

utils.o : utils.c
	gcc -c -o utils.o utils.c

freeComandNode.o : freeComandNode.c
	gcc -c -o freeComandNode.o freeComandNode.c

clean :
	rm -f *.o