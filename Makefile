all:ordenador

ordenador:main.o
	$(CC) $(CFLAGS) $(CDEBUG) main.o -o ordenador

main.o:main.c
	$(CC) $(CFLAGS) $(CDEBUG) -c main.c -o main.o

clean:
	rm -f ordenador main.o
