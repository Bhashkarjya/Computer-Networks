#include<bits/stdc++.h>
#include<fcntl.h>
#include<poll.h>
#include<sys/time.h>
#include<sys/poll.h>
#include<unistd.h>
using namespace std;

int main(int argc,char **argv)
{
    int fd1,fd2;
    char buffer[1000];
    struct pollfd pfds[3];
    fd1=open("file1.txt",O_RDONLY);
    fd2=open("file2.txt",O_RDONLY);

    while(1)
    {
        pfds[0].fd = 0;
        pfds[1].fd = fd1;
        pfds[2].fd = fd2;

        for(int i=0;i<3;i++)
        pfds[i].events = POLLIN;

        int pret = poll(pfds,3,5000);
       // cout<<pret<<" ";
        // if(pret == 0){
        //     cout<<"timeout"<<endl;
        //     continue;
        // }
        if(pfds[0].revents && POLLIN){
            int result = read(0,buffer,1024);
            write(1,buffer,result);
        }
        if(pfds[1].revents && POLLIN){
            int result = read(fd1,buffer,1024);
            write(1,buffer,result);
        }
        if(pfds[2].revents && POLLIN){
            int result = read(fd2,buffer,1024);
            write(1,buffer,result);
        }
    }
}