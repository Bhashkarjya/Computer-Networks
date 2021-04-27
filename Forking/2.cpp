//P1 has mulitples child namely P2 and P3

#include<bits/stdc++.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
using namespace std;

int main(){
    pid_t pid1,pid2;
    pid1=fork();
    if(pid1 == 0){
        cout<<"P2 is being called:"<<getpid()<<endl;
        cout<<"Parent's  pid:"<<getppid()<<endl;
    }
    else{
        pid2=fork();
        if(pid2==0){
            cout<<"P3 is being called:"<<getpid()<<endl;
            cout<<"Parent's pid:"<<getppid()<<endl;
        }
        else{
            waitpid(pid2,0,0);
            waitpid(pid1,0,0);
            cout<<"P1 is being called:"<<getpid()<<endl;
        }
    }
    return 0;
}
 