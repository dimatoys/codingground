all: run

run: runtest1
	./runtest1
	
bmp.o: bmp.cpp bmp.h
	g++ -c bmp.cpp
	
test1.o: test1.cpp bmp.h
	g++ -c test1.cpp
	
runtest1: bmp.o test1.o
	g++ -o runtest1 bmp.o test1.o