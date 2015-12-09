CC=g++
CFLAGS=-std=c++11 -pedantic -Wall
SOURCES=$(addprefix src/, main.cpp RefCounter.cpp SmartPointer.h)
TEST=$(addprefix tests/, blatt08_test.cpp testrunner.cpp)
BIN=bin

.PHONY: all runmain compilemain abgabe makedir clean

all: clean runmain abgabe

runmain: compilemain
	./$(BIN)/main

compilemain: makedir $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(BIN)/main

# Valgrind: still reachable; siehe Ticket 518
abgabe: clean compiletest
	valgrind --leak-check=yes $(BIN)/test

compiletest: makedir $(SOURCES) $(TEST)
	$(CC) -std=c++11 -Wall $(TEST) src/RefCounter.cpp -lcppunit -o $(BIN)/test

makedir:
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)/
