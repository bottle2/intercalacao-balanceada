all:ordenador

ordenador:main.o read write
	$(CC) $(CFLAGS) $(CDEBUG) main.o -o ordenador

main.o:main.c
	$(CC) $(CFLAGS) $(CDEBUG) -c main.c -o main.o

read:fl-rd.c
	$(CC) $(CFLAGS) $(CDEBUG) fl-rd.c -o read

write:fl-gen.c
	$(CC) $(CFLAGS) $(CDEBUG) fl-gen.c -o write

clean:
	rm -f ordenador main.o
