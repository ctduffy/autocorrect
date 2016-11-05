#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#include "linked.h"

/////run with:   gcc -g -std=c99 linked.c trie.c autocorrect.c -o rt


int trie_search(linked_t list, trie_t trie, char* word);

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
	    if(get_letter(get_next_trie(now, i)) != NULL){
			trie_search(list, trie, nex);
	    }
	}
}

int trie_search(linked_t list, trie_t trie, char* word){
	trie_t now = trie;
	char* nowword = word;

	int size = strlen(word);
	char* nowword = (char *)malloc(sizeof(char)*size);
	int i;
	for(i=0; i<size; i++){
		*(nowword+i) = word[i];
	}
	nowword[size] = '\0';

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
		printf("%s\n", word);
		char* thisone = word;
		//if you uncomment this line you have to fix linked list so it doesnt only pass by reference. 
		//What happens is: it puts the pointer to the word in the list, then later changes what is in that pointer, screwing everything up
		linked_add(list, get_trie_frequency(now), thisone);
	}
	wordmaker(word, now, trie, list); ///CURRENT PROBLEM: WHEN it returns the list, and continues the thread of searching for more words (to eventually find aardwolf), it forgets this list, and starts another one over. \/(^^)\/
	return 0;
}

int autocomplete(linked_t list, trie_t trie, char* curr, data_t data){
	//printf("DID IT MAKE IT HERE\n");
	//printf("curr is %c\n", curr[0]);
	if(curr == NULL){
		//printf("curr is null?\n");

	}
	else if(curr[1] == NULL){
		//printf("next letter is null\n");
		if(get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)) != 0 && get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)) != NULL){
			//printf("this freq is greater than 0\n");
			printf("%c", curr[0]);
			return linked_add(list, get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)), data->word);
		}

		return trie_search(list, data->start, data->word);
	}
	else{
		if(trie!=NULL){
			//printf("trie isnt null\n");
			if(get_letter(trie) == NULL){
				//printf("first letter\n");
				return autocomplete(list, get_next_trie(trie, (int) curr[0] - 97), &curr[0], data);
			}
			else{
				//printf("all others\n");
				return autocomplete(list, get_next_trie(trie, (int) curr[1] - 97), &curr[1], data);
			}
		}
		else{
			//printf("trie is null?\n");
		}
	}
	return 0;
}
/*
suggest(){
	startingMatrix = 
}

linked_t autocorrect(linked_t toSearch, trie_t suggestions, char* toCorrect, int maxEdit){

}
*/
int trie_starter(trie_t trie, char* filepath){

	FILE* fp;
	char line[100];

	fp = fopen(filepath, "r");

	while(fgets(line, sizeof(line), fp) != NULL){ //takes in file line by line, loading word into variable line, until it reaches a new line
		//int c =(&line - strtok(line, "\r"));
		//strtok(line, "\n"); //removes \n from the end of the string that is taken in by fgets
		char* this = malloc(100 * sizeof(char));
		int i = 0;
		while(line[i] != '\n' && line[i] != '\r'){
			this[i] = line[i];
			i++;
		}
		this[i]='\0';

		//printf("str: %s\n", this);

		trie_insert(trie, this);
	}
	fclose(fp);
	return 0;
}

int main(){
//int main(int argc, char** argv){ //To have this function take command line arguments: do: int main(int argc, char** argv) 
//	printf("file given: %s\n", argv[1]); //argv[0] is the name of the program, argv[1] is the first argument that you give it (everything is divided by spaces as well)
//	printf("word given: %s\n", argv[2]);
//	printf("num of args given: %i\n", argc);
	
	linked_t linked = linked_create();
	trie_t trie = trie_init();
	int j = trie_starter(trie, "wordssecond.txt");
	//printf("successful trie start? 0 if success %d\n", j);

	char wo[2];

	strcpy(wo, "ab");

	data_t data = malloc(sizeof(struct curr_data));
	data->word = wo;
	data->start = trie;

	autocomplete(linked, trie, wo, data);

	linked_print(linked);

	
	free(data);
	int a = linked_destroy(linked);
	int b = trie_destroy(trie);
	
}


/*
int main(){

	char* first = "word";
	char* second = "set";
	char* third = "setting";

	linked_t linked = linked_create();

	linked_add(linked, 1, first);
	linked_add(linked, 1, second);
	linked_add(linked, 3, third);
	linked_add(linked, 2, first);
	linked_add(linked, 5, first);
	linked_add(linked, 1, first);
	
	linked_print(linked);

	linked_destroy(linked);
	
	return 0;
}*/
