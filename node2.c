#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int data;
	struct _node *next;
}NODE;

int main(void)
{
	NODE *node=(NODE *)malloc(sizeof(NODE));	

	node->next;
	node->data;

	NODE *node_2 = (NODE *)malloc(sizeof(NODE));
	NODE *node_3 = (NODE *)malloc(sizeof(NODE));
	node_2->next = node;
	node_2->data = 1;
	node_3->next = node_2;

	printf("%p\n",node->next);
	printf("%d,%p\n",node_2->data,node_2->next);
	printf("%p\n",node_3->next);

	return 0;
}
