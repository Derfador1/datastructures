
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

LDLIBS+=-lm

driver: driver.o tree.o

driver_bst: driver_bst.o bst.o tree.o

.PHONY: clean debug

clean:
	-rm *.o driver

debug: CFLAGS+=-g
