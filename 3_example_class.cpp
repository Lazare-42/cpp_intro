# include <stdio.h>
# include <stdlib.h>


// structs are now proper types ; a type struct statement is no
// longer needed

// constructor and destructor special methods
// creator and destructor methods are automatically called
// new and delete keywords in C++ do the mallocing and the de-allocating

struct list
{
	struct node {
		node *prev, *next;
		int value;
		node(int v) {value = v; }
		node *advance() {return next;}
	};

	node *first, *last;

	node *begin() { return first; }
	node *end() { return NULL; }

	list() {first = NULL; last = NULL; }
	~list() { clear(); }
	void insert(node *where, int v)
	{
		node *newnode = new node(v);
		newnode->prev = where ? where->prev : last;
		newnode->next = where;
		if (newnode->prev) newnode->prev->next = newnode;
		if (where) where->prev = newnode;
		if (where == first) first = newnode;
		if (!where) last = newnode;
	}
	void push_front(int v) { insert(begin(), v); }
	void push_back(int v) { insert(end(), v); }
	void erase(node *where)
	{
		node *prev = where->prev;
		node *next = where->next;
		if (prev) prev->next = next;
		if (next) next->prev = prev;
		if (where == first) first = next;
		if (where == last) last = prev;
		delete (where);
	}
	void clear() { while(first) erase(first); }
};




int main(void)
{
	struct list my_list;
	
	//	my_list.init(); -- no longer necessary. list::list() is automatically called
	my_list.push_back( 1);
	my_list.push_back( 5);
	my_list.push_front( 8);
	my_list.push_back( 3);

	for (list::node *i = my_list.begin(); i != my_list.end(); i = i->advance())
		printf("%d\n", i->value);

	// my_list.done(); -- no longer necessary. list::~list() is automatically called
	// There is no memory leak here.
	
	return 0;
}

