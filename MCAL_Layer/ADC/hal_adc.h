/* 
 * File:   hal_adc.h
 * Author: Maghraby
 *
 * Created on May 31, 2022, 5:11 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H


/* Section: Includes*/
#include "hal_adc_cfg.h"
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"    
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"

/*Section: Macro Definitions*/
#define ADC_CONVERION_IN_PROGRESS                ((uint8_t)0x01)
#define ADC_CONVERION_COMPLETED_OR_IDLE          ((uint8_t)0x00)


/*Section: Function Like Macros*/
#define ADC_Converter_Module_Enabled()      (ADCON0bits.ADON = 1)
#define ADC_Converter_Module_Disabled()     (ADCON0bits.ADON = 0)

#define ADC_Start_Conversion()              (ADCON0bits.GO_nDONE = 1)

#define ADC_Is_Conversion_In_Progress()     (ADCON0bits.GO_nDONE)

#define ADC_Set_Voltage_Reference()         (ADCON1bits.VCFG1 = 1\
                                             ADCON1bits.VCFG0 = 1)

#define ADC_Enable_Voltage_Reference()         do{ADCON1bits.VCFG1 = 1;\
                                                  ADCON1bits.VCFG0 = 1;\
                                                }while(0)
#define ADC_Disable_Voltage_Reference()        do{ADCON1bits.VCFG1 = 0;\
                                                  ADCON1bits.VCFG0 = 0;\
                                                }while(0)

#define ADC_Select_Channel_Source(_Channel) (ADCON0bits.CHS = _Channel)/*
                                                                            @ref ADC_Select_Channels_t
                                                                        */    

#define ADC_Analog_Digital_Port_Config(_Config)   (ADCON1bits.PCFG = _Config) /*
                                                                                @ref  ADC_Config_Analog_Channels_t
                                                                              */

#define ADC_Select_Clock_Conversion(_Clock)       (ADCON2bits.ADCS = _Clock) /*
                                                                                @ref ADC_Clock_Conv_Select_t
                                                                             */

#define ADC_Select_Acquisition_Time(_Acq)         (ADCON2bits.ACQT = _Acq) /*
                                                                                @ref ADC_Acquisition_Time_t
                                                                             */  

#define ADC_Result_Right_Justified()               (ADCON2bits.ADFM = 1)
#define ADC_Result_Left_Justified()                (ADCON2bits.ADFM = 0)


/*Section: Data Type Declaration*/
typedef enum{
    ADC_CHANNEL_CH0 = 0,
    ADC_CHANNEL_CH1,
    ADC_CHANNEL_CH2,
    ADC_CHANNEL_CH3,
    ADC_CHANNEL_CH4,
    ADC_CHANNEL_CH5,
    ADC_CHANNEL_CH6,
    ADC_CHANNEL_CH7,
    ADC_CHANNEL_CH8,
    ADC_CHANNEL_CH9,
    ADC_CHANNEL_CH10,
    ADC_CHANNEL_CH11,
    ADC_CHANNEL_CH12
}ADC_Select_Channels_t;

typedef enum{
    ADC_ALL_CHANNELS_ANALOG = 0,
    ADC_ANALOG_CHANNEL_AN12 = 3, 
    ADC_ANALOG_CHANNEL_AN11,
    ADC_ANALOG_CHANNEL_AN10,
    ADC_ANALOG_CHANNEL_AN9,
    ADC_ANALOG_CHANNEL_AN8,
    ADC_ANALOG_CHANNEL_AN7,
    ADC_ANALOG_CHANNEL_AN6,
    ADC_ANALOG_CHANNEL_AN5,
    ADC_ANALOG_CHANNEL_AN4,
    ADC_ANALOG_CHANNEL_AN3,
    ADC_ANALOG_CHANNEL_AN2,
    ADC_ANALOG_CHANNEL_AN1,
    ADC_ANALOG_CHANNEL_AN0,            
}ADC_Config_Analog_Channels_t;

typedef enum{
    ADC_FOSC_DIV_2 = 0,
    ADC_FOSC_DIV_8,
    ADC_FOSC_DIV_32,
    ADC_FOSC_RC,
    ADC_FOSC_DIV_4,
    ADC_FOSC_DIV_16,
    ADC_FOSC_DIV_64
}ADC_Clock_Conv_Select_t;

typedef enum{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD            
}ADC_Acquisition_Time_t;

typedef enum{
    ADC_LEFT_JUSTIFIED = 0,
    ADC_RIGHT_JUSTIFIED
}ADC_Result_Format_t;
typedef enum{
    CONVERSION_IN_PROGRESS = 0,
    CONVERSION_COMPLETED
}Conversion_Status_t;
typedef struct{    
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
    void (*ADC_IntHandler)(void);
#endif
    #if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
    uint8_t priority;
    #endif
    ADC_Acquisition_Time_t acq_time;                    /*@ref ADC_Acquisition_Time_t */
    ADC_Clock_Conv_Select_t clk_conv;                   /*@ref ADC_Clock_Conv_Select_t */
    ADC_Config_Analog_Channels_t analog_digital_cfg;    /*@ref ADC_Config_Analog_Channels_t */
    ADC_Select_Channels_t channel_src;                  /*@ref ADC_Select_Channels_t */
    ADC_Result_Format_t res_format;                     /*@ref ADC_Result_Format_t */
    uint8_t voltage_refrence;  
    
}ADC_Cfg_t;

/*Section: Function Prototypes*/
STD_ReturnType ADC_ModuleInitialize(ADC_Cfg_t* _adc);
STD_ReturnType ADC_ModuleDeInitialize(ADC_Cfg_t* _adc);
STD_ReturnType ADC_SelectChannel(ADC_Cfg_t* _adc,ADC_Select_Channels_t channel);
STD_ReturnType ADC_StartConversion(ADC_Cfg_t* _adc);
STD_ReturnType ADC_IsConversionDone(ADC_Cfg_t* _adc ,Conversion_Status_t* conversion_status);
STD_ReturnType ADC_GetConversionResult(ADC_Cfg_t* _adc , uint16_t* result);
STD_ReturnType ADC_GetConversionBlocking(ADC_Cfg_t* _adc , uint8_t* result,ADC_Select_Channels_t channel);
STD_ReturnType ADC_StartConversion_Interrupt(ADC_Cfg_t* _adc ,ADC_Select_Channels_t channel);




#endif	/* HAL_ADC_H */

