#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document
    if (argc != 2) {
        fprintf(stderr, "USAGE: partc FILEIN\n");
        return 1;
    }

    char *input_filename = argv[1];

    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        

        close(pipefd[0]); // close read end

        // Redirect STDOUT to pipe write end
        if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
            perror("dup2");
            return 1;
        }

        close(pipefd[1]); // no longer needed

        // Exec parta
        char *args[] = {"./parta", input_filename, NULL};
        execv("./parta", args);

        // If execv returns, it failed
        perror("execv");
        return 1;

    } else {
        
        close(pipefd[1]); // close write end

        // Redirect STDIN to pipe read end
        if (dup2(pipefd[0], STDIN_FILENO) < 0) {
            perror("dup2");
            return 1;
        }

        close(pipefd[0]); // no longer needed

        // Exec sort
        char *sort_args[] = {
            "sort",
            "-t,",   // split on comma
            "-k2",   // sort by 2nd column
            "-n",    // numeric sort
            NULL
        };

        execv("/usr/bin/sort", sort_args);
        execv("/bin/sort", sort_args);  // fallback

        perror("execv sort");
        return 1;
    }
}
