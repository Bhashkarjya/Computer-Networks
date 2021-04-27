//P1->P2->P3->P4
//P2 is P1's child, P3 is P2's child and so on
#include<bits/stdc++.h>
#include<sys/wait.h>
#include<unistd.h>
using namespace std;

int main()
{
        int pid = fork();
        if(pid==0){ //if the child process is running
            cout<<"P1 is running:"<<getpid()<<endl;
            cout<<"Parent's id:"<<getppid()<<endl;
            pid=fork();
            if(pid==0){
                cout<<"P2 is running:"<<getpid()<<endl;
                cout<<"Parent's id:"<<getppid()<<endl;
                pid=fork();
                if(pid==0){
                    cout<<"P3 is running:"<<getpid()<<endl;
                    cout<<"Parent's id:"<<getppid()<<endl;
                    pid=fork();
                    if(pid==0){
                        cout<<"P4 is running:"<<getpid()<<endl;
                        cout<<"Parent's id:"<<getppid()<<endl;
                    }
                    else{
                        wait(NULL);
                        cout <<"P4 is done"<<endl;
                    }
                }
                else{
                    wait(NULL);
                    cout <<"P3 is done"<<endl;
                }
            }
            else{
                wait(NULL);
                cout <<"P2 is done"<<endl;
            }
        }
        else{
            wait(NULL);
            cout <<"P1 is done"<<endl;
        }
        exit(0);
}