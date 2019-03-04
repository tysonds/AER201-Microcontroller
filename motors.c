
#include "motors.h"

/***************************** Public Functions ******************************/

void motorControl(motorDirection dir){
    //setting all the pins to outputs
    TRISCbits.RC0=0;
    TRISCbits.RC1=0;  
    TRISCbits.RC2=0;
    TRISCbits.RC5=0; 
    
    switch(dir) {
        case FORWARD:
            LATCbits.LATC0=1; //back wheel go forward
            LATCbits.LATC1=0; //back wheel not go backward
            LATCbits.LATC2=1; //front wheel go forward
            LATCbits.LATC5=0; //front wheel not go backward
            break;
        case BACKWARD:
            LATCbits.LATC0=0; //back wheel not go forward
            LATCbits.LATC1=1; //back wheel go backward
            LATCbits.LATC2=0; //front wheel not go forward
            LATCbits.LATC5=1; //front wheel go backward
            break;
        case STOPMOTOR:
            LATCbits.LATC0=0; //back wheel not go forward
            LATCbits.LATC1=0; //back wheel not go backward
            LATCbits.LATC2=0; //back wheel not go forward
            LATCbits.LATC5=0; //back wheel not go backward 
            break;            
    }
}

