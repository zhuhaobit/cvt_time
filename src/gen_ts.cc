#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

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

vector<string> splitString(string str)
{
    istringstream ss(str);
    string s;
    vector<string> res;
    while (ss >> s)
        res.push_back(s);
    return res;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Usage: parse_string file" << endl;
        return -1;
    }
    const char* filename = argv[1];
    ifstream str_file(filename);
    FILE *fp_out = fopen("ml_lidar_ts", "w");
    string line;
    double curr_ts;
    date_time_t curr_date;
    if (str_file.is_open())
    {
        while (str_file.good())
        {
            getline(str_file, line);
            if (line.length() > 0)
            {
                vector<string> ret = splitString(line);
                cout << ret[0] << endl;
                istringstream iss(ret[0]);
                iss >> curr_ts;
                cvt_ts_2_date(curr_ts, &curr_date);
                fprintf(fp_out, "%04d%02d%02d %02d:%02d:%02d.%03d\n",
                        curr_date.year, curr_date.month, curr_date.day,
                        curr_date.hour, curr_date.minute, curr_date.second,
                        curr_date.usec / 1000);
            }
        }
    }

    return 0;
}
