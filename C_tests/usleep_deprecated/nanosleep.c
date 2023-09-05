#include <time.h>   // for nanosleep

void sleep_ms(int milliseconds){ // cross-platform sleep function
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

int main(void)
{
    sleep_ms(1000);
    return 0;
}
