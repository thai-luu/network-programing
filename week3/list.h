#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
typedef struct
{
	char userName[20];
	char passWord[20];
	int status;
	char homePage[20];
} accounttype;

typedef accounttype accounttype;

typedef struct node
{
	accounttype acc;
	struct node *next;
} node;

typedef node node;

void insertAtEnd(node **root, accounttype e);

node *freeList(node *root);

