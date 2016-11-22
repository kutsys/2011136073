all: mtest

# Which compiler
CC = gcc

# Where are include files kept
INCLUDE = .

# Final Compile option
COMOP = -o mtest

.PHONY : all clean

mtest : mtest.o foo.o boo.o bar.o libmy.a
	$(CC) $(COMOP) mtest.o -L$(INCLUDE) -lmy

mtest.o : mtest.c
	$(CC) -c mtest.c

libmy.a : foo.o boo.o bar.o
	ar crv libmy.a foo.o boo.o bar.o

foo.o : foo.c
	$(CC) -c foo.c

boo.o : boo.c
	$(CC) -c boo.c

bar.o : bar.c
	$(CC) -c bar.c

clean :
	rm *.o *.a mtest
