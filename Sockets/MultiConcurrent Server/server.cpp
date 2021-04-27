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

#define PORT1 8080
#define PORT2 8000
#define PORT3 9000
#define MAX_CLIENT 5
#define MAX_DATA 1024

using namespace std;

void MakeTheServiceReady(int &sfd, int &len, struct sockaddr_in& server,int flag)
{
    sfd = socket(AF_INET,SOCK_STREAM,0);
    server.sin_family = AF_INET;
    if(flag==1)
        server.sin_port = htons(PORT1);
    else if(flag==2)
        server.sin_port = htons(PORT2);
    else
        server.sin_port = htons(PORT3);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero,8);
    len = sizeof(server);
    bind(sfd,(struct sockaddr* )&server,len);
    listen(sfd,MAX_CLIENT);
}

void dupcalls(int &nsfd)
{
    dup2(0,12);
    dup2(nsfd,0);
}

int main()
{
    int sfd1,sfd2,sfd3,nsfd,len1,len2,len3;
    struct sockaddr_in server1,server2,server3,client1,client2,client3;
    struct pollfd pfds[3];
    MakeTheServiceReady(sfd1,len1,server1,1);
    MakeTheServiceReady(sfd2,len2,server2,2);
    MakeTheServiceReady(sfd3,len3,server3,3);
    while(1){
        pfds[0].fd = sfd1;
        pfds[1].fd = sfd2;
        pfds[2].fd = sfd3;
        for(int i=0;i<3;i++)
        pfds[i].events = POLLIN;

        poll(pfds,3,500);
        if(pfds[0].revents && POLLIN)
        {
            cout<<"A"<<endl;
            int nsfd1;
            len1 = sizeof(client1);
            nsfd1 = accept(sfd1,(struct sockaddr*)&client1,(socklen_t*)&len1);
            dupcalls(nsfd1);
            pid_t pid = fork();
            if(pid==0){
                execv("./service1",nullptr);
            }
            else{ 
                dup2(12,0);
            }
        }
        if(pfds[1].revents && POLLIN)
        {
            cout<<"B"<<endl;
            int nsfd2;
            len2 = sizeof(client2);
            nsfd2 = accept(sfd2, (struct sockaddr*)&client2,(socklen_t*)&len2);
            dupcalls(nsfd2);
            pid_t pid = fork();
            if(pid == 0){
                execv("./service2",nullptr);
            }
            else{
                dup2(12,0);
            }
        }
        if(pfds[2].revents && POLLIN)
        {
            int nsfd3;
            len3 = sizeof(client3);
            nsfd3 = accept(sfd3, (struct sockaddr*)&client3,(socklen_t*)&len3);
            dupcalls(nsfd3);
            pid_t pid = fork();
            if(pid == 0){
                execv("./service3",nullptr);
            }
            else{
                dup2(12,0);
            }
        }
    }
}