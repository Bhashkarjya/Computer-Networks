#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

sem_t mutex;

void* thread(void* arg)
{
    sem_wait(&mutex); //down operation (sem_value--,process goes to suspended list if sem_value goes down below 0)
    //comes the critical section
    printf("Entering the critical section\n");
    printf("Exiting the critical section\n");
    sem_post(&mutex);//up operation (sem_value++, process wakes up and again tries to enter the critical section if the sem_value becomes >=0)
}

int main(){
    sem_init(&mutex,0,1); //2nd arg-0 for thread,+ve value for process //3rd arg- initial value of semaphore
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread,NULL);
    // &t1 -> NULL or a pointer to a pthread_t object where the function can store the new thread ID
    // 2nd arg - pointer to a pthread_attr_t structure that specifies the attributes of the new thread
    // 3rd arg - the rountine or the function where the thread begins
    // 4th arg - the argument to be send to the start routine
    sleep(2);
    pthread_create(&t2,NULL,thread,NULL);
    pthread_join(t1,NULL);
    //system call to terminate the target thread
    //1st arg - the thread that you want to terminate
    //2nd arg - NULL or a pointer to the location where you want the function to store the value passed to pthread_exit() by the target thread
    pthread_join(t2,NULL);
    sem_destroy(&mutex);
    return 0;
}

//compile using g++ semaphore_using_thread.cpp -lpthread -lrt

//Using semaphores with threads