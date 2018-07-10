#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <string.h>
#include <time.h>

typedef struct Date_Time
{
    unsigned int year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
    unsigned long usec;
} date_time_t;

void cvt_ts_2_date(double ts, date_time_t* date_time)
{
    long sec;
    long usec;

    sec = (int64_t) ts;
    usec = (int64_t) ((ts - sec) * 1000000);
    
    time_t tp = (time_t) sec;
    struct tm *curr_local_time = NULL;
    curr_local_time = localtime(&tp);
    date_time->year = curr_local_time->tm_year + 1900;
    date_time->month = curr_local_time->tm_mon + 1;
    date_time->day = curr_local_time->tm_mday;
    date_time->hour = curr_local_time->tm_hour;
    date_time->minute = curr_local_time->tm_min;
    date_time->second = curr_local_time->tm_sec;
    date_time->usec = usec;
}

void cvt_date_2_ts(date_time_t date_time, double *ts)
{
    time_t tp;
    struct tm curr_local_time;
    curr_local_time.tm_year = date_time.year - 1900;
    curr_local_time.tm_mon = date_time.month - 1;
    curr_local_time.tm_mday = date_time.day;
    curr_local_time.tm_hour = date_time.hour;
    curr_local_time.tm_min = date_time.minute;
    curr_local_time.tm_sec = date_time.second;
    tp = mktime(&curr_local_time);

    *ts = (double)tp + (double)date_time.usec/1000000;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: cvt_ts_to_date <second>.\n");
        return 0;
    }

    /* convert time to date */
    double input = atof(argv[1]);
    date_time_t curr_date;
    cvt_ts_2_date(input, &curr_date);
    printf("%04d%02d%02d %02d:%02d:%02d.%03d\n",
            curr_date.year, curr_date.month, curr_date.day,
            curr_date.hour, curr_date.minute, curr_date.second,
            curr_date.usec / 1000);

    /* convert date to time */
    double curr_time;
    cvt_date_2_ts(curr_date, &curr_time);
    printf("%f\n", curr_time);

    return 0;
}
