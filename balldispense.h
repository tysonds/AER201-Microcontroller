/*
 * File:   balldispense.h
 * Author: tyson
 *
 * Created on February 21, 2019, 6:07 PM
 */

#ifndef BALLDISPENSE_H
#define	BALLDISPENSE_H

#include <stdlib.h>
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "configBits.h"


typedef enum openSide {LEFT,RIGHT} openSide;

void balldispense(openSide direc);


#endif	/* BALLDISPENSE_H */



