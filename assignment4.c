#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct Process{
    int name; // process name
    int arrivalT; // arival time
    int burstT; // burst time
    int waitingT; // waiting time = turnaround -burst
    int turnT; // turnaround time = completion - arrival
    int compleT; // completion time
};

int main(){
    char str[500];
    FILE *file = fopen("rr_input.txt","r");
    if(file == NULL){
        perror("cannot open input file");
        return 0;
    }
    else{
        while(fgets(str,500,file)!= NULL){ // loop until it's done with file
            int totalT = 0; // total time the CPU spend on completing process
            int quantumT; //quantum time
            int totalP =0;; // total number of process, start from 0
            int aT[100];// array of arrival time
            int bT[100];//array of burst time
            int i;
            char * token;
            token = strtok(str," "); // get first token
            while(token != NULL){ // walk through other tokens
                if(strchr(token,'p') != NULL || strchr(token,'P') != NULL ){ // when a token contains p, i.e. it's a process name
                    totalP++;
                    token = strtok(NULL," "); //arrival time
                    aT[totalP] = atoi(token); //assign arrival time to an array
                    token = strtok(NULL," "); //burst time
                    bT[totalP] = atoi(token); //assign burst time to an array
                }
                else{
                    quantumT = atoi(token); // assign quantum time 
                }
                token = strtok(NULL," ");
            }
            struct Process prc[totalP]; // create N process
            int temTotalP = totalP;
            for(i = 0; i < totalP;i++){ // assign name,arrival time and burst time on those processes
                prc[i].name = i+1;
                prc[i].arrivalT = aT[i+1];
                prc[i].burstT = bT[i+1];
            }
            for(totalT = 0,i =1;temTotalP!=0;){
                if(bT[i] <= quantumT && bT[i] >0){ // when a process's burst time <= quantum time
                    totalT = totalT+ bT[i];
                    bT[i] = 0;
                    prc[i-1].compleT = totalT;
                    prc[i-1].turnT = prc[i-1].compleT - prc[i-1].arrivalT;
                    prc[i-1].waitingT = prc[i-1].turnT - prc[i-1].burstT;
                    temTotalP--;
                }
                else if(bT[i] > quantumT){
                    totalT = totalT + quantumT;
                    bT[i] = bT[i] - quantumT;
                }
                if(aT[i+1] <= totalT && i < totalP ){
                    i++;
                }
                else if(i == totalP){
                    i =1;
                }
            }
            
            for(i = 0; i < totalP;i++){
                printf("Process: P%d Arrival Time: %d Burst time: %d Waiting Time:%d Turnround Time:%d\n",prc[i].name,prc[i].arrivalT,prc[i].burstT,prc[i].waitingT,prc[i].turnT);
            }
            int ttt =0; // total turnaround time
            int twt =0;// total waiting time
            double awt; // average waiting time
            double att;// average turnaround time
            for(i = 0; i < totalP;i++){
                ttt = ttt + prc[i].turnT;
                twt = twt +prc[i].waitingT;
            }
            awt =  twt * 1.0 / totalP; // total waiting time / total process number
            att = ttt * 1.0 / totalP; // total turnaround time / total process number
            printf("\nTotal Turnaround Time:%d\n",ttt);
            printf("Average waiting time = %lf\n",awt);
            printf("Average Turnaround Time = %lf\n",att);
        }
    }
    fclose(file);
    return 0;
}

