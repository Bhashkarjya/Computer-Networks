#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<iostream>
#include<arpa/inet.h>
#include<bits/stdc++.h>
#include<sys/poll.h>
#include<netinet/in.h>

#define PORT 8080
#define MAX_CLIENT 5
#define MAX_DATA 1024

using namespace std;

int main()
{
    int nsfd = dup(STDIN_FILENO);
    char buffer[MAX_DATA],buf_sent[MAX_DATA];
    dup2(12,STDIN_FILENO);
    cout<<"Service 1 has started\n";
    int received_bytes = recv(nsfd,buffer,MAX_DATA,0);
    buffer[received_bytes]=0;
    cout<<"Message received by Service 1: "<<buffer<<endl;
    cout<<"Service 1 : Sending message to the client\n";
    fgets(buf_sent,MAX_DATA,stdin);
    send(nsfd,buf_sent,strlen(buf_sent)+1,0);
    buf_sent[strlen(buf_sent)]=0;
    cout<<"Service 1: Message send "<<buf_sent<<endl;
    close(nsfd);
    return 0;
}