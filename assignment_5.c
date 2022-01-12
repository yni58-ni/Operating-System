#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t lock;
int accountBal[10];// account balance
int action[100];
int transCount = 0;
int t= 0; // represent trasnCount
int amount[100];// amount of money for each action 
int accountArray[100]; //store account number

void *trans(void * arg){
    pthread_mutex_lock(&lock);
    if(action[t] == 0){ // deposit
        int accountNum = accountArray[t] -1;
        accountBal[accountNum] = accountBal[accountNum] + amount[t];
        t++;
    }
    else if(action[t] == 1){ // withdraw
        int accountNum = accountArray[t] -1;
        if(amount[t] > accountBal[accountNum]){ // when amount is greaer than account balance
            amount[t] = 0;
        }
        accountBal[accountNum] = accountBal[accountNum] - amount[t];
        t++;
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}



int main(int argc,char **argv){
    FILE *file;
    file = fopen("assignment_6_input.txt","r");
    char line[200];
    int a =0; // account number starts from 0

    if(file){
        while(fgets(line, sizeof(line),file)){ // while the end of file hasn't been reached
            char s[] = " ";
            char *st = strtok(line,s); // break line into tokens and stores them in st ,get the first token

            if(st[0]== 'a'){ // when its an account line
                st = strtok(NULL,s); // get 'b' stoke
                st = strtok(NULL,s); //get 'initial balance' stroke
                accountBal[a] = atoi(st);
                a++;
            }
            
            if(st[0]=='c'){ // when its a client line
                int found =1;
                
                while(found !=0){
                    if(st[0] !='d' && st[0] !='w'){
                        st = strtok(NULL,s);// get 'd' stoke or 'w' stroke
                    }
                if(st[0] == 'd'){
                    action[transCount] = 0; // mark it's an action of "deposit"
                    st = strtok(NULL,s); // get the account number
                    accountArray[transCount] = st[1] - 48;
                    st = strtok(NULL,s); //get the amount;
                    amount[transCount]=atoi(st);
                    transCount ++;
                }

                if(st[0] == 'w'){
                    action[transCount] =1;//mark it's an action of 'withdraw'
                    st = strtok(NULL,s); // get the account number
                    accountArray[transCount] = st[1] - 48;
                    st = strtok(NULL,s); //get the amount;
                    amount[transCount]=atoi(st); //get the amount
                    transCount ++;
                }

                st = strtok(NULL,s);
                if(st == 0){
                    found = 0;
                }
                }

            }

        }
    }

    int i, err_thread;
    pthread_t threads[transCount];
    if(pthread_mutex_init(&lock,NULL) != 0){
        printf("\n mutex initiate failed");
        return 1;
    }

    for(int i = 0; i < transCount; i++){
        err_thread = pthread_create(&threads[i],NULL,trans,&threads[i]);
        if(err_thread !=0){
            printf("\n Creating thread %d failed",i);
        }
    }

    for(int i = 0; i < transCount; i++){
        pthread_join(threads[i],NULL);
    }

    pthread_mutex_destroy(&lock);

    for(int i = 0; i < a; i++){
        printf("a%d b %d\n",i+1,accountBal[i]);
    }

    return 0;

}