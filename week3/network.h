#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
void showIp(char *hostname);
void showDNS(char *IP);
void showIp(char *hostname)
{
    struct in_addr **ListAddress;
    struct hostent *hosts;

    int i;
    if ((hosts = gethostbyname(hostname)) == NULL)
    {

        printf("Not found information\n");
    }
    else
    {

        ListAddress = (struct in_addr **)hosts->h_addr_list;
        for (i = 0; ListAddress[i] != NULL; i++)
        {

            printf("%s \n", inet_ntoa(*ListAddress[i]));
            printf("\n");
        }
        printf("Alias: ");
        if ((hosts->h_aliases) == NULL)
            printf("alias: no alias");
        else
            printf("%s\n", *(hosts->h_aliases));
    }
}
void showDNS(char *IP)
{
    // printf("***%s\n", IP);
    struct hostent *host;
    struct in_addr *ipAdd;
    inet_aton(IP, ipAdd);
    host = gethostbyaddr(ipAdd, sizeof(ipAdd), AF_INET);
    if (host == NULL)
    {
        printf("not found:\n");
    }
    else
    {
        printf("%s\n", host->h_name);
        if ((host->h_aliases) == NULL)
            printf("alias: no alias");
        else
        {
            printf("Alias: ");
            printf("%s", *(host->h_aliases));
            printf("\n");
        }
    }
}
int NumberCheck(char *ip_part)
{
    int Numbers = atoi(ip_part);

    if (Numbers < 0 || Numbers > 256)
        return 0;
    return 1;
}
int checkIp(char *ip)
{
    char str[40];
    strcpy(str, ip);
    char s[2] = ".";
    int counter = 0;
    char *token;
    token = strtok(str, s);
    while (token != NULL)
    {
        if (!NumberCheck(token))
            return 0;

        token = strtok(NULL, s);
        counter++;
    }

    if (counter != 4)
        return 0;

    return 1;
}