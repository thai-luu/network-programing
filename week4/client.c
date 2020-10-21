#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int sock, portNumber, n;
    struct sockaddr_in serv_addr; //Cau truc chua dia chi server ma client can biet de ket noi toi
    int continu = 1;
    char sendbuff[256];
    char recvbuff[256];
    int i = 1;
    //Client nhan tham so hostname va port tu dong lenh
    if (argc != 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portNumber = atoi(argv[2]); //Chuyen cong dich vu thanh so nguyen

    //Tao socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
        herror("ERROR opening socket");
        bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portNumber);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    while(i == 1){
    scanf("%s",sendbuff);
    if(sendbuff == 0) break;
    sendto(sock,sendbuff,strlen(sendbuff),0,(struct sockaddr *) &serv_addr, sizeof(serv_addr));
    recvfrom(sock, recvbuff, sizeof(recvbuff), 0, (struct sockaddr*)NULL, NULL); 
    puts(recvbuff);
    } 
    close(sock);
    return 0;
}