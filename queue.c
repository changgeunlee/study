#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int value;
	struct _node* next;
}NODE;


typedef struct _list{
	int count;
	NODE* head;
}LIST;

void init(LIST* lptr){
	lptr->count=0;
	lptr->head=NULL;
}



int main()
{
	LIST *myList=(LIST*)malloc(sizeof(LIST));
	init(myList);

}
