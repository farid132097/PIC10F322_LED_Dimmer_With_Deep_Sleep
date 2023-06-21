/* 
 * File:   pwm.h
 * Author: faridmdislam@gmail.com
 * PIC10F322 PWM library
 * Created on May 5, 2023, 5:22 PM
 */

uint8_t PWM_Get_Execution_Status(void);
void    PWM_Set_Execution_Status(void);
void    PWM_Clear_Execution_Status(void);

void    PWM_Set_Duty(uint32_t duty);
void    PWM_Enable(void);
void    PWM_Disable(void);
void    PWM_On_20_Percent_Duty_Cycle(void);
void    PWM_On_50_Percent_Duty_Cycle(void);
void    PWM_On_100_Percent_Duty_Cycle(void);
void    PWM_Off(void);

