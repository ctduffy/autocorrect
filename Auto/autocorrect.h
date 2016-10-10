#ifndef _AUTO_CORRECT_
#define _AUTO_CORRECT_

typedef struct curr_data* data_t;

linked_t autocomplete(linked_t list, trie_t trie, char* curr);

linked_t autocorrect(linked_t list, trie_t trie, char* curr, int maxld);

#endif

