BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/lunartec.o

LOG_PWD = ../../../ctrl/raspberry/log
POLL_PWD = ../../../ctrl/raspberry/poll
RS232_PWD = ../../../ctrl/raspberry/rs232
UTIL_PWD = ../../../util
CC = g++
MAKE = make
INCLUDE = -I$(UTIL_PWD)/src -I$(LOG_PWD)/src -I$(POLL_PWD)/src -Isrc -I$(RS232_PWD)/src
LIBS = -L. -llunartec -lrs232 -lutil -llog -lpoll

CFLAGS = -g $(INCLUDE) -fPIC -DRASPI
LDFLAGS = $(LIBS)

all: lunartec

clean:
	rm $(BIN_PWD)/*.o *.so lunartec

lunartec: $(BIN_PWD)/test_lunartec.o
	$(MAKE) liblunartec.so
	$(MAKE) librs232.so
	$(MAKE) libpoll.so
	$(MAKE) libutil.so
	$(MAKE) liblog.so
	$(CC) $< -o $@  $(LDFLAGS)
	
$(BIN_PWD)/test_lunartec.o: test/test_lunartec.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libutil.so:
	$(MAKE -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

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

$(BIN_PWD)/%.o: src/%.cpp
	mkdir -p bin
	$(CC) $(CFLAGS) -c $^ -o $@
