#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<iostream>
#include<arpa/inet.h>

#define PORT 8000
using namespace std;

int main()
{
    int client_fd,len;
    char buf1[80]={0},buf[]="Hello from the client";
    client_fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);
    connect(client_fd,(struct sockaddr*)&server,sizeof(server));
    int sent_bytes = send(client_fd,buf,sizeof(buf),0);
    cout<<"Client: Message sent"<<endl;
    read(client_fd,buf1,80);
    cout<<buf1<<endl;
    return 0;

}