#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/times.h>
#include <string>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

//struct primeInfo{
    pid_t rootPID;
    int lower_bound;
    int upper_bound;
    char* mode;
    int numNodes;
//};

int main(int argc, char* argv[]) {
     printf("enter delegator\n");
    // printf("%s\n", argv[0]);
    // printf("%s\n", argv[1]);
    // printf("%s\n", argv[2]);
    // printf("%s\n", argv[3]);
    rootPID = getppid();
    upper_bound = std::stoi(argv[0]); 
    lower_bound = std::stoi(argv[1]);
    mode = argv[2];
    numNodes = std::stoi(argv[3]);

    //pipes to pass sorted records and time data respectively
    char* pipeName[numNodes];
    char* timePipe[numNodes];
    
    //create names for pipes for each sorter to pass its sorted records and time data
    //ith pipe is for ith sorter
    // int pipeBuffSize=512;
    // for (int i=0;i<numNodes;i++){
    //     // printf("here\n");
    //     // pipeName[i] = malloc(pipeBuffSize*sizeof(char));
    //     // timePipe[i] = malloc(pipeBuffSize*sizeof(char));
        
    //     strcpy(pipeName[i],"/tmp/pipe");
    //     strcpy(timePipe[i],"/tmp/timePipe");
        
    //     char pipeNum[7];
    //     sprintf(pipeNum,"%d",i);
    //     strcat(pipeName[i],pipeNum);
    //     strcat(timePipe[i],pipeNum);
    // }
    //create the named pipes
    char buf1[50];
    for (int i=0;i<numNodes;i++){
        printf("enter loop\n");
        sprintf(buf1,"%d",i);
        printf("past sprint\n");
        char * myfifo = "myfifo"; 
        printf("past char* myfifo\n");
        strcat(myfifo,buf1);
        printf("past buf1\n");
        // mkfifo(pipeName[i],0777);
        // mkfifo(timePipe[i],0777);
    }
}