/* 
 * File:   hal_timer1.c
 * Author: Maghraby
 *
 * Created on June 17, 2022, 1:16 PM
 */

#include "hal_timer1.h"


static void (*TMR1_InterruptHandler)(void) = NULL;

static inline STD_ReturnType hal_timer1_interrupt_handler_init(const timer1_t* timer1);

volatile uint16_t timer1_isr_preload_value;

/**
 * 
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_initialize(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        hal_timer1_disable(timer1);
        hal_timer1_select_clock_source(timer1);
        hal_timer1_synchronize_external_clock(timer1);
        hal_timer1_rw_8bit_16bit_mode(timer1);
        hal_timer1_set_prescaler(timer1);
        hal_timer1_config_timer1_oscillator(timer1);
        hal_timer1_write_value(timer1,timer1->timer1_preload_value);
        timer1_isr_preload_value = timer1->timer1_preload_value;
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
        hal_timer1_interrupt_handler_init(timer1);
        hal_timer1_interrupt_enable(timer1);
#else
        hal_timer1_interrupt_disable(timer1);
#endif
        hal_timer1_enable(timer1);
    }
    else{
        status = E_NOT_OK;                
    }        
    return status;    
}
/**
 * 
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_deinitialize(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        
    }
    else{
        status = E_NOT_OK;                
    }        
    return status;
}
/**
 * 
 * @param timer1
 * @param value
 * @return 
 */
STD_ReturnType hal_timer1_read_value(const timer1_t* timer1,uint16_t* value){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL && value != NULL){
        if(timer1->timer1_rw_mode == TIMER1_RW_REG_16Bit_MODE){
            *value = TMR1;
        }
        else if(timer1->timer1_rw_mode == TIMER1_RW_REG_8Bit_MODE){
            *value  = (uint16_t)TMR1L;
            *value |= (uint16_t)(TMR1H << 8);
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
 * @param timer1
 * @param value
 * @return 
 */
STD_ReturnType hal_timer1_write_value(const timer1_t* timer1,uint16_t value){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        if(timer1->timer1_rw_mode == TIMER1_RW_REG_16Bit_MODE){
            TMR1 = value;
        }
        else if(timer1->timer1_rw_mode == TIMER1_RW_REG_8Bit_MODE){
            TMR1H = (value) >> 8;
            TMR1L = (uint8)(value);            
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
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_select_clock_source(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        if(timer1->timer1_mode == TIMER1_TIMER_MODE && timer1->timer1_clock_source == TIMER1_INTERNAL_CLOCK_SOURCE){
            Timer1_Select_Internal_Clock_Source();
        }
        else if(timer1->timer1_mode == TIMER1_COUNTER_MODE && timer1->timer1_clock_source == TIMER1_EXTERNAL_CLOCK_SOURCE){
            Timer1_Select_External_Clock_Source();            
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
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_synchronize_external_clock(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        if(timer1->timer1_sync_mode == TIMER1_SYNC_COUNTER_MODE){
            Timer1_Synchronous_External_Clock_Input();
        }
        else if(timer1->timer1_sync_mode == TIMER1_ASYNC_COUNTER_MODE){
            Timer1_Asynchronous_External_Clock_Input();
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
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_rw_8bit_16bit_mode(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        if(timer1->timer1_rw_mode == TIMER1_RW_REG_16Bit_MODE){
            Timer1_RW_16bit_Operation();
        }
        else if(timer1->timer1_rw_mode == TIMER1_RW_REG_8Bit_MODE){
            Timer1_RW_8bit_Operation();
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
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_set_prescaler(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        switch(timer1->timer1_prescaler){
            case TIMER1_PRESCALER_DIV_BY_1:
                Timer1_Set_Prescaler_Value(TIMER1_PRESCALER_DIV_BY_1);
                break;                
            case TIMER1_PRESCALER_DIV_BY_2:
                Timer1_Set_Prescaler_Value(TIMER1_PRESCALER_DIV_BY_2);            
                break;                
            case TIMER1_PRESCALER_DIV_BY_4:
                Timer1_Set_Prescaler_Value(TIMER1_PRESCALER_DIV_BY_4);
                break;                
            case TIMER1_PRESCALER_DIV_BY_8:
                Timer1_Set_Prescaler_Value(TIMER1_PRESCALER_DIV_BY_8);
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
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_config_timer1_oscillator(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        if(timer1->timer1_Osc == TIMER1_OSCILLATOR_ENABLE){
            Timer1_Oscillator_Enable();
        }
        else if(timer1->timer1_Osc == TIMER1_OSCILLATOR_DISABLE){
            Timer1_Oscillator_Disable();
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

#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
/**
 * 
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_interrupt_enable(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        Timer1_Interrupt_Enable();
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(timer1->timer1_interrupt_priority_level == INTERRUPT_PRIORITY_HIGH){
            INTERRUPT_GlobalInterruptHighEnable();
            Timer1_High_Priority_Set();            
        }
        else if(timer1->timer1_interrupt_priority_level == INTERRUPT_PRIORITY_LOW){
            INTERRUPT_GlobalInterruptLowEnable();
            Timer1_Low_Priority_Set();
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
#endif
/**
 * 
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_interrupt_disable(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
#if INTERRUPT_FEATURE_USED == INTERRUPT_DISABLE
        Timer1_Interrupt_Disable();
#endif
    }
    else{
        status = E_NOT_OK;                
    }        
    return status; 
}
/**
 * 
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_enable(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        Timer1_Module_Enable();
    }
    else{
        status = E_NOT_OK;                
    }        
    return status; 
}
/**
 * 
 * @param timer1
 * @return 
 */
STD_ReturnType hal_timer1_disable(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        Timer1_Module_Disable();
    }
    else{
        status = E_NOT_OK;                
    }        
    return status; 
}
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
/**
 * 
 * @param timer1
 * @return 
 */
static inline STD_ReturnType hal_timer1_interrupt_handler_init(const timer1_t* timer1){
    STD_ReturnType status = E_OK;
    if(timer1 != NULL){
        if(TMR1_InterruptHandler == NULL && timer1->TMR1_Handler != NULL){
            TMR1_InterruptHandler = timer1->TMR1_Handler;
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

void Timer1_ISR(void){
    Timer1_Clear_Interrupt_Flag();
    TMR1H = (timer1_isr_preload_value) >> 8;
    TMR1L = (uint8)(timer1_isr_preload_value);
    if(TMR1_InterruptHandler != NULL){        
        TMR1_InterruptHandler();
    }    
}
#endif