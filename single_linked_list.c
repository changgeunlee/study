#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define st_node __node
typedef struct node __node;
struct node {
	int data;
	st_node *next;
};

#define st_list __list
typedef struct list __list;
struct list {
	st_node *head;
	st_node *tail;
	int count;
};

int insert_list_head(st_list *list, int data);
void free_list(st_list *list);
void print_list(st_list *list);

int insert_list_head(st_list *list, int data)
{
	st_node *s_node;

	s_node = malloc(sizeof(st_node));
	if(s_node == (st_node *)NULL){
		fprintf(stderr, "malloc failed\n");
		return -1;
	}

	if((list->head == NULL) && (list->tail == NULL)){
		s_node->data = data;
		s_node->next = NULL;

		list->head = s_node;
		list->tail = s_node;
	} else {
		s_node->data = data;

		s_node->next = list->head;
		list->head = s_node;
	}
	printf("[INSERT] DATA[%d]\n", s_node->data);

	return 0;
}

void print_list(st_list *list)
{
	st_node *s_node;
	if((list->head == NULL) || (list->tail == NULL)){
		printf("[PRINT] List is null\n");
		return;
	}

	s_node = list->head;
	while(1){
		if(s_node == NULL) break;

		printf("[PRINT] DATA[%d]\n", s_node->data);
		s_node = s_node->next;
	}

	return;
}

void free_list(st_list *list)
{
	st_node *s_node;
	if((list->head == NULL) || (list->tail == NULL)){
		printf("[FREE] List is null\n");
		return;
	}

	s_node = list->head;
	while(1){
		if(s_node == NULL) break;

		printf("[FREE] DATA[%d]\n", s_node->data);
		free(s_node);
		s_node = s_node->next;
	}

	return;
}

int main(int argc, char **argv)
{
	st_list s_list;
	int s_num;
	int s_count;

	if(argc != 3) {
		fprintf(stderr, "./test4 <insert data> <count>\n");
		return -1;
	}
	(void)memset(((st_list *)&s_list), 0x0, sizeof(s_list));

	for(s_num = (int)atoi(argv[1]), s_count = 0; s_count < (int)atoi(argv[2]); s_count++) {
		insert_list_head(&s_list, s_num);
		++s_num;
	}	

	(void)print_list(&s_list);
	
	(void)free_list(&s_list);

	return 0;
}
