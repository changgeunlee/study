#include <stdio.h>
#include <stdlib.h>

struct NODE
{
	int data;
	struct NODE *next;  //자기 자신이 아닌, 새로 생성된 노드의 주소 기억
	//head 		    //첫 번째 노드를 가르키는 용어
};


void add(struct NODE *target, int data)
{
	struct NODE *newNode = malloc(sizeof(struct NODE));
	newNode->next = target->next;
	newNode->data = data;

	target->next = newNode;

}
void remove_node(struct NODE *target)
{
	struct NODE *remove = target->next;
	target->next = remove->next;
	free(remove);
}

int main()
{
	struct NODE *head = malloc(sizeof(struct NODE));
	head->next = NULL;
	add(head,10);
	remove_node(head);
	add(head,20);
	add(head,30);


	struct NODE *cur = head->next;
	while(cur != NULL){
		printf("%d\n",cur->data);
		cur = cur->next;
	}
	cur = head->next;
	while(cur !=NULL){
		struct NODE *next=cur->next;
		free(cur);
		cur= next;
	}

	free(head);
	return 0;
}
