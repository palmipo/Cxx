BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/log.o

CC = g++
INCLUDE = -Isrc
LIBS =

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all:

clean:
	rm -f $(BIN_PWD)/*.o *.so *.dll

liblog.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

liblog.dll: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -DMAKE_LOG_DLL -c $^ -o $@
