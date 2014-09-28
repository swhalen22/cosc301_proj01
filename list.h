#ifndef __LIST_H__
#define __LIST_H__


/* List data structure declaration */

struct node {
	int val;
	struct node *next;
};
 
/* Function declarations associated with list */
 
void list_insert(const int i, struct node **head);
 
void list_print(struct node *head);
 
void list_clear(struct node *list);


#endif // __LIST_H__
