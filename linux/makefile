CXX = g++
CXXFLAGS = -std=c++11 

OBJECTS = editdis.o

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -static-libstdc++ -o editdis editdis.o

editdis.o:
	$(CXX) $(CXXFLAGS) -c editdis.cpp

clean:
	rm -f *.o
	rm -f ./editdis
