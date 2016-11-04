#ifndef __LINKED_LIST_T__
#define __LINKED_LIST_T__

typedef struct linked_node* linked_t;//an opaque pointer--used for safety--internal structure does not matter for people that use it

linked_t get_next(linked_t this);
char* get_word(linked_t this);
int get_frequency(linked_t this);

linked_t linked_create();
int linked_destroy(linked_t curr);

int linked_add(linked_t list, int freq, char* word);

void linked_print(linked_t list);

#endif // __LINKED_LIST_T__