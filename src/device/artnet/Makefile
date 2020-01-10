BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/artnet.o \
	$(BIN_PWD)/dmxmaster.o \
	$(BIN_PWD)/dmxslave.o

UTIL_PWD = ../../util
LOG_PWD = ../../ctrl/raspberry/log
POLL_PWD = ../../ctrl/raspberry/poll
SOCKET_PWD = ../../ctrl/raspberry/socket
MAKE = make
MKDIR = mkdir -p
CC = g++
INCLUDE = -I$(UTIL_PWD)/src -I$(LOG_PWD)/src -I$(SOCKET_PWD)/src -I$(POLL_PWD)/src -Isrc
LIBS = -L. -lutil -llog -lpoll -lsocket

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll


artnetdirect: $(BIN_PWD)/artnetdirect.o
	$(CC) $^ -o $@ $(LDFLAGS)

$(BIN_PWD)/%.o: test/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@
	
# LINUX
libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libsocket.so:
	$(MAKE) -C $(SOCKET_PWD) $@
	ln -s $(SOCKET_PWD)/$@

libartnet.so:
	$(MAKE) libutil.so
	$(MAKE) libpoll.so
	$(MAKE) libsocket.so
	$(CC) -shared $^ -o $@

# WINDOWS
libutil.dll:
	$(MAKE) -C $(UTIL_PWD) $@
	cp $(UTIL_PWD)/$@ .

liblog.dll:
	$(MAKE) -C $(LOG_PWD) $@
	cp $(LOG_PWD)/$@ .

libpoll.dll:
	$(MAKE) -C $(POLL_PWD) $@
	cp $(POLL_PWD)/$@ .

libsocket.dll:
	$(MAKE) -C $(SOCKET_PWD) $@
	cp $(SOCKET_PWD)/$@ .

libcan.dll:
	$(MAKE) libutil.dll
	$(MAKE) liblog.dll
	$(MAKE) libpoll.dll
	$(MAKE) libsocket.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@
