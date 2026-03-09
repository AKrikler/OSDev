#ifndef TIME_H
#define TIME_H

#include <klibc/stdint.h>
#include <klibc/stdbool.h>

typedef uint32_t time_t;   /* Seconds since epoch */
typedef uint32_t clock_t;  /* Processor time (ticks) */
typedef typeof(sizeof(0)) size_t;

#define CLOCKS_PER_SEC 100 /* Matches PIT frequency (100Hz) */
#define NULL (void*)0

/* Standard C structure for holding broken-down time */
struct tm
{
    int sec;   	/* Seconds [0, 60] */
    int min;   	/* Minutes [0, 59] */
    int hour;  	/* Hours [0, 23] */
    int mday;  	/* Day of month [1, 31] */
    int mon;   	/* Month [1, 12] */
    int year;  	/* Year (e.g., 2026) */
    int wday;  	/* Day of week [0, 6] (0 = Sunday) */
    int yday;  	/* Day of year [0, 365] */
    bool isdst;	/* Daylight Saving Time flag */
};

/* Returns the processor time consumed by the program (system ticks) */
clock_t clock(void);

/* Calculates the difference in seconds between two time_t values */
double difftime(time_t end, time_t beginning);

/* Returns the current calendar time as a time_t object */
time_t time(time_t* timer);

#endif