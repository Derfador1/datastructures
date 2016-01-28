
#ifndef QUEUE_H
 #define QUEUE_H


typedef struct {
	struct llist *head;
	struct llist *tail;
} queue;

queue *queue_create(void);
void queue_destroy(queue *q);

bool queue_is_empty(queue *q);

bool queue_enqueue(queue *q, double data);
void queue_dequeue(queue *q);

#endif
