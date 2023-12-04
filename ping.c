#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char c;
    // int fd_r = atoi(argv[1]);
    int out = open("out.txt", O_WRONLY);
    while(1) {
        if (read(0, &c, 1) <= 0) { // read from stdin
            break;
        }
        printf("%c", c); // write to stdout

        // this will block until the write pipe writes something
        if (read(7, &c, 1) <= 0) { // read from fd_r
            break;
        }
        if (write(out, &c, 1) <= 0) { // write to out.txt
            break;
        }
    }
    close(out);
    return 0;
}
