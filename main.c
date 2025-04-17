#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

#include "utility.h"
#include "graphics.h"

// global variables due to interrupt code
time_t start_time;
time_t end_time;
int minutes = 0;
char subject[100];

// code will run after ctrl-c
void handle_interrupt(int sig) {
    // calculate elapsed minutes
    end_time = time(NULL);
    double seconds = difftime(end_time, start_time);
    minutes = (int)(seconds / 60);

    // get current date
    char date[9];
    get_date(date, sizeof(date));

    // append values to csv file
    // ~/.study/times.csv
    // if the file isn't there, create it!
    // <ddmmyyyy>,<subject>,<minutes>
    
    // make ~/.study directory if not already there
    const char *home = getenv("HOME");
    char dir_path[256];
    snprintf(dir_path, sizeof(dir_path), "%s/.study", home);
    mkdir(dir_path, 0755);  // does nothing if already exists

    // build path to ~/.study/times.csv
    char file_path[300];
    snprintf(file_path, sizeof(file_path), "%s/times.csv", dir_path);

    FILE *file;

    // check if times.csv exists
    // if not we need to create it and add first line
    if (access(file_path, F_OK) != 0) {
        file = fopen(file_path, "w");
        if (file) {
            fprintf(file, "date,subject,minutes\n");
            fclose(file);
        }
    }

    // append new entry to bottom of times.csv
    file = fopen(file_path, "a");
    if (file) {
        fprintf(file, "%s,%s,%d\n", date, subject, minutes);
        fclose(file);
    } else {
        perror("Failed to write to times.csv");
    }

    // output to user and exit program
    printf("\nStudy session ended\n");
    printf("%s: %d minutes\n", subject, minutes);
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
       printf("Usage:\n./study start <subject>\n./study view\n");
       return 1;
    }

    // ensure interrupt is ran on ctrl-c
    signal(SIGINT, handle_interrupt);

    if (strcmp(argv[1], "start") == 0 && argc == 3) {
        // save subject name to global variable
        strncpy(subject, argv[2], sizeof(subject) - 1);
        subject[sizeof(subject) - 1] = '\0'; // to ensure null termination
       
        // update start time and output to user 
        start_time = time(NULL);
        printf("Study session started\n");
        printf("Press Ctrl-C to end\n");

        // infinite loop until ctrl-c
        while (1) {}
    }
    else if (strcmp(argv[1], "view") == 0) {
        // Date info
        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        int year = tm_now->tm_year + 1900;
        int month = tm_now->tm_mon;

        int total_days = days_in_month(year, month);
        int offset = first_day_offset(year, month);
        draw_calendar(total_days, offset);
    }
    else {
        printf("Usage:\n./study start <subject>\n./study view\n");
    }

    /*
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
    */

    return 0;
}

// vim:set et sw=4 ts=4:
