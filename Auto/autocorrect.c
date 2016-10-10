#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../Trie/trie.h"
#include "../Linked/linked.h"
#include "autocorrect.h"

struct curr_data{
	char* word;
	trie_t start;
};

linked_t trie_search(linked_t list, trie_t trie, char* word){
	if(trie!=NULL){
		char* wordnext = word;
		while(wordnext[0] != NULL){
			trie = trie->nextArr[(int) word[0] - 97];
		}
		int i;
		for(i = 0; i < 26; i++){
			return trie_search(list, trie, strcat(word, (char) 1+97));
		}
		if(trie->freq > 0){
			return linked_add(list, trie->freq, word);
		}
	}
}

linked_t autocomplete(linked_t list, trie_t trie, char* curr, data_t data){
	if(curr[1]==NULL){
		if(trie->nextArr[(int) curr[0] - 97]->freq != 0 && trie->nextArr[(int) curr[0] - 97]->freq != NULL){
			return linked_add(list, trie->nextArr[(int) curr[0] - 97]->freq, data->word);
		}
		return trie_search(list, trie, data->word);
	}
	else{
		if(trie!=NULL){
			return autocomplete(list, trie, curr[1], data->word);
		}
	}
}

linked_t autocorrect(linked_t list, trie_t trie, char* curr, int maxld){

}

int main(){

	linked_t linked = linked_create();
	trie_t trie = trie_init();

	data_t data = malloc(sizeof(struct curr_data));
	data->word = "aardwo";
	data->start = trie;

	linked_t result = autocomplete(linked, trie, "aardwo", data);



	free(data);
	int a = linked_destroy(linked);
	int b = trie_destroy(trie);

}