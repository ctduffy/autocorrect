#ifndef _AUTO_CORRECT_
#define _AUTO_CORRECT_

typedef struct curr_data* data_t;

struct trie_node{
	char letter;
	int frequency;
	trie_t nextArr[26];
};

linked_t autocomplete(linked_t list, trie_t trie, char* curr, data_t data);

linked_t autocorrect(linked_t list, trie_t trie, char* curr, int maxld);

#endif

