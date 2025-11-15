#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    // TODO: Complete and document
    if (argc != 3) {
        fprintf(stderr, "USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];

    // Open output file
    int fd = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0770);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Redirect STDOUT to the file
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(fd);
        return 1;
    }

    close(fd);  // no longer needed

    // Print header BEFORE exec
    printf("Category,Count\n");
    fflush(stdout);

    // Prepare exec arguments
    char *parta_args[] = {
        "./parta",
        input_filename,
        NULL
    };

    // Exec parta
    int eret = execv("./parta", parta_args);

    // If execv returns, it failed
    perror("execv");
    return 1;
}
