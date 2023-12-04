#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char c;
    while (read(0, &c, 1) > 0) {
        printf("%c", c);
    }
    return 0;
}
