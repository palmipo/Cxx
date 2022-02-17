BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/log.o

MAKE = make
MKDIR = mkdir -p
CC = g++
INCLUDE = -Isrc
LIBS =

CFLAGS = -g -std=c++11 $(INCLUDE) -fPIC
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

liblog.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

liblog.dll: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(MKDIR) $(BIN_PWD)
	$(CC) $(CFLAGS) -DMAKE_LOG_DLL -c $^ -o $@
