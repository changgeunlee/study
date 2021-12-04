#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INET_IPV4	0
#define INET_IPV6	1


#define ipv4_node __ipv4_node
typedef struct ipv4_node_st __ipv4_node;
struct ipv4_node_st {
	char v4[16];
	
	ipv4_node *prev;
	ipv4_node *next;
};

#define ipv6_node __ipv6_node
typedef struct ipv6_node_st __ipv6_node;
struct ipv6_node_st {
	char v6[42];

	ipv6_node *prev;
	ipv6_node *next;
};

#define domain_list __domain_list
typedef struct domain_list_st __domain_list;
struct domain_list_st {
	ipv4_node *v4head;
	ipv4_node *v4tail;

	ipv6_node *v6head;
	ipv6_node *v6tail;

	domain_list *prev;
	domain_list *next;

	char domain_name[42];
	int v4_count;
	int v6_count;
};

#define list __list
typedef struct list_st __list;
struct list_st {
	domain_list *head;
	domain_list *tail;

	int total_count;
};

int init(list **l);
domain_list *alloc_domain_list(char *name);
int append_list(list *l, domain_list *domain);
void *alloc_domain_node(int type, char *ip);
int append_domain_list(domain_list *domain, void *node, int type);
void print_list(list *l);
void free_list(list **l);

int init(list **l) 
{
	if ((*l) != (list *)NULL) {
		printf("[%s][%d] list is not null\n",__func__, __LINE__);
		return -1;
	}

	*l = malloc(sizeof(list));
	if ((*l) == (list *)NULL){
		printf("[%s][%d] list malloc failed\n",__func__, __LINE__);
		return -1;
	}

	(*l)->head = (*l)->tail = NULL;
	(*l)->total_count = 0;
	printf("[%s][%d] list[%p] list->head[%p] list->tail[%p]\n",__func__, __LINE__, (*l), (*l)->head, (*l)->tail);

	return 0;
}

domain_list *alloc_domain_list(char *name)
{
	domain_list *domain;

	domain = malloc(sizeof(domain_list));
	if (domain == (domain_list*)NULL){
		printf("[%s][%d] domain_list malloc failed\n",__func__, __LINE__);
		return NULL;
	}

	domain->v4head = domain->v4tail = NULL;
	domain->v6head = domain->v6tail = NULL;
	snprintf(&domain->domain_name[0], sizeof(domain->domain_name),
			"%s", name);
	printf("[%s][%d] domain_list[%p] domain_list->v4head[%p] domain_list->v4tail[%p] domain_list->v6head[%p] domain_list->v6tail[%p] domain_list->prev[%p] domain_list->next[%p] name[%s]\n",__func__, __LINE__, 
			domain, 
			domain->v4head, domain->v4tail,
			domain->v6head, domain->v6tail,
			domain->prev, domain->next,
			domain->domain_name);

	return domain;
}

int append_list(list *l, domain_list *domain) 
{
	if (l == (list *)NULL){
		free(domain);
		printf("[%s][%d] list is null, so domain freed\n",__func__, __LINE__);
		return -1;
	}
	if (domain == (domain_list *)NULL){
		printf("[%s][%d] domain_list is null\n",__func__, __LINE__);
		return -1;
	}

	if ((l->head == (domain_list *)NULL) && (l->tail == (domain_list *)NULL)){
		l->head = l->tail = domain;	
		l->total_count++;
	
		printf("-----------------------------------\n");
		printf("[%s][%d] list[%p] list->head[%p] list->tail[%p] list->total_count[%d]\n",__func__, __LINE__, l, l->head, l->tail, l->total_count);
		printf("[%s][%d] domain_list[%p] domain_list->v4head[%p] domain_list->v4tail[%p] domain_list->v6head[%p] domain_list->v6tail[%p]\n",__func__, __LINE__, domain, domain->v4head, domain->v4tail, domain->v6head, domain->v6tail);
		printf("-----------------------------------\n");
	} else {
		l->tail->next = domain;
		l->tail = domain;

		printf("-----------------------------------\n");
		printf("[%s][%d] list[%p] list->head[%p] list->tail[%p] list->total_count[%d]\n",__func__, __LINE__, l, l->head, l->tail, l->total_count);
		printf("[%s][%d] domain_list[%p] domain_list->v4head[%p] domain_list->v4tail[%p] domain_list->v6head[%p] domain_list->v6tail[%p]\n",__func__, __LINE__, domain, domain->v4head, domain->v4tail, domain->v6head, domain->v6tail);
		printf("-----------------------------------\n");
	}

	return 0;
} 

