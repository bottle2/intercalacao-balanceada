CC = gcc 
CFLAGS=-Wpedantic -Wall -Wextra -O2 -march=native -flto
all:organizador read write

.SUFFIXES:.c .o
.c.o:
	$(CC) $(CFLAGS) $(CDEBUG) -c $<

organizador:main.o merge.o queue.o try.o util.o
	$(CC) $(CFLAGS) $(CDEBUG) $(LDFLAGS) \
		-o organizador main.o merge.o queue.o try.o util.o\
		$(LDLIBS)
main.o:main.c try.h config.h util.h
merge.o:merge.c merge.h queue.h config.h util.h
queue.o:queue.c queue.h
try.o:try.c try.h config.h
util.o:util.c util.h
read:read.c
write:write.c

clean:
	rm -f main.o queue.o try.o organizador read write
	rm -f *teste*

test:
	./write arq 4000000
	./organizador arq arq-ordenado
	./read arq-ordenado

check:
	cppcheck --enable=all --suppress=missingIncludeSystem main.c queue.c merge.c try.c
	cppcheck --enable=all --suppress=missingIncludeSystem write.c
	cppcheck --enable=all --suppress=missingIncludeSystem read.c
