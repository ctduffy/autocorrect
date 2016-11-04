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

int linked_add(linked_t list, int freq, char* word){
	if(list->word == NULL && list->frequency == -1 && list->next == NULL){
		linked_t now = malloc(sizeof(struct linked_node));
		now->frequency = freq;
		now->word = word;
		list->next = now;
		return 0;
	}
	else{
		linked_t now = malloc(sizeof(struct linked_node));
		now->word = word;
		now->frequency = freq;

		int next = list->next->frequency;
		linked_t this = list->next;

		while(!(next <= frequency)){
			if(this->next != NULL){
				this = this->next;
			}
			else{
				now->next = NULL;
				this->next = now;
				return 0;
			}
		}
		now->next = list->next;
		list->next = now;
		return 0;

		/*
		if(list->next->frequency <= freq){
			linked_t now = malloc(sizeof(struct linked_node));
			now->word = word;
			now->frequency = freq;
			now->next = list->next;
			list->next = now;
			return 0;
		}
		else{
			linked_t this = list->next;
			while(this->frequency > freq){
				if(this->next != NULL){
					this = this->next;
				}
				else{
					linked_t new = malloc(sizeof(struct linked_node));
					new->word = word;
					new->frequency = freq;
					new->next = NULL;
					this->next = new;
					return 0;
				}
			}

		}
		*/
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