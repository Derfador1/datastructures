
#include "queue.h"

queue *queue_create(void)
{
	queue *q = malloc(*q);
	if(!q) {
		return NULL;
	}
	q->head = NULL;
	q->tail = NULL;

	return q;
}

void queue_destroy(queue *q)
{
	if(!q) {
		return;	
	}
	ll_destroy(q->head);

	free(q);
}

bool queue_is_empty(queue *q);

bool queue_enqueue(queue *q, double data);
double queue_dequeue(queue *q);
