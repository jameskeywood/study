#ifndef UTILITY_H
#define UTILITY_H

struct tm *parse_date(char *date);
void get_date(char *buffer, size_t size);
void get_next_date(char *buffer, size_t size, char *date);
void get_weekday(char *buffer, size_t size, char *date);

int days_in_month(int year, int month);
int first_day_offset(int year, int month);

#endif
