/* 
 * File:   rtc.h
 * Author: tyson
 *
 * Created on March 1, 2019, 12:17 PM
 */

#ifndef RTC_H
#define	RTC_H

#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "configBits.h"
#include "I2C.h"
#include "lcd.h"

const char happynewyear[7] = {
    0x00, // 0 Seconds 
    0x05, // 53 minutes
    0x16, // 24 hour mode, set to 3:00
    0x05, // Friday
    0x22, // 22nd
    0x02, // February
    0x19  // 2019
};

void rtc(void);

void rtc_set_time(void);

int rtc_get_time(void);

int abs(int num);

float timedifference(int initial_time_secs);

#endif	/* RTC_H */

