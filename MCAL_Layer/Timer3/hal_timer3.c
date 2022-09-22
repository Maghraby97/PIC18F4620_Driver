/* 
 * File:   hal_timer3.c
 * Author: Maghraby
 *
 * Created on June 24, 2022, 11:05 PM
 */


#include "hal_timer3.h"

static void (*TMR3_InterruptHandler)(void) = NULL;
volatile uint16_t timer3_isr_preload_value;

static inline STD_ReturnType hal_timer3_interrupt_handler_init(const timer3_t* timer3);


/**
 * 
 * @param timer3
 * @return 
 */
STD_ReturnType hal_timer3_initialize(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        hal_timer3_disable(timer3);
        hal_timer3_set_prescaler(timer3);
        
        hal_timer3_select_clock_source(timer3);
        //hal_timer3_synchronize_external_clock(timer3);
        hal_timer3_rw_8bit_16bit_mode(timer3);
        
        
        hal_timer3_write_value(timer3,timer3->timer3_preload_value);
        timer3_isr_preload_value = timer3->timer3_preload_value;
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
        hal_timer3_interrupt_handler_init(timer3);
        hal_timer3_interrupt_enable(timer3);
#else
        hal_timer3_interrupt_disable(timer3);
#endif
        hal_timer3_enable(timer3);
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
/**
 * 
 * @param timer3
 * @return 
 */
STD_ReturnType hal_timer3_deinitialize(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
/**
 * 
 * @param timer3
 * @param value
 * @return 
 */
STD_ReturnType hal_timer3_read_value(const timer3_t* timer3,uint16_t* value){
    STD_ReturnType status = E_OK;
    
    uint8 l_tmr3l = ZERO_INIT, l_tmr3h = ZERO_INIT;
    
    if(timer3 != NULL && value != NULL){
        if(timer3->timer3_rw_mode == TIMER3_RW_REG_16Bit_MODE){
            *value = TMR3;
        }
        else if(timer3->timer3_rw_mode == TIMER3_RW_REG_8Bit_MODE){
//            *value  = (uint16_t)TMR3L;
//            *value = *value | ((uint16_t)(TMR3H << 8));
            
            l_tmr3l = TMR3L;
            l_tmr3h = TMR3H;
            *value = (uint16)((l_tmr3h << 8) + l_tmr3l);
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
 * @param timer3
 * @param value
 * @return 
 */
STD_ReturnType hal_timer3_write_value(const timer3_t* timer3,uint16_t value){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        if(timer3->timer3_rw_mode == TIMER3_RW_REG_16Bit_MODE){
            TMR3 = value;
        }
        else if(timer3->timer3_rw_mode == TIMER3_RW_REG_8Bit_MODE){
            TMR3H = (value) >> 8;
            TMR3L = (uint8)(value);            
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
 * @param timer3
 * @return 
 */
STD_ReturnType hal_timer3_select_clock_source(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        if(timer3->timer3_mode == TIMER3_TIMER_MODE && timer3->timer3_clock_source == TIMER3_INTERNAL_CLOCK_SOURCE){
            Timer3_Select_Internal_Clock_Source();
        }
        else if(timer3->timer3_mode == TIMER3_COUNTER_MODE && timer3->timer3_clock_source == TIMER3_EXTERNAL_CLOCK_SOURCE){
            Timer3_Select_External_Clock_Source();            
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
 * @param timer3
 * @return 
 */
STD_ReturnType hal_timer3_synchronize_external_clock(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        if(timer3->timer3_sync_mode == TIMER3_SYNC_COUNTER_MODE){
            Timer3_Synchronous_External_Clock_Input();
        }
        else if(timer3->timer3_sync_mode == TIMER3_ASYNC_COUNTER_MODE){
            Timer3_Asynchronous_External_Clock_Input();
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
 * @param timer3
 * @return 
 */
STD_ReturnType hal_timer3_rw_8bit_16bit_mode(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        if(timer3->timer3_rw_mode == TIMER3_RW_REG_16Bit_MODE){
            Timer3_RW_16bit_Operation();
        }
        else if(timer3->timer3_rw_mode == TIMER3_RW_REG_8Bit_MODE){
            Timer3_RW_8bit_Operation();
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
 * @param timer3
 * @return 
 */
STD_ReturnType hal_timer3_set_prescaler(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        switch(timer3->timer3_prescaler){
            case TIMER3_PRESCALER_DIV_BY_1:
                Timer3_Set_Prescaler_Value(TIMER3_PRESCALER_DIV_BY_1);
                break;                
            case TIMER3_PRESCALER_DIV_BY_2:
                Timer3_Set_Prescaler_Value(TIMER3_PRESCALER_DIV_BY_2);            
                break;                
            case TIMER3_PRESCALER_DIV_BY_4:
                Timer3_Set_Prescaler_Value(TIMER3_PRESCALER_DIV_BY_4);
                break;                
            case TIMER3_PRESCALER_DIV_BY_8:
                Timer3_Set_Prescaler_Value(TIMER3_PRESCALER_DIV_BY_8);
                break;                
            default:
                status = E_NOT_OK;
                break;
        }
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
/**
 * 
 * @param timer3
 * @return 
 */
STD_ReturnType hal_timer3_interrupt_enable(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        Timer3_Interrupt_Enable();
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(timer3->timer3_interrupt_priority_level == INTERRUPT_PRIORITY_HIGH){
            INTERRUPT_GlobalInterruptHighEnable();
            Timer3_High_Priority_Set();            
        }
        else if(timer3->timer3_interrupt_priority_level == INTERRUPT_PRIORITY_LOW){
            INTERRUPT_GlobalInterruptLowEnable();
            Timer3_Low_Priority_Set();
        }
        else{
            status = E_NOT_OK;   
        }        
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif        
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
/**
 * 
 * @param timer3
 * @return 
 */
STD_ReturnType hal_timer3_interrupt_disable(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
#if INTERRUPT_FEATURE_USED == INTERRUPT_DISABLE
        Timer3_Interrupt_Disable();
#endif
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
/**
 * 
 * @param timer3
 * @return 
 */
STD_ReturnType hal_timer3_enable(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        Timer3_Module_Enable();
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
/**
 * 
 * @param timer3
 * @return 
 */
STD_ReturnType hal_timer3_disable(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        Timer3_Module_Disable();
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
/**
 * 
 * @param timer3
 * @return 
 */
static inline STD_ReturnType hal_timer3_interrupt_handler_init(const timer3_t* timer3){
    STD_ReturnType status = E_OK;
    if(timer3 != NULL){
        if(TMR3_InterruptHandler == NULL && timer3->TMR3_Handler != NULL){
            TMR3_InterruptHandler = timer3->TMR3_Handler;
        }
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}

void Timer3_ISR(void){
    Timer3_Clear_Interrupt_Flag();
    TMR3H = (timer3_isr_preload_value) >> 8;
    TMR3L = (uint8)(timer3_isr_preload_value);
    if(TMR3_InterruptHandler != NULL){        
        TMR3_InterruptHandler();
    }    
}
#endif