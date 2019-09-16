MAKE = make

all: 1wire i2c rs232 socket spi

clean:
	$(MAKE) -C 1wire clean
	$(MAKE) -C i2c clean
	$(MAKE) -C rs232 clean
	$(MAKE) -C socket clean

1wire: 
	$(MAKE) -C $@

i2c:
	$(MAKE) -C $@

rs232:
	$(MAKE) -C $@

socket:
	$(MAKE) -C $@

spi:
	$(MAKE) -C $@
