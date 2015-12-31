LDFLAGS=-lcurl 
CPPFLAGS=



CPPFLAGS += $(shell pkg-config --cflags json-c)
LDFLAGS += $(shell pkg-config --libs json-c)

CPPFLAGS += $(shell pkg-config libxml-2.0 --cflags)
LDFLAGS += $(shell pkg-config libxml-2.0 --libs)

LDFLAGS +=-ljson
CPPFLAGS +=-I /usr/include/json

all: Meteo News


Meteo: Tools.o
News: Tools.o

clean:
	rm *.o Meteo News
