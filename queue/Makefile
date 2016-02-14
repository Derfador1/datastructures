
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

CFLAGS+=-I../llist

LDLIBS+=-lm

# The double_llist.o is cheating and should be punished
# It really should be a path include parameter to LDFLAGS
driver: driver.o ll_queue.o ../llist/double_llist.o

.PHONY: clean debug

clean:
	-rm *.o

debug: CFLAGS+=-g
debug: driver
