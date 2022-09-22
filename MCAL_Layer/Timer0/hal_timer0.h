/* 
 * File:   hal_timer0.h
 * Author: Maghraby
 *
 * Created on June 10, 2022, 3:24 PM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* Section: Includes*/

#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "hal_timer0_config.h"

/*Section: Macro Declarations*/

#define TIMER0_MODULE_DISABLED    ((uint8_t)0)
#define TIMER0_MODULE_ENABLED     ((uint8_t)1)

#define TIMER0_PRESCALER_ENABLED       ((uint8_t)0)
#define TIMER0_PRESCALER_DISABLED      ((uint8_t)1)

#define TIMER0_RISING_EDGE_INCREMENT_SELECTED   ((uint8_t)0)
#define TIMER0_FALLING_EDGE_INCREMENT_SELECTED  ((uint8_t)1)

#define TIMER0_INTERNAL_CLOCK_SOURCE_SELECTED   ((uint8_t)0)
#define TIMER0_EXTERNAL_CLOCK_SOURCE_SELECTED   ((uint8_t)1)

#define TIMER0_REGISTER_SIZE_16BIT_SELECTED  ((uint8_t)0)
#define TIMER0_REGISTER_SIZE_8BIT_SELECTED   ((uint8_t)1)

#define TIMER0_OPERATION_MODE_TIMER    ((uint8_t)0)
#define TIMER0_OPERATION_MODE_COUTNER  ((uint8_t)1)

/*Section: Function Like Macros*/

#define Timer0_Module_Enable()  (T0CONbits.TMR0ON = 1)
#define Timer0_Module_Disable()  (T0CONbits.TMR0ON = 0)


#define Timer0_Set_Prescaler_Value(_Prescaler)  (T0CONbits.T0PS = _Prescaler)

#define Timer0_Prescaler_Enable()  (T0CONbits.PSA = 0)
#define Timer0_Prescaler_Disable() (T0CONbits.PSA = 1)

#define Timer0_Increment_On_Rising_Edge()  (T0CONbits.T0SE = 0)
#define Timer0_Increment_On_Falling_Edge()  (T0CONbits.T0SE = 1)

#define Timer0_Select_Internal_Clock_Source()  (T0CONbits.T0CS = 0)
#define Timer0_Select_External_Clock_Source()  (T0CONbits.T0CS = 1)

#define Timer0_Set_Register_Size_8Bit() (T0CONbits.T08BIT = 1)
#define Timer0_Set_Register_Size_16Bit() (T0CONbits.T08BIT = 0)

/*Section: Data Type Declaration*/


typedef enum{
    TIMER0_PSF_DIV_BY_2 = 0,
            TIMER0_PSF_DIV_BY_4,
            TIMER0_PSF_DIV_BY_8,
            TIMER0_PSF_DIV_BY_16,
            TIMER0_PSF_DIV_BY_32,
            TIMER0_PSF_DIV_BY_64,
            TIMER0_PSF_DIV_BY_128,
            TIMER0_PSF_DIV_BY_256,            
}timer0_prescaler_values_t;

typedef enum{
    TIMER0_INCREMENT_ON_RISING_EDGE = 0,
            TIMER0_INCREMENT_ON_FALLING_EDGE        
}timer0_edge_inrement_t;

typedef enum{
    TIMER0_CLOCK_SOURCE_INTERNAL = 0,
            TIMER0_CLOCK_SOURCE_EXTERNAL
}timer0_clock_source_t;

typedef enum{
    TIMER0_REGISTER_16BIT = 0,
            TIMER0_REGISTER_8BIT
}timer0_register_size_t;

typedef enum{
    TIMER0_TIMER_MODE = 0,
            TIMER0_COUNTER_MODE
}timer0_operation_mode_t;

typedef struct{
    /*don`t forget to add the interrupt handler callback function*/
    
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
    void (*TMR0_Handler)(void);
#endif
   
#if INTERRUPT_PRIORITY_FEATURE_USED   ==  INTERRUPT_PRIORITY_ENABLE
    uint8_t timer0_interrupt_priority_level;
#endif
    timer0_operation_mode_t mode;
    timer0_register_size_t register_size;
    timer0_clock_source_t clocksrc;
    timer0_edge_inrement_t edge_incr;
    uint8_t prescaler_enable_bit;
    timer0_prescaler_values_t prescaler_value;
    uint16_t preloaded_value;
    
}timer0_t;
/*Section: Function Prototypes*/

STD_ReturnType hal_timer0_initialize(const timer0_t* timer0);
STD_ReturnType hal_timer0_deinitialize(const timer0_t* timer0);
STD_ReturnType hal_timer0_read_value(const timer0_t* timer0,uint16_t* value);
STD_ReturnType hal_timer0_write_value(const timer0_t* timer0,uint16_t value);
STD_ReturnType hal_timer0_select_clock_source(const timer0_t* timer0);
STD_ReturnType hal_timer0_select_edge_increment(const timer0_t* timer0);
STD_ReturnType hal_timer0_select_8bit_or_16bit_mode(const timer0_t* timer0);
STD_ReturnType hal_timer0_enable_prescaler(const timer0_t* timer0);
STD_ReturnType hal_timer0_disable_prescaler(const timer0_t* timer0);
STD_ReturnType hal_timer0_set_prescaler_value(const timer0_t* timer0);
STD_ReturnType hal_timer0_interrupt_enable(const timer0_t* timer0);
STD_ReturnType hal_timer0_interrupt_disable(const timer0_t* timer0);
STD_ReturnType hal_timer0_enable(const timer0_t* timer0);
STD_ReturnType hal_timer0_disable(const timer0_t* timer0);
#endif	/* HAL_TIMER0_H */

