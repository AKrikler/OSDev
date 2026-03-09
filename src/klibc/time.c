#include <klibc/time.h>
#include <drivers/cmos.h>
#include <drivers/pit.h>

static char time_str_buffer[26];
static const char* days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
static const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

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