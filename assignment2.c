#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    pid_t pid,ci,pi;
    int port[2];
    char x[20] = "",y[20] ="",z[20] ="",n[20]="";
    
    if(pipe (port) < 0){ // pipe fails
        perror("pipe error");
        exit(0);
    }
    
    pid = fork();
    if ( pid < 0){ // fork fails
        perror ("fork error");
        exit(0);
    }
    
    if(pid > 0){ // parent
        pi = getpid();
        strcat(x, argv[1]); // read X from user
        write(port[1],x,strlen(argv[1])); // wrrite X into pipe
        wait(NULL);
        read(port[0],&n,15); // read Z' from the pipe
        printf("parent (PID %d) reads concatenated result from the pipe (Z'= '%s')\n",pi,n);
        
    }
    else{ // child
        ci = getpid();
        pi = getppid();
        read(port[0],&x,strlen(argv[1])); // read x from pipe
        printf("parent (PID %d) created a child (PID %d)\n",pi,ci);
        printf("parent (PID %d) receives X = '%s'from the user\n",pi,x);
        printf("parent (PID %d) writes X = '%s' to the pipe\n",pi,x);
        strcat(y,argv[2]); // read Y from user
        strcat(z,argv[3]); // rad z from user
        printf("child (PID %d) receives Y = '%s'and Z = '%s'from the user\n",ci,y,z);
        strcat(strcat(y," "),z);
        printf("child (PID %d) concatenates Y and Z to generate Y' = '%s'\n",ci,y);
        printf("child (PID %d) read X from pipe = '%s'\n",ci,x);
        strcat(strcat(x," "),y);
        printf("child (PID %d) concatenates X and Y' to generate Z' = '%s'\n",ci,x);
        write(port[1],x,strlen(x)); // write Z' into the pipe
        printf("child (PID %d) writes Z'into the pipe\n",ci);
    }
    return 0;
}

