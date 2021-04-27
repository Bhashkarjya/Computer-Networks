//Thread a reads and thread b writes
//One way communication between threads using pipes

#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int fd[2];
//file descriptor to be accessed by the threads

void* reading(void* arg){
    while(1){
        char ch;
        int res = read(fd[0],&ch,sizeof(char));
        if(res != 1){
            perror("error in reading");
            exit(3);
        }
        cout<<"Reader is reading this: "<<ch<<endl;
        cout<<endl;
    }
}

void* writing(void* arg){
    while(1){
        char ch;
        int res = write(fd[1],&ch,sizeof(char));
        if(res != 1){
            perror("error in writing;");
            exit(2);
        }
        cout<<"Writer is writing this: "<<ch<<endl;
        if(ch=='Z'){
            ch='A'-1;
        }
        ch++;
        cout<<endl;
    }
}

int main()
{
    pthread_t t1,t2;
    if(pipe(fd) == -1){
        cout<<"Error in opening the pipe"<<endl;
        return 0;
    }
    pthread_create(&t1,NULL,reading,NULL);
    pthread_create(&t2,NULL,writing,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}