CC=gcc
CFLAGS= -I.

memo: memo.c libmemo.o
	$(CC) -o memo memo.c libmemo.o $(CFLAGS)
libmemo.o:
	$(CC) -c libmemo.c $(CFLAGS)
