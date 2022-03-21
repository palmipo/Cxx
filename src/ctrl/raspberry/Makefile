BIN_PWD = bin/$(HOSTNAME)
MKDIR = mkdir -p
MAKE = make
CC = g++
GPIO_PWD = gpio
I2C_PWD = i2c
JOYSTICK_PWD = joystick
POLL_PWD = poll
UART_PWD = rs232
SOCKET_PWD = socket
SPI_PWD = spi
UTIL_PWD = ../../util

OBJECTS = \
	$(GPIO_PWD)/$(BIN_PWD)/raspigpio.o \
	$(GPIO_PWD)/$(BIN_PWD)/raspigpiofactory.o \
	$(I2C_PWD)/$(BIN_PWD)/raspii2c.o \
	$(JOYSTICK_PWD)/$(BIN_PWD)/joystick.o \
	$(JOYSTICK_PWD)/$(BIN_PWD)/forcefeedback.o \
	$(POLL_PWD)/$(BIN_PWD)/pollfactory.o \
	$(POLL_PWD)/$(BIN_PWD)/polldevice.o \
	$(UART_PWD)/$(BIN_PWD)/rs232unix.o \
	$(UART_PWD)/$(BIN_PWD)/rs232factory.o \
	$(SOCKET_PWD)/$(BIN_PWD)/socketbase.o \
	$(SOCKET_PWD)/$(BIN_PWD)/socketcan.o \
	$(SOCKET_PWD)/$(BIN_PWD)/sockettcp.o \
	$(SOCKET_PWD)/$(BIN_PWD)/socketudp.o \
	$(SOCKET_PWD)/$(BIN_PWD)/socketfactory.o \
	$(SPI_PWD)/$(BIN_PWD)/raspispi.o

INCLUDE = -I$(GPIO_PWD)/src -I$(I2C_PWD)/src -I$(JOYSTICK_PWD)/src -I$(POLL_PWD)/src -I$(UART_PWD)/src -I$(SOCKET_PWD)/src -I$(SPI_PWD)/src -I$(UTIL_PWD)/src -I../interface/src
LIBS = -L. -lpoll

CFLAGS = -g -std=c++11 $(INCLUDE)
LDFLAGS = $(LIBS)

all: libraspi.so

clean:
	$(MAKE) -C $(GPIO_PWD) $@
	$(MAKE) -C $(I2C_PWD) $@
	$(MAKE) -C $(JOYSTICK_PWD) $@
	$(MAKE) -C $(POLL_PWD) $@
	$(MAKE) -C $(UART_PWD) $@
	$(MAKE) -C $(SOCKET_PWD) $@
	$(MAKE) -C $(SPI_PWD) $@
	rm -f $(BIN_PWD)/*.o *.so


libraspi.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

# GLOBAL
$(GPIO_PWD)/$(BIN_PWD)/%.o: $(GPIO_PWD)/src/%.cpp
	$(MKDIR) $(GPIO_PWD)/$(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI

$(I2C_PWD)/$(BIN_PWD)/%.o: $(I2C_PWD)/src/%.cpp
	$(MKDIR) $(I2C_PWD)/$(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI

$(JOYSTICK_PWD)/$(BIN_PWD)/%.o: $(JOYSTICK_PWD)/src/%.cpp
	$(MKDIR) $(JOYSTICK_PWD)/$(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI

$(POLL_PWD)/$(BIN_PWD)/%.o: $(POLL_PWD)/src/%.cpp
	$(MKDIR) $(POLL_PWD)/$(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI

$(UART_PWD)/$(BIN_PWD)/%.o: $(UART_PWD)/src/%.cpp
	$(MKDIR) $(UART_PWD)/$(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI

$(SOCKET_PWD)/$(BIN_PWD)/%.o: $(SOCKET_PWD)/src/%.cpp
	$(MKDIR) $(SOCKET_PWD)/$(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI

$(SPI_PWD)/$(BIN_PWD)/%.o: $(SPI_PWD)/src/%.cpp
	$(MKDIR) $(SPI_PWD)/$(BIN_PWD)
	$(CC) $(CFLAGS) -c $^ -o $@ -fPIC -DRASPI

