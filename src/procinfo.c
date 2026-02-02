#include "../include/common.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void usage(const char *a){fprintf(stderr,"Usage: %s <pid>\n",a); exit(1);}
static int isnum(const char*s){for(;*s;s++) if(!isdigit(*s)) return 0; return 1;}
static int filepath = 256;

int main(int c, char**v){
    
    if(c!=2||!isnum(v[1])) usage(v[0]);
    printf("/proc/%d/stat", v[1]);

    
    printf("Hey the code is moving along");

    char filepath1[filepath];
    char filepath2[filepath];
    char filepath3[filepath];


    snprintf(filepath1, sizeof(filepath1), "/proc/%s/stat", v[1]);
    snprintf(filepath2, sizeof(filepath2), "/proc/%s/status", v[1]);
    snprintf(filepath3, sizeof(filepath3), "/proc/%s/cmdline", v[1]);

    FILE *fp = fopen(filepath1, "r");
    
    if (fp == NULL){
        perror("Error doesn't exist or permission not granted.");
        return 1;
    }

    int procpid;
    char procstate;
    int ppid;

    if (fscanf(fp, "%d   %c  %d", &procpid, &procstate, &ppid) == 3) {
        
    printf("made it to fscanf");

    printf("PID: %d", procpid);
    printf("STATE: %c", procstate);
    printf("PPID: %d", ppid);
    }
        /*
        flcose(fp);
        fp = fopen(filepath2, "r");

        fscanf(fp, "%")
        */
    
    fclose(fp);
    
    return 0;
}

    /*  
    okay so digesting this code what we have is something that verifies what is provided
    is a number, what we need to alter we need to take this PID provided and display information 
    from the provided directories 
        /proc/<pid>/stat
        /proc/<pid>/status
        /proc/<pid>/cmdline
    */

    //psuedocode
    /*
        case 1 : non-numeric (already given)
        case 2 : PID not found -> return PID not found
        case 3 : Permission denied -> return permission denied
        case 4 : return the information from the directories
    */