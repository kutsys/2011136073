mtest : mtest.o foo.o boo.o bar.o libmy.a
	gcc -o mtest mtest.o -L. -lmy

mtest.o : mtest.c
	gcc -c mtest.c

libmy.a : foo.o boo.o bar.o
	ar crv libmy.a foo.o boo.o bar.o

foo.o : foo.c
	gcc -c foo.c

boo.o : boo.c
	gcc -c boo.c

bar.o : bar.c
	gcc -c bar.c
