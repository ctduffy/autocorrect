#ifndef __LINKED_LIST_T__
#define __LINKED_LIST_T__

typedef struct linked_node* linked_t;//an opaque pointer--used for safety--internal structure does not matter for people that use it

struct linked_node{
	char* word;
	int frequency;
	linked_t next;
};

linked_t linked_create();
int linked_destroy(linked_t curr);

linked_t linked_add(linked_t list, int freq, char* word);

void linked_print(linked_t list);

#endif // __LINKED_LIST_T__