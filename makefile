
all: phase1Main.o CDA.o
	g++ phase1Main.o CDA.o -o Phase01

phase1Main.o: phase1Main.cpp
	g++ -c phase1Main.cpp

CDA.o: CDA.cpp 
	g++ -c CDA.cpp

clean:
	rm *.o output