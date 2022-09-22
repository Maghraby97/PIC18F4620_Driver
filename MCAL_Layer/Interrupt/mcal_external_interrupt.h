/* 
 * File:   mcal_external_interrupt.h
 * Author: Maghraby
 *
 * Created on May 11, 2022, 1:56 AM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section: Includes*/

#include "mcal_interrupt_config.h"



/*Section: Macro Definitions*/


/*Section: Function Like Macros*/

#if INTERRUPT_EXTERNAL_FEATURE_USED == INTERRUPT_EXTERNAL_ENABLE

  //External interrupt INT0 

#define EXT_INT0_InterruptEnable()      (INTCONbits.INT0IE = 1)
#define EXT_INT0_InterruptDisable()     (INTCONbits.INT0IE = 0)
#define EXT_INT0_InterruptFlagClear()    (INTCONbits.INT0IF = 0)
#define EXT_INT0_RisingEdgeSelect()      (INTCON2bits.INTEDG0 = 1)
#define EXT_INT0_FallingEdgeSelect()     (INTCON2bits.INTEDG0 = 0)

  //External interrupt INT1

#define EXT_INT1_InterruptEnable()       (INTCON3bits.INT1IE = 1)
#define EXT_INT1_InterruptDisable()      (INTCON3bits.INT1IE = 0)
#define EXT_INT1_InterruptFlagClear()    (INTCON3bits.INT1IF = 0)
#define EXT_INT1_RisingEdgeSelect()      (INTCON2bits.INTEDG1 = 1)
#define EXT_INT1_FallingEdgeSelect()     (INTCON2bits.INTEDG1 = 0)

  //External interrupt INT2

#define EXT_INT2_InterruptEnable()       (INTCON3bits.INT2IE = 1)
#define EXT_INT2_InterruptDisable()      (INTCON3bits.INT2IE = 0)
#define EXT_INT2_InterruptFlagClear()    (INTCON3bits.INT2IF = 0)
#define EXT_INT2_RisingEdgeSelect()      (INTCON2bits.INTEDG2 = 1)
#define EXT_INT2_FallingEdgeSelect()     (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE

#define EXT_INT1_HighPrioritySet()   (INTCON3bits.INT1IP = 1)
#define EXT_INT1_LowPrioritySet()    (INTCON3bits.INT1IP = 0)

#define EXT_INT2_HighPrioritySet()   (INTCON3bits.INT2IP = 1)
#define EXT_INT2_LowPrioritySet()    (INTCON3bits.INT2IP = 0)

#endif


#endif

#if INTERRUPT_ON_CHANGE_FEATURE_USED == INTERRUPT_ON_CHANGE_ENABLE
    //Interrupt on Change 
#define EXT_RBx_InterruptEnable()    (INTCONbits.RBIE = 1)
#define EXT_RBx_InterruptDisable()   (INTCONbits.RBIE = 0)
#define EXT_RBx_InterruptFlagClear() (INTCONbits.RBIF = 0)



#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE

#define EXT_RBx_HighPrioritySet()     (INTCON2bits.RBIP = 1)
#define EXT_RBx_LowPrioritySet()      (INTCON2bits.RBIP = 0)


#endif


#endif

/*Section: Data Type Declaration*/
typedef void (*Int_Handler_High)(void);
typedef void (*Int_Handler_Low)(void);
typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
    
}interrupt_INTx_edge;

typedef enum{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2

}interrupt_INTx_src;




typedef struct{
    /*the EXT_InterruptHandler is a pointer to a function , why? in the APP layer we have a function that should be executed whenever an interrupt occurs at the 
      MCAL layer.The function is implemented in the APP layer.So to call it inside of the MCAL layer from the APP layer. We have to apply the concept of callback function
      so we need to store its address in the EXT_InterruptHandler pointer. and when an ISR occurs we call  that function within the ISR by using the help of the EXT_InterruptHandler
      pointer.
     * ?????? ???? ??? ?? ??? ??  ??? ??? ??????
     * Callback function 
     
     Example:
     void ISR(void){
        
        EXT_InterruptHandler();
      
    }
     */

    void(*EXT_InterruptHandler)(void); 
    Pin_Config_t mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src  src;
    interrupt_priority_cfg priority;

}interrupt_INTx_t;

typedef struct{
    void(*EXT_InterruptHandler_High)(void);
    void(*EXT_InterruptHandler_Low)(void);
    Pin_Config_t mcu_pin;
    interrupt_priority_cfg priority;
 
}interrupt_RBx_t;

/*Section: Function Prototypes*/

STD_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t* int_obj);
STD_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t* int_obj);
STD_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t* int_obj);
STD_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t* int_obj);

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8_t source);
void RB5_ISR(uint8_t source);
void RB6_ISR(uint8_t source);
void RB7_ISR(uint8_t source);
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

