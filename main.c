/*
 * File:   main.c
 * Author: faridmdislam@gmail.com
 * PIC10F322 Based LED Dimmer and Low Power Deep Sleep mode
 * Created on May 5, 2023, 3:47 PM
 */

#define _XTAL_FREQ 8000000

#include <xc.h>
#include "configbits.h"
#include "button.h"
#include "sleep.h"
#include "pwm.h"

void main(void) {
    
    Button_Init();
    Sleep_Init();
    PWM_Clear_Execution_Status();
    
    while(1){
        
        if(Button_Get_Sleep_Mode()==1){
            SLEEP();
        }
        
    }
}

void interrupt ISRs(void){
    Button_ISR_Executables();
}
