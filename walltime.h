#ifndef WALLTIME_H
#define WALLTIME_H

#include <sys/time.h>

static inline unsigned long long walltime_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long long)tv.tv_sec * 1000
        +  (unsigned long long)tv.tv_usec / 1000;
}

static inline unsigned long long walltime_us(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long long)tv.tv_sec * 1000000
        +  (unsigned long long)tv.tv_usec;
}


#endif
