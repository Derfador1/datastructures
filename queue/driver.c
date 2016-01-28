
#include <stdio.h>

#include "queue.h"

int main(void)
{
	queue *queuey = queue_create();

	queue_enqueue(queuey, 82.1);
	queue_enqueue(queuey, 51.3);
	queue_enqueue(queuey, 89.99999);

	queue_destroy(queuey);
}
