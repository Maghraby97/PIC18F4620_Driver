/* 
 * File:   hal_ccp1.c
 * Author: Maghraby
 *
 * Created on June 27, 2022, 5:43 PM
 */

#include "hal_ccp1.h"

static void (*CCP1_InterruptHandler)(void) = NULL;
static void (*CCP2_InterruptHandler)(void) = NULL;



/**
 * 
 * @param ccp1obj
 * @return 
 */
STD_ReturnType hal_ccp_init(const ccp_t* ccpobj){
    STD_ReturnType status = E_OK;
    if(ccpobj != NULL){
        if(ccpobj->cpp_instance == CCP1_INSTANCE){
            CCP1_Module_Set_Operational_Mode(CCP_MODULE_DISABLE);
        }
        else if(ccpobj->cpp_instance == CCP2_INSTANCE){
            CCP2_Module_Set_Operational_Mode(CCP_MODULE_DISABLE);
        }
        else{
            status = E_NOT_OK;
        }
        
        if(ccpobj->ccp_mode == CCP_COMPARE_MODE_){
            if(ccpobj->cpp_instance == CCP1_INSTANCE){
                switch(ccpobj->ccp_submode){
                    case CCP_COMPARE_MODE_TOGGLE_OUTPUT:
                        CCP1_Module_Set_Operational_Mode(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
                        break;
                    case CCP_COMPARE_MODE_CCP_PIN_HIGH:
                        CCP1_Module_Set_Operational_Mode(CCP_COMPARE_MODE_CCP_PIN_HIGH);
                        break;
                    case CCP_COMPARE_MODE_CCP_PIN_LOW:
                        CCP1_Module_Set_Operational_Mode(CCP_COMPARE_MODE_CCP_PIN_LOW);
                        break;
                    case CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT:
                        CCP1_Module_Set_Operational_Mode(CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT);
                        break;
                    case CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT:
                        CCP1_Module_Set_Operational_Mode(CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT);
                        break;
                    default:
                        status = E_NOT_OK;
                        break;                    
                }
            }
            else if(ccpobj->cpp_instance == CCP2_INSTANCE){
                switch(ccpobj->ccp_submode){
                    case CCP_COMPARE_MODE_TOGGLE_OUTPUT:
                        CCP2_Module_Set_Operational_Mode(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
                        break;
                    case CCP_COMPARE_MODE_CCP_PIN_HIGH:
                        CCP2_Module_Set_Operational_Mode(CCP_COMPARE_MODE_CCP_PIN_HIGH);
                        break;
                    case CCP_COMPARE_MODE_CCP_PIN_LOW:
                        CCP2_Module_Set_Operational_Mode(CCP_COMPARE_MODE_CCP_PIN_LOW);
                        break;
                    case CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT:
                        CCP2_Module_Set_Operational_Mode(CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT);
                        break;
                    case CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT:
                        CCP2_Module_Set_Operational_Mode(CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT);
                        break;
                    default:
                        status = E_NOT_OK;
                        break;                    
                }
            }
            else{
                status = E_NOT_OK;
            }            
        }
        else if(ccpobj->ccp_mode == CCP_CAPTURE_MODE_){
            if(ccpobj->cpp_instance == CCP1_INSTANCE){
                switch(ccpobj->ccp_submode){
                    case CCP_CAPTURE_MODE_EVERY_FALLING_EDGE:
                        CCP1_Module_Set_Operational_Mode(CCP_CAPTURE_MODE_EVERY_FALLING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_EVERY_RISING_EDGE:
                        CCP1_Module_Set_Operational_Mode(CCP_CAPTURE_MODE_EVERY_RISING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_EVERY_4_RISING_EDGE:
                        CCP1_Module_Set_Operational_Mode(CCP_CAPTURE_MODE_EVERY_4_RISING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_EVERY_16_RISING_EDGE:
                        CCP1_Module_Set_Operational_Mode(CCP_CAPTURE_MODE_EVERY_16_RISING_EDGE);
                        break;
                    default:
                        status = E_NOT_OK;
                        break;                    
                }
            }
            else if(ccpobj->cpp_instance == CCP2_INSTANCE){
                switch(ccpobj->ccp_submode){
                    case CCP_CAPTURE_MODE_EVERY_FALLING_EDGE:
                        CCP2_Module_Set_Operational_Mode(CCP_CAPTURE_MODE_EVERY_FALLING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_EVERY_RISING_EDGE:
                        CCP2_Module_Set_Operational_Mode(CCP_CAPTURE_MODE_EVERY_RISING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_EVERY_4_RISING_EDGE:
                        CCP2_Module_Set_Operational_Mode(CCP_CAPTURE_MODE_EVERY_4_RISING_EDGE);
                        break;
                    case CCP_CAPTURE_MODE_EVERY_16_RISING_EDGE:
                        CCP2_Module_Set_Operational_Mode(CCP_CAPTURE_MODE_EVERY_16_RISING_EDGE);
                        break;
                    default:
                        status = E_NOT_OK;
                        break;                    
                }
            }
            else{
                status = E_NOT_OK;
            }            
        }
        else if(ccpobj->ccp_mode == CCP_PWM_MODE_){
            if(ccpobj->cpp_instance == CCP1_INSTANCE){
                CCP1_Module_Set_Operational_Mode(CCP_PWM_MODE);
            }
            else if(ccpobj->cpp_instance == CCP2_INSTANCE){
                CCP2_Module_Set_Operational_Mode(CCP_PWM_MODE);
            }
            else{
                status = E_NOT_OK;
            }
            
#if CCP_MODE_OF_OPERATION_SELECTED == CCP_PWM_MODE_SELECTED
            PR2 = (uint8_t)((_XTAL_FREQ / (ccpobj->ccp_pwm_frequency * 4.0 * ccpobj->timer2_prescaler_value * ccpobj->timer2_postscaler_value ))-1);                    
#endif  
        }
        else{
            status = E_NOT_OK;
        }     
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
        if(ccpobj->cpp_instance == CCP1_INSTANCE){
            CCP1_Interrupt_Enable();
            CCP1_Clear_Interrupt_Flag();
            CCP1_InterruptHandler = ccpobj->CCP1_Handler;
        }
        else if(ccpobj->cpp_instance == CCP2_INSTANCE){
            CCP2_Interrupt_Enable();
            CCP2_Clear_Interrupt_Flag();
            CCP2_InterruptHandler = ccpobj->CCP2_Handler;
        }
        else{
            status = E_NOT_OK;
        }        
#if INTERRUPT_PRIORITY_FEATURE_USED ==  INTERRUPT_PRIORITY_ENABLE 
        INTERRUPT_PriorityLevelsEnable();
        if(ccpobj->cpp_instance == CCP1_INSTANCE){
            if(ccpobj->ccp1_interrupt_priority_level == INTERRUPT_PRIORITY_HIGH){
                INTERRUPT_GlobalInterruptHighEnable();
                CCP1_High_Priority_Set();            
            }
            else if(ccpobj->ccp_interrupt_priority_level == INTERRUPT_PRIORITY_LOW){
                INTERRUPT_GlobalInterruptLowEnable();
                CCP1_Low_Priority_Set();
            }
            else{
                status = E_NOT_OK;   
            }
        }
        else if(ccpobj->cpp_instance == CCP2_INSTANCE){
            if(ccpobj->ccp2_interrupt_priority_level == INTERRUPT_PRIORITY_HIGH){
                INTERRUPT_GlobalInterruptHighEnable();
                CCP2_High_Priority_Set();            
            }
            else if(ccpobj->ccp2_interrupt_priority_level == INTERRUPT_PRIORITY_LOW){
                INTERRUPT_GlobalInterruptLowEnable();
                CCP2_Low_Priority_Set();
            }
            else{
                status = E_NOT_OK;   
            }
            
        }
        else{
            status = E_NOT_OK;
        } 
        
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();    
#endif
#endif        
    }    
    else{
        status = E_NOT_OK;
    }
    return status;
}
/**
 * 
 * @param ccp1obj
 * @return 
 */
STD_ReturnType hal_ccp_deinit(const ccp_t* ccpobj){
    STD_ReturnType status = E_OK;
    if(ccpobj != NULL){
        if(ccpobj->cpp_instance == CCP1_INSTANCE){
            CCP1_Module_Set_Operational_Mode(CCP_MODULE_DISABLE);
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
            CCP1_Interrupt_Disable();
#endif    
        }
        else if(ccpobj->cpp_instance == CCP2_INSTANCE){
            CCP2_Module_Set_Operational_Mode(CCP_MODULE_DISABLE);
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
            CCP2_Interrupt_Disable();
#endif
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


/**
 * 
 * @param ccp1obj
 * @return 
 */
STD_ReturnType hal_ccp_isCaptureReady(const ccp_t* ccpobj,uint8_t *_capture_status){
    STD_ReturnType status = E_OK;
    if(_capture_status != NULL){       
        if(ccpobj->cpp_instance == CCP1_INSTANCE){
            *_capture_status = PIR1bits.CCP1IF;
            CCP1_Clear_Interrupt_Flag();
        }
        else if(ccpobj->cpp_instance == CCP2_INSTANCE){
            *_capture_status = PIR2bits.CCP2IF;
            CCP2_Clear_Interrupt_Flag();
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
/**
 * 
 * @param ccp1obj
 * @param value
 * @return 
 */
STD_ReturnType hal_ccp_readCaptureValue(const ccp_t* ccpobj,uint16_t* value){
    STD_ReturnType status = E_OK;
    if(ccpobj != NULL && value != NULL){
        if(ccpobj->cpp_instance == CCP1_INSTANCE){
            CCPR_Reg_t ccpr_val;
            ccpr_val.ccprL = CCPR1L;
            ccpr_val.ccprH = CCPR1H;
            *value = ccpr_val.ccpr_Reg;            
        }
        else if(ccpobj->cpp_instance == CCP2_INSTANCE){
            CCPR_Reg_t ccpr_val;
            ccpr_val.ccprL = CCPR2L;
            ccpr_val.ccprH = CCPR2H;
            *value = ccpr_val.ccpr_Reg;  
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

/**
 * 
 * @param compare_status
 * @return 
 */
STD_ReturnType hal_ccp_isCompareComplete(const ccp_t* ccpobj,uint8 *compare_status){
    STD_ReturnType status = E_OK;
    if(compare_status != NULL){
        if(ccpobj->cpp_instance == CCP1_INSTANCE){
            *compare_status = PIR1bits.CCP1IF;
            CCP1_Clear_Interrupt_Flag();
        }
        else if(ccpobj->cpp_instance == CCP2_INSTANCE){
            *compare_status = PIR2bits.CCP2IF;
            CCP2_Clear_Interrupt_Flag();
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
/**
 * 
 * @param compare_value
 * @return 
 */
STD_ReturnType hal_ccp_compareModeSetValue(const ccp_t* ccpobj,uint16 compare_value){
    STD_ReturnType status = E_OK;
    CCPR_Reg_t ccpr_val;
    ccpr_val.ccpr_Reg = compare_value;
    if(ccpobj->cpp_instance == CCP1_INSTANCE){        
        CCPR1L = ccpr_val.ccprL;
        CCPR1H = ccpr_val.ccprH;        
    }
    else if(ccpobj->cpp_instance == CCP2_INSTANCE){
        CCPR2L = ccpr_val.ccprL;
        CCPR2H = ccpr_val.ccprH;        
    }
    else{
        status = E_NOT_OK;
    }
    return status;    
}
/**
 * 
 * @param duty
 * @return 
 */
STD_ReturnType hal_ccp_setPWMDuty(const ccp_t* ccpobj,const uint8_t duty){
    STD_ReturnType status = E_OK;
    uint16_t l_duty_temp;
    l_duty_temp =  (uint16)(4 * (PR2 + 1) * (duty / 100.0));
    if(ccpobj->cpp_instance == CCP1_INSTANCE){
        CCP1CONbits.DC1B = (uint8_t)(l_duty_temp & 0x0003);
        CCPR1L = (uint8_t)(l_duty_temp >> 2);       
    }
    else if(ccpobj->cpp_instance == CCP2_INSTANCE){
        CCP2CONbits.DC2B = (uint8_t)(l_duty_temp & 0x0003);
        CCPR2L = (uint8_t)(l_duty_temp >> 2); 
    }
    else{
        status = E_NOT_OK;
    }
    return status;    
}
/**
 * 
 * @return 
 */
STD_ReturnType hal_ccp_PWMStart(const ccp_t* ccpobj){
    STD_ReturnType status = E_OK;
    CCP1_Module_Set_Operational_Mode(CCP_PWM_MODE);
    if(ccpobj->cpp_instance == CCP1_INSTANCE){
        CCP1_Module_Set_Operational_Mode(CCP_PWM_MODE);
    }
    else if(ccpobj->cpp_instance == CCP2_INSTANCE){
        CCP2_Module_Set_Operational_Mode(CCP_PWM_MODE);
    }
    else{
        status = E_NOT_OK;
    }
    return status;    
}
/**
 * 
 * @return 
 */
STD_ReturnType hal_ccp_PWMStop(const ccp_t* ccpobj){
    STD_ReturnType status = E_OK;
    if(ccpobj->cpp_instance == CCP1_INSTANCE){
        CCP1_Module_Set_Operational_Mode(CCP_MODULE_DISABLE);
    }
    else if(ccpobj->cpp_instance == CCP2_INSTANCE){
        CCP2_Module_Set_Operational_Mode(CCP_MODULE_DISABLE);
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;    
    
}

void CCP1_ISR(void){
    CCP1_Clear_Interrupt_Flag();
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }else{
        /*nothing*/
    }
}
void CCP2_ISR(void){
    CCP2_Clear_Interrupt_Flag();
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }else{
        /*nothing*/
    }
}