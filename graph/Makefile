
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

CFLAGS+=-I../llist -I../hash -I../queue
LDFLAGS+=-L../llist -L../hash -L../queue

driver: driver.o graph.o ../llist/llist.o ../hash/hash.o ../queue/queue.o


.PHONY: clean debug

clean:
	-rm *.o

debug: CFLAGS+=-g
debug: driver
