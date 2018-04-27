all: main.o
	g++ -std=c++11 -o editdis main.o

main.o:
	g++ -std=c++11 -c main.cpp

clean:
	rm -f *.o
	rm -f ./editdis
