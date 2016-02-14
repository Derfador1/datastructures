
#include <stdio.h>

#include "queue.h"

int main(void)
{
	queue *queuey = queue_create();

	queue_enqueue(queuey, (void*)89);
	queue_enqueue(queuey, (void*)82);
	queue_enqueue(queuey, (void*)51);
	queue_enqueue(queuey, (void*)89);
	while(!queue_is_empty(queuey)) {
		printf("%p\n", queue_dequeue(queuey));
	}
	queue_enqueue(queuey, (void*)82);
	queue_enqueue(queuey, (void*)82);
	queue_enqueue(queuey, (void*)51);
	queue_enqueue(queuey, (void*)82);
	queue_enqueue(queuey, (void*)89);
	queue_enqueue(queuey, (void*)82);
	queue_enqueue(queuey, (void*)51);
	queue_enqueue(queuey, (void*)89);
	queue_enqueue(queuey, (void*)89);
	queue_enqueue(queuey, (void*)82);
	queue_enqueue(queuey, (void*)51);
	queue_enqueue(queuey, (void*)89);

	queue_flatten(&queuey);

	while(!queue_is_empty(queuey)) {
		printf("%p\n", queue_dequeue(queuey));
	}

	queue_disassemble(queuey);
}
