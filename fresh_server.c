#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char *argv[])
{
    int socket_dh;
    struct sockaddr_in server;

    // create socket
    socket_dh = socket(AF_INET, SOCK_STREAM, 0);
    printf("Sokcet dh is %d\n", socket_dh);	

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );

    // bind
    int stat;
    stat = bind(socket_dh, (struct sockaddr *)&server, sizeof(server));
    printf("bind status %d\n", stat);
    if(stat < 0)
        printf("bad bind status\n");

    //listen for connections
    listen(socket_dh, 2);

    // accept incoming connections
    puts("Wating for client");
    int client_socket;
    struct sockaddr_in client_addr;
    client_socket = accept(socket_dh, (struct sockaddr *)&client_addr,(socklen_t*)&client_socket); 
    printf("connection established with client discriptor is %d\n", client_socket); 


    while(1) 
    {
        // recieve the message and send somthing back
        int count;
        char recv_buf[1000];
        char client_str[100] = "Client: ";
        count = recv(client_socket, recv_buf, 2000, 0);
        //printf("count %d\n", count);
        //printf("the message from client is %s\n", recv_buf);
        int send_status;
        
        strcat(client_str,  recv_buf);
       // printf("client_str%s\n", client_str);
       // printf("recv_buf%s\n", recv_buf);
        
        send_status = send(client_socket,client_str, 2000, 0);
        //printf("send_status %d\n", send_status);
        recv_buf[0] = '\0';
    }
    
    
    close(socket_dh);
    return 0;
}// end main
