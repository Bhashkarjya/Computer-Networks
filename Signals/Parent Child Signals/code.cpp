#include<iostream>
#include<signal.h>
#include<cstdlib>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>

using namespace std;

void sighup_handler(int signum){
    //signal(SIGHUP,sighup_handler);
    cout<<"Child: Received a sighup signal"<<endl;
}

void sigint_handler(int signum)
{
    //signal(SIGINT,sigint_handler);
    cout<<"Child: Received a sigint signal"<<endl;
}

void sigquit_handler(int signum){
    //signal(SIGQUIT,sigquit_handler);
    cout<<"Child: Received a sigquit handler"<<endl;
}

void ChildToParentSignal(int signum){
    cout<<"Parent: Received a signal from the child"<<endl;
}

int main()
{
    pid_t pid;
    pid=fork();
    signal(SIGHUP,sighup_handler);
    signal(SIGINT,sigint_handler);
    signal(SIGQUIT,sigquit_handler);
    signal(SIGUSR1,ChildToParentSignal);
    if(pid<0){
        perror("Error detected in creating child process");
        return 1;
    }
    if(pid==0){
        //child process
        sleep(3);
        cout<<"Child: Sending a signal to parent"<<endl;
        kill(getpid(),SIGUSR1);
        sleep(1);
    }
    else if(pid>0)
    {
        cout<<"Parent: Sending sighup"<<endl;
        kill(pid,SIGHUP);
        sleep(1);
        cout<<"Parent: Sending sigquit"<<endl;
        kill(pid,SIGQUIT);
        sleep(1);
    }
}