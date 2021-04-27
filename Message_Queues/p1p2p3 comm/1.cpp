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

struct messagebuf message1,message2;
int main()
{
    //generate a key for the message queue
    key_t key=ftok("MSG_Q",65);
    //create a new message queue
    int msgid = msgget(key,0666|IPC_CREAT);
    message1.mtype = 1;
    message2.mtype = 2;
    int i=0;
    while(1){
        if(i%2==0){
            cout<<"Process 1:Waiting for user input:\n";
            fgets(message1.mtext,MAX_SIZE,stdin);
            msgsnd(msgid,&message1,sizeof(message1),0);
            cout<<"Process 1: Message sent to Process 2.\n";
        }
        else{
            cout<<"Process 1:Waiting for user input:\n";
            fgets(message2.mtext,MAX_SIZE,stdin);
            msgsnd(msgid,&message2,sizeof(message2),0);
            cout<<"Process 1: Message sent to Process 3.\n";
        }
        i++;
        sleep(1);
    }
    return 0;
}