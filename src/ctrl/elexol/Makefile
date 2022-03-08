BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/etherio.o

CC = g++
INCLUDE = -I../../util/src/ -I../raspberry/log/src/ -I../raspberry/poll/src -I../raspberry/socket/src -Isrc
LIBS = -L. -letherio24 -lsocket -lpoll -lutil -llog
CFLAGS = -g $(INCLUDE)
LDFLAGS = $(LIBS)

all: abris_jardin 

clean:
	rm $(BIN_PWD)/*.o abris_jardin *.so

abris_jardin: $(BIN_PWD)/abris_jardin.o libetherio24.so libsocket.so libpoll.so liblog.so libutil.so
	$(CC) $< -o $@ $(LDFLAGS)

$(BIN_PWD)/abris_jardin.o: test/abris_jardin.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

libetherio24.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

libsocket.so:
	$(MAKE) -C ../raspberry/socket $@
	ln -s ../raspberry/socket/$@

libpoll.so:
	$(MAKE) -C ../raspberry/poll $@
	ln -s ../raspberry/poll/$@

libutil.so:
	$(MAKE) -C ../../util $@
	ln -s ../../util/$@

liblog.so:
	$(MAKE) -C ../raspberry/log $@
	ln -s ../raspberry/log/$@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI
