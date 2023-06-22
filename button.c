
#define  _XTAL_FREQ 8000000
#include <xc.h>
#include "pwm.h"

//#define BUTTON_HARDWARE_DEBOUNCE_PRESENT
#define BUTTON_DEBOUNCE_NOP_CYCLES     100
#define BUTTON_MAX_STATE               4U
#define BUTTON_STATE_SYSTEM_SLEEP      0U
#define BUTTON_STATE_20_PERCENT_DUTY   1U
#define BUTTON_STATE_50_PERCENT_DUTY   2U
#define BUTTON_STATE_100_PERCENT_DUTY  3U

#define BUTTON_TRIS                    TRISA
#define BUTTON_LAT                     LATA
#define BUTTON_ANSEL                   ANSELA
#define BUTTON_bp                      0x00U
#define BUTTON_bm                      (0x01<<BUTTON_bp)

#define PCI_RISING_EDGE_REG            IOCAP
#define PCI_FALLING_EDGE_REG           IOCAN
#define PCI_FLAG_REG                   IOCAF
#define INTTERRUPT_CONTROLLER_REG      INTCON
#define INTTERRUPT_CONTROLLER_IOCIF_bp 0x00U
#define INTTERRUPT_CONTROLLER_INTF_bp  0x01U
#define INTTERRUPT_CONTROLLER_IOCIE_bp 0x03U
#define INTTERRUPT_CONTROLLER_INTE_bp  0x04U
#define INTTERRUPT_CONTROLLER_PEIE_bp  0x06U
#define INTTERRUPT_CONTROLLER_GIE_bp   0x07U
#define INTTERRUPT_CONTROLLER_IOCIF_bm (0x01<<INTTERRUPT_CONTROLLER_IOCIF_bp)
#define INTTERRUPT_CONTROLLER_INTF_bm  (0x01<<INTTERRUPT_CONTROLLER_INTF_bp)
#define INTTERRUPT_CONTROLLER_IOCIE_bm (0x01<<INTTERRUPT_CONTROLLER_IOCIE_bp)
#define INTTERRUPT_CONTROLLER_INTE_bm  (0x01<<INTTERRUPT_CONTROLLER_INTE_bp)
#define INTTERRUPT_CONTROLLER_PEIE_bm  (0x01<<INTTERRUPT_CONTROLLER_PEIE_bp)
#define INTTERRUPT_CONTROLLER_GIE_bm   (0x01<<INTTERRUPT_CONTROLLER_GIE_bp)

volatile uint8_t Button_State = 0, sleep_mode=0, button_functions_executed=0;

void Button_Init(void){
    TRISA =(1<<2);
    ANSELA=0x00;
    INTCON = 0;          //Clear
    OPTION_REG&=~0xC0;   //INTEDG
    INTCON=0x90;         //INTE, GIE
}

void Button_Set_Sleep_Mode(void){
    sleep_mode = 1;
}

void Button_Set_Active_Mode(void){
    sleep_mode = 0;
}

uint8_t Button_Get_State(void){
    return Button_State;
}

uint8_t Button_Get_Sleep_Mode(void){
    return sleep_mode;
}


void Button_ISR_Executables(void){
    if(INTCON & (1<<1)){
        __delay_ms(10);
        if((PORTA & 0x04) == 0 ){
            Button_State++;
            if(Button_State>3){
                Button_State=0;
            }
            button_functions_executed=0;
        }
        while( (PORTA & 0x04) == 0 );
        __delay_ms(10);
        
        if(button_functions_executed==0){
            if(Button_Get_State()==0){
                PWM_Off();
                Button_Set_Sleep_Mode();
            }else{
                Button_Set_Active_Mode();
                PWM_Disable();
                PWM_Enable();
                if(Button_Get_State() == 1){
                    PWM_On_20_Percent_Duty_Cycle();
                }else if(Button_Get_State() == 2){
                    PWM_On_50_Percent_Duty_Cycle();
                }else if(Button_Get_State() == 3){
                    PWM_On_100_Percent_Duty_Cycle();
                }
            }
            button_functions_executed=1;
        }
        
        
        INTCON&=~0x02;
    }
}