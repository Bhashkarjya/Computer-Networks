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
    int sockfd,client_fd,len,opt=1,status;
    char buf1[80]={0},buf[]="Hello from the server";
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    status = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT,&opt,sizeof(opt));
    struct sockaddr_in server,client;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero,8);
    len = sizeof(server);
    status = bind(sockfd,(struct sockaddr*)&server,len);
    status = listen(sockfd,5);
    client_fd = accept(sockfd, (struct sockaddr*)&client, (socklen_t*)&len);
    status = read(client_fd,buf1,80);
    cout<<buf1<<endl;
    int sent_bytes=send(client_fd,buf,sizeof(buf),0);
    cout<<"Server: Message sent"<<endl;
    cout<<inet_ntoa(client.sin_addr)<<endl;
    close(sockfd);
    // cout<<inet_ntoa(client.sin_addr)<<endl;

}