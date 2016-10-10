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
		int len = strlen(word);
		char* newword = word;
		for(i = 0; i < 26; i++){
			newword[len] = (char) i + 97;
			newword[len + 1] = "\0";
			return trie_search(list, trie, newword);
		}
		if(trie->frequency > 0){
			return linked_add(list, trie->frequency, word);
		}
	}
}

linked_t autocomplete(linked_t list, trie_t trie, char* curr, data_t data){
	if(curr[1]==NULL){
		if(trie->nextArr[(int) curr[0] - 97]->frequency != 0 && trie->nextArr[(int) curr[0] - 97]->frequency != NULL){
			return linked_add(list, trie->nextArr[(int) curr[0] - 97]->frequency, data->word);
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

	linked_t linked = linked_create();
	trie_t trie = trie_init();

	char* wor = "aardwo";

	data_t data = malloc(sizeof(struct curr_data));
	data->word = wor;
	data->start = trie;

	linked_t result = autocomplete(linked, trie, wor, data);



	free(data);
	int a = linked_destroy(linked);
	int b = trie_destroy(trie);

}