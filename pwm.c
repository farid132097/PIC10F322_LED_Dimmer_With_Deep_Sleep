

#include <xc.h>

#define PWM_TRIS  TRISA
#define PWM_LAT   LATA
#define PWM_ANSEL ANSELA
#define PWM_bp    0x01U

void PWM_Set_Duty(uint16_t duty){
    uint16_t temp=duty;
    temp&=0x3FF;
    PWM2DCL=(temp&0x03)<<6;
    PWM2DCH=(temp>>2);
}

void PWM_Enable(void){
    PWM_ANSEL &=~ (1<<PWM_bp);
    PWM_TRIS |= (1<<PWM_bp);
    PWM2CON   = 0x00;
    PR2       = 100;
    PWM_Set_Duty(20);
    PIR1 &=~ (1<<1);       //TMR2IF
    T2CON = (1<<0)|(1<<2); //Prescaler 4, TMRON
    PWM2CON = (1<<7);      //PWM2EN
    while((PIR1 & (1<<1)) == 0);
    PWM_TRIS &=~(1<<PWM_bp);
    PWM2CON |= (1<<6);     //PWM2OE
}

void PWM_Disable(void){
    PWM2CON   = 0x00;
    PR2       = 0;
    PWM_Set_Duty(0);
    T2CON = 0;
    PWM2CON = 0;
    PWM_TRIS &=~ (1<<PWM_bp);
    PWM_ANSEL &=~ (1<<PWM_bp);
    PWM_LAT &=~ (1<<PWM_bp);
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