#include "rtc.h"


void rtc(void) {
    int i=0;
    
  /*  LATD = 0x00;
    TRISD = 0x00;
    
    I2C_Master_Init(100000);
    initLCD();
    while (1){
        timedifference(8595);
        
    } 
    */
    //rtc_get_time();
    
    
    // RD2 is the character LCD RS
    // RD3 is the character LCD enable (E)
    // RD4-RD7 are character LCD data lines
    LATD = 0x00;
    TRISD = 0x00;
    
    initLCD();

    // Initialize I2C Master with 100 kHz clock
    I2C_Master_Init(100000);
    
    // Set the time in the RTC. To see the RTC keep time, comment this line out
    // after programming the PIC directly before with this line included
    //rtc_set_time();
    
    // Main loop
    unsigned char time[7]; // Create a byte array to hold time read from RTC
    while(i<3){
        // Reset RTC memory pointer
        I2C_Master_Start(); // Start condition
        I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
        I2C_Master_Write(0x00); // Set memory pointer to seconds
        I2C_Master_Stop(); // Stop condition

        // Read current time
        I2C_Master_Start(); // Start condition
        I2C_Master_Write(0b11010001); // 7 bit RTC address + Read
        for(unsigned char i = 0; i < 6; i++){
            time[i] = I2C_Master_Read(ACK); // Read with ACK to continue reading
        }
        time[6] = I2C_Master_Read(NACK); // Final Read with NACK
        I2C_Master_Stop(); // Stop condition
        
        // Print received data on LCD
        lcd_home();
        printf("%02x/%02x/%02x", time[6],time[5],time[4]); // Print date in YY/MM/DD
        lcd_set_ddram_addr(LCD_LINE2_ADDR);
        printf("%02x:%02x:%02x", time[2],time[1],time[0]); // HH:MM:SS
        __delay_ms(1000);
        i=i+1;
    }  
    lcd_clear();
}

/** @brief Writes the happynewyear array to the RTC memory */
void rtc_set_time(void){
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b11010000); //7 bit RTC address + Write
    I2C_Master_Write(0x00); // Set memory pointer to seconds
    
    // Write array
    for(char i=0; i < 7; i++){
        I2C_Master_Write(happynewyear[i]);
    }
    
    I2C_Master_Stop(); //Stop condition
}

int rtc_get_time(void){
    
    // Set the time in the RTC. To see the RTC keep time, comment this line out
    // after programming the PIC directly before with this line included
    //rtc_set_time();
    
    // Main loop
    int total=0;
    unsigned char time[7]; // Create a byte array to hold time read from RTC
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b11010000); // 7 bit RTC address + Write
    I2C_Master_Write(0x00); // Set memory pointer to seconds
    I2C_Master_Stop(); // Stop condition
    // Read current time
    I2C_Master_Start(); // Start condition
    I2C_Master_Write(0b11010001); // 7 bit RTC address + Read
    for(unsigned char i = 0; i < 6; i++){
        time[i] = I2C_Master_Read(ACK); // Read with ACK to continue reading
        }
    time[6] = I2C_Master_Read(NACK); // Final Read with NACK
    I2C_Master_Stop(); // Stop condition
        
    // Print received data on LCD
    //lcd_home();
    //printf("%02x/%02x/%02x", time[2],time[1],time[0]);
    int t1=(int)time[2];
    int t2=(int)time[1];
    int t3=(unsigned int)time[0];
    t1=t1/16*10+t1%16;
    t2=t2/16*10+t2%16;
    t3=t3/16*10+t3%16;
   //lcd_set_ddram_addr(LCD_LINE2_ADDR);
   // printf("%d:%d:%d",t1,t2,t3);
    t1=t1-12;
    total=t1*3600+(t2*60)+t3;
    //lcd_set_ddram_addr(LCD_LINE4_ADDR);
    //printf("%d",total);
    return total;
}

int abs(int num){
    if (num<0){
        return (-1*num);}
    else{ return num;}
}

float timedifference(int initial_time_secs){
    int result=0;
    int timenow=0;
    timenow=rtc_get_time();
    result=abs((timenow-initial_time_secs));
    //lcd_set_ddram_addr(LCD_LINE4_ADDR);
    //printf("%d",result);
    return (float)result;    
}


