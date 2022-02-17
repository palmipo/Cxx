#1wire  gpio  i2c  joystick  log  Makefile  poll  rs232  socket  spi
MAKE = make

all: 1wire gpio i2c joystick log poll rs232 socket spi
	$(MAKE) -C 1wire $@
	$(MAKE) -C gpio $@
	$(MAKE) -C i2c $@
	$(MAKE) -C joystick $@
	$(MAKE) -C log $@
	$(MAKE) -C poll $@
	$(MAKE) -C rs232 $@
	$(MAKE) -C socket $@
	$(MAKE) -C spi $@

clean:
	$(MAKE) -C 1wire $@
	$(MAKE) -C gpio $@
	$(MAKE) -C i2c $@
	$(MAKE) -C joystick $@
	$(MAKE) -C log $@
	$(MAKE) -C poll $@
	$(MAKE) -C rs232 $@
	$(MAKE) -C socket $@
	$(MAKE) -C spi $@

1wire: 
	$(MAKE) -C $@

gpio: 
	$(MAKE) -C $@

i2c:
	$(MAKE) -C $@

joystick: 
	$(MAKE) -C $@

log: 
	$(MAKE) -C $@

poll: 
	$(MAKE) -C $@

rs232:
	$(MAKE) -C $@

socket:
	$(MAKE) -C $@

spi:
	$(MAKE) -C $@
