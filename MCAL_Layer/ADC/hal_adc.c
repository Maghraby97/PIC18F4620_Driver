/* 
 * File:   hal_adc_cfg.c
 * Author: Maghraby
 *
 * Created on May 31, 2022, 5:11 PM
 */

#include "hal_adc.h"

#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
static void(*ADC_InterruptHandler)(void) = NULL;
#endif

STD_ReturnType ADC_ModuleInitialize(ADC_Cfg_t* _adc){
    STD_ReturnType status = E_OK;
    if(_adc != NULL){
        /*Disable the interrupt*/
        #if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
        ADC_Interrupt_Disable();
        #endif
        /*Disable the module*/
        ADC_Converter_Module_Disabled();
        /*Select the default channel*/
        ADC_Select_Channel_Source(_adc->channel_src);        
        /*configure the configuration bits for the Analog and digital channels*/
        ADC_Analog_Digital_Port_Config(_adc->analog_digital_cfg);
        /*configure the voltage refrence*/
        ADC_Disable_Voltage_Reference();
        /*configure the conversion clock bits*/
        ADC_Select_Clock_Conversion(_adc->clk_conv);       
        /*configure the acquisition time*/
        ADC_Select_Acquisition_Time(_adc->acq_time);
        /*configure the result format*/
        if(_adc->res_format == ADC_LEFT_JUSTIFIED){
            ADC_Result_Left_Justified();
        }
        else if(_adc->res_format == ADC_RIGHT_JUSTIFIED){
            ADC_Result_Right_Justified();
        }
        else{
            status = E_NOT_OK;
        }
             
        /*Enable the A/D Module*/
        ADC_Converter_Module_Enabled();
        /*Enable interrupt and priority if needed*/
        
        
        #if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
            ADC_Interrupt_Clear_Flag();
            #if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if(_adc->priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_GlobalInterruptLowEnable();
                ADC_Interrupt_SetLowPriority();
            }
            else if(_adc->priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_GlobalInterruptHighEnable();
                ADC_Interrupt_SetHighPriority();
            }
            else{
                status = E_NOT_OK;
            }
            #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
            #endif
        ADC_Interrupt_Enable();
        if(ADC_InterruptHandler == NULL){
            ADC_InterruptHandler = _adc->ADC_IntHandler;
        }
        else{
            status = E_NOT_OK;
        }  
        #else
        ADC_Interrupt_Disable();
        #endif
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
STD_ReturnType ADC_ModuleDeInitialize(ADC_Cfg_t* _adc){
    STD_ReturnType status = E_OK;
    if(_adc != NULL){
        ADC_Converter_Module_Disabled();
        #if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
            #if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
            INTERRUPT_PriorityLevelsDisable();
            if(_adc->priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_GlobalInterruptLowDisable();                
            }
            else if(_adc->priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_GlobalInterruptHighDisable();                
            }
            else{
                status = E_NOT_OK;
            }
            #else
            INTERRUPT_GlobalInterruptDisable();
            INTERRUPT_PeripheralInterruptDisable();
            ADC_Interrupt_Disable();
            #endif
        #endif
    }
    else{
        status = E_NOT_OK;
    }    
    return status;
}
STD_ReturnType ADC_SelectChannel(ADC_Cfg_t* _adc,ADC_Select_Channels_t channel){
    STD_ReturnType status = E_OK;
    if(_adc != NULL){
        ADC_Select_Channel_Source(channel);
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
STD_ReturnType ADC_StartConversion(ADC_Cfg_t* _adc){
    STD_ReturnType status = E_OK;
    if(_adc != NULL){
        ADC_Start_Conversion();
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
STD_ReturnType ADC_IsConversionDone(ADC_Cfg_t* _adc ,Conversion_Status_t* conversion_status){
    STD_ReturnType status = E_OK;
    if(_adc != NULL && conversion_status != NULL){
        *conversion_status = (uint8_t)(!(ADC_Is_Conversion_In_Progress()));
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
STD_ReturnType ADC_GetConversionResult(ADC_Cfg_t* _adc , uint16_t* result){
    STD_ReturnType status = E_OK;
    if(_adc != NULL && result!= NULL){
        if(_adc->res_format == ADC_LEFT_JUSTIFIED){
            *result = (uint16_t)((ADRESL >> 6)+(ADRESH << 2));
        }
        else if(_adc->res_format == ADC_RIGHT_JUSTIFIED){
            *result = (uint16_t)(ADRESL+(ADRESH << 8));
        }
        else{
            status = E_NOT_OK;
        }
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
STD_ReturnType ADC_GetConversionBlocking(ADC_Cfg_t* _adc , uint8_t* result,ADC_Select_Channels_t channel){
    STD_ReturnType status = E_OK;
    if(_adc != NULL && result!= NULL){
        ADC_SelectChannel(_adc,channel);
        ADC_Start_Conversion();
        while(ADCON0bits.GO_nDONE);
        status = ADC_GetConversionResult(_adc,result);       
    }
    else{
        status = E_NOT_OK;
    }    
    return status;
}
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
STD_ReturnType ADC_StartConversion_Interrupt(ADC_Cfg_t* _adc ,ADC_Select_Channels_t channel){
    STD_ReturnType status = E_OK;
    if(_adc != NULL){
        #if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
        ADC_Interrupt_Clear_Flag();
        #endif
        status = ADC_SelectChannel(_adc,channel);
        status = ADC_Start_Conversion();
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
#endif
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
void ADC_ISR(void){
    ADC_Interrupt_Clear_Flag();
    if(ADC_InterruptHandler){
        ADC_InterruptHandler();
    }
    else{
        /*Nothing*/
    }
}
#endif