
#include <stdbool.h>
#include <stdio.h>

#include "llist.h"
#include "hash.h"
#include "queue.h"
#include "graph.h"

graph *big_graph(void);
void print_item(const void *data, bool is_node);

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
					goto DONE;
				}
			}

			check = check->next;
		}

		ll_disassemble(adjacencies);
	}

DONE:
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
	graph *graphy = graph_create();

	graph_add_node(graphy, "A");
	graph_add_node(graphy, "B");
	graph_add_edge(graphy, "B", "A", 5);
	graph_add_node(graphy, "C");
	graph_add_node(graphy, "D");
	graph_add_edge(graphy, "B", "D", 5);
	graph_add_edge(graphy, "D", "B", 5);
	graph_add_edge(graphy, "C", "A", 5);
	graph_add_node(graphy, "E");

	graph_print(graphy, print_item);

	printf("\n%zu nodes, %zu edges\n", graph_node_count(graphy), graph_edge_count(graphy));

	struct llist *path = graph_path(graphy, (void *)"D", (void *)"A");
	struct llist *curr = path;
	while(curr) {
		printf(u8"%s → ", (char *)(curr->data));
		curr = curr->next;
	}
	printf("\n");
	ll_disassemble(path);

	graph *bigun = big_graph();
	graph_print(bigun, print_item);

	graph_disassemble(graphy);
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

