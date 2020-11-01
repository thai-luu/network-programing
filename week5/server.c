#include "list.h"
#define pass "Insert password"
#define notok "not OK"
#define ok "OK"
#define not "Account not ready"
#define wrong "Wrong account"
#define block "Account is blocked"
#define MAX 10000
#define bye "bye"
#define goodbye "Goodbye"
#define space " "
void readFile(FILE *p, node **root);
node *checkUser(node *root, accounttype e);
void writeFile(FILE *p, node *root);

int split(char *buffer, char *only_number, char *only_string);
int main(int argc, char *argv[])
{
    int count = 0;
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char buffSend[1024] = {0};
    char *hello = "Hello from server";
    char *hell;
    int continuos = 1;
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
    fclose(p);
    //tao socket
    // tao file mo ta soket
    if (argc != 2)
        printf("input invalid ");
    else
    {
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
        //gan dia chi cho socket
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        char only_string[100];
        char only_number[100];
        int Port = atoi(argv[1]);
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(Port);
        // bind
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        //listen, chi dinh socket lang nghe ket noi
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        //accept, chap nhan ket noi
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        while (continuos == 1)
        {
            char str_cli_ip[INET_ADDRSTRLEN];
            struct sockaddr_in *ip_client = (struct sockaddr_in *)&address;
            hell = buffSend;
            inet_ntop(AF_INET, &ip_client->sin_addr, str_cli_ip, INET_ADDRSTRLEN);
            char str_cli_port[INET_ADDRSTRLEN];
            //read, doc du lieu gan vao bien valread tra ve so byte ma no doc duoc
            valread = read(new_socket, buffer, 1024);
            if (strcmp(buffer, bye) == 0)
                break;
            hello = buffer;
           // printf("%s\n", buffer);
            strcpy(user.userName, buffer);
            while ((account = checkUser(root, user)) == NULL)
            {
               // printf("Account is blocked\n");
                strcpy(buffSend, wrong);
                send(new_socket, hell, 1000, 0);
                valread = read(new_socket, buffer, 1024);
                strcpy(user.userName, buffer);
               // printf("%s\n", buffer);
            }
            if (account->acc.status == 0)
            {

               // printf("Account is blocked\n");
                strcpy(buffSend, not );
                send(new_socket, hell, 1000, 0);
            }
            if (account->acc.status == 1)
            {
               // printf("Account is active\n");
                strcpy(buffSend, pass);
                send(new_socket, hell, 1000, 0);
                valread = read(new_socket, buffer, 1024);
                while (strcmp(account->acc.passWord, buffer) != 0)
                {
                    count++;
                    if (count == 3)
                    {
                       // printf("account is blocked\n");
                        strcpy(buffSend, block);
                        send(new_socket, hell, 1000, 0);
                        account->acc.status = 0;
                        p = fopen("nguoidung.txt", "w");
                        writeFile(p, root);
                        fclose(p);
                        break;
                    }
                   // printf("password worng:\n");
                    strcpy(buffSend, notok);
                    send(new_socket, hell, 1000, 0);
                    valread = read(new_socket, buffer, 1024);
                }
                if (count < 3)
                {
                    //printf("password ok\n");
                    strcpy(buffSend, ok);
                    send(new_socket, hell, 1000, 0);
                    valread = read(new_socket, buffer, 1024);
                    if(strcmp(buffer,bye) == 0) {
                        strcpy(buffSend, goodbye);
                        strcat(buffSend,space);
                        strcat(buffSend,account->acc.userName);
                        send(new_socket, hell, 1000, 0);
                        break;
                    }
                    if (split(buffer, only_number, only_string) == 1)
                    {
                        
                    }
                    else
                    {
                        strcpy(only_number, "Error");
                        strcpy(only_string, "");
                    }
                    strcat(only_number, only_string);
                    send(new_socket, only_number, 1000, 0);
                    strcpy(account->acc.passWord, buffer);
                    p = fopen("nguoidung.txt", "w");
                    writeFile(p, root);
                    fclose(p);
                }
            }
            if (account->acc.status == 2)
            {
                //printf("Account is idle\n");
                strcpy(buffSend, not );
                send(new_socket, hell, 1000, 0);
            }
        }
        close(new_socket);
        return 0;
    }
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
void writeFile(FILE *p, node *root)
{
    node *temp = root;
    while (temp != NULL)
    {
        fprintf(p, "%s %s %d %s\n", temp->acc.userName, temp->acc.passWord, temp->acc.status, temp->acc.homePage);
        temp = temp->next;
    }
}

int split(char *buffer, char *only_number, char *only_string)
{

    strcpy(only_string, buffer);
    int kai = 0;
    strcpy(only_number, buffer);
    int jai = 0;
    int mai = 0;
    for (int i = 0; i < 100; i++)
    {
        char ch = only_number[i];
        if (ch == '\0')
            break;
        if (ch >= '0' && ch <= '9')
        {
            only_number[jai] = ch;
            jai++;
        }
        else if ((ch >= 'a' && ch <= 'z') || (ch == ' '))
        {
            only_string[kai] = ch;
            kai++;
        }
        else
        {
            return 0;
        }
    }
    only_number[jai] = '\0';
    only_string[kai] = '\0';
    return 1;
}