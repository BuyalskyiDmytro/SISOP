#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

char *global_message;

void alarm_handler(int sig) {
    printf("%s\n", global_message); 
    exit(0); 
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <seconds> <message>\n", argv[0]);
        return 1;
    }

    int interval = atoi(argv[1]);
    global_message = argv[2];

    signal(SIGALRM, alarm_handler); 

    pid_t pid = fork(); 

    if (pid == 0) {
        alarm(interval); 
        pause();
    } else if (pid > 0) {
        wait(NULL); 
    } else {
        perror("fork");
        return 2;
    }

    return 0;
}