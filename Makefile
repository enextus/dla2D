CC = gcc
CFLAGS = -arch i386 -Wall -O3
INCLUDES = 
LFLAGS = 
LIBS = -lm

OBJS = dla.o paulslib.o bitmaplib.o

all: dla

dla: $(OBJS)
	$(CC) $(INCLUDES) $(CFLAGS) -o dla $(OBJS) $(LFLAGS) $(LIBS)

dla.o: dla.c
	$(CC) $(INCLUDES) $(CFLAGS) -c dla.c

paulslib.o: paulslib.c paulslib.h
	$(CC) $(INCLUDES) $(CFLAGS) -c paulslib.c

bitmaplib.o: bitmaplib.c bitmaplib.h
	$(CC) $(INCLUDES) $(CFLAGS) -c bitmaplib.c

clean:
	rm -rf dla core $(OBJS)

