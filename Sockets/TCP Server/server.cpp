//A Simple TCP Server.
//To connect to this server run the following commands
// netstat -atp  checks if the server is listening
// telnet localhost PORT_NUMBER  connects the client to the server listening at the specific PORT_NUMBER

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<iostream>
#include<arpa/inet.h>

#define PORT 10000
using namespace std;

int main()
{
    int sockfd,clientfd;
    struct sockaddr_in server,client;
    char buf[]="Hello Everyone";
    cout<<getpid()<<endl;
    //structure to store information about the port address,family and IP address
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    //domain=AF_INET(IPv4 protocol) and AF_INET(IPv6 protocol) communication domain
    //type= comm type.SOCK_STREAM for TCP(connection oriented) and SOCK_DGRAM for UDP(connectionless)
    //protocol used. 0 stands for IP
    //returns a fd for socket,establishes the end points
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT); 
    //htons() converts Big Endian to Little Indian format
    server.sin_addr.s_addr = INADDR_ANY;
    bzero(&server.sin_zero,8);
    int len = sizeof(server);
    //assigning local address
    bind(sockfd,(struct sockaddr*)&server,len);
    listen(sockfd,10);
    while(1){
        clientfd = accept(sockfd,(struct sockaddr*)&client,(socklen_t*)&len);
        int status = send(clientfd,buf,sizeof(buf),0);
        cout<<"Send "<<status<<" bytes to the client\n";
        sleep(2);
        // close(sockfd);
    }
    return 0;
}