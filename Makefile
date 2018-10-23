CC=g++
CFLAGS=-Wall -Wextra
EXEC=tableMaker passwordCracker

all: $(EXEC)

utils.o: sha256.o utils.h utils.cpp
	$(CC) -c sha256.o utils.cpp  $(CFLAGS)

sha256.o: sha256.h sha256.cpp
	$(CC) -c sha256.cpp $(CFLAGS)

tableMaker: tableMaker.cpp sha256.o utils.o
	$(CC) -o tableMaker sha256.o utils.o tableMaker.cpp $(CFLAGS)

passwordCracker: passwordCracker.cpp sha256.o utils.o
	$(CC) -o passwordCracker sha256.o utils.o passwordCracker.cpp $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf tableMaker passwordCracker rainbowTable.txt
