

#include <xc.h>

#define PWM_TRIS  TRISA
#define PWM_LAT   LATA
#define PWM_ANSEL ANSELA
#define PWM_bp    0x01U

void PWM_Set_Duty(uint32_t duty){
    if(duty>100){
        duty=100;
    }else if(duty<0){
        duty=0;
    }
    duty*=1023;
    duty/=100;
    uint16_t temp=duty;
    temp&=0x3FF;
    PWM2DCL=(temp&0x03)<<6;
    PWM2DCH=(temp>>2);
}

void PWM_Enable(void){
    PWM_ANSEL|= (1<<PWM_bp);
    PWM_TRIS |= (1<<PWM_bp);
    PR2       = 0xFF;
    T2CON     = (1<<0)|(1<<2); //Prescaler 4, TMRON
    PIR1     &=~(1<<1);       //TMR2IF
    PWM2DCH   = 0xFF;
    PWM2DCL   = 0xC0;
    PWM2CON   = (1<<6)|(1<<7); 
    PWM_TRIS &=~(1<<PWM_bp);
}

void PWM_Disable(void){
    PWM_ANSEL&=~(1<<PWM_bp);
    PWM_TRIS &=~(1<<PWM_bp);
    PWM_LAT  &=~(1<<PWM_bp);
    PR2       = 0;
    T2CON     = 0;
    PIR1     &=~(1<<1);
    PWM2DCH   = 0;
    PWM2DCL   = 0;
    PWM2CON   = 0;
}

void PWM_On_20_Percent_Duty_Cycle(void){
    PWM_Enable();
    PWM_Set_Duty(20);
}

void PWM_On_50_Percent_Duty_Cycle(void){
    PWM_Enable();
    PWM_Set_Duty(50);
}

void PWM_On_100_Percent_Duty_Cycle(void){
    PWM_Enable();
    PWM_Set_Duty(99);
}

void PWM_Off(void){
    PWM_Disable();
}