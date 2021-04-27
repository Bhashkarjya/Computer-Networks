//Using pipes to communicate between parent and child processes
#include<bits/stdc++.h>
#include<unistd.h>
#include<stdio.h>
using namespace std;
#define SIZE 50
int main(int argc, char* argv[])
{
    int fd[2],fd1[2];
    //fd[0] is the file descriptor to read
    //fd[1] is the file descriptor to write
    if(pipe(fd) == -1 || pipe(fd1) == -1)
    {
        //error occurs in opening the pipe
        cout<<"Error occurred in opening the pipe\n";
        return 0;
    }
    pid_t pid=fork();
    if(pid == 0){
        //enters the child process
        //writing from the child process
        close(fd[0]); //closing the read fd of the child process
        close(fd1[1]); 
        string str,str1;
        read(fd1[0],&str1,SIZE);
        cout<<"Data read from the parent process: ";
        cout<<str1<<endl;
        cout<<"Enter the string from the child process: "<<endl;
        getline(cin,str);
        write(fd[1],&str,SIZE);
        close(fd1[0]);
        close(fd[1]); //closing the write fd of the child process
    }
    else
    {
        //enters the parent process
        //reading from the child prcess
        close(fd[1]);
        close(fd1[0]);
        string str,str1;
        cout<<"Enter the string from the parent process: "<<endl;
        getline(cin,str1);
        write(fd1[1],&str1,SIZE);
        read(fd[0],&str,SIZE);
        cout<<"Data read from the child process:"<<str<<endl;
        close(fd[0]);
    }
    return 0;
}