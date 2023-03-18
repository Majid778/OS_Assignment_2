#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/times.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

using namespace std;

// handler for SIGUSR1
int sig1Count = 0;
void sig1helper(int sig)
{
    signal(SIGUSR1, sig1helper);
    sig1Count++;
}

// handler for SIGUSR2
int sig2Count = 0;
void sig2helper(int sig)
{
    signal(SIGUSR2, sig2helper);
    sig2Count++;
}

int main(int argc, char *argv[])
{
    int lowerBound, upperBound, numOfNodes, diff, remainder, baseSize;
    char option;
    pid_t rootPID = getpid();

    // Parse command line arguments
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-l")
        {
            lowerBound = std::stoi(argv[++i]);
        }
        else if (arg == "-u")
        {
            upperBound = std::stoi(argv[++i]);
        }
        else if (arg == "-e")
        {
            option = 'e';
            // sprintf(option, "%d", "e"); 
        }
        else if (arg == "-r")
        {
            option = 'r';
            // sprintf(option, "%d", "r"); 
        }
        else if (arg == "-n")
        {
            numOfNodes = std::stoi(argv[++i]);
        }
    }

    cout << lowerBound << endl;
    cout << upperBound << endl;
    cout << numOfNodes << endl;
    cout << option << endl;

    // for signal handling from the subsequent nodes
    signal(SIGUSR1, sig1helper);
    signal(SIGUSR2, sig2helper);

    double t1, t2, cpu_time;
    struct tms tb1, tb2;
    double ticspersec;
    int i, sum = 0;
    ticspersec = (double)sysconf(_SC_CLK_TCK);
    t1 = (double)times(&tb1);

    diff = (upperBound - lowerBound) + 1;
    remainder = diff % numOfNodes;
    baseSize = (diff - remainder) / numOfNodes;

    int delegatorSizes[numOfNodes];
    int lb = lowerBound, ub = 0;

    for (int i = 0; i < numOfNodes; i++)
    {
        if (i < remainder)
        {
            delegatorSizes[i] = baseSize + 1;
        }
        else
        {
            delegatorSizes[i] = baseSize;
        }
    }

    ub = lb + delegatorSizes[0] - 1;
    char buffer1[50];
    char buffer2[50];
    char buffer3[50];

    sprintf(buffer1, "%d", ub);
    sprintf(buffer2, "%d", lb);
    sprintf(buffer3, "%d", numOfNodes);

    for (int i = 0; i < numOfNodes; i++)
    {

        int delegatorID = fork();

        // check for fork failed
        if (delegatorID < 0)
        {
            cout << "error creating delgator node\n";
            return -1;
        }
        else if (delegatorID == 0)
        {
            cout << buffer1 << endl;
            cout << buffer2<< endl;
            cout << buffer3<< endl;
            cout << option << endl;
            if (option == 'e') {
                if (execlp("./delegator", buffer1, buffer2, "e", buffer3, NULL) == -1)
                {
                    int e = errno;
                    printf("ERROR %d\n", e);
                };
            }
            else if (option == 'r') {
                if (execlp("./delegator", buffer1, buffer2, "r", buffer3, NULL) == -1)
                {
                    int e = errno;
                    printf("ERROR %d\n", e);
                };
            }
        }

        else
        {
            t2 = (double)times(&tb2);
            cpu_time = (double)((tb2.tms_utime + tb2.tms_stime) -
                                (tb1.tms_utime + tb1.tms_stime));
            printf("Run time was %lf sec ( REAL time ) although we used the CPU for %lf sec ( CPU time ).\n", (t2 - t1) / ticspersec, cpu_time / ticspersec);
        }

        lb = lb + delegatorSizes[i];
        ub = ub + delegatorSizes[i+1];
        sprintf(buffer1, "%d", ub);
        sprintf(buffer2, "%d", lb); 
    }
}

// are the d nodes just a fork of the root or is it an exec
// ^ same for worker

// how and where are the pipes used

// randomize?

// whats non-blocking?