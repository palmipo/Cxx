BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/canopenfactory.o \
	$(BIN_PWD)/canopenbuffer.o \
	$(BIN_PWD)/canopensdobuffer.o \
	$(BIN_PWD)/canopenstatemachine.o \
	$(BIN_PWD)/canopenfifo.o \
	$(BIN_PWD)/canopennmt.o \
	$(BIN_PWD)/canopensync.o \
	$(BIN_PWD)/canopenemcy.o \
	$(BIN_PWD)/canopenguard.o \
	$(BIN_PWD)/canopenpdo.o \
	$(BIN_PWD)/canopensdo.o \
	$(BIN_PWD)/canopen.o

RASPI_CTRL = ../ctrl/raspberry
LOG_PWD = $(RASPI_CTRL)/log
POLL_PWD = $(RASPI_CTRL)/poll
SOCKET_PWD = $(RASPI_CTRL)/socket
CAN_PWD = $(RASPI_CTRL)/can
CC = g++
INCLUDE = -I$(LOG_PWD)/src -I$(SOCKET_PWD)/src -I$(CAN_PWD)/src -I$(POLL_PWD)/src -Isrc
LIBS = -L. -lcan -lsocket -lpoll -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libcanopen.dll

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

# LINUX
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so:
	$(MAKE) -C $(POLL_PWD) $@
	ln -s $(POLL_PWD)/$@

libsocket.so:
	$(MAKE) -C $(SOCKET_PWD) $@
	ln -s $(SOCKET_PWD)/$@

libcan.so:
	$(MAKE) -C $(CAN_PWD) $@
	ln -s $(CAN_PWD)/$@

libcanopen.so: $(OBJECTS)
	$(MAKE) libcan.so
	$(MAKE) libsocket.so
	$(MAKE) libpoll.so
	$(MAKE) liblog.so
	$(CC) -shared $^ -o $@

# WINDOWS
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
	$(MAKE) -C $(CAN_PWD) $@
	cp $(CAN_PWD)/$@ .

libcanopen.dll: $(OBJECTS)
	$(MAKE) libcan.dll
	$(MAKE) libsocket.dll
	$(MAKE) libpoll.dll
	$(MAKE) liblog.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
