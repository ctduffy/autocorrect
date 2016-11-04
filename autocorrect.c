#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#include "linked.h"


/////run with:   gcc -g -std=c99 linked.c trie.c autocorrect.c -o rt


linked_t trie_search(linked_t list, trie_t trie, char* word);

typedef struct curr_data* data_t;

struct curr_data{
	char* word;
	trie_t start;
};

void wordmaker(char* word, trie_t now, trie_t trie, linked_t list){
	int i;
	//char* nexlist[26];
	for(i = 0; i<26; i++){
		char n = ((char) i + 97);

		int len = strlen(word);

	    char nex[len+1];
	    int j;
	    for(j = 0; j<len; j++){
	    	nex[j] = word[j];
	    } 
	    nex[len] = n;
	    nex[len+1] = '\0';
	    //nexlist[i] = nex;
	    if(get_letter(get_next_trie(now, i)) != NULL){
	    	printf("added %c\n", n);
	    	printf("This works! continuing on this path\n");
			trie_search(list, trie, nex);
	    }
	}
}

linked_t trie_search(linked_t list, trie_t trie, char* word){
	trie_t now = trie;
	char* nowword = word;
	while(nowword[0]!= NULL){
		if(get_letter(now) == NULL){
			now = get_next_trie(now, (int) nowword[0] - 97);
		}
		else if(get_letter(get_next_trie(now, (int) nowword[1] - 97)) != NULL){
			now = get_next_trie(now, (int) nowword[1] - 97);
			nowword = &nowword[1];
		}
		else{
			nowword = &nowword[1];
		}
		
	}
	if(get_trie_frequency(now) > 0){
		printf("found a word!!, adding: %s\n", word);
		list = linked_add(list, get_trie_frequency(now), word);
	}
	wordmaker(word, now, trie, list); ///CURRENT PROBLEM: WHEN it returns the list, and continues the thread of searching for more words (to eventually find aardwolf), it forgets this list, and starts another one over. \/(^^)\/
	return list;
}

linked_t autocomplete(linked_t list, trie_t trie, char* curr, data_t data){
	//printf("DID IT MAKE IT HERE\n");
	//printf("curr is %c\n", curr[0]);
	if(curr == NULL){
		printf("curr is null?\n");
	}
	else if(curr[1] == NULL){
		printf("next letter is null\n");
		if(get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)) != 0 && get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)) != NULL){
			printf("this freq is greater than 0\n");
			return linked_add(list, get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)), data->word);
		}

		return trie_search(list, data->start, data->word);
	}
	else{
		if(trie!=NULL){
			printf("trie isnt null\n");
			if(get_letter(trie) == NULL){
				printf("first letter\n");
				return autocomplete(list, get_next_trie(trie, (int) curr[0] - 97), &curr[0], data);
			}
			else{
				printf("all others\n");
				return autocomplete(list, get_next_trie(trie, (int) curr[1] - 97), &curr[1], data);
			}
		}
		else{
			printf("trie is null?\n");
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

	int cont = trie_contains(trie, "aardwolf");

	printf("putin? %d\n", cont);

	fclose(fp);
	return 0;
}

int main(){ //To have this function take command line arguments: do: int main(int argc, char** argv) 
	//printf("%s", argv[1]); //argv[0] is the name of the program, argv[1] is the first argument that you give it (everything is divided by spaces as well)
	//printf("%i", argc)
	linked_t linked = linked_create();
	trie_t trie = trie_init();
	int j = trie_starter(trie, "wordsEn.txt");
	printf("successful trie start? 0 if success %d\n", j);

	data_t data = malloc(sizeof(struct curr_data));
	data->word = "aard";
	data->start = trie;

	linked = autocomplete(linked, trie, "aardwo", data);

	linked_print(linked);

	//char* first = "wrod";
	//char* second = "set";

	//linked_t result = linked_create();

	//linked = linked_add(linked, 1, first);
	//linked = linked_add(linked, 1, second);
	//linked_print(linked);

	free(data);
	int a = linked_destroy(linked);
	int b = trie_destroy(trie);

	return 0;
}

