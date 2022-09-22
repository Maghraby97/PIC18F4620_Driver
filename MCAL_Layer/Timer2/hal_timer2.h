/* 
 * File:   hal_timer2.h
 * Author: Maghraby
 *
 * Created on June 24, 2022, 4:08 PM
 */

#ifndef HAL_TIMER_2_H
#define	HAL_TIMER_2_H

/* Section: Includes*/


#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "hal_timer2_config.h"

/*Section: Macro Declarations*/

#define TIMER2_MODULE_DISABLED    ((uint8_t)0)
#define TIMER2_MODULE_ENABLED     ((uint8_t)1)

#define TIMER2_PRESCALER_DIV_BY_1     ((uint8_t)0)
#define TIMER2_PRESCALER_DIV_BY_4     ((uint8_t)1)
#define TIMER2_PRESCALER_DIV_BY_16     ((uint8_t)2)

#define TIMER2_POSTSCALER_DIV_BY_1      ((uint8_t)0)
#define TIMER2_POSTSCALER_DIV_BY_2      ((uint8_t)1)
#define TIMER2_POSTSCALER_DIV_BY_3      ((uint8_t)2)
#define TIMER2_POSTSCALER_DIV_BY_4      ((uint8_t)3)
#define TIMER2_POSTSCALER_DIV_BY_5      ((uint8_t)4)
#define TIMER2_POSTSCALER_DIV_BY_6      ((uint8_t)5)
#define TIMER2_POSTSCALER_DIV_BY_7      ((uint8_t)6)
#define TIMER2_POSTSCALER_DIV_BY_8      ((uint8_t)7)
#define TIMER2_POSTSCALER_DIV_BY_9      ((uint8_t)8)
#define TIMER2_POSTSCALER_DIV_BY_10     ((uint8_t)9)
#define TIMER2_POSTSCALER_DIV_BY_11     ((uint8_t)10)
#define TIMER2_POSTSCALER_DIV_BY_12     ((uint8_t)11)
#define TIMER2_POSTSCALER_DIV_BY_13     ((uint8_t)12)
#define TIMER2_POSTSCALER_DIV_BY_14     ((uint8_t)13)
#define TIMER2_POSTSCALER_DIV_BY_15     ((uint8_t)14)
#define TIMER2_POSTSCALER_DIV_BY_16     ((uint8_t)15)

/*Section: Function Like Macros*/
#define Timer2_Module_Enable()  (T2CONbits.TMR2ON = 1)
#define Timer2_Module_Disable()  (T2CONbits.TMR2ON = 0)

#define Timer2_Set_Prescaler_Value(_Prescaler)  (T2CONbits.T2CKPS = _Prescaler)

#define Timer2_Set_Postscaler_Value(_Postscaler)  (T2CONbits.TOUTPS = _Postscaler)

/*Section: Data Type Declaration*/

typedef struct{
    /*don`t forget to add the interrupt handler callback function*/
    
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
    void (*TMR2_Handler)(void);
#endif
   
#if INTERRUPT_PRIORITY_FEATURE_USED   ==  INTERRUPT_PRIORITY_ENABLE
    uint8_t timer2_interrupt_priority_level;
#endif
    uint8_t timer2_preload_value;
    uint8_t timer2_prescaler_value  : 2 ;
    uint8_t timer2_postscaler_value : 4 ;
    uint8_t                  : 2 ;
    
}timer2_t;

/*Section: Function Prototypes*/
STD_ReturnType hal_timer2_initialize(const timer2_t* timer2);
STD_ReturnType hal_timer2_deinitialize(const timer2_t* timer2);
STD_ReturnType hal_timer2_read_value(const timer2_t* timer2,uint8_t* value);
STD_ReturnType hal_timer2_write_value(const timer2_t* timer2,uint8_t value);
#endif	/* HAL_TIMER_2_H */

