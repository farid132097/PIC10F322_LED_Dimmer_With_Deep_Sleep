
#include <xc.h>

//#define BUTTON_HARDWARE_DEBOUNCE_PRESENT
#define BUTTON_DEBOUNCE_NOP_CYCLES     10000
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

volatile uint8_t Button_State = 0;

void Button_Init(void){
    BUTTON_TRIS |=  BUTTON_bm;
    BUTTON_ANSEL&=~ BUTTON_bm;
    PCI_FALLING_EDGE_REG |= BUTTON_bm;
    if((INTTERRUPT_CONTROLLER_REG & INTTERRUPT_CONTROLLER_IOCIE_bm) == 0){
        INTTERRUPT_CONTROLLER_REG |= INTTERRUPT_CONTROLLER_IOCIE_bm;
    }
    if((INTTERRUPT_CONTROLLER_REG & INTTERRUPT_CONTROLLER_GIE_bm) == 0){
        INTTERRUPT_CONTROLLER_REG |= INTTERRUPT_CONTROLLER_GIE_bm;
    }
    if((INTTERRUPT_CONTROLLER_REG & INTTERRUPT_CONTROLLER_IOCIF_bm) == 0){
        INTTERRUPT_CONTROLLER_REG &=~ INTTERRUPT_CONTROLLER_IOCIF_bm;
    }
    if(PCI_FLAG_REG & BUTTON_bm){
        PCI_FLAG_REG &=~ BUTTON_bm;
    }
}

uint8_t Button_Get_State(void){
    return Button_State;
}

uint8_t Button_Interrupt_Fired(void){
    uint8_t status = 0;
    if(INTTERRUPT_CONTROLLER_REG & INTTERRUPT_CONTROLLER_IOCIF_bm){
        if(PCI_FLAG_REG & BUTTON_bm){
            status =1;
        }
    }
    return status;
}

void Button_ISR_Executables(void){
    if(Button_Interrupt_Fired()){
        #ifdef BUTTON_HARDWARE_DEBOUNCE_PRESENT
        // if a 100nF capacitor is present between button and GND 
        // do nothing
        #else
        // need a software debounce filter to prevent multiple interrupts
        for(uint16_t i=0; i<BUTTON_DEBOUNCE_NOP_CYCLES;i++){
            NOP(); 
        }
        #endif
        Button_State++;
        if(Button_State > (BUTTON_MAX_STATE - 1)){
            Button_State = 0;
        }
        PCI_FLAG_REG &=~ BUTTON_bm;
        INTTERRUPT_CONTROLLER_REG &=~ INTTERRUPT_CONTROLLER_IOCIF_bm;
    }
}