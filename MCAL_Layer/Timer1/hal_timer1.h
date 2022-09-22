/* 
 * File:   hal_timer1.h
 * Author: Maghraby
 *
 * Created on June 17, 2022, 1:16 PM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* Section: Includes*/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "hal_timer1_config.h"


/*Section: Macro Declarations*/

#define TIMER1_COUNTER_MODE            1
#define TIMER1_TIMER_MODE              0

#define TIMER1_ASYNC_COUNTER_MODE      1
#define TIMER1_SYNC_COUNTER_MODE       0

#define TIMER1_OSCILLATOR_ENABLE       1
#define TIMER1_OSCILLATOR_DISABLE      0

#define TIMER1_PRESCALER_DIV_BY_1      0
#define TIMER1_PRESCALER_DIV_BY_2      1
#define TIMER1_PRESCALER_DIV_BY_4      2
#define TIMER1_PRESCALER_DIV_BY_8      3

#define TIMER1_RW_REG_8Bit_MODE        0
#define TIMER1_RW_REG_16Bit_MODE       1

#define TIMER1_INTERNAL_CLOCK_SOURCE   0
#define TIMER1_EXTERNAL_CLOCK_SOURCE   1

/*Section: Function Like Macros*/

#define Timer1_Module_Enable()  (T1CONbits.TMR1ON = 1)
#define Timer1_Module_Disable()  (T1CONbits.TMR1ON  = 0)


#define Timer1_Select_External_Clock_Source()  (T1CONbits.TMR1CS = 1)
#define Timer1_Select_Internal_Clock_Source()  (T1CONbits.TMR1CS = 0)

#define Timer1_Asynchronous_External_Clock_Input() (T1CONbits.nT1SYNC = 1)
#define Timer1_Synchronous_External_Clock_Input() (T1CONbits.nT1SYNC = 0)

#define Timer1_Oscillator_Enable()       (T1CONbits.T1OSCEN = 1)
#define Timer1_Oscillator_Disable()       (T1CONbits.T1OSCEN = 0)

#define Timer1_Set_Prescaler_Value(_Prescaler)   (T1CONbits.T1CKPS = _Prescaler)

#define Timer1_Is_Device_Clock_From_Timer1_Oscillator()  (T1CONbits.T1RUN)

#define Timer1_RW_16bit_Operation() (T1CONbits.RD16 = 1)
#define Timer1_RW_8bit_Operation()  (T1CONbits.RD16 = 0)


/*Section: Data Type Declaration*/
typedef struct{
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
    void (*TMR1_Handler)(void);
    uint8_t timer1_interrupt_priority_level;
#endif
    uint16_t timer1_preload_value;
    uint8_t timer1_mode;
    uint8_t timer1_clock_source   : 1;    
    uint8_t timer1_sync_mode      : 1;
    uint8_t timer1_Osc            : 1;
    uint8_t timer1_prescaler      : 2;
    uint8_t timer1_rw_mode        : 1;
    uint8_t                       : 2;
    
}timer1_t;


/*Section: Function Prototypes*/
STD_ReturnType hal_timer1_initialize(const timer1_t* timer1);
STD_ReturnType hal_timer1_deinitialize(const timer1_t* timer1);
STD_ReturnType hal_timer1_read_value(const timer1_t* timer1,uint16_t* value);
STD_ReturnType hal_timer1_write_value(const timer1_t* timer1,uint16_t value);
STD_ReturnType hal_timer1_select_clock_source(const timer1_t* timer1);
STD_ReturnType hal_timer1_synchronize_external_clock(const timer1_t* timer1);
STD_ReturnType hal_timer1_rw_8bit_16bit_mode(const timer1_t* timer1);
STD_ReturnType hal_timer1_set_prescaler(const timer1_t* timer1);
STD_ReturnType hal_timer1_config_timer1_oscillator(const timer1_t* timer1);
STD_ReturnType hal_timer1_interrupt_enable(const timer1_t* timer1);
STD_ReturnType hal_timer1_interrupt_disable(const timer1_t* timer1);
STD_ReturnType hal_timer1_enable(const timer1_t* timer1);
STD_ReturnType hal_timer1_disable(const timer1_t* timer1);
#endif	/* HAL_TIMER1_H */

