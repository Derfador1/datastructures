
#include <stdio.h>

#include "queue.h"

int main(void)
{
	queue *queuey = queue_create();

	queue_enqueue(queuey, 89);
	queue_enqueue(queuey, 82);
	queue_enqueue(queuey, 51);
	queue_enqueue(queuey, 89);
	queue_enqueue(queuey, 82);
	queue_enqueue(queuey, 82);
	queue_enqueue(queuey, 51);
	queue_enqueue(queuey, 82);

	queue_flatten(&queuey);

	while(!queue_is_empty(queuey)) {
		printf("%lf\n", queue_dequeue(queuey));
	}

	queue_destroy(queuey);
}
