OBJECTS = \
	bin/lunartec.o

RS232_PWD = ../../../ctrl/raspberry/rs232
CC = g++
MAKE = make
INCLUDE = -I../../../ctrl/interface -I../../../ctrl/raspberry/factory/src -Isrc -I$(RS232_PWD)/src/
LIBS = -L. -llunartec -lrs232 -llog4cxx

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: lunartec

clean:
	rm bin/*.o liblunartec.so librs232.so lunartec

lunartec: bin/test_lunartec.o liblunartec.so librs232.so
	$(CC) $< -o $@  $(LDFLAGS)
	
bin/test_lunartec.o: test/test_lunartec.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

librs232.so:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

liblunartec.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

bin/lunartec.o: src/lunartec.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
