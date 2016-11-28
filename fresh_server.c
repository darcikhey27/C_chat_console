#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char *argv[])
{
    int socket_dh; // the socket discriptor
    struct sockaddr_in server; // struct of type sockaddr_in 

    // (1) create socket
    socket_dh = socket(AF_INET, SOCK_STREAM, 0);
    printf("Sokcet dh is %d\n", socket_dh);	

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET; // using inet type of family address

    /* INADDR_ANY means that we will use any ip address local to this computer for example
     * localhost, loopback or 127.0.0.1. (0.0.0.0) == anyadress */
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons( 8888 ); // port 8888 will be used

    // (2) bind
    int stat;
    stat = bind(socket_dh, (struct sockaddr *)&server, sizeof(server));
    printf("bind status %d\n", stat);
    if(stat < 0)
        printf("bad bind status\n");

    // (3) listen for connections
    listen(socket_dh, 2);

    puts("Wating for client");
    int client_socket;
    struct sockaddr_in client_addr;

    // (4) accept connection 
    client_socket = accept(socket_dh, (struct sockaddr *)&client_addr,(socklen_t*)&client_socket); 
    printf("connection established with client discriptor is %d\n", client_socket); 

    // (5) , (6) recieve data and send data 
    while(1) 
    {
        // recieve the message and send somthing back
        int count;
        char recv_buf[1000];
        char client_str[100] = "(server is replying) ";

        // recieve data from client from recv command
        count = recv(client_socket, recv_buf, 2000, 0);
        int send_status;
        // string concatanation 
        strcat(client_str,  recv_buf);

        // send stuff to client with send command
        send_status = send(client_socket,client_str, 2000, 0);
        //printf("send_status %d\n", send_status);
        recv_buf[0] = '\0'; // clear string
    }

    close(socket_dh);
    return 0;

}// end main
