objects = enigma.o plugboard.o rotor.o reflector.o
enigma: main.cpp $(objects)
	g++ -Wall -g main.cpp $(objects) errors.h -o enigma

%.o: %.h errors.h


.phony: clean
clean:
	rm enigma $(objects)
