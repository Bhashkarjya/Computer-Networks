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

int main(){

  cout<<"Creating all the semaphores:\n";
  sem_t *s12 = sem_open("s12",O_CREAT|O_EXCL,0666,0);
  sem_t *s23 = sem_open("s23",O_CREAT|O_EXCL,0666,0);
  sem_t *s34 = sem_open("s34",O_CREAT|O_EXCL,0666,0);
  sem_t *s41 = sem_open("s41",O_CREAT|O_EXCL,0666,0);
  sleep(2);
  cout<<"All the semaphores have been created.\n";
  return 0;
}