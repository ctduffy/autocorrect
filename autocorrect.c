#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"
#include "linked.h"


/////run with:   gcc -g -std=c99 linked.c trie.c autocorrect.c -o rt




typedef struct curr_data* data_t;

struct curr_data{
	char* word;
	trie_t start;
};



linked_t trie_search(linked_t list, trie_t trie, char* word){
	trie_t now = trie;
	char* nowword = word;
	while(nowword[0]!= NULL){
		now = get_next_trie(now, (int) nowword[0] - 97);
		nowword = &nowword[1];
	}
	if(get_trie_frequency(now) > 0){
		return linked_add(list, get_trie_frequency(now), word);
	}
	int i;
	//int len = (int) strlen(word);
	//char* newword = word;
	for(i = 0; i<26; i++){
		char th[2] = {((char) i + 97), 'A'};
		char* newword = strncat(word, &th, 1);
		return trie_search(list, trie, newword);
	}

	/*
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
			newword[len + 1] = '\0';
			return trie_search(list, trie, newword);
		}
		if(get_trie_frequency(trie) > 0){
			return linked_add(list, get_trie_frequency(trie), word);
		}
	}
	*/
}

linked_t autocomplete(linked_t list, trie_t trie, char* curr, data_t data){
	printf("DID IT MAKE IT HERE\n");
	printf("curr is %c\n", curr[0]);
	if(curr == NULL){

	}
	else if(curr[1] == NULL){
		if(get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)) != 0 && get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)) != NULL){
			return linked_add(list, get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)), data->word);
		}
		return trie_search(list, data->start, data->word);
	}
	else{
		if(trie!=NULL){
			return autocomplete(list, get_next_trie(trie, (int) curr[0] - 97), &curr[1], data);
		}
	}
}

linked_t autocorrect(linked_t list, trie_t trie, char* curr, int maxld){

}

int trie_starter(trie_t trie, char* filepath){

	FILE* fp;
	char line[255];

	fp = fopen(filepath, "r");

	while(fgets(line, sizeof(line), fp) != NULL){ //takes in file line by line, loading word into variable line, until it reaches a new line
		strtok(line, "\n"); //removes \n from the end of the string that is taken in by fgets
		
		//below function removes everything from string except letters. Source: http://www.programiz.com/c-programming/examples/remove-characters-string
		int i;
		int j;
		for(i=0; line[i]!='\0'; ++i)
	    {
	        while (!((line[i]>='a'&&line[i]<='z') || line[i]=='\0'))
	        {
	            for(j=i;line[j]!='\0';++j)
	            {
	                line[j]=line[j+1];
	            }
	            line[j]='\0';
	        }
	    }

		//printf("%s\n", line);
		trie_insert(trie, line);
	}
	fclose(fp);
	return 0;
}

int main(){
	linked_t linked = linked_create();
	trie_t trie = trie_init();
	int j = trie_starter(trie, "wordsfirst.txt");
	printf("%d\n", j);

	data_t data = malloc(sizeof(struct curr_data));
	data->word = "aardwo";
	data->start = trie;

	printf("here?\n");

	linked_t result = autocomplete(linked, trie, "aardwo", data);



	free(data);
	int a = linked_destroy(linked);
	int b = trie_destroy(trie);

	return 0;
}

