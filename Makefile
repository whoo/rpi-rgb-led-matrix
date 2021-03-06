CFLAGS=-Wall -O3 -g -fpermissive
CXXFLAGS=-Wall -O3 -g -std=gnu++0x -fpermissive
OBJECTS=main.o gpio.o led-matrix.o thread.o effect.o font.o Getdata.o effect2.o tools.o pasa.o
BINARIES=led-matrix clear test-data
LDFLAGS=-lrt -lm -lpthread -lpulse-simple -lpulse -L/usr/lib/pulseaudio -lm -lfftw3

all : $(BINARIES)

led-matrix.o: led-matrix.cc led-matrix.h
main.o: led-matrix.h

led-matrix : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	chmod a+s led-matrix

clean: 
	rm -f $(OBJECTS) $(BINARIES) clear.o test-data.o

effect.o: font.h 

test-data: test-data.o Getdata.o  thread.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clear: clear.o gpio.o led-matrix.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)



