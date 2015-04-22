CC= gcc
CFLAGS= -O3
CPPFLAGS= 

all:
	$(CC) $(CFLAGS) $(CPPFLAGS) -o fbmode fbmode.c
