OBJECTS = \
	bin/lunartec.o

LOG_PWD = ../../../ctrl/raspberry/log
POLL_PWD = ../../../ctrl/raspberry/factory
RS232_PWD = ../../../ctrl/raspberry/rs232
CC = g++
MAKE = make
INCLUDE = -I$(LOG_PWD)/src -I$(POLL_PWD)/src -Isrc -I$(RS232_PWD)/src
LIBS = -L. -llunartec -lrs232 -llog -lpoll

CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: lunartec

clean:
	rm bin/*.o liblunartec.so librs232.so lunartec

lunartec: bin/test_lunartec.o
	$(MAKE) liblunartec.so
	$(MAKE) librs232.so
	$(MAKE) libpoll.so
	$(MAKE) liblog.so
	$(CC) $< -o $@  $(LDFLAGS)
	
bin/test_lunartec.o: test/test_lunartec.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

liblog.so:
	$(MAKE -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so:
	$(MAKE -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

librs232.so:
	$(MAKE) -C $(RS232_PWD) $@
	ln -s $(RS232_PWD)/$@

liblunartec.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

bin/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
