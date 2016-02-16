
#include <stdbool.h>
#include <stdio.h>

#include "llist.h"
#include "hash.h"
#include "queue.h"
#include "graph.h"

graph *big_graph(void);
void print_item(const void *data, bool is_node);
void print_path(const struct llist *path);

struct pqueue_node {
	const void *data;
	int priority;
};

struct pqueue_node *__make_node(const void *data, int priority)
{
	struct pqueue_node *pqn = malloc(sizeof(*pqn));
	if(!pqn) {
		return NULL;
	}
	pqn->data = data;
	pqn->priority = priority;

	return pqn;
}

struct llist *dijkstra_path(const graph *g, const void *from, const void *to)
{

	return NULL;
}





struct llist *graph_path(const graph *g, const void *from, const void *to)
{
	hash *visited = hash_create();
	queue *to_process = queue_create();

	hash_insert(visited, from, NULL);
	queue_enqueue(to_process, from);

	while(!queue_is_empty(to_process)) {
		void *curr = queue_dequeue(to_process);

		struct llist *adjacencies = graph_adjacent_to(g, curr);
		struct llist *check = adjacencies;
		while(check) {
			if(!hash_exists(visited, check->data)) {
				hash_insert(visited, check->data, curr);
				queue_enqueue(to_process, check->data);
				if(check->data == to) {
					ll_disassemble(adjacencies);
					goto FOUND;
				}
			}

			check = check->next;
		}

		ll_disassemble(adjacencies);
	}

	queue_disassemble(to_process);
	hash_disassemble(visited);
	return NULL;

FOUND:
	queue_disassemble(to_process);

	struct llist *path = ll_create(to);
	while(hash_fetch(visited, path->data)) {
		ll_add(&path, hash_fetch(visited, path->data));
	}

	hash_disassemble(visited);

	return path;
}

int main(void)
{
	graph *bigun = big_graph();
	graph_print(bigun, print_item);

	printf("\n%zu nodes, %zu edges\n", graph_node_count(bigun), graph_edge_count(bigun));

	{
		struct llist *path = graph_path(bigun, "A", "L");
		printf("From A to L: ");
		print_path(path);
		ll_disassemble(path);
	}

	{
		struct llist *path = dijkstra_path(bigun, "A", "L");
		printf("Shortest A to L: ");
		print_path(path);
		ll_disassemble(path);
	}

	{
		struct llist *path = graph_path(bigun, "K", "L");
		printf("From K to L: ");
		print_path(path);
		ll_disassemble(path);
	}

	{
		struct llist *path = dijkstra_path(bigun, "K", "L");
		printf("Shortest K to L: ");
		print_path(path);
		ll_disassemble(path);
	}

	{
		struct llist *path = graph_path(bigun, "D", "A");
		printf("From D to A: ");
		print_path(path);
		ll_disassemble(path);
	}


	graph_disassemble(bigun);
}

graph *big_graph(void)
{
	graph *g = graph_create();

	graph_add_node(g, "A");
	graph_add_node(g, "B");
	graph_add_node(g, "C");
	graph_add_node(g, "D");
	graph_add_node(g, "E");
	graph_add_node(g, "F");
	graph_add_node(g, "G");
	graph_add_node(g, "H");
	graph_add_node(g, "J");
	graph_add_node(g, "K");
	graph_add_node(g, "L");

	graph_add_edge(g, "A", "B", 14);
	graph_add_edge(g, "A", "K", 11);
	graph_add_edge(g, "A", "C", 10);
	graph_add_edge(g, "B", "C", 3);
	graph_add_edge(g, "B", "F", 6);
	graph_add_edge(g, "C", "B", 1);
	graph_add_edge(g, "C", "E", 6);
	graph_add_edge(g, "D", "C", 6);
	graph_add_edge(g, "D", "G", 10);
	graph_add_edge(g, "E", "D", 6);
	graph_add_edge(g, "E", "F", 15);
	graph_add_edge(g, "E", "H", 7);
	graph_add_edge(g, "E", "K", 9);
	graph_add_edge(g, "E", "B", 11);
	graph_add_edge(g, "F", "H", 8);
	graph_add_edge(g, "F", "C", 7);
	graph_add_edge(g, "F", "L", 16);
	graph_add_edge(g, "G", "E", 13);
	graph_add_edge(g, "G", "J", 10);
	graph_add_edge(g, "H", "G", 5);
	graph_add_edge(g, "H", "J", 9);
	graph_add_edge(g, "J", "F", 19);
	graph_add_edge(g, "J", "L", 7);
	graph_add_edge(g, "K", "C", 5);
	graph_add_edge(g, "K", "G", 18);

	return g;
}

void print_item(const void *data, bool is_node)
{
	if(is_node) {
		printf("\n%s", (char *)data);
	} else {
		printf(u8" → %s", (char *)data);
	}
}

void print_path(const struct llist *path)
{
	while(path) {
		printf(u8"%s → ", (char *)(path->data));
		path = path->next;
	}
	printf("\n");
}
