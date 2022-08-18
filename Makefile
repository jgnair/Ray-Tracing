# -*- MakeFile -*-

all:test
test:main.o
	g++ main.o -o test -l m
main.o:main.cc 
	g++ -c main.cc
clean:
	rm *.o test
