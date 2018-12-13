# include <stdio.h>
# include <stdlib.h>


// structs can also be nested for simplification

struct list
{
	struct node {
		struct node *prev, *next;
		int value;
		void init(int v) {value = v; }
		struct node *advance() {return next;}
	};

	struct node *first, *last;
	struct node *begin() { return first; }
	struct node *end() { return NULL; }
	void init() {first = NULL; last = NULL; }
	void insert(struct node *where, int v)
	{
		struct node *newnode = (struct node*)malloc(sizeof(*newnode));
		newnode->init(v);
		newnode->prev = where ? where->prev : last;
		newnode->next = where;
		if (newnode->prev) newnode->prev->next = newnode;
		if (where) where->prev = newnode;
		if (where == first) first = newnode;
		if (!where) last = newnode;
	}
	void push_front(int v) { insert(begin(), v); }
	void push_back(int v) { insert(end(), v); }
	void erase(struct node *where)
	{
		struct node *prev = where->prev;
		struct node *next = where->next;
		if (prev) prev->next = next;
		if (next) next->prev = prev;
		if (where == first) first = next;
		if (where == last) last = prev;
		free (where);
	}
	void clear() { while(first) erase(first); }
	void done() { clear(); }
};




int main(void)
{
	struct list my_list;
	
	my_list.init();
	my_list.push_back( 1);
	my_list.push_back( 5);
	my_list.push_front( 8);
	my_list.push_back( 3);

	for (list::node *i = my_list.begin(); i != my_list.end(); i = i->advance())
		printf("%d\n", i->value);
	my_list.done();
	
	return 0;
}

