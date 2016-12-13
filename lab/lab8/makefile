all: mproc2

.PHONY : all clean

mproc2 : mproc2.o
	gcc -D_REENTRANT -o mproc2 mproc2.c -lpthread

clean :
	rm -rf mproc2
