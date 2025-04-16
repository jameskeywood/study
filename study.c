#include <stdio.h>
#include <time.h>

// parse ddmmyyyy into tm struct
struct tm *parse_ddmmyyyy(char *date) {
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

// put date (ddmmyyyy) in buffer
void get_date(char *buffer, size_t size) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buffer, size, "%d%m%Y", tm);
}

// put next date (ddmmyyyy) in buffer from an input date
void get_next_date(char *buffer, size_t size, char *date) {
    struct tm *tm = parse_ddmmyyyy(date);
    time_t t = mktime(tm);
    t += 86400; // add 1 day in seconds
    tm = localtime(&t);
    strftime(buffer, size, "%d%m%Y", tm);
}

// put weekday in buffer from input date
void get_weekday(char *buffer, size_t size, char *date) {
    struct tm *tm = parse_ddmmyyyy(date);
    strftime(buffer, size, "%a", tm);
}

int main(void) {
    char date[9];
    get_date(date, sizeof(date));
    char weekday[4];
    get_weekday(weekday, sizeof(weekday), date);

    printf("Date: %s\n", date);
    printf("Weekday: %s\n", weekday);

    char next_date[9];
    get_next_date(next_date, sizeof(next_date), date); 
    char next_weekday[4];
    get_weekday(next_weekday, sizeof(next_weekday), next_date);

    printf("Next date: %s\n", next_date);
    printf("Next weekday: %s\n", next_weekday);

    return 0;
}

// vim:set et sw=4 ts=4:
