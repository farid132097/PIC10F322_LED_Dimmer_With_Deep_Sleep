

#include <xc.h>

#define PWM_TRIS  TRISA
#define PWM_LAT   LATA
#define PWM_ANSEL ANSELA
#define PWM_bp    0x01U

volatile uint8_t executed=0;

uint8_t PWM_Get_Execution_Status(void){
    return executed;
}

void PWM_Set_Execution_Status(void){
    executed=1;
}

void PWM_Clear_Execution_Status(void){
    executed=0;
}

void PWM_Set_Duty(uint32_t duty){
    duty*=1023;
    duty/=100;
    uint16_t temp=duty;
    temp&=0x3FF;
    PWM2DCH=(temp>>2);
    PWM2DCL=(temp&0x03)<<6;
}

void PWM_Enable(void){
    PWM_LAT   &=~ (1<<1);
    PWM_TRIS  |= (1<<1);
    PWM_ANSEL |= (1<<1);
    PWM2CON = (1<<6)|(1<<7);
    PWM2DCH = 0x7F;
    PWM2DCL = 0xC0;
    PR2   = 0xFF;
    TMR2  = 0x00;
    PIR1 &=~ (1<<1);
    T2CON = (1<<2);
    PWM_TRIS  &=~ (1<<1);
}

void PWM_Disable(void){
    PWM_TRIS  |= (1<<1);
    PWM2CON = 0;
    T2CON = 0;
    PR2   = 0;
    TMR2  = 0;
    PWM2DCH = 0;
    PWM2DCL = 0;
    PWM_LAT   &=~ (1<<1);
    PWM_ANSEL &=~ (1<<1);
    PWM_TRIS  &=~ (1<<1);
}

void PWM_On_20_Percent_Duty_Cycle(void){
    //if(PWM_Get_Execution_Status()==0){
        //PWM_Disable();
        //PWM_Enable();
        PWM_Set_Duty(20);
        //PWM_Set_Execution_Status();
    //}
}

void PWM_On_50_Percent_Duty_Cycle(void){
    //if(PWM_Get_Execution_Status()==0){
        //PWM_Disable();
        //PWM_Enable();
        PWM_Set_Duty(50);
        //PWM_Set_Execution_Status();
    //}
}

void PWM_On_100_Percent_Duty_Cycle(void){
    //if(PWM_Get_Execution_Status()==0){
        //PWM_Disable();
        //PWM_Enable();
        PWM_Set_Duty(95);
        //PWM_Set_Execution_Status();
    //}
}

void PWM_Off(void){
    //if(PWM_Get_Execution_Status()==0){
        PWM_Disable();
        //PWM_Set_Execution_Status();
    //}
}