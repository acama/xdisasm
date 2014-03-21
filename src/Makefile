CC=gcc
APP=../build/xdisasmbin
CFLAGS= -Wall -L../build/lib/ -lxdisasm -ggdb

default: all

all: makelib xdisasm

makelib:
	cd libxdisasm && $(MAKE)

xdisasm: main.o
	$(CC) $(CFLAGS) -o ${APP} main.o

clean:
	rm -rf *.o ${APP}
	cd libxdisasm && $(MAKE) clean
