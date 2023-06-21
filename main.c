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

uint8_t button_state=0;

void main(void) {
    
    Button_Init();
    Sleep_Init();
    
    while(1){
          
        if(Button_Get_Sleep_Mode()==0){
            if(!(PORTA & 0x04)){
                while( PORTA & 0x04){};
                
            }
        }else{
            PWM_Off();
            SLEEP();
        }
    }
}

void interrupt ISRs(void){
    Button_ISR_Executables();
}
