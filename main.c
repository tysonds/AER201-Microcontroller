

#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "configBits.h"
#include "lcd.h"
#include "motors.h"
#include <stdlib.h>
#include "balldispense.h"
#include "getdata.h"
#include "rtc.h"
#include "I2C.h"


const char msg_start1[] = "PRESS KEY";
const char msg_start2[] = "TO START";

const char msg_wait[] = "WAIT ...";
const char msg_run_in_progress[] = "RUN IN PROGRESS";
const char msg_run_complete[] = "RUN COMPLETE";

const char msg_press1_1[] = "PRESS 1 FOR";
const char msg_press1_2[] = "OPERATION TIME";

const char msg_press2_1[] = "PRESS 2 FOR";
const char msg_press2_2[] = "# CANISTERS";

const char msg_press3_1[] = "PRESS 3 FOR";
const char msg_press3_2[] = "# DISPENSED";

const char msg_press4_1[] = "PRESS 4 FOR";
const char msg_press4_2[] = "CAN. DISTS.";

const char msg_press5_1[]="PRESS 5 FOR";
const char msg_press5_2[]="# SUPPLIED";

const char msg_press6_1[]="PRESS 6 FOR";
const char msg_press6_2[]="TOT. DIST.";

volatile bool key_was_pressed = false;
volatile bool run_complete=false; 
void main(void){
     // RD2 is the character LCD RS
    // RD3 is the character LCD enable (E)
    // RD4-RD7 are character LCD data lines
    LATD = 0x00;
    TRISD = 0x00;
    
    // Set all A/D ports to digital (pg. 222)
    ADCON1 = 0b00001111;
    
    // Enable RB1 (keypad data available) interrupt
    INT1IE = 1;
    
    // Initialize LCD
    initLCD();
    
    // Enable interrupts
    ei();
    
    bool any_key_is_pressed=false; 
    volatile float operation_time; 
    int start_time=0;
    while (1){
        if (key_was_pressed){
            key_was_pressed=false;
            if (!any_key_is_pressed){
                any_key_is_pressed=true;
                
            }
            else if (!run_complete){
                lcd_clear();
                lcd_set_ddram_addr(LCD_LINE2_ADDR); printf("%s", msg_run_in_progress);
            }
        }
   
        if (run_complete){
            lcd_clear()
            lcd_set_ddram_addr(LCD_LINE2_ADDR); printf("JOSH IS");
            lcd_set_ddram_addr(LCD_LINE3_ADDR); printf("A BITCH");
            while (1){
            }
            }
    
        if (any_key_is_pressed){
            motorControl(FORWARD);
            __delay_ms(10000);
            motorControl(STOPMOTOR);
            __delay_ms(100);
            motorControl(BACKWARD);
            __delay_ms(10000);
            motorControl(STOPMOTOR);
            run_complete=true;
            any_key_is_pressed=false; 
     }
    }
}
   

/**
 * @brief Any time an interrupt is generated, the microcontroller will execute
 *        this function (as long as interrupts are enabled). Any interrupts
 *        which are enabled need to be handled in this function, otherwise
 *        unexpected behavior will arise, perhaps even causing the PIC to reset
 *        (you AT LEAST need to clear the flag for each interrupt which is
 *        enabled!)
 */


void __interrupt() interruptHandler(void){
    // Interrupt on change handler for RB1
    if(INT1IF){
        // Notice how we keep the interrupt processing very short by simply
        // setting a "flag" which the main program loop checks
        key_was_pressed = true;
        INT1IF = 0; // Clear interrupt flag bit to signify it's been handled
    }
}