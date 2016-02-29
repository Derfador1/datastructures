
#define _BSD_SOURCE
#include "hash.h"

#include <stdint.h>
#include <string.h>

struct h_llist {
	char *key;
	void *value;
	struct h_llist *next;
};

struct _hash {
	size_t item_count;
	size_t capacity;
	struct h_llist **data;
};

// static so that it will only be seen
// in this compilation unit
static const size_t DEFAULT_SIZE = 8;
static const double LOAD_FACTOR = 0.7;

static hash *__hash_create(size_t capacity);
static uint64_t __wang_hash(uint64_t key);

static void h_llist_disassemble(struct h_llist *list);
static void h_llist_destroy(struct h_llist *list);

static struct h_llist *h_llist_create(int key, void *value);
static size_t hashish(int key, size_t capacity);

// Negative returns imply error
// 0 return implies no work taken
// positive implies hash resized
static int hash_recalculate(hash *h);

hash *hash_create(void)
{
	return __hash_create(DEFAULT_SIZE);
}

void hash_disassemble(hash *h)
{
	if(h) {
		for(size_t n=0; n < h->capacity; ++n) {
			h_llist_disassemble(h->data[n]);
		}

		free(h->data);
		free(h);
	}
}

void hash_destroy(hash *h)
{
	if(h) {
		for(size_t n=0; n < h->capacity; ++n) {
			h_llist_destroy(h->data[n]);
		}

		free(h->data);
		free(h);
	}
}


bool hash_insert(hash *h, int key, void *value)
{
	if(!h || !key) {
		return false;
	}

	size_t idx = hashish(key, h->capacity);

	// Search the hash for the value to update
	struct h_llist *tmp = h->data[idx];
	while(tmp) {
		if(tmp->key == key) {
			tmp->value = value;
			return true;
		}
		tmp = tmp->next;
	}

	// If the load factor is hit, rebuild the hash,
	// and recalculate the index
	int val = hash_recalculate(h);
	if(val < 0) {
		return false;
	} else if(val > 0) {
		idx = hashish(key, h->capacity);
	}

	struct h_llist *new = h_llist_create(key, value);
	if(!new) {
		return false;
	}

	// Add new value to head of linked list
	new->next = h->data[idx];
	h->data[idx] = new;
	h->item_count += 1;

	return true;
}

void *hash_fetch(hash *h, int key)
{
	if(!h || !key) {
		return NULL;
	}

	size_t idx = hashish(key, h->capacity);
	struct h_llist *tmp = h->data[idx];

	while(tmp) {
		if(tmp->key == key) {
			return tmp->value;
		}

		tmp = tmp->next;
	}

	return NULL;
}

bool hash_exists(hash *h, int key)
{
	if(!h || !key) {
		return false;
	}

	size_t idx = hashish(key, h->capacity);
	struct h_llist *tmp = h->data[idx];

	while(tmp) {
		if(tmp->key = key) {
			return true;
		}

		tmp = tmp->next;
	}

	return false;
}

static int hash_recalculate(hash *h)
{
	if(h->item_count < LOAD_FACTOR * h->capacity) {
		return 0;
	}

	hash *cpy = __hash_create(h->capacity * 2);
	if(!cpy) {
		return -2;
	}

	for(size_t n=0; n < h->capacity; ++n) {
		struct h_llist *tmp = h->data[n];
		while(tmp) {
			hash_insert(cpy,
					tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}

	for(size_t n=0; n < h->capacity; ++n) {
		h_llist_disassemble(h->data[n]);
	}
	free(h->data);

	h->capacity = cpy->capacity;
	h->item_count = cpy->item_count;
	h->data = cpy->data;

	free(cpy);

	return 1;
}

void hash_traverse(hash *h,
		void (*func)(const char *, void *))
{
	for(size_t n = 0; n < h->capacity; ++n) {
		struct h_llist *tmp = h->data[n];
		while(tmp) {
			func(tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
}


static hash *__hash_create(size_t capacity)
{
	hash *h = malloc(sizeof(*h));
	if(!h) {
		return NULL;
	}

	h->data = calloc(capacity,
			sizeof(*h->data));
	if(!h->data) {
		free(h);
		return NULL;
	}

	h->capacity = capacity;
	h->item_count = 0;
	return h;
}

static uint64_t __wang_hash(uint64_t key)
{
	key = (~key) + (key << 21); // key = (key << 21) - key - 1;
	key = key ^ (key >> 24);
	key = (key + (key << 3)) + (key << 8); // key * 265
	key = key ^ (key >> 14);
	key = (key + (key << 2)) + (key << 4); // key * 21
	key = key ^ (key >> 28);
	key = key + (key << 31);
	return key;
}

static void h_llist_disassemble(struct h_llist *list)
{
	while(list) {
		struct h_llist *tmp = list->next;
		free(list->key);
		free(list);
		list = tmp;
	}
}

static void h_llist_destroy(struct h_llist *list)
{
	while(list) {
		struct h_llist *tmp = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = tmp;
	}
}


static struct h_llist *h_llist_create(int key, void *value)
{
	struct h_llist *node = malloc(sizeof(*node));
	if(!node) {
		return NULL;
	}

	node->key = key;
	if(!node->key) {
		free(node);
		return NULL;
	}
	node->value = value;
	node->next = NULL;

	return node;
}

static size_t hashish(int key,
		size_t capacity)
{
	uint64_t buf = key;
	//strncpy((char *)(&buf), key, sizeof(buf));

	return __wang_hash(buf) % capacity;
}

