//Diamond question

#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;

int main()
{
    pid_t pid1;
    pid1=fork();
    if(pid1==0){
        cout<<"Child is running"<<endl;
        //Writing to the y shared memory
        key_t key = ftok("y_shared_memory",65);
        int shmid = shmget(key,1024,0666|IPC_CREAT);
        char *str = (char*) shmat(shmid,(void*)0,0); 
	    printf("Enter your data into y: "); 
	    cin.getline(str,1000); 
	    printf("Data written in the y shared memory: %s\n",str); 
	    shmdt(str);
        exit(0);
        //exiting from the child process
    }
    else{
        wait(NULL);
        cout<<"Parent is running"<<endl;
        //it will read from the x_shared memory
        key_t key = ftok("x_shared_memory",65); 
        int shmid = shmget(key,1024,0666|IPC_CREAT); 
        char *str = (char*) shmat(shmid,(void*)0,0); 
        printf("Data read from x_shared_memory: %s\n",str); 
        shmdt(str); 
        shmctl(shmid,IPC_RMID,NULL);
        exit(0);
    }
    return 0;
}