#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"

struct trie_node{
	char letter;
	int frequency;
	trie_t nextArr[26]; 
};

trie_t trie_init() { //takes in nothing, allocates memory for empty trie with letter = NULL and empty tries for the nextArr list
	trie_t thistrie = malloc(sizeof(struct trie_node));
	int i;
	thistrie->letter = NULL;

	thistrie->frequency = 0;
	for(i = 0; i<26; i++){
		thistrie->nextArr[i] = NULL;
	}
	return thistrie;
}

int trie_destroy(trie_t trie){ //tail recursion destroy function: first finds all parts of the tree and then starts from the bottom up to destory them
	int i;
	if(trie->nextArr[0] != NULL){
		for(i=0; i<26; i++){
			trie_destroy(trie->nextArr[i]);
		}
	}
	free(trie);
	return 1;
}

trie_t trie_next(int numb) {//takes in letter, allocates memory for trie with letter = letter taken in and empty tries for the nextArr list
	trie_t thistrie = malloc(sizeof(struct trie_node));

	char letter = (char) numb + 97;

	thistrie->letter = letter;
	thistrie->frequency = 0;
	int i;
	for(i = 0; i<26; i++){
		thistrie->nextArr[i] = NULL;
	}
	return thistrie;
}

int trie_insert(trie_t trie, char* word){ //recursively inserts a word and a when it reaches the end of the word, adds one to the frequency to the word that is there. If a branch doesnt already exist, it will create new branches as needed
	int i;
	//printf("word now: %s\n", word);
	if(trie == NULL){
		return -1;
	}
	else if(trie->letter == NULL){
		for(i = 0; i<26; i++){
			if(trie->nextArr[i] == NULL){
				trie->nextArr[i] = trie_next(i);
			}
		}
		int curr = word[0] - 97; 
		char* left = &word[0];
		trie_insert(trie->nextArr[curr], left);
	}
	else if(strlen(word) == 1){
		trie->frequency += 1; 
	}
	else if((trie->letter == NULL) && (trie->frequency == 0)){
		for(i = 0; i<26; i++){
			if(trie->nextArr[i] == NULL){
				trie->nextArr[i] = trie_next(i);
			}
		}
		int curr = word[0] - 97; 
		char* left = &word[0];
		trie_insert(trie->nextArr[curr], left);
	}
	else{
		for(i = 0; i<26; i++){
			if(trie->nextArr[i] == NULL){
				trie->nextArr[i] = trie_next(i);
			}
		}
		int curr = word[1] - 97; 
		char* left = &word[1];
		trie_insert(trie->nextArr[curr], left);
	}
	return 1;
}

int trie_contains(trie_t trie, char* word){ //checks if given trie contains given word, checks with recursion
	if(trie == NULL){
		return 0;
	}
	else if(trie->letter == NULL){
		if(trie->frequency == 0){
			int i;
			for(i=0; i<26; i++){
				if(trie->nextArr[i] != NULL){
					if(trie->nextArr[i]->letter == word[0]){
						return trie_contains(trie->nextArr[i], &word[0]);
					}
				}
			}
		}
		else{
			return 0;
		}
	}
	else if((trie->frequency > 0) && ((int)strlen(word) == 1)){
		//printf("found the word!!! (And its frequency is: %d)\n", trie->frequency);
		int freq = trie->frequency;
		return freq;
	}
	else{
		int i;
		//printf("on: %c\n", trie->letter);
		if(trie->letter == word[0]){
			for(i=0; i<26; i++){
				if(trie->nextArr[i] != NULL){
					if(trie->nextArr[i]->letter == word[1]){
						return trie_contains(trie->nextArr[i], &word[1]);
					}
				}
			}
		}
	}
}

int main(){

	trie_t myfirst = trie_init();

	FILE* fp;
	char line[255];



	fp = fopen("wordsfirst.txt", "r");

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
		trie_insert(myfirst, line);
	}

	int oh = trie_contains(myfirst, "abasement");

	printf("success??:%d\n", oh);

	trie_destroy(myfirst);
	fclose(fp);

	malloc(sizeof(struct trie_node));

	return 0;

}

