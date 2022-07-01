# Makefile for tree demo programs
# Sally Goldin, 1 July 2022

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= directoryTree$(EXECEXT) stringBubble$(EXECEXT) treeSort$(EXECEXT)

all : $(EXECUTABLES)

linkedListQueue.o : linkedListQueue.c abstractQueue.h
	gcc -c linkedListQueue.c

filesearch.o :	filesearch.c filesearch.h
	gcc -c filesearch.c

directoryTree.o : directoryTree.c filesearch.h
	gcc -c directoryTree.c

# compile with DEBUG defined to test with internal 'main'
binaryTree$(EXECEXT) : binaryTree.c
	gcc -DDEBUG -o binaryTree$(EXECEXT) binaryTree.c
		    

timeFunctions.o : timeFunctions.c timeFunctions.h
	gcc -c timeFunctions.c

binaryTree.o : binaryTree.c binaryTree.h
	gcc -c binaryTree.c

stringBubble.o : stringBubble.c timeFunctions.h
	gcc -c stringBubble.c


treeSort.o : treeSort.c binaryTree.h timeFunctions.h
	gcc -c treeSort.c

stringBubble$(EXECEXT) : stringBubble.o timeFunctions.o
	gcc -o stringBubble$(EXECEXT) stringBubble.o timeFunctions.o

treeSort$(EXECEXT) : treeSort.o binaryTree.o timeFunctions.o
	gcc -o treeSort$(EXECEXT) treeSort.o binaryTree.o timeFunctions.o

directoryTree$(EXECEXT) : directoryTree.o filesearch.o
	gcc -o directoryTree$(EXECEXT) directoryTree.o filesearch.o

clean : 
	-rm *.o
	-rm $(EXECUTABLES)


