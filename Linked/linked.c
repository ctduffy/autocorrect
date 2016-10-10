#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct linked_node{
	char* word;
	int frequency;
	linked_t next;
};

linked_t linked_create(){
	linked_t newlinked = malloc(sizeof(struct linked_node));
	newlinked->word = NULL;
	newlinked->frequency = NULL;
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
	if(list->word == NULL){
		list->frequency = freq;
		list->word = word;
		return list;
	}
	else{
		linked_t this = list;
		int cont = 1;
		while(this->frequency > freq){
			if(this->next != NULL){
				this = this->next;
				cont = 1;
			}
			else{
				cont = 0;
				linked_t new = malloc(sizeof(stuct linked_node));
				new->word = word;
				new->frequency = freq;
				new->next = NULL;
				this->next = new;
			}
		}
		if(cont = 1){
			linked_t now = malloc(sizeof(struct linked_node));
			now->word = word;
			now->frequency = freq;
			now->next = this;
		}
		return this;
	}
}

int main(){
	linked_t testcase = linked_create();
	testcase = linked_add(testcase, 1, "one");

	printf("this word is: %s, its freq is: %d\n", testcase->word, testcase->frequency);

	int hello = linked_destroy(testcase);
	return 0;
}