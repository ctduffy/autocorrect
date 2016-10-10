#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"
#include "linked.h"

typedef struct curr_data* data_t;

struct curr_data{
	char* word;
	trie_t start;
};

linked_t trie_search(linked_t list, trie_t trie, char* word){
	if(trie!=NULL){
		char* wordnext = word;
		while(wordnext[0] != NULL){
			trie = get_next_trie(trie, (int) word[0] - 97);
		}
		int i;
		int len = strlen(word);
		char* newword = word;
		for(i = 0; i < 26; i++){
			newword[len] = (char) i + 97;
			newword[len + 1] = "\0";
			return trie_search(list, trie, newword);
		}
		if(get_trie_frequency(trie) > 0){
			return linked_add(list, get_trie_frequency(trie), word);
		}
	}
}

linked_t autocomplete(linked_t list, trie_t trie, char* curr, data_t data){
	printf("DID IT MAKE IT HERE");
	if((int)strlen(curr) = 1){
		if(get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)) != 0 && get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)) != NULL){
			return linked_add(list, get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)), data->word);
		}
		return trie_search(list, trie, data->word);
	}
	else{
		if(trie!=NULL){
			return autocomplete(list, trie, curr[1], data);
		}
	}
}

linked_t autocorrect(linked_t list, trie_t trie, char* curr, int maxld){

}

int main(){

	printf("1here?");

	linked_t linked = linked_create();
	trie_t trie = trie_init();

	data_t data = malloc(sizeof(struct curr_data));
	data->word = "aardwo";
	data->start = trie;

	printf("here?");

	linked_t result = autocomplete(linked, trie, wor, data);



	free(data);
	int a = linked_destroy(linked);
	int b = trie_destroy(trie);

	return 0;

}