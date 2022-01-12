#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <pthread.h> 
#include <string.h>

int port[2];
int X,Y,S;  // global variable of x, y sum
void *sum(void *thread_id){ // a function excuted by thread 100, performs addition
    S = X+Y; // peoforms X+Y
    int *id =(int*)thread_id;
    printf("thread(TID %d) reads X = %d and Y = %d from the pipe\n",*id,X,Y);
    write(port[1],&S,sizeof(S));
    printf("thread(TID %d) writes X + Y = %d to the pipe\n",*id,S);
}

void *odd_even(void *thread_id){ // a function excuted by thread 101, determine is the sums an even or odd #
    int s;
    int *id =(int*)thread_id;
    read(port[0],&s,sizeof(S));
    printf("thread(TID %d) reads X + Y = %d from the pipe\n",*id,s);
    if(s%2 == 0){
        printf("thread(TID %d) identifies X + Y = %d as an even number\n",*id,s);
    }
    else{
        printf("thread(TID %d) identifies X + Y = %d as an odd number\n",*id,s);
    }
    write(port[1],&S,sizeof(S));
    printf("thread(TID %d) writes X + Y = %d to the pipe\n",*id,S);
}

void *digit_count(void *thread_id){ // a function excuted by thread 102, determine the # of digits in the sum
    int count = 0;
    int c;
    int *id =(int*)thread_id;
    read(port[0],&c,sizeof(S));
    printf("thread(TID %d) reads X + Y = %d from the pipe\n",*id,c);
    do{
        c /= 10;
        ++count;
    }while(c != 0);
    printf("thread(TID %d) identifies X + Y = %d as a %d digit number\n",*id,S,count);

}

int main(int argc, char *argv[])
{
    pthread_t t1,t2,t3;
    int x,y;

    
    if(pipe(port) < 0){ // pipe fails
        perror("pip error");
        exit(0);
    }
    x = atoi(argv[1]); // read x from user
    write(port[1],&x,strlen(argv[1])); // write x into pipe
    
    read(port[0],&X,strlen(argv[1])); // read X from pipe

    y = atoi(argv[2]); // read y from user
    write(port[1],&y,strlen(argv[2])); // write y into pipe
    read(port[0],&Y,strlen(argv[2])); // read Y from pipe

    pid_t pid = getpid();
    printf("paretn(PID %d) receives X = %d and Y = %d from the user\n",pid,X,Y);
    printf("paretn(PID %d) writes X = %d and Y = %d to the pipe\n",pid,X,Y);

    int thread_id_1 = 100;
    pthread_create(&t1,NULL,sum,&thread_id_1); // create thread 100
    pthread_join(t1,NULL); // wait untill thread 100 is finished

    int thread_id_2 = 101;
    pthread_create(&t2,NULL,odd_even,&thread_id_2); // create thread 101
    pthread_join(t2,NULL); // wait untill thread 101 is finished

    int thread_id_3 = 102;
    pthread_create(&t3,NULL,digit_count,&thread_id_3); // create thread 102
    pthread_join(t3,NULL); // wait untill thread 101 is finished


    return 0;
}
