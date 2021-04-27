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

using namespace std;

int main()
{
    int server_fd,client_fd,len;
    pid_t pid;
    char buffer[MAX_DATA];
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server,client;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero,8);

    bind(server_fd,(struct sockaddr*)&server,sizeof(server));
    listen(server_fd,MAX_CLIENT);
    //server is now ready to connect to other clients

    while(1)
    {
        cout<<"Server is waiting for new client connections\n";
        len = sizeof(client);
        client_fd = accept(server_fd,(struct sockaddr* )&client,(socklen_t*)&len);
        cout<<"Server is now connected to "<<inet_ntoa(client.sin_addr)<<endl;
        pid = fork();
        if(pid == 0)
        {
            while(1)
            {
                int received_bytes = recv(client_fd,buffer,MAX_DATA,0);
                if(received_bytes == 0){
                    close(client_fd);
                    break;
                }
                else
                {
                    buffer[received_bytes] = 0;
                    send(client_fd,buffer,received_bytes,0);
                    cout<<"Received and sent: "<<buffer<<endl;
                }
            }
            //exit(0);
        }
        else
        {
            close(client_fd);
        }
    } 
}