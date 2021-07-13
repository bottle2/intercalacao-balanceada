CC = GCC 
all:organizador read write

organizador:main.o list.o
	$(CC) $(CFLAGS) $(CDEBUG) $(LDFLAGS) -o organizador main.o list.o $(LDLIBS)
main.o:main.c
list.o:list.c list.h
read:read.c
write:write.c

clean:
	rm -f main.o list.o organizador read write
	rm -f *teste*

test:
	./write teste 1000
	./organizador teste teste-ordenado
	./read teste-ordenado
