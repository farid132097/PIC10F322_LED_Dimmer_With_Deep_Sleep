/*
 * File:   main.c
 * Author: faridmdislam@gmail.com
 * PIC10F322 Based LED Dimmer and Low Power Deep Sleep mode
 * Created on May 5, 2023, 3:47 PM
 */


#include <xc.h>
#include "configbits.h"
#include "button.h"
#include "sleep.h"
#include "pwm.h"


void main(void) {
    
    Button_Init();
    PWM_Init();
    Sleep_Init();
    
    while(1){
       
        if(Button_Get_State() == 0){         //system sleep, pwm off
            //disable pwm module
            //disable associated timer
        }else if( Button_Get_State() == 1){  //pwm on 20% duty cycle
            //check if pwm module is enabled
            //if not enabled, enable timer and pwm module
            //set duty cycle to 20%
        }else if( Button_Get_State() == 2){  //pwm on 50% duty cycle
            //check if pwm module is enabled
            //if not enabled, enable timer and pwm module
            //set duty cycle to 50%
        }else if( Button_Get_State() == 3){  //pwm on 100% duty cycle
            //check if pwm module is enabled
            //if not enabled, enable timer and pwm module
            //set duty cycle to 100%
        }
    }
    return;
}

void interrupt ISRs(void){
    Button_ISR_Executables();
}
