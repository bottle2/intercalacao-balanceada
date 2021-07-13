CC = gcc 
CFLAGS=-Wpedantic -Wall -Wextra
all:organizador read write

.SUFFIXES:.c .o
.c.o:
	$(CC) $(CFLAGS) $(CDEBUG) -c $<

organizador:main.o queue.o
	$(CC) $(CFLAGS) $(CDEBUG) $(LDFLAGS) -o organizador main.o queue.o $(LDLIBS)
main.o:main.c
queue.o:queue.c queue.h
read:read.c
write:write.c

clean:
	rm -f main.o queue.o organizador read write
	rm -f *teste*

test:
	./write teste 1000
	./organizador teste teste-ordenado
	./read teste-ordenado

check:
	cppcheck --enable=all --suppress=missingIncludeSystem main.c queue.c
