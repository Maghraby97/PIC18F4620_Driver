/* 
 * File:   hal_timer0.h
 * Author: Maghraby
 *
 * Created on June 10, 2022, 3:24 PM
 */

#include "hal_timer0.h"


#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
static void (*TMR0_InterruptHandler)(void) = NULL;
static inline STD_ReturnType hal_timer0_interrupt_handler_init(const timer0_t* timer0);
#endif




/**
 * 
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_initialize(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        //uint8_t Interrupt_Bit_Status = INTCONbits.TMR0IE;
        
        /*Disable the timer module*/
        Timer0_Module_Disable();
#if INTERRUPT_FEATURE_USED == INTERRUPT_DISABLE        
        /*Disable the interrupt*/
        Timer0_Interrupt_Disable();
#endif        
        
        /*Check the timer mode and the clock source whether internal or external*/
        hal_timer0_select_clock_source(timer0);
        
        /*Select edge increment*/
        hal_timer0_select_edge_increment(timer0);
        /*Select the TMR0 register size whether 8bit or 16bit*/
        hal_timer0_select_8bit_or_16bit_mode(timer0);
        
        /*Select the prescaler value and the enable bit */
        if(timer0->prescaler_enable_bit == TIMER0_PRESCALER_ENABLED){
            hal_timer0_enable_prescaler(timer0);
            hal_timer0_set_prescaler_value(timer0);            
        }
        else if(timer0->prescaler_enable_bit == TIMER0_PRESCALER_DISABLED){
            hal_timer0_disable_prescaler(timer0);
        }
        else{
            status = E_NOT_OK;
        }
        /*Set the preloaded value*/
        TMR0H = (timer0->preloaded_value)>>8;
        TMR0L = (uint8_t)(timer0->preloaded_value);
        
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
        /*Initialize the interrupt handler*/
        hal_timer0_interrupt_handler_init(timer0);
        
        /*Enable the interrupt*/        
        hal_timer0_interrupt_enable(timer0);
#endif
        
        /*Enable Timer0 Module*/
        Timer0_Module_Enable();
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
/**
 * 
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_deinitialize(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        hal_timer0_interrupt_disable(timer0);
        hal_timer0_disable(timer0);
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
/**
 * 
 * @param timer0
 * @param value
 * @return 
 */
STD_ReturnType hal_timer0_read_value(const timer0_t* timer0,uint16_t* value){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL && value != NULL){
        *value = (uint16_t)TMR0L;
        *value |= (uint16_t)(TMR0H << 8);
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
/**
 * 
 * @param timer0
 * @param value
 * @return 
 */
STD_ReturnType hal_timer0_write_value(const timer0_t* timer0,uint16_t value){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        TMR0H = (uint8_t)(value >> 8);
        TMR0L = (uint8_t)value;
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}

/**
 * 
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_select_clock_source(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        /*Check the timer mode and the clock source whether internal or external*/
        if(timer0->mode == TIMER0_TIMER_MODE && timer0->clocksrc == TIMER0_INTERNAL_CLOCK_SOURCE_SELECTED){
            Timer0_Select_Internal_Clock_Source();
        }
        else if(timer0->mode == TIMER0_COUNTER_MODE && timer0->clocksrc == TIMER0_EXTERNAL_CLOCK_SOURCE_SELECTED){
            Timer0_Select_External_Clock_Source();
            /*Select Edge Increment*/
            hal_timer0_select_edge_increment(timer0);
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
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_select_edge_increment(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        /*Select Edge Increment*/
        if(timer0->edge_incr == TIMER0_RISING_EDGE_INCREMENT_SELECTED){
            Timer0_Increment_On_Rising_Edge();
        }
        else if(timer0->edge_incr == TIMER0_FALLING_EDGE_INCREMENT_SELECTED){
            Timer0_Increment_On_Falling_Edge();
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
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_select_8bit_or_16bit_mode(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        /*Select the TMR0 register size whether 8bit or 16bit*/
        if(timer0->register_size == TIMER0_REGISTER_8BIT){
            Timer0_Set_Register_Size_8Bit();
        }
        else if(timer0->register_size == TIMER0_REGISTER_16BIT){
            Timer0_Set_Register_Size_16Bit();
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
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_enable_prescaler(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        if(timer0->prescaler_enable_bit == TIMER0_PRESCALER_ENABLED){
            Timer0_Prescaler_Enable();
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
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_disable_prescaler(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        if(timer0->prescaler_enable_bit == TIMER0_PRESCALER_DISABLED){
            Timer0_Prescaler_Disable();
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
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_set_prescaler_value(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        switch(timer0->prescaler_value){
            case TIMER0_PSF_DIV_BY_2:
                Timer0_Set_Prescaler_Value(TIMER0_PSF_DIV_BY_2);
                break;
            case TIMER0_PSF_DIV_BY_4:
                Timer0_Set_Prescaler_Value(TIMER0_PSF_DIV_BY_4);
                break;
            case TIMER0_PSF_DIV_BY_8:
                Timer0_Set_Prescaler_Value(TIMER0_PSF_DIV_BY_8);
                break;
            case TIMER0_PSF_DIV_BY_16:
                Timer0_Set_Prescaler_Value(TIMER0_PSF_DIV_BY_16);
                break;
            case TIMER0_PSF_DIV_BY_32:
                Timer0_Set_Prescaler_Value(TIMER0_PSF_DIV_BY_32);
                break;
            case TIMER0_PSF_DIV_BY_64:
                Timer0_Set_Prescaler_Value(TIMER0_PSF_DIV_BY_64);
                break;
            case TIMER0_PSF_DIV_BY_128:
                Timer0_Set_Prescaler_Value(TIMER0_PSF_DIV_BY_128);
                break;
            case TIMER0_PSF_DIV_BY_256:
                Timer0_Set_Prescaler_Value(TIMER0_PSF_DIV_BY_128);
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

#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
/**
 * 
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_interrupt_enable(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        Timer0_Interrupt_Enable();
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(timer0->timer0_interrupt_priority_level == INTERRUPT_PRIORITY_HIGH){
            INTERRUPT_GlobalInterruptHighEnable();
            Timer0_High_Priority_Set();            
        }
        else if(timer0->timer0_interrupt_priority_level == INTERRUPT_PRIORITY_LOW){
            INTERRUPT_GlobalInterruptLowEnable();
            Timer0_Low_Priority_Set();
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
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_interrupt_disable(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
        Timer0_Interrupt_Disable();
#endif
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}



/**
 * 
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_enable(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        Timer0_Module_Enable();
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
/**
 * 
 * @param timer0
 * @return 
 */
STD_ReturnType hal_timer0_disable(const timer0_t* timer0){
    STD_ReturnType status = E_OK;
    if(timer0 != NULL){
        Timer0_Module_Disable();
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
/**
 * 
 * @param timer0
 * @return 
 */
static inline STD_ReturnType hal_timer0_interrupt_handler_init(const timer0_t* timer0){
    STD_ReturnType status = E_NOT_OK;
    if(timer0 != NULL){
        TMR0_InterruptHandler = timer0->TMR0_Handler;  
    }
    else{   
        status = E_NOT_OK;
    }  
    return status;
}
#endif
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
void Timer0_ISR(void){
    Timer0_Clear_Interrupt_Flag();
    if(TMR0_InterruptHandler != NULL){
        TMR0_InterruptHandler();
    }
    
}
#endif