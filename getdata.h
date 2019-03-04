/* 
 * File:   getdata.h
 * Author: tyson
 *
 * Created on March 1, 2019, 12:05 PM
 */

#ifndef GETDATA_H
#define	GETDATA_H

#include <xc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "configBits.h"
#include "lcd.h"
#include "I2C.h"

unsigned char getdata(void);

void power_on(void);

void power_off(void);

#endif	/* GETDATA_H */