void *alloc_domain_node(int type, char *ip)
{
	void *node;

	if (type == INET_IPV4){
		node = malloc(sizeof(ipv4_node));
		if (((ipv4_node *)node) == (ipv4_node *)NULL){
			printf("[%s][%d] ipv4_node malloc failed\n",__func__, __LINE__);
			return NULL;
		}
		((ipv4_node *)node)->prev = ((ipv4_node *)node)->next = NULL;
		snprintf(&((ipv4_node *)node)->v4[0], sizeof(((ipv4_node *)node)->v4),
				"%s", ip);
		printf("[%s][%d] == ipv4 == domain_node[%p] domain_node->prev[%p] domain_node->next[%p] domain_node->v4[%s]\n",__func__, __LINE__, ((ipv4_node *)node), ((ipv4_node *)node)->prev, ((ipv4_node *)node)->next, ((ipv4_node *)node)->v4);
	} else{
		node = malloc(sizeof(ipv6_node));
		if (((ipv6_node *)node) == (ipv6_node *)NULL){
			printf("[%s][%d] ipv6_node malloc failed\n",__func__, __LINE__);
			return NULL;
		}
		((ipv6_node *)node)->prev = ((ipv6_node *)node)->next = NULL;
		snprintf(&((ipv6_node *)node)->v6[0], sizeof(((ipv6_node *)node)->v6),
				"%s", ip);
		printf("[%s][%d] == ipv6 == domain_node[%p] domain_node->prev[%p] domain_node->next[%p] domain_node->ipv6[%s]\n",__func__, __LINE__, ((ipv6_node *)node), ((ipv6_node *)node)->prev, ((ipv6_node *)node)->next, ((ipv6_node *)node)->v6);
	}

	return node;
}

int append_domain_list(domain_list *domain, void *node, int type)
{
	if (domain == (domain_list *)NULL) {
		printf("[%s][%d] domain is null\n",__func__, __LINE__);
		return -1;
	}

	if (type == INET_IPV4) {
		if ((domain->v4head == (ipv4_node *)NULL) && (domain->v4tail == (ipv4_node *)NULL)){
			domain->v4head = domain->v4tail = (ipv4_node *)node;	
		} else {
			((ipv4_node *)node)->next = domain->v4head;
			domain->v4head = (ipv4_node *)node;
		}
		domain->v4_count++;
		printf("[%s][%d] == ipv4 == domain_list[%p] domain_list->v4head[%p] domain_list->v4tail[%p] domain_list->total_count[%d]\n",__func__, __LINE__, domain, domain->v4head, domain->v4tail, domain->v4_count);
	} else {
		if ((domain->v6head == (ipv6_node *)NULL) && (domain->v6tail == (ipv6_node *)NULL)){
			domain->v6head = domain->v6tail = (ipv6_node *)node;	
		} else {
			((ipv6_node *)node)->next = domain->v6head;
			domain->v6head = (ipv6_node *)node;
		}
		domain->v6_count++;
		printf("[%s][%d] == ipv6 == domain_list[%p] domain_list->v6head[%p] domain_list->v6tail[%p] domain_list->total_count[%d]\n",__func__, __LINE__, domain, domain->v6head, domain->v6tail, domain->v6_count);
	}

	return 0;
}

void print_list(list *l)
{
	domain_list *tmp;
	if (l == (list *)NULL) {
		printf("[%s][%d] list is null\n", __func__, __LINE__);
		return;
	}

	tmp = l->head;
	while(tmp) {
		ipv4_node *tmp_v4node;
		ipv6_node *tmp_v6node;

		tmp_v4node = tmp->v4head;
		if (tmp_v4node) {
			while(tmp_v4node) {
				printf("[%s][%d] == ipv4 == list[%p] list->head[%p] domain_list->head[%p] domain_list->prev[%p] domain_list->next[%p]\n", __func__, __LINE__, l, tmp, tmp_v4node, tmp_v4node->prev, tmp_v4node->next);
				tmp_v4node = tmp_v4node->next;
			}
		}

		tmp_v6node = tmp->v6head;
		if (tmp_v6node) {
			while(tmp_v6node) {
				printf("[%s][%d] == ipv6 == list[%p] list->head[%p] domain_list->head[%p] domain_list->prev[%p] domain_list->next[%p]\n", __func__, __LINE__, l, tmp, tmp_v6node, tmp_v6node->prev, tmp_v6node->next);
				tmp_v6node = tmp_v6node->next;
			}
		}
		tmp = tmp->next;
	}

	return;
}

