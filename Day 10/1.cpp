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

#define MAX_SIZE 1000

key_t key;
int msgid;
sem_t *s12,*s41,*s23,*s34;

struct messageBuf1{
  long mtype,value;
}msg1,msg2;

struct messageBuf2{
  long mtype;
  char buf[100];
}msg3;

void createMsgQ(){
  key = ftok("temp1", 65);
  msgid = msgget(key, 0666 | IPC_CREAT);
}

void openSemaphores(){
  s12 = sem_open("s12",O_CREAT|O_EXCL,0666,0);
  s23 = sem_open("s23",O_CREAT|O_EXCL,0666,0);
  s34 = sem_open("s34",O_CREAT|O_EXCL,0666,0);
  s41 = sem_open("s41",O_CREAT|O_EXCL,0666,0);
}

void receivingPID(){
  msg1.mtype=1;
  msg1.value=getpid();
  int status = msgsnd(msgid,&msg1,sizeof(msg1),0);
  sem_post(s41);
  sem_wait(s12);
  msgrcv(msgid, &msg2, sizeof(msg2), 1, 0);
  cout << "The received PID of P2: "<<msg2.value<<endl;
  return;
}

void sendingMessage(){
  cout<<"Enter the message:\n";
  msg3.mtype=msg2.value;
  fgets(msg3.buf,MAX_SIZE,stdin);
  msgsnd(msgid,&msg3,sizeof(msg3),0);
  msgrcv(msgid,&msg3,sizeof(msg3),getpid(),0);
  cout<<"Received from P4: "<<msg3.buf<<endl;
  return;
}

int main(){

  openSemaphores(); 
  cout << "PID of P1 : " << getpid() << endl;
  createMsgQ();
  receivingPID();
  sendingMessage();
  return 0;
}