CC = gcc
CFLAGS = -c -Wall
LIBS = -lrt -pthread -lncursesw
INC = -IzbPrint/
OBJ = gcc.o outline.o make.o cmake.o zbPrint.o

all: gcc make outline cmake

gcc: gcc.o zbPrint.o
	$(CC) zbPrint.o gcc.o $(INC) $(LIBS) -o gcc

make: make.o zbPrint.o
	$(CC) zbPrint.o make.o $(INC) $(LIBS) -o make

outline: outline.o zbPrint.o
	$(CC) zbPrint.o outline.o $(INC) $(LIBS) -o outline
	
cmake: cmake.o zbPrint.o
	$(CC) zbPrint.o cmake.o $(INC) $(LIBS) -o cmake

zbPrint.o: zbPrint/zbPrint.c zbPrint/zbPrint.h
	$(CC) zbPrint/zbPrint.c $(INC) $(CFLAGS) -o zbPrint.o

gcc.o: gcc.c
	$(CC) gcc.c $(CFLAGS) $(INC) -o gcc.o

make.o: make.c
	$(CC) make.c $(CFLAGS) $(INC) -o make.o

outline.o: outline.c
	$(CC) outline.c $(CFLAGS) $(INC) -o outline.o

cmake.o: cmake.c
	$(CC) cmake.c $(CFLAGS) $(INC) -o cmake.o


.PHONY : clean
clean:
	rm $(OBJ)

.PHONY : install
install:
	install -t ~/lib/ 
