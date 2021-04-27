#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<iostream>
#include<arpa/inet.h>

#define PORT 8080
#define MAX_CLIENT 5
#define MAX_DATA 1024
#define IP_ADDRESS "127.0.0.1"

using namespace std;

int main()
{
    int client_fd,len;
    char send_msg[MAX_DATA],received_msg[MAX_DATA];
    struct sockaddr_in server;
    client_fd = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    connect(client_fd, (struct sockaddr*)&server,sizeof(server));

    while(1){
        cout<<"Client 1: Enter the message that you want to send to the server\n";
        fgets(send_msg,MAX_DATA,stdin);
        int msg_length = strlen(send_msg) + 1;
        int sent = send(client_fd,send_msg,msg_length,0);
        int received_bytes = recv(client_fd,received_msg,MAX_DATA,0);
        cout<<"Message received by the server and echoed back to Client 1 is: "<<received_msg<<endl;
    }

    return 0;
}