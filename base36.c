#include <stdio.h>
#include <time.h>

#define NS_PER_S 1000000000L

struct timespec ts_subtract(struct timespec time1, struct timespec time2);

int main()
{
    int c;

    long dt;
    struct timespec ts_now, ts_last;
    clock_gettime(CLOCK_REALTIME, &ts_last);
    
    for (;;) {
        clock_gettime(CLOCK_REALTIME, &ts_now);
        dt = ts_subtract(ts_now, ts_last).tv_nsec;
        ts_last = ts_now;

        c = getc(stdin);

        if (c == EOF) break;
        else if (c >= '0' && c <= '9') c -= '0';
        else if (c >= 'a' && c <= 'z') c -= 'a' - 10;
        else if (c >= 'A' && c <= 'Z') c -= 'A' - 10;
        else continue;

        c = c * 255 / 35;

        putc((unsigned char) c, stdout);

        fprintf(stderr, "\r%ld Hz     \t", (NS_PER_S/dt));
    }
    return 0;
}

struct timespec ts_subtract(struct timespec time1, struct timespec time2)
{
    struct timespec result;
    result.tv_sec = time1.tv_sec - time2.tv_sec;
    if (time1.tv_nsec < time2.tv_nsec) {
        result.tv_nsec = time1.tv_nsec + NS_PER_S - time2.tv_nsec;
        result.tv_sec--;
    } else {
        result.tv_nsec = time1.tv_nsec - time2.tv_nsec;
    }

    return (result);
}
