#include <klibc/time.h>
#include <drivers/cmos.h>
#include <drivers/pit.h>

static char time_str_buffer[26];
static const char* days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
static const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

clock_t clock(void) { return (clock_t)pit_get_ticks(); }

double difftime(time_t end, time_t beginning) { return (double)(end - beginning); }

time_t time(time_t* timer)
{
    struct tm now;
    cmos_read_rtc(&now);
    
    time_t seconds = (time_t)now.sec + (now.min * 60) + (now.hour * 3600) + (now.yday * 86400) + ((now.year - 2000) * 31536000);
    
    if (timer) *timer = seconds;
    return seconds;
}

static const char* get_day_suffix(int day) {
    if (day >= 11 && day <= 13) return "th";
    switch (day % 10) {
        case 1:  return "st";
        case 2:  return "nd";
        case 3:  return "rd";
        default: return "th";
    }
}

void print_date(void)
{
	struct tm now;
    cmos_read_rtc(&now);
	kprintf("%s %s %d%s, %02d:%02d UTC\n", days[now.wday], months[now.mon], now.mday, get_day_suffix(now.mday), now.hour, now.min);
}