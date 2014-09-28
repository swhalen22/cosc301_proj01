#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* your list function definitions */
void list_insert(int val, struct node** head) {
	 
    struct node* tmp = (struct node*) malloc(sizeof(struct node));
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->val = val;
    new_node->next = NULL;
	
		
    if (*head == NULL) { //first number added to linked list
	*head = new_node;
	return;
    }
		

    if (new_node->val <= (*head)->val) {
	new_node->next = *head;
	*head = new_node;
	return;
    }

    tmp = *head;	
    while (tmp->next && new_node->val > tmp->next->val) {
	tmp = tmp->next;
    }
		
    if (tmp->next == NULL) tmp->next = new_node;
    else {
	new_node->next = tmp->next;
	tmp->next = new_node;
    }
		
}
	 
void list_print(struct node *head) {
    //Based off of hw03
    while (head != NULL){
	printf("%i\n",head->val);
	head = head->next;
    }
}
	 
void list_clear(struct node *list) {
    //Taken from hw03
    while (list != NULL) {
	struct node *tmp = list;
	list = list->next;
	free(tmp);
    }
}


