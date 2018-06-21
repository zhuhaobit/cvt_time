#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
    time_t curr_time;
    struct tm *curr_local_time = NULL;
    unsigned int year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
    struct timeval tp;

    double input;
    long sec;
    long usec;

    if (argc != 2)
    {
        printf("Usage: cvt_time <second>.\n");
        return 0;
    }

    input = atof(argv[1]);
    sec = (int64_t) input;
    usec = (int64_t) ((input - sec) * 1000000);

    tp.tv_sec = (time_t) sec;
    tp.tv_usec = (suseconds_t) usec;

    //curr_time = time(&curr_time);
    //uos_assert(curr_time != -1);
    curr_local_time = localtime(&tp);
    year = curr_local_time->tm_year + 1900;
    month = curr_local_time->tm_mon + 1;
    day = curr_local_time->tm_mday;
    hour = curr_local_time->tm_hour;
    minute = curr_local_time->tm_min;
    second = curr_local_time->tm_sec;

    printf("%04d%02d%02d %02d:%02d:%02d.%3d\n",
            year, month, day, hour, minute, second, usec / 1000);

    return 0;
}
