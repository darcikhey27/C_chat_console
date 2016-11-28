/*
   C ECHO client example using sockets
   */
#include <stdio.h> //printf
#include <stdlib.h>
#include <string.h>    //strlen
#include <unistd.h>
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <sys/types.h>
#include <netinet/in.h>

int main(int argc , char *argv[])
{
    /* get the ip and port from argv */
    char *server_ip = argv[1]; 
    int port = atoi(argv[2]);
    printf("argc %d\n", argc);
    int sock;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];


    // (1) Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    server.sin_addr.s_addr = inet_addr(server_ip);
    server.sin_family = AF_INET;
    server.sin_port = htons( port );

    // (2) Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
    puts("connections success");
    //strcpy(message, "darci is the best mofo");
    int s, recieve;

    printf("Enter a message to send to server "); 
    while(1) 
    {
        fgets(message, sizeof(message), stdin);
        // (3) send to server 
        if( send(sock, message, strlen(message), 0) < 0 )
        {
            puts("Error while sending");
        }
        //puts("message has been sent to the server");

        char recv_buff[1000];
        int recv_status;
        // recieve from server 
        recv_status = recv(sock, recv_buff, 2000, 0);
        //printf("Client1: ");
        puts(recv_buff);
        //printf("recv_status %d\n", recv_status);
        recv_buff[0] = '\0';

    }

    close(sock); 
    return 0;
}
