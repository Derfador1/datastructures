
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

CFLAGS+=-I../llist

driver: driver.o graph.o

.PHONY: clean debug

clean:
	-rm *.o

debug: CFLAGS+=-g
debug: driver
