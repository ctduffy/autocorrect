#ifndef _TRIE_LIST_T
#define _TRIE_LIST_T

typedef struct trie_node* trie_t; 

char get_letter(trie_t this){;
int get_trie_frequency(trie_t this);
trie_t get_next_trie(trie_t this, int place);

trie_t trie_init();
int trie_destroy(trie_t trie);

int trie_insert(trie_t trie, char* word);
int trie_contains(trie_t trie, char* word);

#endif