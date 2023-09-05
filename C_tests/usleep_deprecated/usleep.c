
#include <unistd.h> // for usleep

void sleep_ms(int milliseconds){ // cross-platform sleep function
    if (milliseconds >= 1000)
      sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
}

int main(void)
{
    sleep_ms(1000);
    return 0;
}
