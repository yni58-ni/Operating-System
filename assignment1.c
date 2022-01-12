#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if(argc != 2){
        printf("argc error\n");
        exit(1);
    }
    
    pid_t pid,pid1,pid2;
	int pi,ci;
    pid = fork (); // parent creats child_1
    
    if (pid < 0) { //fork unsuccessful
        printf("child_1 unsuccessful");
        exit(1);
    }
    if (pid > 0) { // parent
        wait(NULL); // parent goes to child_1
        
        pid1 = fork();// parent creats child_2
        if (pid1 < 0) {
            printf("child_2 unsuccessful");
            exit(1);
        }
        if(pid1 > 0){ // parent
            wait(NULL); // parent goes to child_2
        }
        if (pid1 == 0){ // child _2
            ci = getpid(); // get child_2 ID
            pi = getppid(); // get parent ID
            printf("\nparent (PID %d) created child_2 (PID %d)\n",pi,ci);
            pid2 = fork (); // child_2.1
            if ( pid2 < 0){
                printf("child_2.1 unsuccessful");
                exit(1);
            }
            if(pid2 > 0){ // child_2
                wait(NULL); // parent goes to child_2.1
                printf("\nchild_1 and child_2 are completed and parent process is terminating...\n");
            }
            if (pid2 == 0){ // child_2.1
                ci = getpid(); // get child_2.1 ID
                pi = getppid(); // get parent(child_2) ID
            printf("\nchild_2 (PID %d) created child_2.1 (PID %d)\n",pi,ci);
            char* c1 = (char*)malloc(sizeof(char)*40);
            sprintf(c1,"%d for child_2.1\n",ci);
            printf("\nchild_2.1 (PID %d) is calling an external program external_program.out and leaving child_2\n\n",ci);
            execl(argv[1],argv[1],c1,NULL); // OS terminate child_2.1
            }
        }
    }
    if (pid == 0){ //child_1
        ci = getpid(); // get child_1 ID
        pi = getppid(); // get parent ID
        printf("\nparent (PID %d) created child_1 (PID %d)\n",pi,ci);
        printf("\nparent (PID %d) is waiting for child_1 (PID %d) to compile before creating child_2\n",pi,ci);
        char* c1 = (char*)malloc(sizeof(char)*40);
        sprintf(c1,"%d for child_1\n",ci);
        printf("\nchild_1 (PID %d) is calling an external program external_program.out and leaving parent\n\n",ci);
        execl(argv[1],argv[1],c1,NULL); // OS terminate child_1
    }
    return 0;
}
