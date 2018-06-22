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
        printf("Usage: cvt_date_to_ts <date time>.\n");
        return 0;
    }

    /* convert time to date */
    char buf1[16];
    char buf2[8];
    char buf3[8];
    char buf4[8];
    char buf5[8];
    sscanf(argv[1], "%[0-9] %[0-9]:%[0-9]:%[0-9].%[0-9]",
           buf1, buf2, buf3, buf4, buf5);

    date_time_t curr_date;
    int date = atoi(buf1);
    curr_date.year = date/10000;
    curr_date.month = (date%10000)/100;
    curr_date.day = (date%10000)%100;
    curr_date.hour = atoi(buf2);
    curr_date.minute = atoi(buf3);
    curr_date.second = atoi(buf4);
    curr_date.usec = atoi(buf5)*1000;

    double curr_ts;
    cvt_date_2_ts(curr_date, &curr_ts);
    printf("%04d%02d%02d %02d:%02d:%02d.%3d\n",
            curr_date.year, curr_date.month, curr_date.day,
            curr_date.hour, curr_date.minute, curr_date.second,
            curr_date.usec / 1000);
    printf("%f\n", curr_ts);

    return 0;
}