#include <drivers/cmos.h>
#include <arch/i386/io.h>

#define CMOS_ADDR 0x70
#define CMOS_DATA 0x71

#define SECOND_LOC		0x00
#define MINUTE_LOC		0x02
#define HOUR_LOC 		0x04
#define MDAY_LOC		0x07
#define MONTH_LOC		0x08
#define YEAR_LOC		0x09
#define WDAY_LOC		0x06
#define STATUS_A_LOC 	0x0A // In progress
#define STATUS_B_LOC 	0x0B // 12 hour

static bool is_leap_year(int year) { return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)); }

static int is_update_in_progress()
{
    outb(CMOS_ADDR, STATUS_A_LOC);
    return (inb(CMOS_DATA) & 0x80);
}

static uint8_t get_rtc_register(int reg)
{
    outb(CMOS_ADDR, reg);
    return inb(CMOS_DATA);
}

static uint8_t bcd_to_bin(uint8_t bcd) { return ((bcd / 16) * 10) + (bcd & 0xf); }

void cmos_read_rtc(struct tm *timeptr)
{
    while (is_update_in_progress()) {}

	static const int days_in_months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    uint8_t second    = get_rtc_register(SECOND_LOC);
    uint8_t minute    = get_rtc_register(MINUTE_LOC);
    uint8_t hour      = get_rtc_register(HOUR_LOC);
    uint8_t mday      = get_rtc_register(MDAY_LOC);
    uint8_t month     = get_rtc_register(MONTH_LOC);
    uint8_t year   	  = get_rtc_register(YEAR_LOC);
	uint8_t wday 	  = get_rtc_register(WDAY_LOC);
    uint8_t registerB = get_rtc_register(STATUS_B_LOC);

    if (!(registerB & 0x04))
	{
        second = bcd_to_bin(second);
        minute = bcd_to_bin(minute);
        hour   = bcd_to_bin(hour);
        mday   = bcd_to_bin(mday);
        month  = bcd_to_bin(month);
        year   = bcd_to_bin(year);
		wday   = bcd_to_bin(wday);
    }

    if (!(registerB & 0x02) && (hour & 0x80)) hour = ((hour & 0x7F) + 12) % 24;

    timeptr->sec  = (int)second;
    timeptr->min  = (int)minute;
    timeptr->hour = (int)hour;
    timeptr->mday = (int)mday;
    timeptr->mon  = (int)month;
    timeptr->year = (int)year + 2000;
	timeptr->wday = (int)wday;

    timeptr->yday = 0;
    for (int i = 0; i < timeptr->mon - 1; i++) timeptr->yday += days_in_months[i];
    if (timeptr->mon > 2 && is_leap_year(timeptr->year)) timeptr->yday += 1;
    timeptr->yday += (timeptr->mday - 1);

    timeptr->isdst = false; // Handle in userspace
}