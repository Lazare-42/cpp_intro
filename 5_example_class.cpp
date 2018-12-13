# include <stdio.h>
# include <stdlib.h>

// What if we need another data types than integers ?

template<typename T>
struct list
{
	struct node {
		node *prev, *next;
		T value;
		node(T v) {value = v; }
		node *advance() {return next;}
	};

	node *first, *last;

	node *begin() { return first; }
	node *end() { return NULL; }

	list() {first = NULL; last = NULL; }
	~list() { clear(); }
	void insert(node *where, T v)
	{
		node *newnode = new node(v);
		newnode->prev = where ? where->prev : last;
		newnode->next = where;
		if (newnode->prev) newnode->prev->next = newnode;
		if (where) where->prev = newnode;
		if (where == first) first = newnode;
		if (!where) last = newnode;
	}
	void push_front(T v) { insert(begin(), v); }
	void push_back(T v) { insert(end(), v); }
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
	list<int> my_list;
	
	my_list.push_back( 1);
	my_list.push_back( 5);
	my_list.push_front( 8);
	my_list.push_back( 3);

	for (auto i = my_list.begin(); i != my_list.end(); i = i->advance())
		printf("%d\n", i->value);

	list<const char *> my_list2;
	
	my_list2.push_back("Europe");
	my_list2.push_back("Asia");
	my_list2.push_front("Africa");
	my_list2.push_back("Oceania");

	for (auto i = my_list2.begin(); i != my_list2.end(); i = i->advance())
		printf("%s\n", i->value);
	
	return 0;
}

