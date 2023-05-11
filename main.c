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
    
    //Button_Init();
    //Sleep_Init();
    
    PWM_On_20_Percent_Duty_Cycle();
    
    uint8_t val=100;
    while(1){
       
//        if(Button_Get_State() == 0){         //system sleep, pwm off
//            PWM_Off();
//            SLEEP();
//        }else if( Button_Get_State() == 1){  //pwm on 20% duty cycle
//            PWM_On_20_Percent_Duty_Cycle();
//        }else if( Button_Get_State() == 2){  //pwm on 50% duty cycle
//            PWM_On_50_Percent_Duty_Cycle();
//        }else if( Button_Get_State() == 3){  //pwm on 100% duty cycle
//            PWM_On_100_Percent_Duty_Cycle();
//        }
        
        val--;
        if(val<1){
            val=100;
        }
        PWM_Set_Duty(val);
        __delay_ms(100);
    }
    return;
}

void interrupt ISRs(void){
    Button_ISR_Executables();
}
