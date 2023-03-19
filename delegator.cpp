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
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

    pid_t rootPID;
    int low_bound;
    int up_bound;
    char* mode;
    int numNodes;


int main(int argc, char* argv[]) {
     printf("enter delegator\n");
    int workerSizes[numNodes];

    rootPID = getppid();
    up_bound = stoi(argv[0]); 
    low_bound = stoi(argv[1]);
    mode = argv[2];
    numNodes = stoi(argv[3]);

     char* pipeName[numNodes];
     char* timePipe[numNodes];


    char buffer[] = "pipe1";
    for (int i = 1; i <= numNodes; i++) {
        buffer[4] = '0' + i;
        pipeName[i] = buffer;
        cout<<pipeName[i]<<endl;
    }
    char buffer[] = "time1";
    for (int i = 1; i <= numNodes; i++) {
        buffer[4] = '0' + i;
        timePipe[i] = buffer;
        cout<<timePipe[i]<<endl;
    }

    //create the named pipes
    for (int i=0;i<numNodes;i++){
        mkfifo(pipeName[i],0777);
        mkfifo(timePipe[i],0777);
    }

    int diff = (up_bound - low_bound) + 1;
    int remainder = diff % numNodes;
    int baseSize = (diff - remainder) / numNodes;

    for (int i = 0; i < numNodes; i++)
    {
        if (i < remainder)
        {
            workerSizes[i] = baseSize + 1;
        }
        else
        {
            workerSizes[i] = baseSize;
        }
    }

    int lb = low_bound;
    int ub = lb + workerSizes[0] - 1;



    char upper[50];
    char lower[50];
    char numofnodes[50];
    sprintf(upper, "%d", ub);
    sprintf(lower, "%d", lb);
    sprintf(numofnodes, "%d", numNodes);


    for (int i=0;i<numNodes;i++){

        if (fork()==0){
            if(i%2){

                if(execlp("./prime1",lower,upper,NULL)==-1){
                    int e=errno;
                    printf("ERROR %d\n",e);
                    printf("odd sorter not executing\n");
                };
            }else{

                if(execlp("./prime2",lower,upper,NULL)==-1){
                    int e=errno;
                    printf("ERROR %d\n",e);
                    printf("even sorter not executing\n");
                };

            }

            exit(0);
        }

        lb = lb + workerSizes[i];
        ub = ub + workerSizes[i+1];
    }
}