//#define _DEFAULT_SOURCE
#include <unistd.h>
#include <time.h>
#include <stdio.h>

int my_usleep_opt(long int microseconds){
    struct timespec req;
    if(microseconds < 1000000){
        req.tv_sec = 0;
        req.tv_nsec = microseconds * 1000;
    } else {
        req.tv_sec = microseconds / 1000000;
        req.tv_nsec = (microseconds % 1000000) * 1000;
    }
    return nanosleep(&req, NULL);
}

int my_usleep(long int microseconds){
    struct timespec req = {
        .tv_sec = microseconds / 1000000,
        .tv_nsec = (microseconds % 1000000) * 1000
    };
    return nanosleep(&req, NULL);
}

static inline int get_current_time(struct timespec *ts);
struct timespec get_duration(struct timespec *start, struct timespec *end);
void print_duration(struct timespec *ts);
void compare_durations(struct timespec *ts, struct timespec *expected);

int main(int argc, char **argv)
{
    if(argc < 3){
        fprintf(stderr, "Require two integer arguments: MICROSECONDS REPETITIONS\n");
        return 1;
    }

    int microseconds;
    if(sscanf(argv[1], "%d", &microseconds) != 1){
        fprintf(stderr, "Unable to parse '%s' as float\n", argv[1]);
        return 1;
    }
    int reps;
    if(sscanf(argv[2], "%d", &reps) != 1){
        fprintf(stderr, "Unable to parse '%s' as float\n", argv[2]);
        return 1;
    }
    long long unsigned int expected_nano = (microseconds * 1000) * reps;
    struct timespec expected = {
        .tv_sec = expected_nano / 1000000000,
        .tv_nsec = expected_nano % 1000000000
    };

    struct timespec t0,t1,t2,t3;
    get_current_time(&t0);
    for(int i = 0; i < reps ; i++){
        my_usleep(microseconds);
    }
    get_current_time(&t1);
    for(int i = 0; i < reps ; i++){
        usleep(microseconds);
    }
    get_current_time(&t2);
    for(int i = 0; i < reps ; i++){
        my_usleep_opt(microseconds);
    }
    get_current_time(&t3);

    fprintf(stderr, "=================================================\n");
    fprintf(stderr, "my_usleep: ");
    struct timespec d1 = get_duration(&t0, &t1);
    print_duration(&d1);
    compare_durations(&d1, &expected);
    fprintf(stderr, "=================================================\n");
    fprintf(stderr, "usleep: ");
    struct timespec d2 = get_duration(&t1, &t2);
    print_duration(&d2);
    compare_durations(&d2, &expected);
    fprintf(stderr, "=================================================\n");
    fprintf(stderr, "my_usleep_opt: ");
    struct timespec d3 = get_duration(&t2, &t3);
    print_duration(&d3);
    compare_durations(&d3, &expected);

    fprintf(stderr, "=================================================\n");
    fprintf(stderr, "Difference |usleep - my_usleep|: ");
    struct timespec d4 = get_duration(&d1, &d2);
    if(d4.tv_sec < 0){
        struct timespec d5 = get_duration(&d2, &d1);
        print_duration(&d5);
    } else {
        print_duration(&d4);
    }


    return 0;
}

static inline int get_current_time(struct timespec *ts){
    return clock_gettime(CLOCK_MONOTONIC, ts);
}

struct timespec get_duration(struct timespec *start, struct timespec *end){
    int seconds = end->tv_sec - start->tv_sec;
    int nanoseconds = end->tv_nsec - start->tv_nsec;
    if(nanoseconds < 0){
        nanoseconds += 1000000000;
        seconds -= 1;
    }
    return (struct timespec){.tv_sec = seconds, .tv_nsec = nanoseconds };
}
void compare_durations(struct timespec *ts, struct timespec *expected)
{
    float microseconds = 1000000 * ts->tv_sec + ts->tv_nsec / 1000.0;
    float expected_microseconds = 1000000 * expected->tv_sec + expected->tv_nsec / 1000.0;
    float difference = microseconds - expected_microseconds;
    float diff_percent = (difference*100)/expected_microseconds;
    printf("Expected %.2fus, got %.2fus, difference is %.2fus(%.1f%%)\n", expected_microseconds, microseconds, difference, diff_percent);
}
void print_duration(struct timespec *ts){
    float milliseconds = 1000 * ts->tv_sec + ts->tv_nsec / 1000000.0;
    fprintf(stderr, "sec: %ld, nsec: %ld, (ms: %f)\n", ts->tv_sec, ts->tv_nsec, milliseconds);
}
