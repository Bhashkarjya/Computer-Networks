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
#include <bits/stdc++.h>

using namespace std;

#define MAX_SIZE 50
struct messagebuf{
    long mtype;
    char mtext[200];
} message1,message2,m1;

struct messagebuf1{
    long mtype;
    int value;
}new_m1,server;

int msgid;
key_t key;

void* read1(void* arg){
    while(1){
        msgrcv(msgid,&message1,sizeof(message1),2,0);
        cout<<"C2: "<<message1.mtext<<endl;
    }
    pthread_exit((void*)0);
}

void* read2(void* arg){
    while(1){
        msgrcv(msgid,&message2,sizeof(message2),3,0);
        cout<<"C3: "<<message2.mtext<<endl;
    }
    pthread_exit((void*)0);
}

void* write(void* arg){

    while(1){
        sleep(1);
        m1.mtype=1;
        fgets(m1.mtext,MAX_SIZE,stdin);
        msgsnd(msgid,&m1,sizeof(m1),0);
        cout<<"Message sent\n";
    }
    pthread_exit((void*)0);
}

int main()
{
    key = ftok("ChatServer",65);
    msgid = msgget(key,0666|IPC_CREAT);

    new_m1.mtype=1;
    new_m1.value=getpid();
    msgsnd(msgid,&new_m1,sizeof(new_m1),0);
    cout<<"PID of Client 1 : "<<new_m1.value<<endl;

    msgrcv(msgid,&server,sizeof(server),new_m1.value,0);
    cout<<"PID of the server is: "<<server.value<<endl;
    cout<<"Client 1 starts\n";

    pthread_t t1,t2,t3;
    pthread_create(&t2,NULL,write,NULL);
    pthread_create(&t1,NULL,read1,NULL);
    pthread_create(&t3,NULL,read2,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    return 0;
}