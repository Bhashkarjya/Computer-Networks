#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/un.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <unistd.h>
#include <bits/stdc++.h>
using namespace std;
#define PORT1 5000
#define PORT2 6500
#define PORT3 7000
#define CONTROLLEN CMSG_LEN(sizeof(int))
static struct cmsghdr *cmptr = NULL;
int inet_serv_listen(int port)
{
    struct sockaddr_in servaddr;
    int sfd, len;
    int opt=1;
    if((sfd = socket(AF_INET, SOCK_STREAM, 0))==0)
    {
        perror("socket");
        exit(1);
    }
    if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(int)))
    {
        perror("setsockopt");
        exit(1);
    }
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if(bind(sfd, (struct sockaddr*)&servaddr,sizeof(servaddr))<0)
    {
        perror("bind");
        exit(1);
    }

    if(listen(sfd,10)<0)
    {
        perror("listen");
        exit(1);
    }
    return sfd;
}
void fun(int nsfd){

    char buff1[1024] = "s1:";
    char buff2[1024] = {0};
    int read = recv( nsfd , buff2, 1024, 0);
    buff2[read] = '\0';
    printf("message recv : %s\n",buff2);
    fgets(buff2,1024,stdin);
    strcat(buff1,buff2);
    send(nsfd,buff1,strlen(buff1),0);
    buff1[strlen(buff1)]='\0';
    printf("message sent : %s\n",buff1);
}

int main(){
  struct sockaddr_in inet_cliaddr1,inet_cliaddr2,inet_cliaddr3;
  int len1,len2,len3,sfd1,nsfd1,sfd2,nsfd2,sfd3,nsfd3;
  fd_set cfd;

  sfd1=inet_serv_listen(PORT1);
  sfd2=inet_serv_listen(PORT2);
  sfd3=inet_serv_listen(PORT3);

  nsfd1=accept(sfd1,(struct sockaddr*)&inet_cliaddr1,(socklen_t*)&len1);
  fun(nsfd1);
  nsfd2=accept(sfd2,(struct sockaddr*)&inet_cliaddr2,(socklen_t*)&len2);
  fun(nsfd2);
  nsfd3=accept(sfd3,(struct sockaddr*)&inet_cliaddr3,(socklen_t*)&len3);
  fun(nsfd3);
  
  return 0;
}