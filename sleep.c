

#include <xc.h>

//#define OSCILLATOR_CONFIG_REG             OSCCON
//#define OSCILLATOR_CONFIG_HFIOFS_bp       0x00U
//#define OSCILLATOR_CONFIG_LFIOFR_bp       0x01U
//#define OSCILLATOR_CONFIG_HFIOFR_bp       0x03U
//#define OSCILLATOR_CONFIG_IRCF_gp         0x04U
//#define OSCILLATOR_CONFIG_HFIOFS_bm       (0x01<<OSCILLATOR_CONFIG_HFIOFS_bp)
//#define OSCILLATOR_CONFIG_LFIOFR_bm       (0x01<<OSCILLATOR_CONFIG_LFIOFR_bp)
//#define OSCILLATOR_CONFIG_HFIOFR_bm       (0x01<<OSCILLATOR_CONFIG_HFIOFR_bp)
//#define OSCILLATOR_CONFIG_IRCF_16MHz_gm   (0x07<<OSCILLATOR_CONFIG_IRCF_gp)
//#define OSCILLATOR_CONFIG_IRCF_8MHz_gm    (0x06<<OSCILLATOR_CONFIG_IRCF_gp)
//#define OSCILLATOR_CONFIG_IRCF_4MHz_gm    (0x05<<OSCILLATOR_CONFIG_IRCF_gp)
//#define OSCILLATOR_CONFIG_IRCF_2MHz_gm    (0x04<<OSCILLATOR_CONFIG_IRCF_gp)
//#define OSCILLATOR_CONFIG_IRCF_1MHz_gm    (0x03<<OSCILLATOR_CONFIG_IRCF_gp)
//#define OSCILLATOR_CONFIG_IRCF_500kHz_gm  (0x02<<OSCILLATOR_CONFIG_IRCF_gp)
//#define OSCILLATOR_CONFIG_IRCF_250kHz_gm  (0x01<<OSCILLATOR_CONFIG_IRCF_gp)
//#define OSCILLATOR_CONFIG_IRCF_31kHz_gm   (0x00<<OSCILLATOR_CONFIG_IRCF_gp)
//
//#define REFERENCE_CLOCK_CONTROL_REG       CLKRCON
//#define REFERENCE_CLOCK_CONTROL_CLKROE_bp 0x06U
//#define REFERENCE_CLOCK_CONTROL_CLKROE_bm (0x01<<REFERENCE_CLOCK_CONTROL_CLKROE_bp)
//
//#define WATCHDOG_CONTROL_REG              WDTCON
//#define WATCHDOG_CONTROL_SWDTEN_bp        0x00U
//#define WATCHDOG_CONTROL_SWDTEN_bm        (0x01<<WATCHDOG_CONTROL_SWDTEN_bp)
//
#define FVR_CONTROL_REG                   FVRCON
//#define FVR_CONTROL_ADFVR_gp              0x00U
//#define FVR_CONTROL_TSRNG_bp              0x04U
//#define FVR_CONTROL_TSEN_bp               0x05U
//#define FVR_CONTROL_FVRRDY_bp             0x06U
//#define FVR_CONTROL_FVREN_bp              0x07U
//
#define VREG_CONTROL_REG                  VREGCON
//#define VREG_CONTROL_VREGPM1_bp           0x01U
//#define VREG_CONTROL_VREGPM1_bm           (0x01<<VREG_CONTROL_VREGPM1_bp)
//
#define ADC_CONTROL_REG                   ADCON
//#define ADC_CONTROL_ADON_bp               0x00U
//#define ADC_CONTROL_ADON_bm               (0x01<<ADC_CONTROL_ADON_bp)
//
//void Sleep_Select_Internal_8MHz_Oscillator(void){
//    OSCILLATOR_CONFIG_REG = OSCILLATOR_CONFIG_IRCF_8MHz_gm;
//    while((OSCILLATOR_CONFIG_REG & OSCILLATOR_CONFIG_HFIOFR_bm) == 0);
//    while((OSCILLATOR_CONFIG_REG & OSCILLATOR_CONFIG_HFIOFS_bm) == 0);
//}
//
//void Sleep_Disable_Reference_Clock_Output(void){
//    REFERENCE_CLOCK_CONTROL_REG &=~ REFERENCE_CLOCK_CONTROL_CLKROE_bm;
//}
//
//void Sleep_Disable_Watchdog(void){
//    WATCHDOG_CONTROL_REG &=~ WATCHDOG_CONTROL_SWDTEN_bm;
//}
//
//void Sleep_Disable_FVR(void){
//    FVR_CONTROL_REG = 0x00;
//}
//
//void Sleep_Enable_Voltage_Regulator_In_Low_Power_Mode(void){
//    VREG_CONTROL_REG = 0x02;
//}
//
//void Sleep_Disable_ADC(void){
//    ADC_CONTROL_REG = 0x00;
//}

/////////////update according to pin out///////////////
void Sleep_Unused_GPIO_Config(void){
    //TRISA &=~ 1;
    //WPUA &=~ 1;
    LATA &=~ 1;
}

void Sleep_Init(void){
    WPUA = (1<<3);       //weak pull-up on reset
//    Sleep_Select_Internal_8MHz_Oscillator();
//    Sleep_Disable_Reference_Clock_Output();
//    Sleep_Disable_Watchdog();
    ADC_CONTROL_REG = 0x00;
    FVR_CONTROL_REG = 0x00;
    VREG_CONTROL_REG = 0x02;
    Sleep_Unused_GPIO_Config();
}
