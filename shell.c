#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

int main(void) {
    
    size_t size_buf= 0;
    char *buf = NULL;
    ssize_t num_count;
    bool pipe = false; //for the boolean part

    while (1 && !pipe) {
        if (isatty(STDIN_FILENO) == 0)
        {
            pipe = true;
        }

        // Display prompt
        write(STDOUT_FILENO, "cisfun$ ", 9);

        // Read user input
        num_count = getline(&buf, &size_buf, stdin);
        /*num_count = read(STDIN_FILENO, buf, size_buf);*/
        if (num_count == -1)//indicates an EOF
        {
            perror("Exiting ...");
            free(buf);
            exit(-1);
        }

        //when user types in enter,getline stores a newline character
        // we need to replace it with a null terminated byte.
       if (buf[num_count -1] == '\n') 
       {
        buf [num_count] = '\0';
       }

        // Parse user input
        char *token = strtok(buf, " \n");
        if (token == NULL) {
            // Empty command, prompt again
            continue;
        }

        // Fork child process to execute command
        pid_t pid = fork();
        if (pid == -1) {
            // Error forking process
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            // Execute command
             if (execve(token, (char *[]) {token, NULL}, NULL) == -1) {
                // Error executing command
                perror("execve");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            // Wait for child process to complete
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                // Error waiting for child process
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }

        
}
 // Free memory and exit
    free(buf);
    exit(EXIT_SUCCESS);
    
}
