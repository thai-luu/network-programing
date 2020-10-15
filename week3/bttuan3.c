#include "list.h"
#include "network.h"
void readFile(FILE *p, node **root);
node *checkUser(node *root, accounttype e);
node *checkAccount(node *root, accounttype e);
void writeFile(FILE *p, node *root);
void save(FILE *p, accounttype e);
node *checkPassword(node *root, accounttype e);
int main()
{
    int dem;
    char userS[20];
    char *input = userS;
    char userLogin[20];
    int a;
    char pass[20];
    char active[20];
    char CodeActive[] = "LTM121216";
    FILE *p;
    node *root = NULL;
    accounttype user;
    node *account = NULL;
    p = fopen("nguoidung.txt", "r+");
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
        printf("3.Sign in\n4.Search\n5.Change password\n6.Sign out\n7.Homepage with domain name\n8.Homepage with Ip address\nYou choice (1-6, other to quit)\n");
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            printf("username: ");
            scanf("%s", user.userName);
            while (checkUser(root, user) != NULL)
            {
                printf("Account existed\n");
                printf("invite you to re-enter\nusername: ");
                scanf("%s", user.userName);
            }
            printf("password: ");
            scanf("%s", user.passWord);
            printf("Homepage: ");
            scanf("%s", user.homePage);
            user.status = 2;
            printf("Successful registration. Activation required.\n");
            insertAtEnd(&root, user);
            save(p, user);
            fclose(p);
            break;
        case 2:
            printf("username: ");
            scanf("%s", user.userName);
            printf("password: ");
            scanf("%s", user.passWord);
            while ((account = checkAccount(root, user)) == NULL)
            {
                printf("The account does not exist or the password is wrong\n");
                printf("invite you to re-enter\nusername: ");
                scanf("%s", user.userName);
                printf("password: ");
                scanf("%s", user.passWord);
            }
            if (account->acc.status == 0)
            {
                printf("Could not activate the locked account\n");
                break;
            }
            if (account->acc.status == 1)
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
                    account->acc.status = 0;

                    break;
                }
                printf("Account is not activated\nPlease re-enter the activation code:");
                scanf("%s", active);
            }
            if (count < 3)
            {
                printf("Account is activated\n");
                account->acc.status = 1;
            }
            p = fopen("nguoidung.txt", "w");
            writeFile(p, root);
            fclose(p);

            break;
        case 3:
            printf("username: ");
            scanf("%s", user.userName);
            while (checkUser(root, user) == NULL)
            {
                printf("Cannot find account\n");
                printf("Invite you to re-enter\nusername: ");
                scanf("%s", user.userName);
            }
            strcpy(userLogin, user.userName);
            printf("password: ");
            scanf("%s", user.passWord);

            int countt = 0;
            while ((account = checkPassword(root, user)) == NULL)
            {
                countt++;
                if (countt == 3)
                {
                    printf("Password is incorrect. Account is blocked \n");
                    account->acc.status = 0;
                    
                    break;
                }
                printf("Password is incorrect \n");
                printf("invite you to re-enter\npassword: ");
                scanf("%s", user.passWord);
            }
            if (countt < 3)
            {

                if (account->acc.status == 1)
                {
                    printf("Hello %s\n", user.userName);
                    strcpy(userS,account->acc.homePage);
                    dem = 1;
                }
                else
                    puts("Account is blocked");
            }
            p = fopen("nguoidung.txt", "w");
            writeFile(p, root);
            fclose(p);
            break;
        case 4:
            printf("username: ");
            scanf("%s", user.userName);
            while ((account = checkUser(root, user)) == NULL)
            {
                printf("Cannot find account \n");
                printf("invite you to re-enter\nusername: ");
                scanf("%s", user.userName);
            }
            if (account->acc.status == 0)
                printf("Account is blocked\n");
            if (account->acc.status == 1)
                printf("Account is active\n");
            if (account->acc.status == 2)
                printf("Account is idle\n");
            break;
        case 5:
            printf("username: ");
            scanf("%s", user.userName);
            while ((account = checkUser(root, user)) == NULL)
            {
                printf("Can not find account\n");
                printf("invite you to re-enter\nusername: ");
                scanf("%s", user.userName);
            }
            printf("password: ");
            scanf("%s", user.passWord);
            while ((account = checkPassword(root, user)) == NULL)
            {
                printf("Current password is incorrect. Please try again \n");
                printf("invite you to re-enter\npassword: ");
                scanf("%s", user.passWord);
            }
            printf("NewPassword: ");
            scanf("%s", account->acc.passWord);
            printf("Password is change\n");
            p = fopen("nguoidung.txt", "w");
            writeFile(p, root);
            fclose(p);
            break;
        case 6:
            printf("username: ");
            scanf("%s", user.userName);
            while ((account = checkUser(root, user)) == NULL)
            {
                printf("Can not find account\n");
                printf("invite you to re-enter\nusername: ");
                scanf("%s", user.userName);
            }
            if ((strcmp(user.userName, userLogin)) == 0)
            {
                printf("Goodbye %s\n", user.userName);
                dem = 0;
            }
            else
            {
                printf("Account is not sign in \n");
            }
            break;
            case 7:
           if(dem == 1 ){
            printf("Domain name : ");
            //if(checkIp(input) == 0)
            //printf("%s\n",userS);
            //if(checkIp(input) == 1) 
            showDNS(input);
           }
           if (dem == 0)
            printf("Account is not sign in \n");
            break;
            case 8:
            if(dem ==1){
                printf("IP address: ");
                
            }
            if (dem == 0)
            printf("Account is not sign in \n");
            break;
        default:
            break;
        }
    } while (a == 1 || a == 2 || a == 3 || a == 4 || a == 5 || a == 6 || a == 7 || a == 8);
    if (a != 1 && a != 2 && a != 3 && a != 4 && a != 5 && a != 6 && a != 7 && a != 8)
        fclose(p);
    return 0;
}
void readFile(FILE *p, node **root)
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

void writeFile(FILE *p, node *root)
{
    node *temp = root;
    while (temp != NULL)
    {
        fprintf(p, "%s %s %d %s\n", temp->acc.userName, temp->acc.passWord, temp->acc.status, temp->acc.homePage);
        temp = temp->next;
    }
}