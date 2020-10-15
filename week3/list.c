#include "list.h"
void insertAtEnd(node **root, accounttype e){
	node *NewNode = (node *) malloc(sizeof(node));
	NewNode->acc = e;
	if(*root == NULL){
		*root = NewNode;
		return;
	}
	node *current = *root;
	while(current->next != NULL){
		current = current->next;
	}
	current->next = NewNode;
}
node *freeList(node *root){		//free list, can return root de truyen gia tri ra khoi function
	node *to_free;
	to_free = root;
	while(to_free != NULL){
		root = root->next;
		free(to_free);
		to_free = root;
	}
	return root;
}

