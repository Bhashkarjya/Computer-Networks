//Thread a reads and thread b writes
//Two way communication between threads using two pipes

#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int fd[2],fd1[2];
//file descriptor to be accessed by the threads

void* readWrite(void* arg){
    while(1){
        char ch,ch1;
        int res1= write(fd1[1],&ch1,sizeof(char));
        int res = read(fd[0],&ch,sizeof(char));
        if(res != 1 && res1 != 1){
            perror("error in reading");
            exit(3);
        }
        cout<<"T1 is reading this: "<<ch<<endl;
        cout<<endl;
        cout<<"T1 is writing this: "<<ch1<<endl;
        if(ch1=='Z'){
            ch1='A'-1;
        }
        ch1++;
    }
}

void* writeRead(void* arg){
    while(1){
        char ch,ch1;
        int res = write(fd[1],&ch,sizeof(char));
        int res1 = read(fd1[0],&ch1,sizeof(char));
        if(res != 1){
            perror("error in writing;");
            exit(2);
        }
        cout<<endl;
        cout<<"T2 is reading this: "<<ch1<<endl;
        cout<<endl;
        cout<<"T2 is writing this: "<<ch<<endl;
        if(ch=='Z'){
            ch='A'-1;
        }
        ch++;
    }
}

int main()
{
    pthread_t t1,t2;
    if(pipe(fd) == -1 || pipe(fd1) == -1){
        cout<<"Error in opening the pipe"<<endl;
        return 0;
    }
    pthread_create(&t1,NULL,readWrite,NULL);
    pthread_create(&t2,NULL,writeRead,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}