MAKE = make

all: lib

clean:
	$(MAKE) -C src clean

lib:
	$(MAKE) -C src all
