BIN_PWD = bin/$(HOSTNAME)

OBJECTS = \
	$(BIN_PWD)/raspii2c.o

CC = g++
INCLUDE = -I../../interface -Isrc -I../log/src
LIBS = -L. -llog

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libraspii2c.so

clean:
	rm -f $(BIN_PWD)/*.o libraspii2c.so

libraspii2c.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

$(BIN_PWD)/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@
