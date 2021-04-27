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
#include <bits/stdc++.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <sys/msg.h>
using namespace std;

void unLinkSemaphores(){
    sem_unlink("s12");
    sem_unlink("s23");
    sem_unlink("s34");
    sem_unlink("s41");
    cout<<"Unlinked all the semaphores.\n";
}

void destroyMsgQ(){
    key_t key = ftok("temp1", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    msgctl(msgid, IPC_RMID, NULL);
    cout<<"Destroyed the message queue.\n";
}

int main(){
    unLinkSemaphores();
    destroyMsgQ();
}