BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/device.o \
	$(BIN_PWD)/fifo.o

LOG_PWD = ../../src/ctrl/raspberry/log
MAKE = make
MKDIR = mkdir -p
CC = g++
INCLUDE = -Isrc
LIBS = -L.

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

test_callback: $(BIN_PWD)/test_callback.o
	$(MAKE) liblog.so
	$(MAKE) libutil.so
	$(CC) -o $@ $^ $(LIBS) -llog

test_callback.exe: $(BIN_PWD)/test_callback.o
	$(MAKE) liblog.dll
	$(MAKE) libutil.dll
	$(CC) -o $@ $^ $(LIBS) -llog

$(BIN_PWD)/test_callback.o: test/test_callback.cpp
	$(CC) $(CFLAGS) -I$(LOG_PWD)/src -c $^ -o $@

# LINUX
liblog.so:
	$(MAKE) -C $(LOG_PWD) $@
	ln -s $(LOG_PWD)/$@

libutil.so: $(OBJECTS)
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# WINDOWS
liblog.dll:
	$(MAKE) -C $(LOG_PWD) $@
	cp $(LOG_PWD)/$@ .

libutil.dll: $(OBJECTS)
	$(CC) -shared $^ -o $@ $(LDFLAGS)

# GLOBAL
$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -DMAKE_UTIL_DLL -c $^ -o $@
