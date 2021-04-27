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
}m1;

key_t key;
int msgid;

int main(){
    key=ftok("op",65);
    msgid=msgget(key,0666|IPC_CREAT);
    msgrcv(msgid,&m1,sizeof(m1),1,0);
    cout<<m1.mtext<<endl;
    return 0;
}