# include <stdio.h>
# include <stdlib.h>

struct list_node
{
	struct list_node *prev, *next;
	int value;
};

struct list
{
	struct list_node *first, *last;
};

void list_node_init(struct list_node *n, int v) { n->value = v; }
struct list_node *list_advance(struct list_node *i) {return i->next;}
struct list_node *list_begin(struct list *i) { return i->first; }
struct list_node *list_end(struct list *i) {(void)i ; return NULL; }

void list_init(struct list *i) {i->first = NULL; i->last = NULL; }

void list_insert(struct list *i, struct list_node *where, int v)
{
	struct list_node *newnode = (struct list_node*)malloc(sizeof(*newnode));
	list_node_init(newnode, v);
	newnode->prev = where ? where->prev : i->last;
	newnode->next = where;
	if (newnode->prev) newnode->prev->next = newnode;
	if (where) where->prev = newnode;
	if (where == i->first) i->first = newnode;
	if (!where) i->last = newnode;
}

void list_push_front(struct list *i, int v) {list_insert(i, list_begin(i), v); }
void list_push_back(struct list *i, int v) { list_insert(i, list_end(i), v); }
void list_erase(struct list *i, struct list_node *where)
{
	struct list_node *prev = where->prev;
	struct list_node *next = where->next;
	if (prev) prev->next = next;
	if (next) next->prev = prev;
	if (where == i->first) i->first = next;
	if (where == i->last) i->last = prev;
	free (where);
}

void list_clear(struct list *i) { while(i->first) list_erase(i, i->first); }
void list_done(struct list *i) { list_clear(i); }

int main(void)
{
	struct list my_list;
	struct list_node *i;

	list_init(&my_list);
	list_push_back(&my_list, 1);
	list_push_back(&my_list, 5);
	list_push_front(&my_list, 8);
	list_push_back(&my_list, 3);

	for (i = list_begin(&my_list); i != list_end(&my_list); i = list_advance(i))
		printf("%d\n", i->value);
	list_done(&my_list);
	
	return 0;
}

