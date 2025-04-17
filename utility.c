#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// parse ddmmyyyy into tm struct
/*
struct tm *parse_date(char *date) {
    // create empty static tm struct
    static struct tm tm = {0};

    // populate integer variables with date values
    int day, month, year;
    sscanf(date, "%2d%2d%4d", &day, &month, &year);

    // update tm struct from date values
    tm.tm_mday = day;
    tm.tm_mon  = month - 1;     // tm_mon is 0-based
    tm.tm_year = year - 1900;   // tm_year is years since 1900
                                //
    // normalise any invalid dates
    time_t t = mktime(&tm);

    // ensure fully populated, then return
    struct tm *computed_tm = localtime(&t);
    return computed_tm;
}
*/

// put date (ddmmyyyy) in buffer
void get_date(char *buffer, size_t size) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buffer, size, "%d%m%Y", tm);
}

// put next date (ddmmyyyy) in buffer from an input date
/*
void get_next_date(char *buffer, size_t size, char *date) {
    struct tm *tm = parse_date(date);
    time_t t = mktime(tm);
    t += 86400; // add 1 day in seconds
    tm = localtime(&t);
    strftime(buffer, size, "%d%m%Y", tm);
}
*/

// put weekday in buffer from input date
/*
void get_weekday(char *buffer, size_t size, char *date) {
    struct tm *tm = parse_date(date);
    strftime(buffer, size, "%a", tm);
}
*/

// returns number of days in a month
int days_in_month(int year, int month) {
    struct tm first_day = {0};
    first_day.tm_year = year - 1900;
    first_day.tm_mon = month + 1;
    first_day.tm_mday = 0;
    mktime(&first_day);
    return first_day.tm_mday;
}

// returns weekday offset (0 = Mon, ..., 6 = Sun)
int first_day_offset(int year, int month) {
    struct tm t = {0};
    t.tm_year = year - 1900;
    t.tm_mon = month;
    t.tm_mday = 1;
    mktime(&t);
    int wday = t.tm_wday;
    return (wday == 0) ? 6 : wday - 1;
}

// vim:set et sw=4 ts=4:
