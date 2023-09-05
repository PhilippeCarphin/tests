#ifndef _POSIX_C_SOURCE
// #warning "_POSIX_C_SOURCE starts out undefined"
#include <stdlib.h>
#include <time.h>
#endif
#include <stdio.h>

/*
 * Funky thing with _POSIX_C_SOURCE.
 *
 * If no prior include is done, we go into the third branch so we #include
 * <unistd.h> but this causes _POSIX_C_SOURCE to become defined and it happens
 * to become defined to a value that is greater than 199309L.
 *
 * This causes us to go into the 2nd branch of '#ifdef ... #elif ... #else ...
 * #endif' inside sleep_ms().  But because we didn't include <time.h>, struc
 * timespec is not defined.
 *
 * This is why this file starts with #include <stdlib.h>.  It causes
 * _POSIX_C_SOURCE to be defined which causes to enter the same branch here and
 * in sleep_ms().
 */
#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds){ // cross-platform sleep function
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
    printf("%d\n", _POSIX_C_SOURCE);
}

int main(void)
{
    sleep_ms(1000);
    return 0;
}
