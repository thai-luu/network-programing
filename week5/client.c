#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <unistd.h>
#include <ctype.h>
#define MAX 10000
int main(int argc, char const *argv[]) 
{ 
    int r = 0;
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client";
    char buffer[1024] = {0}; 
    int continuos = 1;
    if(argc != 3) printf("Input invalid\n");
    else{
    //tao socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    int Port = atoi(argv[2]);
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(Port); 
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    // connect
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    while(continuos == 1){
        char messSend[1024];
        r = scanf("%[^\n]",messSend);
        if(r == 0) break;
        getchar();
        hello = messSend;
        send(sock , hello , 1000 , 0 ); 
        valread = read( sock , buffer, 1024); 
        printf("%s\n",buffer );
        if (strcmp(messSend, "bye") == 0)
        {
            continuos = 0;
        }
        fflush(stdin);
    }
    close(sock);
    return 0; 
} 
}