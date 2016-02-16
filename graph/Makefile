
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

CFLAGS+=-I../llist -I../hash
LDFLAGS+=-L../llist -L../hash

driver: driver.o graph.o ../llist/llist.o ../hash/hash.o


.PHONY: clean debug

clean:
	-rm *.o

debug: CFLAGS+=-g
debug: driver