void free_list(list **l)
{
	domain_list *tmp;

	tmp = (*l)->head;
	while(tmp) {
		ipv4_node *tmp_v4node;
		ipv6_node *tmp_v6node;
		domain_list *tmp_free_domain_list;

		tmp_v4node = tmp->v4head;
		if (tmp_v4node) {
			while(tmp_v4node) {
				ipv4_node *tmp_free_node;

				tmp_free_node = tmp_v4node->next;
				printf("[%s][%d] v4node free[%p]\n", __func__, __LINE__, tmp_v4node);
				free(tmp_v4node);
				tmp_v4node = tmp_free_node;
			}
		}

		tmp_v6node = tmp->v6head;
		if (tmp_v6node) {
			while(tmp_v6node) {
				ipv6_node *tmp_free_node;

				tmp_free_node = tmp_v6node->next;
				printf("[%s][%d] v6node free[%p]\n", __func__, __LINE__, tmp_v6node);
				tmp_v6node = tmp_v6node->next;
				free(tmp_v6node);
				tmp_v6node = tmp_free_node;
			}
		}
		tmp_free_domain_list = tmp->next;
		printf("[%s][%d] domain_list free[%p]\n", __func__, __LINE__, tmp);
		free(tmp);
		tmp = tmp_free_domain_list;
	}

	if ((*l) != (list*)NULL) {
		printf("[%s][%d] list free[%p]\n", __func__, __LINE__, (*l));
		free((*l));
		*l = NULL;
	}

	return;
}

int main(void)
{
	list *list = NULL;
	domain_list *domain1 = NULL;
	ipv4_node *v4node1, *v4node2;
	ipv6_node *v6node1, *v6node2;

	domain_list *domain2 = NULL;
	ipv4_node *v4node3, *v4node4;
	ipv6_node *v6node3, *v6node4;

	if (init(&list) < 0) {
		printf("[%s][%d] init failed\n",__func__, __LINE__);
		return 0;
	}

	domain1 = alloc_domain_list("www.naver.com");
	if (append_list(list, domain1) < 0) {
		printf("[%s][%d] append_list failed\n",__func__, __LINE__);
		return 0;
	}

	v4node1 = (ipv4_node *)alloc_domain_node(INET_IPV4, "172.10.10.20");
	if (append_domain_list(domain1, v4node1, INET_IPV4) < 0){
		printf("[%s][%d] append_node failed\n",__func__, __LINE__);
		return 0;
	}
	v4node2 = (ipv4_node *)alloc_domain_node(INET_IPV4, "192.168.104.10");
	if (append_domain_list(domain1, v4node2, INET_IPV4) < 0){
		printf("[%s][%d] append_node failed\n",__func__, __LINE__);
		return 0;
	}
	v6node1 = (ipv6_node *)alloc_domain_node(INET_IPV6, "fec0::1");
	if (append_domain_list(domain1, v6node1, INET_IPV6) < 0){
		printf("[%s][%d] append_node failed\n",__func__, __LINE__);
		return 0;
	}
	v6node2 = (ipv6_node *)alloc_domain_node(INET_IPV6, "fec0::2");
	if (append_domain_list(domain1, v6node2, INET_IPV6) < 0){
		printf("[%s][%d] append_node failed\n",__func__, __LINE__);
		return 0;
	}

	domain2 = alloc_domain_list("www.google.com");
	if (append_list(list, domain2) < 0) {
		printf("[%s][%d] append_list failed\n",__func__, __LINE__);
		return 0;
	}

	v4node3 = (ipv4_node *)alloc_domain_node(INET_IPV4, "100.100.100.1");
	if (append_domain_list(domain2, v4node3, INET_IPV4) < 0){
		printf("[%s][%d] append_node failed\n",__func__, __LINE__);
		return 0;
	}
	v4node4 = (ipv4_node *)alloc_domain_node(INET_IPV4, "200.200.200.1");
	if (append_domain_list(domain2, v4node4, INET_IPV4) < 0){
		printf("[%s][%d] append_node failed\n",__func__, __LINE__);
		return 0;
	}
	v6node3 = (ipv6_node *)alloc_domain_node(INET_IPV6, "fec0::3");
	if (append_domain_list(domain2, v6node3, INET_IPV6) < 0){
		printf("[%s][%d] append_node failed\n",__func__, __LINE__);
		return 0;
	}
	v6node4 = (ipv6_node *)alloc_domain_node(INET_IPV6, "fec0::4");
	if (append_domain_list(domain2, v6node4, INET_IPV6) < 0){
		printf("[%s][%d] append_node failed\n",__func__, __LINE__);
		return 0;
	}

	(void)print_list(list);
	(void)free_list(&list);
	(void)print_list(list);

	return 0;
}
