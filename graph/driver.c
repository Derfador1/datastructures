
#include <stdbool.h>
#include <stdio.h>

#include "llist.h"
#include "hash.h"
#include "queue.h"
#include "graph.h"

void print_item(const void *data, bool is_node)
{
	if(is_node) {
		printf("\n%s", (char *)data);
	} else {
		printf(u8" → %s", (char *)data);
	}
}

struct llist *graph_path(const graph *g, void *from, void *to)
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

	graph_add_node(graphy, (void *)"A");
	graph_add_node(graphy, (void *)"B");
	graph_add_edge(graphy, (void *)"B", (void *)"A", 5);
	graph_add_node(graphy, (void *)"C");
	graph_add_node(graphy, (void *)"D");
	graph_add_edge(graphy, (void *)"B", (void *)"D", 5);
	graph_add_edge(graphy, (void *)"D", (void *)"B", 5);
	graph_add_edge(graphy, (void *)"C", (void *)"A", 5);
	graph_add_node(graphy, (void *)"E");

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

	graph_disassemble(graphy);
}
