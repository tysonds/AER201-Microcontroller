/* 
 * File:   motors.h
 * Author: tyson
 *
 * Created on February 21, 2019, 4:45 PM
 */



#ifndef MOTORS_H
#define	MOTORS_H

#include <stdlib.h>
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "configBits.h"

typedef enum motorDirection {FORWARD,BACKWARD,STOPMOTOR} motorDirection;

void motorControl(motorDirection dir);

#endif	/* MOTORS_H */

