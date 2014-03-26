CC=gcc
APP=../build/xdisasmbin
CFLAGS= -Wall -L../build/lib/ -lxdisasm -ggdb

default: all

all: makelib xdisasm

withstatic: makelibwithstatic xdisasm

makelib:
	cd libxdisasm && $(MAKE)

makelibwithstatic:
	cd libxdisasm && $(MAKE) withstatic

xdisasm: main.o
	$(CC) $(CFLAGS) -o ${APP} main.o

clean:
	rm -rf *.o ${APP}
	cd libxdisasm && $(MAKE) clean
