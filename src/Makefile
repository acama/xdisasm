CC=gcc
APP=../build/xdisasmbin
CFLAGS= -Wall 
LDFLAGS= -Llibxdisasm/build/lib/ -lxdisasm


default: all

all: getlib makelib xdisasm

withstatic: getlib makelibwithstatic xdisasm

getlib:
	test -d libxdisasm || git clone https://github.com/acama/libxdisasm

makelib:
	cd libxdisasm && $(MAKE)
	cp libxdisasm/build/lib/libxdisasm.so ../build/lib/libxdisasm.so

makelibwithstatic:
	cd libxdisasm && $(MAKE) withstatic 
	cp libxdisasm/build/lib/libxdisasm.so ../build/lib/libxdisasm.so

xdisasm: main.o
	$(CC) $(CFLAGS) main.o -o ${APP} $(LDFLAGS)

clean:
	rm -rf *.o ${APP}
	rm -rf libxdisasm
