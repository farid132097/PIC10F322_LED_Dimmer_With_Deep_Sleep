/* 
 * File:   button.h
 * Author: faridmdislam@gmail.com
 * PIC10F322 button operations
 * Created on May 5, 2023, 5:23 PM
 */

void     Button_Init(void);
uint8_t  Button_Get_State(void);
uint8_t  Button_Interrupt_Fired(void);
void     Button_ISR_Executables(void);

