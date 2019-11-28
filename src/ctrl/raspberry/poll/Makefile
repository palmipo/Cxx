BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/pollfactory.o \
	$(BIN_PWD)/polldevice.o \
	$(BIN_PWD)/pollmutex.o \
	$(BIN_PWD)/pollbuffer.o

UTIL_PWD = ../../../util
LOG_PWD = ../log
MAKE = make
MKDIR = mkdir -p
CC = g++
INCLUDE = -Isrc -I$(UTIL_PWD)/src -I$(LOG_PWD)/src
LIBS = -L. -lutil -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

# LINUX
libutil.so:
	$(MAKE) -C $(UTIL_PWD) $@
	ln -s $(UTIL_PWD)/$@

liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libpoll.so: $(OBJECTS)
	$(MAKE) libutil.so
	$(MAKE) liblog.so
	$(CC) -shared $^ -o $@

# WINDOWS
libutil.dll:
	$(MAKE) -C $(UTIL_PWD) $@
	cp $(UTIL_PWD)/$@ .

liblog.dll:
	$(MAKE) -C $(LOG_PWD) $@
	cp $(LOG_PWD)/$@ .

libpoll.dll: $(OBJECTS)
	$(MAKE) libutil.dll
	$(MAKE) liblog.dll
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# GLOBAL
$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -DMAKE_POLL_FACTORY_DLL -c $^ -o $@
