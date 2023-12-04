#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int p1[2];
    pipe(p1);

    int p2[2];
    pipe(p2);
    printf("%d, %d\n", p1[0], p1[1]);
    printf("%d, %d\n", p2[0], p2[1]);

    if (fork() == 0) {
        close(0);
        open("bruh.json", O_RDONLY);

        close(1);
        dup(p1[1]);

        close(7);
        dup(p2[0]);

        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execl("ping",  NULL);
    }
    if (fork() == 0) {
        // redirect stdin to p1[0]
        close(0);
        dup(p1[0]);

        // redirect stdout to pipe write 2
        close(1);
        dup(p2[1]);

        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execl("pong", NULL);
    }

    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);

    wait(0);
    wait(0);

    exit(0);
}
