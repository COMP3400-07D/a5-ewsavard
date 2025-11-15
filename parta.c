#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
    // TODO: Complete and document
    if (argc != 2) {
            fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
            return 1;
        }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    ssize_t bytes;

    int upper = 0, lower = 0, number = 0, space = 0, others = 0;

    while ((bytes = read(fd, buffer, 8)) > 0) {
        for (ssize_t i = 0; i < bytes; i++) {
            unsigned char c = buffer[i];

            if (isupper(c)) upper++;
            else if (islower(c)) lower++;
            else if (isdigit(c)) number++;
            else if (isspace(c)) space++;
            else others++;
        }
    }

    if (bytes < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    close(fd);

    printf("Upper,%d\n", upper);
    printf("Lower,%d\n", lower);
    printf("Number,%d\n", number);
    printf("Space,%d\n", space);
    printf("Others,%d\n", others);

    return 0;
    return 0;
}
