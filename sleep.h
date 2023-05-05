/* 
 * File:   sleep.h
 * Author: faridmdislam@gmail.com
 * PIC10F322 sleep library
 * Created on May 5, 2023, 5:22 PM
 */

void Sleep_Select_Internal_8MHz_Oscillator(void);
void Sleep_Disable_Reference_Clock_Output(void);
void Sleep_Disable_Watchdog(void);
void Sleep_Disable_FVR(void);
void Sleep_Enable_Voltage_Regulator_In_Low_Power_Mode(void);
void Sleep_Disable_ADC(void);
void Sleep_Init(void);

