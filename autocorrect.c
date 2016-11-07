#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"
#include "linked.h"
#include "leven.h"

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
	for(i = 0; i<26; i++){//for each letter
		char n = ((char) i + 97); //make a new letter from a to z

		int len = strlen(word); //get length of current word

	    char nex[len+1]; //make a new char with one more than the length of the current word
	    int j;
	    for(j = 0; j<len; j++){
	    	nex[j] = word[j]; //copy the current word into nex
	    } 
	    nex[len] = n; //add the new letter onto nex
	    nex[len+1] = '\0'; //then add a end of string character onto it
	    if(get_letter(get_next_trie(now, i)) != NULL){ //then if the letter of the next trie of the letter just added isnt null
			//printf("adding this letter, supposedly works: %c\n", get_letter(get_next_trie(now, i)));
			trie_search(list, trie, nex); //search for it with trie search
	    }
	}
}

int trie_search(linked_t list, trie_t trie, char* word){
	trie_t now = trie; //now is another trie which i can loop through

	int size = strlen(word); //size of given word
	char* nowword = (char *)malloc(sizeof(char)*size); //nowword is a new word that i will use
	int i; 
	for(i=0; i<size; i++){ //going through every letter in word and copying nowword to it (maybe this would have worked with strcpy??)
		*(nowword+i) = word[i];
	}
	nowword[size] = '\0';//set end of string to null terminator

	while(nowword[0]!= NULL){ //while the given word isnt zero, continue down the trie
		if(get_letter(now) == NULL){ //if the current letter in the trie is null
			now = get_next_trie(now, (int) nowword[0] - 97); //move down the trie one letter, to the first letter of nowword
		}
		else if(nowword[1] == NULL){
			nowword = &nowword[1];
		}
		else if(get_letter(get_next_trie(now, (int) nowword[1] - 97)) != NULL){ //else if the trie node at the next letter in nowword isnt null
			now = get_next_trie(now, (int) nowword[1] - 97); //move down the trie to that
			nowword = &nowword[1];//and set nowword to the next letter in nowword
		}
		else{
			nowword = &nowword[1];
		}
	}
	if(get_trie_frequency(now) > 0){
		//printf("%s\n", word);
		char* thisone = word;
		linked_add(list, get_trie_frequency(now), thisone);
	}
	wordmaker(word, now, trie, list);
	/*
	if(get_trie_frequency(now) != NULL){
		wordmaker(word, now, trie, list); 
	}
	else{
		wordmaker(word, now, trie, list); 
	}*/
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
			//printf("%c", curr[0]);
			linked_add(list, get_trie_frequency(get_next_trie(trie, (int) curr[0] - 97)), data->word);
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
easier way:

get every word in the trie that has length +- maxEdit
put each word into the linked with its frequency if its edit distance is less than or equal to maxEdit


how to improve this: make it trim branches if they are impossible: check if the first x number of letters are within a certain edit distance of the first x letters, and clear the branch if it isnt


bug with this: if I type in a

*/

int finder(linked_t linked, trie_t trie, int maxEdit, char* wording, char* check){
	if(wording != '\0'){
		int worlen = strlen(wording);
		int i;
		if(get_trie_frequency(trie) > 0){
			int alen = strlen(check);
			if(DL(check, wording, alen, worlen) <= maxEdit){
				linked_add(linked, get_trie_frequency(trie), wording);
			}
		}

		for(i = 0; i<26; i++){
			char next = get_letter(get_next_trie(trie, i));
			trie_t yo = get_next_trie(trie, i);
			if(next != NULL){
				char new[worlen + 1];
				int j;
				for(j=0;j<worlen;j++){
					*(new+j) = wording[j];
				}

				*(new+worlen) = next;
				new[worlen + 1] = '\0';

				finder(linked, yo, maxEdit, new, check);
			}
		}
		return 0;
	}
	else{
		int i;
		if(get_trie_frequency(trie) > 0){
			int alen = strlen(check);
			if(DL(check, wording, alen, 0) <= maxEdit){
				linked_add(linked, get_trie_frequency(trie), wording);
			}
		}
		for(i = 0; i<26; i++){
			char next = get_letter(get_next_trie(trie, i));
			trie_t yo = get_next_trie(trie, i);
			if(next != NULL){
				char* nchar = malloc(sizeof(char));
				*nchar = next;
				*(nchar+1) = '\0';		
				finder(linked, yo, maxEdit, nchar, check);
			}
		}
		
		return 0;
	}
}


int DLcorrect(linked_t linked, trie_t trie, char* word, int maxEdit){
	char* thi = '\0';
	finder(linked, trie, maxEdit, thi, word);
	return 0;
}


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
		free(this);
	}
	fclose(fp);
	return 0;
}

//int main(){
int main(int argc, char** argv){ //To have this function take command line arguments: do: int main(int argc, char** argv) 
	printf("file given: %s\n", argv[1]); //argv[0] is the name of the program, argv[1] is the first argument that you give it (everything is divided by spaces as well)
	printf("word given: %s\n", argv[2]);
	printf("num of args given: %i\n", argc);
	if(argc < 3){
		printf("didnt give enough arguments. please try again.\n");
		return -1;
	}
	
	linked_t linked = linked_create();
	trie_t trie = trie_init();
	int j = trie_starter(trie, argv[1]);
	if(j!=0){
		printf("something is wrong with the given file\n");
		return -1;
	}

	//printf("successful trie start? 0 if success %d\n", j);



	int leng = strlen(argv[2]);

	char wo[leng];

	strcpy(wo, argv[2]);

	data_t data = malloc(sizeof(struct curr_data));
	data->word = wo;
	data->start = trie;

	//autocomplete(linked, trie, wo, data);

	int maxEdit = 1;
	DLcorrect(linked, trie, wo, maxEdit);
	//autocorrect(linked, trie, wo, maxEdit);

	linked_print(linked);

	
	free(data);
	int a = linked_destroy(linked);
	int b = trie_destroy(trie);
	return 0;
	
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
