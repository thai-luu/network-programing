#include "list.h"
void readFile(FILE *p, node **root);
node *checkUser(node *root, elementtype e);
node *checkAccount(node *root, elementtype e);
void writeFile(FILE *p, node *root);
void saveToFile(FILE *p, elementtype e);
node *checkPassword(node *root, elementtype e);
int main()
{
    char userLogin[20];
    int a;
    char pass[20];
    char active[20];
    char CodeActive[] = "LTM121216";
    FILE *p;
    node *root = NULL;
    elementtype element;
    node *account = NULL;
    p = fopen("test1.txt", "r+");
    if (p == NULL)
    {
        printf("File does not exist\n");
        return 0;
    }

    readFile(p, &root);

    do
    {
        printf("1.Register\n");
        printf("2.Active\n");
        printf("3.Sign in\n4.Search\n5.Change password\n6.Sign out\nYou choice (1-6, other to quit)\n");
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            getchar();
            printf("username: ");
            scanf("%s", element.user_name);
            while (checkUser(root, element) != NULL)
            {
                printf("Account existed\n");
                printf("invite you to re-enter\nusername: ");
                scanf("%s", element.user_name);
            }
            printf("password: ");
            scanf("%s", element.password);
            element.status = 2;
            printf("Successful registration. Activation required.\n");
            insertAtEnd(&root, element);
            saveToFile(p, element);
            fclose(p);
            break;
        case 2:

            getchar();
            printf("username: ");
            scanf("%s", element.user_name);
            printf("password: ");
            scanf("%s", element.password);
            while ((account = checkAccount(root, element)) == NULL)
            {
                getchar();
                printf("The account does not exist or the password is wrong\n");
                printf("invite you to re-enter\nusername: ");
                scanf("%s", element.user_name);
                printf("password: ");
                scanf("%s", element.password);
            }
            if (account->element.status == 0)
            {
                printf("Could not activate the locked account\n");
                break;
            }
            if (account->element.status == 1)
            {
                printf("Account has been activated before\n");
                break;
            }
            printf("Active code: ");
            scanf("%s", active);

            int count = 0;
            while (strcmp(active, CodeActive) != 0)
            {
                count++;
                if (count == 3)
                {
                    printf("Activation code is incorrect.Account is blocked\n");
                    account->element.status = 0;

                    break;
                }
                printf("Account is not activated\nPlease re-enter the activation code:");
                scanf("%s", active);
            }
            if (count < 3)
            {
                printf("Account is activated\n");
                account->element.status = 1;
            }
            p = fopen("test1.txt", "w");
            writeFile(p, root);
            fclose(p);

            break;
        case 3:
            getchar();
            printf("username: ");
            scanf("%s", element.user_name);
            while (checkUser(root, element) == NULL)
            {
                printf("Cannot find account\n");
                printf("Invite you to re-enter\nusername: ");
                scanf("%s", element.user_name);
            }
            strcpy(userLogin, element.user_name);
            printf("password: ");
            scanf("%s", element.password);

            int countt = 0;
            while ((account = checkPassword(root, element)) == NULL)
            {
                countt++;
                if (countt == 3)
                {
                    printf("Password is incorrect. Account is blocked \n");
                    account->element.status = 0;

                    break;
                }
                printf("Password is incorrect \n");
                printf("invite you to re-enter\npassword: ");
                scanf("%s", element.password);
            }
            if (countt < 3)
            {

                if (account->element.status == 1)
                {
                    printf("Hello %s\n", element.user_name);
                }
                else
                    puts("Account is blocked");
            }
            p = fopen("test1.txt", "w");
            writeFile(p, root);
            fclose(p);
            break;
        case 4:
            printf("username: ");
            scanf("%s", element.user_name);
            while ((account = checkUser(root, element)) == NULL)
            {
                printf("Cannot find account \n");
                printf("invite you to re-enter\nusername: ");
                scanf("%s", element.user_name);
            }
            if (account->element.status == 0)
                printf("Account is blocked\n");
            if (account->element.status == 1)
                printf("Account is active\n");
            if (account->element.status == 2)
                printf("Account is idle\n");
            break;
        case 5:
            getchar();
            printf("username: ");
            scanf("%s", element.user_name);
            while ((account = checkUser(root, element)) == NULL)
            {
                printf("Can not find account\n");
                printf("invite you to re-enter\nusername: ");
                scanf("%s", element.user_name);
            }
            printf("password: ");
            scanf("%s", element.password);
            while ((account = checkPassword(root, element)) == NULL)
            {
                printf("Current password is incorrect. Please try again \n");
                printf("invite you to re-enter\npassword: ");
                scanf("%s",element.password);
            }
            printf("NewPassword: ");
            scanf("%s", account->element.password);
            printf("Password is change\n");
            p = fopen("test1.txt", "w");
            writeFile(p, root);
            fclose(p);
            break;
        case 6:
        getchar();
            printf("username: ");
            scanf("%s", element.user_name);
            while ((account = checkUser(root, element)) == NULL)
            {
                printf("Can not find account\n");
                printf("invite you to re-enter\nusername: ");
                scanf("%s", element.user_name);
            }
            if ((strcmp(element.user_name,userLogin)) == 0)
            {
                printf("Goodbye %s\n",element.user_name);
            }
            else
            {
                printf("Account is not sign in \n");
            }
            
            break;
        default:
            break;
        }
    } while (a == 1 || a == 2 || a == 3 || a == 4 || a == 5 || a == 6);
    fclose(p);
    return 0;
}
void readFile(FILE *p, node **root)
{
    (*root) = freeList(*root);
    elementtype element;
    element.login = 0;
    while (fscanf(p, "%s%s%d", element.user_name, element.password, &(element.status)) != EOF)
    {
        insertAtEnd(root, element);
    }
}
node *checkUser(node *root, elementtype e)
{
    node *temp = root;
    while (temp != NULL)
    {

        if (strcmp(temp->element.user_name, e.user_name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
void saveToFile(FILE *p, elementtype e)
{
    fprintf(p, "%s %s %d\n", e.user_name, e.password, e.status);
}
node *checkAccount(node *root, elementtype e)
{
    node *temp = root;
    while (temp != NULL)
    {
        if (strcmp(temp->element.user_name, e.user_name) == 0)
        {
            if (strcmp(temp->element.password, e.password) == 0)
                return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
node *checkPassword(node *root, elementtype e)
{
    node *temp = root;
    while (temp != NULL)
    {

        if (strcmp(temp->element.password, e.password) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void writeFile(FILE *p, node *root)
{
    node *temp = root;
    while (temp != NULL)
    {
        fprintf(p, "%s %s %d\n", temp->element.user_name, temp->element.password, temp->element.status);
        temp = temp->next;
    }
}