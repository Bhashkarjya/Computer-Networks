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

struct messagebuf{
    long mtype;
    char mtext[200];
} msg1,msg2,msg3;

struct messagebuf1{
    long mtype;
    int value;
} p[4],sender[4];


int msgid;
key_t key;

void* func1(void* arg){

    while(1){
        msgrcv(msgid,&msg1,sizeof(msg1),1,0);
        cout<<"Msg from C1: "<<msg1.mtext<<endl;
        msgsnd(msgid,&msg2,sizeof(msg2),0);
        msgsnd(msgid,&msg3,sizeof(msg3),0);
    }
    pthread_exit((void*)0);
}

void* func2(void* arg){

    while(1){
        msgrcv(msgid,&msg2,sizeof(msg2),2,0);
        cout<<"Msg from C2: "<<msg2.mtext<<endl;
        msgsnd(msgid,&msg1,sizeof(msg1),0);
        msgsnd(msgid,&msg3,sizeof(msg3),0);
    }
    pthread_exit((void*)0);
}

void* func3(void* arg){

    while(1){
        msgrcv(msgid,&msg3,sizeof(msg3),3,0);
        cout<<"Msg from C3: "<<msg3.mtext<<endl;
        msgsnd(msgid,&msg1,sizeof(msg1),0);
        msgsnd(msgid,&msg2,sizeof(msg2),0);
    }
    pthread_exit((void*)0);
}

int main()
{
    key = ftok("ChatServer",65);
    msgid = msgget(key,0666|IPC_CREAT);

    msgrcv(msgid,&p[1],sizeof(p[1]),1,0);
    msgrcv(msgid,&p[2],sizeof(p[2]),2,0);
    msgrcv(msgid,&p[3],sizeof(p[3]),3,0);

    cout<<"PIDs of the client processes are\n";
    for(int i=1;i<=3;i++){
        cout<<p[i].value<<" ";
    }
    cout<<endl;

    for(int i=1;i<=3;i++){
        sender[i].mtype=p[i].value;
        sender[i].value=getpid();
        msgsnd(msgid,&sender[i],sizeof(sender[i]),0);
    }
    cout<<"Server PID send to all the clients\n";

    pthread_t t1,t2,t3;
    pthread_create(&t1,NULL,func1,NULL);
    pthread_create(&t2,NULL,func2,NULL);
    pthread_create(&t3,NULL,func3,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    return 0;
}