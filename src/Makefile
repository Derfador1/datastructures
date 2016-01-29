
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

josephus: josephus.o ../llist/llist.o

rpn.o: rpn.c
rpn.o: CFLAGS+=-I../stack -I../llist

rpn: rpn.o ../stack/ll_stack.o ../llist/double_llist.o
rpn: CFLAGS+=-I../stack -I../llist
	

.PHONY: clean debug

clean:
	-rm *.o

debug: CFLAGS+=-g
