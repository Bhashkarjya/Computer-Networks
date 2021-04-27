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

#define MAX_SIZE 30

struct messagebuf{
    long mtype;
    char mtext[200];
}m1,m2;

key_t key;
int msgid,status;

struct msqid_ds buf;

void MessageQueueStatus(){
    cout<<"Time of last msgsnd system call: "<<buf.msg_stime<<endl;
    cout<<"Time of last msgrcv system call: "<<buf.msg_rtime<<endl;
    cout<<"Time of creation of message queue: "<<buf.msg_ctime<<endl;
    cout<<"No of bytes in the message queue: "<<buf.msg_cbytes<<endl;
    cout<<"No of messages in the queue: "<<buf.msg_qnum<<endl;
    cout<<"PID of last msgsnd: "<<buf.msg_lspid<<endl;
    cout<<"PID of last msgrcv: "<<buf.msg_lrpid<<endl;
    cout<<endl;
}

int main(){
    key =ftok("op",65);
    msgid=msgget(key,0666|IPC_CREAT);
    m1.mtype=1;
    m2.mtype=2;

    //Using msgctl with the IPC_STAT cmd to retrieve all the values of the message queue
    status = msgctl(msgid,IPC_STAT,&buf);
    cout<<"Current status of the message queue before msgsnd:\n";
    MessageQueueStatus();

    fgets(m1.mtext,MAX_SIZE,stdin);
    fgets(m2.mtext,MAX_SIZE,stdin);
    msgsnd(msgid,&m1,sizeof(m1),0);
    msgsnd(msgid,&m2,sizeof(m2),0);

    status = msgctl(msgid,IPC_STAT,&buf);
    cout<<"Current status of the message queue after msgsnd:\n";
    MessageQueueStatus();
    
    system("./2");
    system("./3");
    sleep(3);

    status = msgctl(msgid,IPC_STAT,&buf);
    cout<<"Status of the message queue after msgrcv():\n";
    MessageQueueStatus();

    //2nd part of the assignment, to alter the message of a message queue

    //3rd part of the assignment, to delete a message from the message queue

    return 0;
}