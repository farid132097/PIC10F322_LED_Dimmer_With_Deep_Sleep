

#include <xc.h>

#define PWM_TRIS  TRISA
#define PWM_LAT   LATA
#define PWM_ANSEL ANSELA
#define PWM_bp    2U


void PWM_Init(void){
    PWM_TRIS &=~ (1<<PWM_bp);
    PWM_ANSEL &=~ (1<<PWM_bp);
    PWM_LAT &=~ (1<<PWM_bp);
}

void PWM_On_20_Percent_Duty_Cycle(void){
    PWM_LAT |= (1<<PWM_bp);
}

void PWM_On_50_Percent_Duty_Cycle(void){
    PWM_LAT |= (1<<PWM_bp);
}

void PWM_On_100_Percent_Duty_Cycle(void){
    PWM_LAT |= (1<<PWM_bp);
}

void PWM_Off(void){
    PWM_LAT &=~ (1<<PWM_bp);
}