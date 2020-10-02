#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
typedef struct
{
	char user_name[20];
	char password[20];
	int status;
	int login;
} elementtype;

typedef elementtype elementtype;

typedef struct node
{
	elementtype element;
	struct node *next;
} node;

typedef node node;

node *makeNewNode(elementtype e);

void insertAtHead(node **root, elementtype e);

void insertAtEnd(node **root, elementtype e);

void insertBeforeCurrent(node **root, node **cur, elementtype e);

void insertAfterCurrent(node **root, node **cur, elementtype e);

void insertAtPosition(node **root, elementtype e, int n);

void deleteFirst(node **root);

void deleteCurrent(node **root, node *cur);

void deleteAtPosition(node **root, int n);

node *freeList(node *root);

node *reverseList(node *root);