#include "mcc_generated_files/mcc.h"
#include "LCD.h"
#include "LCD4Bit.h"
#include "math.h"
#include <stdio.h>
#include <string.h>


struct LCD theLCD;
double time;
double Lap_time;
uint16_t ms=0;
uint16_t s=0;
bool start=0;

//functions
void steup_LCD(char x [10],char y [10]);
void LCD_printplz(char x [10],char y [16]);
void timer_callback();
void timer_start_restart();
void timer_record_lap();


void main(void){
    SYSTEM_Initialize();
    INTERRUPT_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    TMR2_Initialize();
    TMR2_SetInterruptHandler(timer_callback);
    IOCAF4_SetInterruptHandler(timer_start_restart);
    IOCAF5_SetInterruptHandler(timer_record_lap);
    __delay_ms(200);
    steup_LCD("FinalProject:338","Timer Start?");
    while (start==0){};
    TMR2_Start();
    while(1){         
        char str1[16];
        char str2[16];                         
        time = (ms/1000.00) + s;
        sprintf(str1, "Time: %.3fs",time);
        sprintf(str2, "Lap1: %.3fs",Lap_time); 
        LCD_printplz(str1,str2);
    }        
}



void timer_callback()
{
    ms= ms+1;
    if(ms >= 1000){
        ms= ms-1000;
        s=s+1;
    }
}

void timer_start_restart()
{
    if(start==0){
        start=1;
    }
    else if (start==1){
        time     = 0;
        s        = 0;
        ms       = 0;
        Lap_time = 0;
    }
}

void timer_record_lap()
{
    Lap_time=time;
}

void steup_LCD(char x [10],char y [10]){
    // if error, then use the following code
    PORTD = 0;
    ANSELD = 0;
    TRISD = 0;
    LCD_initParallel(&theLCD, LCD_4BITMODE, &LATD, &LATD, 7, 6);
    LCD_begin(&theLCD, 16, 2, LCD_5x8DOTS);
    LCD_clear(&theLCD);
    LCD_home(&theLCD);
    LCD_setCursor(&theLCD, 0, 0);
    LCD_printString(&theLCD, x);
    LCD_setCursor(&theLCD, 0, 1);
    LCD_printString(&theLCD, y);
    __delay_ms(200);
}

void LCD_printplz(char x [10],char y [16]){
    // if error, then use the following code
    LCD_clear(&theLCD);
    LCD_home(&theLCD);
    LCD_setCursor(&theLCD, 0, 0);
    LCD_printString(&theLCD, x);
    LCD_setCursor(&theLCD, 0, 1);
    LCD_printString(&theLCD, y);
}

