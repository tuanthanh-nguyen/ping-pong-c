#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int DURATION = 2;

int main() {
    int p1[2];
    pipe(p1);

    int p2[2];
    pipe(p2);

    int fd1 = open("out1.txt", O_WRONLY);
    int fd2 = open("out2.txt", O_WRONLY);

    int ps1, ps2;

    if (ps1 = fork() == 0) {
        // close the redundant fd
        close(p1[0]);
        close(p2[1]);

        char c;
        while(write(p1[1], "a", 1) > 0) {
            read(p2[0], &c, 1);
            write(fd1, &c, 1);
        }
        close(p1[1]);
        close(p2[0]);
        close(fd1);
        exit(0);
    }
    if (ps2 = fork() == 0) {
        // close the redundant fd
        close(p1[1]);
        close(p2[0]);

        char c;
        int fd = open("out2.txt", O_WRONLY);
        while(read(p1[0], &c, 1) > 0) {
            write(fd2, &c, 1);
            write(p2[1], "b", 1);
        }
        close(p1[0]);
        close(p2[1]);
        close(fd2);
        exit(0);
    }

    // close the redundant fds in parent process
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);

    // duration set in seconds
    sleep(DURATION);

    kill(p1, 1);
    kill(p2, 1);

    off_t offset1 = lseek(fd1, 0, SEEK_CUR);
    printf("written to out1.txt %lld bytes\n", (long long)offset1);

    off_t offset2 = lseek(fd1, 0, SEEK_CUR);
    printf("written to out2.txt %lld bytes\n", (long long)offset2);

    close(fd1);
    close(fd2);

    exit(0);
}

