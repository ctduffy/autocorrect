#ifndef _TRIE_LIST_T
#define _TRIE_LIST_T

typedef struct trie_node* trie_t; 


struct trie_node{
	char letter;
	int frequency;
	trie_t nextArr[26]; 
};
trie_t trie_init();
int trie_destroy(trie_t trie);

int trie_insert(trie_t trie, char* word);
int trie_contains(trie_t trie, char* word);

#endif