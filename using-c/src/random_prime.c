#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "util.h"

static int large_enough(unsigned long long i)
{
    return (i >= 1000000000000000000LLU);
}

int main(void)
{
    int err;
    int fd;
    unsigned long long i;
    fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        err = errno;
        fprintf(stderr, "Could not open /dev/urandom, %s\n",
            strerror(err));
        exit(EXIT_FAILURE);
    }
    do {
        do {
            read(fd, &i, sizeof(i));
            //fprintf(stderr, "STDERR generated %llu\n", i);
        } while (!large_enough(i));
        //fprintf(stderr, "STDERR testing %llu\n", i);
    } while (!is_prime(i));
    printf("%llu\n", i);
    close(fd);
    exit(EXIT_SUCCESS);
}
