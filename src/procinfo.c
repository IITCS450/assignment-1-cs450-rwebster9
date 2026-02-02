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


    //in retrospect, I should've trapped these in functions to not make code so long completing same operation
    char filepath1[filepath]; //<-- stat
    char filepath2[filepath]; //<-- status
    char filepath3[filepath]; //<-- cmdline


    snprintf(filepath1, sizeof(filepath1), "/proc/%s/stat", v[1]);
    snprintf(filepath2, sizeof(filepath2), "/proc/%s/status", v[1]);
    snprintf(filepath3, sizeof(filepath3), "/proc/%s/cmdline", v[1]);

    FILE *fp = fopen(filepath1, "r");

    if (fp == NULL){
        perror("Error doesn't exist or permission not granted.\n");
        return 1;
    }

    int procpid;
    char procstate;
    int ppid;
    int utime;
    int stime;
    char cmdlinename[256];
    char vmline[256];

    if (fscanf(fp, "%d %*s %c %d %*d %*d %*d %*d %*u %*u %*u %*u %*u %d %d", &procpid, &procstate, &ppid, &utime, &stime) == 5) {
    
    float cpu_t = (utime) + (stime);
    printf("PID: %d\n", procpid);
    printf("STATE: %c\n", procstate);
    printf("PPID: %d\n", ppid);
    printf("CPU_T: %0.3f\n", cpu_t);
    
}

    fclose(fp);    
    fp = fopen(filepath3, "r");

    if (fscanf(fp,"%s", &cmdlinename)) {
        printf("Cmd: %s\n", cmdlinename);
    } else {
        printf("Error cmd does not exist or permission not granted.\n");
    }

    fclose(fp);    

    fp = fopen(filepath2, "r");

//    if (fp){
        while (fgets(vmline, sizeof(vmline), fp)) {

            if (strncmp(vmline, "VmRSS:", 6) == 0) {
                printf("%s", vmline); 
                break;
            }  
        }
    
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