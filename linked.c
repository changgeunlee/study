#include <stdio.h>
#include <stdlib.h>

#define DATE	0
#define WEEK	1
#define MONTHLY 2
#define PERIOD	3
#define MAX  	4

#define node_t __node_st
typedef struct node_st __node_st;
struct node_st {
	int var;
	node_t *next;
};

#define list_t __list_st
typedef struct list_st __list_st;
struct list_st {
	node_t *head;
	node_t *tail;
	int total_count;
};

void free_list(list_t *list[]);
void print_list(list_t *list[0]);
void init_list(list_t *list[]);
int append_list(list_t *list[], node_t *node, int type);
node_t *malloc_node(int data);

void free_list(list_t *list[])
{
	int i;	
	list_t *tlist;

	for(i=0;i<MAX;i++){
		node_t *thead;
		node_t *ttail;

		tlist = list[i];
		if(tlist == NULL){
			printf("[%s][%d] list is null\n",__func__,__LINE__);		
			continue;
		}

		thead = tlist->head;
		ttail = tlist->tail;
		while(thead){
			node_t *tmp;
			printf("[%s][%d] type[%d] head[%p] head->next[%p] tail[%p] tail->next[%p] var[%d]\n",__func__,__LINE__, i, thead, thead->next, ttail, ttail->next, thead->var);
			tmp = thead->next;
			free(thead);
			thead = tmp;
		}
		printf("[%s][%d] type[%d] list[%p]\n",__func__,__LINE__, i, tlist);
		free(tlist);
	}
	return;
}

void print_list(list_t *list[])
{
	int i;	
	list_t *tlist;

	for(i=0;i<MAX;i++){
		node_t *thead;
		node_t *ttail;

		tlist = list[i];
		if(tlist == NULL){
			printf("[%s][%d] list is null\n",__func__,__LINE__);		
			continue;
		}

		thead = tlist->head;
		ttail = tlist->tail;
		while(thead){
			printf("[%s][%d] type[%d] head[%p] head->next[%p] tail[%p] tail->next[%p] var[%d]\n",__func__,__LINE__, i, thead, thead->next, ttail, ttail->next, thead->var);
			thead = thead->next;
		}
	}

	return;
}

void init_list(list_t *list[])
{
	int i;
	for(i = 0; i < MAX; i++){
		list[i] = malloc(sizeof(list_t));
		if(list[i] == NULL){
			printf("[%s][%d] list malloc failed\n", __func__,__LINE__);
			continue;
		}
		printf("[%s][%d] list malloc[%p]\n", __func__,__LINE__,list[i]);
	}
	return;
}


node_t *malloc_node(int data)
{
	node_t *n;
	n = malloc(sizeof(node_t));
	if (n == NULL){
		printf("[%s][%d] malloc failed\n", __func__,__LINE__);
		return NULL;
	}
	n->var = data;
	n->next = NULL;
	printf("[%s][%d] malloc success[%d] n[%p] n->n[%p]\n", __func__,__LINE__, n->var, n, n->next);
	return n;
}

int append_list(list_t *list[], node_t *node, int type)
{
	list_t *tlist;

	if (list[type] == (list_t*)NULL){
		printf("[%s][%d] list is null\n", __func__,__LINE__);
		return -1;
	}
	tlist = list[type];
	//printf("[%s][%d] type[%d] list[%p]\n", __func__,__LINE__, type, tlist);
	if ((tlist->head == NULL) && (tlist->tail == NULL)){
		tlist->head = tlist->tail = node;
		printf("[%s][%d] {{FIRST}}  type[%d] node[%p] head[%p] head->next[%p] tail[%p] tail->next[%p]\n", __func__,__LINE__, type, node, tlist->head, tlist->head->next, tlist->tail, tlist->tail->next);
	} else {
		node->next = tlist->head;
		tlist->head = node;
		printf("[%s][%d] {{SECOND}}  type[%d] node[%p] head[%p] head->next[%p] tail[%p]\n", __func__,__LINE__, type, node, tlist->head, tlist->head->next, tlist->tail);
	}
	
	return 0;
}

int main(void)
{
	int ret = 0;
	list_t *list[4] = {0,};

	/* 1. initialize list */
	(void)init_list(list);

	/* 2. make node */
	node_t *node1;
	node1 = malloc_node((int)10);

	/* 3. append list */
	ret = append_list(list, node1, DATE);
	if (ret == -1) {
		free(node1);
		//return 0;
	}

	/* 2. make node */
	node_t *node5;
	node5 = malloc_node((int)100);

	/* 3. append list */
	ret = append_list(list, node5, DATE);
	if (ret == -1) {
		free(node5);
		//return 0;
	}

	/* 2. make node */
	node_t *node6;
	node6 = malloc_node((int)1000);

	/* 3. append list */
	ret = append_list(list, node6, DATE);
	if (ret == -1) {
		free(node6);
		//return 0;
	}

	/* 2. make node */
	node_t *node2;
	node2 = malloc_node((int)20);

	/* 3. append list */
	ret = append_list(list, node2, WEEK);
	if (ret == -1) {
		free(node2);
		//return 0;
	}

	/* 2. make node */
	node_t *node3;
	node3 = malloc_node((int)30);

	/* 3. append list */
	ret = append_list(list, node3, MONTHLY);
	if (ret == -1) {
		free(node3);
		//return 0;
	}

	/* 2. make node */
	node_t *node4;
	node4 = malloc_node((int)40);

	/* 3. append list */
	ret = append_list(list, node4, PERIOD);
	if (ret == -1) {
		free(node4);
		//return 0;
	}

	(void)print_list(list); // TODO
	(void)free_list(list); // TODO
	return 0;
}

