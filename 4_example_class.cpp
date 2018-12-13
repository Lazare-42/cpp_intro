# include <stdio.h>

// linked list is already found in the C++ standard library
# include <list>

int main(void)
{
	std::list<int> my_list;
	
	my_list.push_back( 1);
	my_list.push_back( 5);
	my_list.push_front( 8);
	my_list.push_back( 3);

	for (auto i = my_list.begin(); i != my_list.end(); i = i->advance())
		printf("%d\n", i->value);

	std::list<const char *> my_list2;
	
	my_list2.push_back("Europe");
	my_list2.push_back("Asia");
	my_list2.push_front("Africa");
	my_list2.push_back("Oceania");

	for (auto i = my_list2.begin(); i != my_list2.end(); i = i->advance())
		printf("%s\n", i->value);
	return 0;
}

