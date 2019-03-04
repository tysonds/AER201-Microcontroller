#include "balldispense.h"

/***************************** Public Functions ******************************/

const int delay_time = 2000;

void balldispense(openSide direc){
    switch(direc) {
        case LEFT:
            TRISEbits.RE0=0; //left solenoid for left trap door 1
            TRISEbits.RE1=0; //left solenoid for left trap door 2
            //first I will open and close left trap door 1
            LATEbits.LATE0=1; //open left trap door 1
            __delay_ms(delay_time); //I will determine the exact time later via testing
            LATEbits.LATE0=0; //close left trap door 1
            __delay_ms(delay_time); 
            LATEbits.LATE1=1; //open left trap door 2
            __delay_ms(delay_time);
            LATEbits.LATE1=0; //close left trap door 2 
            __delay_ms(delay_time);
            break;
        case RIGHT:
            TRISCbits.RC6=0; //right solenoid for right trap door 1
            TRISCbits.RC7=0; //right solenoid for right trap door 2
            //first I will open and close left trap door 1
            LATCbits.LATC6=1; //open right trap door 1
            __delay_ms(delay_time); //I will determine the exact time later via testing
            LATCbits.LATC6=0; //close right trap door 1
            __delay_ms(delay_time); 
            LATCbits.LATC7=1; //open right trap door 2
            __delay_ms(delay_time);
            LATCbits.LATC7=0; //close right trap door 2 
            __delay_ms(delay_time);
            break;
}
}
