#ifndef CMOS_H
#define CMOS_H

#include <klibc/time.h>

/* Reads the current date and time from the CMOS RTC registers into a tm struct */
void cmos_read_rtc(struct tm *timeptr);

#endif