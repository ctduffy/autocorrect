#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include "linked.h"

 
struct linked_node{
	char* word;
	int frequency;
	linked_t next;
};

linked_t get_next(linked_t this){
	return this->next;
}
char* get_word(linked_t this){
	return this->word;
}
int get_frequency(linked_t this){
	return this->frequency;
}

linked_t linked_create(){
	linked_t newlinked = malloc(sizeof(struct linked_node));
	newlinked->word = NULL;
	newlinked->frequency = INT_MAX;
	newlinked->next = NULL;
	return newlinked;
}

int linked_destroy(linked_t curr){
	if(curr->next != NULL){
		linked_destroy(curr->next);
	}
	free(curr);
	return 0;
}

int linked_add(linked_t list, int freq, char* word){
	//printf("searching through list, on word: %s, or maybe this %s? \n", list->word, list->next->word);
	linked_t now = malloc(sizeof(struct linked_node));
	now->word = word;
	now->frequency = freq;
	now->next = list->next;
	list->next = now;
	/*
	

	if(list == NULL){
		return -1;
	}
	else if(list->next == NULL){//if this is the last thing in the list
		linked_t now = malloc(sizeof(struct linked_node));

		char tword[100];
		
		int i = 0;
		while(word[i] != '\0'){
			tword[i] = word[i];
			i++;
		}
		tword[i]='\0';
		now->word = tword;
		now->frequency = freq;
		list->next = now;
		now->next = NULL;
		return 0;
	}
	else if(list->frequency > freq){// if this node has a higher frequency than freq
		if(freq >= list->next->frequency){ //if the node after this one has a lower frequency than freq
			linked_t now = malloc(sizeof(struct linked_node));

			char tword[100];
			
			int i = 0;
			while(word[i] != '\0'){
				tword[i] = word[i];
				i++;
			}
			tword[i]='\0';
			now->word = tword;
			now->next = list->next;
			list->next = now;
			return 0;
		}
	}
	else{
		return linked_add(list->next, freq, word);
	}
	*/
}

void linked_print(linked_t list){
	printf("made it here\n");
	if(list != NULL){
		if(list->word != NULL){
			printf("this word is: %s, its freq is: %d\n", list->word, list->frequency);
			linked_print(list->next);
		}
		else if(list->word == NULL){
			linked_print(list->next);
		}
	}
}

/*
int main(){
	linked_t testcase = linked_create();
	testcase = linked_add(testcase, 10, "ten");
	testcase = linked_add(testcase, 2, "two");
	testcase = linked_add(testcase, 100, "one hundred");
	testcase = linked_add(testcase, 100, "one hundred");
	
	linked_print(testcase);
	
	int hello = linked_destroy(testcase);
	return 0;
}*/