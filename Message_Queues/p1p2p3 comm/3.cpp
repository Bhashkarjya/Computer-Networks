#include <time.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/select.h>
#include <sys/un.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <netinet/ether.h>
#include <netinet/udp.h>
#include <semaphore.h>
#include <sys/msg.h>
#include<bits/stdc++.h>

#define MAX_SIZE 20

using namespace std;

struct messagebuf{
    long mtype;
    char mtext[200];
};

struct messagebuf message;
int main()
{
    //generate a key for the message queue
    key_t key=ftok("MSG_Q",65);
    //create a new message queue
    int msgid = msgget(key,0666|IPC_CREAT);
    while(1){
        cout<<"Process 3:Waiting for message from Process 1:\n";
        msgrcv(msgid,&message,sizeof(message),2,0);
        cout<<message.mtext<<endl;
        cout<<"Process 3:Message received from Process 1\n";
        sleep(2);
    }
    return 0;
}