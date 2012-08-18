CXX=g++
LD=g++
SRC=src
CFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb
LIBS=-lsfml-graphics -lsfml-system -lsfml-window
	
NM=ColorsTest 

all: compile 

compile: $(NM)

$(NM): main.o Color.o Gradient.o
	$(LD) -o $(NM) main.o Color.o Gradient.o $(LIBS)

main.o: $(SRC)/main.cpp $(SRC)/Color.h  $(SRC)/Gradient.h 
	$(CXX) $(CFLAGS) -c -o $@ $<

Color.o: $(SRC)/Color.cpp $(SRC)/Color.h  
	$(CXX) $(CFLAGS) -c -o $@ $<

Gradient.o: $(SRC)/Gradient.cpp $(SRC)/Color.h $(SRC)/Gradient.h 
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(NM)

run:
	./$(NM)

 
