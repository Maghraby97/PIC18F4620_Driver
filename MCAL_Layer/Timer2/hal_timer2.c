/* 
 * File:   hal_timer2.c
 * Author: Maghraby
 *
 * Created on June 24, 2022, 4:09 PM
 */

#include "hal_timer2.h"

#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
static void (*TMR2_InterruptHandler)(void) = NULL;
static inline STD_ReturnType hal_timer2_interrupt_handler_init(const timer2_t* timer2);
static inline STD_ReturnType hal_timer2_interrupt_enable(const timer2_t* timer2);
#endif

static uint8 timer2_preload = ZERO_INIT;

STD_ReturnType hal_timer2_initialize(const timer2_t* timer2){
    STD_ReturnType status = E_OK;
    if(timer2 != NULL){
        
        
        /*Disable the timer module*/
        Timer2_Module_Disable();
#if INTERRUPT_FEATURE_USED == INTERRUPT_DISABLE        
        /*Disable the interrupt*/
        Timer2_Interrupt_Disable();
#endif        
        /*Select the prescaler value */
        Timer2_Set_Prescaler_Value(timer2->timer2_prescaler_value);
        /*Select the postscaler value*/
        Timer2_Set_Postscaler_Value(timer2->timer2_postscaler_value);
        /*Set the preloaded value*/
        TMR2 = timer2->timer2_preload_value;
        
        
        
      //  PR2 =timer2->timer2_preload_value;
       
        
        timer2_preload = timer2->timer2_preload_value;
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
        /*Initialize the interrupt handler*/
        hal_timer2_interrupt_handler_init(timer2);
        
        /*Enable the interrupt*/        
        hal_timer2_interrupt_enable(timer2);
#endif
        
        /*Enable Timer2 Module*/
        Timer2_Module_Enable();
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}

/**
 * 
 * @param timer2
 * @return 
 */
STD_ReturnType hal_timer2_deinitialize(const timer2_t* timer2){
    STD_ReturnType status = E_OK;
    if(timer2 != NULL){
        Timer2_Module_Disable();
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
        Timer2_Interrupt_Disable();
#endif     
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}

/**
 * 
 * @param timer2
 * @param value
 * @return 
 */
STD_ReturnType hal_timer2_read_value(const timer2_t* timer2,uint8_t* value){
    STD_ReturnType status = E_OK;
    if(timer2 != NULL && value != NULL){
        *value = TMR2;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}

/**
 * 
 * @param timer2
 * @param value
 * @return 
 */
STD_ReturnType hal_timer2_write_value(const timer2_t* timer2,uint8_t value){
    STD_ReturnType status = E_OK;
    if(timer2 != NULL){
        TMR2 = value;
    }
    else{
        status = E_NOT_OK;
    }
    return status;   
}

#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
/**
 * 
 * @param timer2
 * @return 
 */
static inline STD_ReturnType hal_timer2_interrupt_enable(const timer2_t* timer2){
    STD_ReturnType status = E_OK;
    if(timer2 != NULL){
        
        Timer2_Interrupt_Enable();
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if(timer2->timer2_interrupt_priority_level == INTERRUPT_PRIORITY_HIGH){
            INTERRUPT_GlobalInterruptHighEnable();
            Timer2_High_Priority_Set();            
        }
        else if(timer2->timer2_interrupt_priority_level == INTERRUPT_PRIORITY_LOW){
            INTERRUPT_GlobalInterruptLowEnable();
            Timer2_Low_Priority_Set();
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
#if  INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
/**
 * 
 * @param timer2
 * @return 
 */
static inline STD_ReturnType hal_timer2_interrupt_handler_init(const timer2_t* timer2){
    STD_ReturnType status = E_OK;
    if(timer2 != NULL){
        TMR2_InterruptHandler = timer2->TMR2_Handler;
    }
    else{
        status = E_NOT_OK;
    }
    return status;    
    
}

void Timer2_ISR(void){
    Timer2_Clear_Interrupt_Flag(); 
   // PR2 = timer2_preload;
    TMR2 = timer2_preload;
    if(TMR2_InterruptHandler){
        
        TMR2_InterruptHandler();
    }
}

#endif