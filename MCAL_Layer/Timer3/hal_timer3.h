/* 
 * File:   hal_timer3.h
 * Author: Maghraby
 *
 * Created on June 24, 2022, 11:05 PM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H


/* Section: Includes*/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "hal_timer3_config.h"
/*Section: Macro Declarations*/
#define TIMER3_TIMER_MODE              0
#define TIMER3_COUNTER_MODE            1

#define TIMER3_ASYNC_COUNTER_MODE      1
#define TIMER3_SYNC_COUNTER_MODE       0

#define TIMER3_PRESCALER_DIV_BY_1      0
#define TIMER3_PRESCALER_DIV_BY_2      1
#define TIMER3_PRESCALER_DIV_BY_4      2
#define TIMER3_PRESCALER_DIV_BY_8      3

#define TIMER3_RW_REG_8Bit_MODE        0
#define TIMER3_RW_REG_16Bit_MODE       1

#define TIMER3_INTERNAL_CLOCK_SOURCE   0
#define TIMER3_EXTERNAL_CLOCK_SOURCE   1

/*Section: Function Like Macros*/
#define Timer3_Module_Enable()  (T3CONbits.TMR3ON = 1)
#define Timer3_Module_Disable()  (T3CONbits.TMR3ON  = 0)

#define Timer3_Select_External_Clock_Source()  (T3CONbits.TMR3CS = 1)
#define Timer3_Select_Internal_Clock_Source()  (T3CONbits.TMR3CS = 0)

#define Timer3_Asynchronous_External_Clock_Input() (T3CONbits.nT3SYNC = 1)
#define Timer3_Synchronous_External_Clock_Input() (T3CONbits.nT3SYNC = 0)

#define Timer3_Set_Prescaler_Value(_Prescaler)   (T3CONbits.T3CKPS = _Prescaler)

#define Timer3_RW_16bit_Operation() (T3CONbits.RD16 = 1)
#define Timer3_RW_8bit_Operation()  (T3CONbits.RD16 = 0)
/*Section: Data Type Declaration*/

typedef struct{
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
    void (*TMR3_Handler)(void);
    uint8_t timer3_interrupt_priority_level;
#endif
    uint16_t timer3_preload_value;
    uint8_t timer3_mode;
    uint8_t timer3_clock_source   : 1;    
    uint8_t timer3_sync_mode      : 1;
    uint8_t timer3_prescaler      : 2;
    uint8_t timer3_rw_mode        : 1;
    uint8_t                       : 2; 
}timer3_t;

/*Section: Function Prototypes*/
STD_ReturnType hal_timer3_initialize(const timer3_t* timer3);
STD_ReturnType hal_timer3_deinitialize(const timer3_t* timer3);
STD_ReturnType hal_timer3_read_value(const timer3_t* timer3,uint16_t* value);
STD_ReturnType hal_timer3_write_value(const timer3_t* timer3,uint16_t value);
STD_ReturnType hal_timer3_select_clock_source(const timer3_t* timer3);
STD_ReturnType hal_timer3_synchronize_external_clock(const timer3_t* timer3);
STD_ReturnType hal_timer3_rw_8bit_16bit_mode(const timer3_t* timer3);
STD_ReturnType hal_timer3_set_prescaler(const timer3_t* timer3);

STD_ReturnType hal_timer3_interrupt_enable(const timer3_t* timer3);
STD_ReturnType hal_timer3_interrupt_disable(const timer3_t* timer3);
STD_ReturnType hal_timer3_enable(const timer3_t* timer3);
STD_ReturnType hal_timer3_disable(const timer3_t* timer3);
#endif	/* HAL_TIMER3_H */

