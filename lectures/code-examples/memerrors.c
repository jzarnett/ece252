#include <stdlib.h>

typedef struct node_t {
	int val;
	struct node_t *next;
} node_t;

/* insert at tail */
node_t *insert(node_t *head, int val) {
	node_t *node = malloc(sizeof(node_t));
	node->val = val;
	node->next = NULL;

	if(!head) return node;

	node_t *curr = head;
	while(curr->next) curr = curr->next;
	curr->next = node;
	return head;
}

/* remove from tail */
int remove(node_t *head) {
	if(!head->next) {
		int temp = head->val;
		free(head);
		return temp;
	}

	node_t *curr = head;
	while(curr->next->next) curr = curr->next;
	int temp = curr->next->val;
	free(curr->next);
	curr->next = NULL;
	return temp;
}

/* Uncomment various commented lines in main() to see changing valgrind
 * reports:
 * gcc -g -std=c99 -o memerrors memerrors.c
 * valgrind --leak-check=full ./memerrors 5
 */

int main(int argc, char **argv) {
	int n = atoi(argv[1]);
	node_t *list = NULL;
	for(int i=0; i<n; i++)
		list = insert(list, i);
	//for(int i=0; i<n; i++)
		//remove(list);
	//remove(list);

	/*
	int *a = malloc(n*sizeof(int));
	int i = 0;
	while(i++ < n) a[i] = i;
	//free(a);
	*/
}
