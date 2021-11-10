#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

static void sighandler(int sig){
    if (sig == SIGINT){
        int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd == -1){
            printf("Error creating file out.txt: %s\n", strerror(errno));
        }
        char msg[] = "Program exited due to SIGINT";
        int w = write(fd, msg, strlen(msg));
        if(w == -1){
            printf("Error writing to file out.txt: %s\n", strerror(errno));
        }
        exit(0);
        close(fd);
    } 
    if (sig == SIGUSR1){
        printf("ppid: %d\n", getppid());
    }
}
int main(){
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    while(1){
        printf("pid: %d\n", getpid());
        sleep(1);
    }
    return 0;
}
