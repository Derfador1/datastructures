
#define QUEUE_ARRAY
#include "queue.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

static const size_t DEFAULT_QUEUE_CAPACITY = 8;

// Doubles the capacity of the queue
bool __queue_resize(queue *q);

// IMPORTANT: the head and tail are only equal in an empty
// queue.  This means the queue always has at least one
// empty slot.

queue *queue_create(void)
{
	queue *q = malloc(sizeof(*q));
	if(!q) {
		return NULL;
	}

	q->data = malloc(DEFAULT_QUEUE_CAPACITY * sizeof(*q->data));
	if(!q->data) {
		free(q);
		return NULL;
	}
	q->tail = q->head = 0;
	q->capacity = DEFAULT_QUEUE_CAPACITY;

	return q;
}

void queue_destroy(queue *q)
{
	if(!q) {
		return;
	}

	free(q->data);
	free(q);
}

bool queue_is_empty(queue *q)
{
	return !q || q->tail == q->head;
}

size_t queue_size(queue *q)
{
	if(!q) {
		return 0;
	}

	if(q->head > q->tail) {
		return q->capacity - q->head + q->tail;
	} else {
		return q->tail - q->head;
	}
}

bool queue_enqueue(queue *q, void *data)
{
	if(!q) {
		return false;
	}

	if(queue_size(q) == q->capacity - 1) {
		if(!__queue_resize(q)) {
			return false;
		}
	}
	
	q->data[q->tail++] = data;
	q->tail %= q->capacity;

	return true;
}

void *queue_dequeue(queue *q)
{
	// If the user needs to distinguish between stored NULL values
	// and failure, they should be checking if the queue is empty
	if(queue_is_empty(q)) {
		return NULL;
	}

	void *value = q->data[q->head++];
	q->head %= q->capacity;

	return value;
}

void queue_flatten(queue **q)
{
}

// Double capacity, copies data.
bool __queue_resize(queue *q)
{
	void **new_data = realloc(q->data, 2*q->capacity * sizeof(*q->data));

	if(!new_data) {
		return false;
	}
	q->data = new_data;

	// Copy from start of array if it has looped around
	if(q->tail < q->head) {
		memcpy(q->data + q->capacity, q->data, q->tail * sizeof(*q->data));
		q->tail += q->capacity;
	}

	q->capacity *= 2;

	return true;
}
