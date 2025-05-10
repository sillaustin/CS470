#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    //array to hold process id
    pid_t pids[10];
    //array to hold commands and their terminators
    char* commands[10][4] = {
        {"ls", "-l", NULL},
        {"date", NULL, NULL},
        {"pwd", NULL, NULL},
        {"echo", "Hello Austin", NULL},
        {"mkdir", "testfolder", NULL},
        {"touch", "testfolder/testfile", NULL},
        {"tree", NULL, NULL},
        {"rm", "testfolder/testfile", NULL},
        {"rmdir", "testfolder", NULL},
        {"ps", NULL, NULL}
    };

    //setting up child processes
    for (int i = 0; i < 10; ++i){
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }else if (pids[i] == 0){
            //display the command and process
            printf("[Child %d] PID: %d executing: %s\n", i, getpid(), commands[i][0]);
            //use execvp to insert command
            execvp(commands[i][0], commands[i]);
            //check for failure
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
        
    }

    for (int i = 0; i < 10; ++i){
        int status;
        //set up parent to wait
        pid_t pid = waitpid(pids[i], &status, 0);
        if (pid == -1) {
            perror("waitpid failed");
            continue;
        }
        //check exit satuts
        if (WIFEXITED(status)){
            //if successfull
            printf("[Parent] Child %d (PID %d) exited with status %d\n", i, pid, WEXITSTATUS(status));
        }else if (WIFSIGNALED(status)) {
            //if failed
            printf("[Parent] Child %d (PID %d) terminated by signal %d\n", i, pid, WTERMSIG(status));
        } else {
            //everything else???
            printf("[Parent] Child %d (PID %d) ended abnormally\n", i, pid);
        }
    }

return 0;
}