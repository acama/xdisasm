CFLAGS := -fPIC -O3 -g -Wall -Werror
CC := gcc
MAJOR := 1
MINOR := 0
NAME := xdisasm
VERSION := $(MAJOR).$(MINOR)
 
lib: lib$(NAME).so
 
lib$(NAME).so: $(NAME).o
	$(CC) -shared -Wl,-soname,lib$(NAME).so $^ -o ../build/lib/$@ -lbfd -lopcodes
 
clean:
	$(RM) *.o *.so*
