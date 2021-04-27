#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <string.h>
#include<bits/stdc++.h>
#include<signal.h>
#include<cstdlib>
using namespace std;

void* thread1(void*){
  mkfifo("serve",0666);mkfifo("C2",0666);
	mkfifo("C1",0666);mkfifo("C3",0666);
	while(1){
	int fd = open("server",0x0000);
	cout<<"Serve Fifo is opened\n";
	char buff[1024];
	read(fd,&buff,1024);
	cout<<"Message read from group by server "<<buff<<"\n";
  int wd[3];
  wd[0] = open("C1",0x0001);
  wd[1] = open("C2",0x0001);
  wd[2] = open("C3",0x0001);

	 //write(wd[0],buff,1024);
  int x = buff[1]-'0';
  for(int i=0;i<3;i++){
    if(x!=i+1){
      write(wd[i],buff,1024);
    }
  }
  //close(wd[0]);
	close(wd[0]);close(wd[1]);close(wd[2]);
	close(fd);
   }
}

void signal_callback_handler(int signum)
{
    //This code runs when we type ctrl C from the keyboard
    cout<<"C3 has left the chat"<<endl;
    exit(signum);
}

int main()
{
    pthread_t t1;
    signal(SIGINT,signal_callback_handler);
	pthread_create(&t1,NULL,thread1,NULL);

	pthread_join(t1,NULL);
	return 0;
}