#ifndef UNISTD_H
#define UNISTD_H

#include <klibc/stdint.h>

/* Suspends execution for a specified number of milliseconds */
void msleep(uint32_t msec);

/* Suspends execution for a specified number of seconds */
unsigned int sleep(unsigned int seconds);

/* Returns total seconds since system boot */
uint32_t get_uptime_s(void);

/* Returns total milliseconds since system boot */
unsigned int get_uptime_ms(void);

#endif