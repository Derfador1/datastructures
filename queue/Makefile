
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

CFLAGS+=-I../llist

driver: driver.o queue.o

queue.o: ll_queue.o ../llist/llist.o
	$(LD) -r $^ -o $@

#queue.o: array_queue.o
#	$(LD) -r $^ -o $@

.PHONY: clean debug

clean:
	-rm *.o

debug: CFLAGS+=-g
debug: driver
