#include "../include/common.h"
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <linux/time.h> // monotonic wouldnt work without this, this was VSCODES suggestion

static void usage(const char *a){fprintf(stderr,"Usage: %s <cmd> [args]\n",a); exit(1);}

static double d(struct timespec a, struct timespec b){
    return (b.tv_sec-a.tv_sec)+(b.tv_nsec-a.tv_nsec)/1e9;
}

int main(int c,char**v){
pid_t pid = fork();

    struct timespec start, end;
    
    //Guard checks to make sure everything works
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {

        execvp(v[1], &v[1]);
        perror("Execvp failed");
        exit(1);

    } else {

        int status;
        clock_gettime(CLOCK_MONOTONIC, &start);

        waitpid(pid, &status, 0);
        
        clock_gettime(CLOCK_MONOTONIC, &end);

        printf("Child PID: %d ", pid);

        if (WIFEXITED(status)) {
            printf("Exit Code: %d ", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Sig: %d ", WTERMSIG(status));
        }

        printf("Elapsed Time: %.3f seconds\n", d(start, end));
    }
    
    return 0;
}
