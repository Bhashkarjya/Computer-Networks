//Terminate the program after 5 ctrl+c
#include<bits/stdc++.h>
#include<cstdlib>
#include<signal.h>
#include<unistd.h>
#include<iostream>
using namespace std;

void signal_handler(int signum){
    static int cnt=0;
    cnt++;
    cout<<endl;
    cout<<"Attempt to terminate:"<<cnt<<endl;
    if(cnt==5){
        exit(signum);
    }
    signal(SIGINT,signal_handler);
    //signal_callback_handler(signum);
}   

int main()
{
    signal(SIGINT,signal_handler);
    while(1){
        cout<<"Process is running"<<endl;
        sleep(2);
    }
}