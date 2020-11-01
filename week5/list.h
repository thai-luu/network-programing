#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
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

//*void readFile(FILE *p, node **root);
//node *checkUser(node *root, accounttype e);
void save(FILE *p, accounttype e);
node *checkAccount(node *root, accounttype e);
node *checkPassword(node *root, accounttype e);
//void writeFile(FILE *p, node *root);