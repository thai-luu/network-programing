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
/*void readFile(FILE *p, node **root)
{
    (*root) = freeList(*root);
    accounttype user;
    while (fscanf(p, "%s%s%d%s", user.userName, user.passWord, &(user.status), user.homePage) != EOF)
    {
        insertAtEnd(root, user);
    }
}
node *checkUser(node *root, accounttype e)
{
    node *temp = root;
    while (temp != NULL)
    {

        if (strcmp(temp->acc.userName, e.userName) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
*/
void save(FILE *p, accounttype e)
{
    fprintf(p, "%s %s %d %s\n", e.userName, e.passWord, e.status, e.homePage);
}
node *checkAccount(node *root, accounttype e)
{
    node *temp = root;
    while (temp != NULL)
    {
        if (strcmp(temp->acc.userName, e.userName) == 0)
        {
            if (strcmp(temp->acc.passWord, e.passWord) == 0)
                return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
node *checkPassword(node *root, accounttype e)
{
    node *temp = root;
    while (temp != NULL)
    {

        if (strcmp(temp->acc.passWord, e.passWord) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

/*void writeFile(FILE *p, node *root)
{
    node *temp = root;
    while (temp != NULL)
    {
        fprintf(p, "%s %s %d %s\n", temp->acc.userName, temp->acc.passWord, temp->acc.status, temp->acc.homePage);
        temp = temp->next;
    }
}
*/
