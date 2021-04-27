//Count the number of CTRL + C interrupts from the keyboard
#include<bits/stdc++.h>
#include<cstdlib>
#include<signal.h>
#include<unistd.h>
#include<iostream>
using namespace std;

void signal_callback_handler(int signum){
    static int cnt=0;
    cnt++;
    cout<<endl;
    if(cnt==10)
    exit(signum);
    cout<<"Number of CTRL+C interrupts from keyboard: "<<cnt<<endl;
    signal(SIGINT,signal_callback_handler);
    //signal_callback_handler(signum);
}   

int main()
{
    signal(SIGINT,signal_callback_handler);
    while(1){
        cout<<"Process is running"<<endl;
        sleep(2);
    }
}