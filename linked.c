#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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
	newlinked->frequency = -1;
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

linked_t linked_add(linked_t list, int freq, char* word){
	if(list->word == NULL && list->frequency == -1 && list->next != NULL){
		list->next->frequency = freq;
		list->next->word = word;
		return list;
	}
	else{
		if(list->next->frequency == freq){
			linked_t now = malloc(sizeof(struct linked_node));
			now->word = word;
			now->frequency = freq;
			now->next = list->next;
			return now;
		}
		else{
			linked_t this = list->next;
			while(this->frequency > freq){
				if(this->next != NULL){
					this = this->next;
					//cont = 1;
				}
				else{
					//cont = 0;
					linked_t new = malloc(sizeof(struct linked_node));
					new->word = word;
					new->frequency = freq;
					new->next = NULL;
					this->next = new;
					return this;
				}
			}
		}
	}
}

void linked_print(linked_t list){
	printf("made it here\n");
	if(list != NULL){
		if(list->word != NULL){
			printf("this word is: %s, its freq is: %d\n", list->word, list->frequency);
			linked_print(list->next);
		}
		else if(list->word == NULL && list->frequency == -1 && list->next != NULL){
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