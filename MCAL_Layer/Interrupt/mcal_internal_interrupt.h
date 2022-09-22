/* 
 * File:   mcal_internal_interrupt.h
 * Author: Maghraby
 *
 * Created on May 11, 2022, 1:57 AM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section: Includes*/


#include "mcal_interrupt_config.h"



/*Section: Macro Definitions*/


/*Section: Function Like Macros*/
#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
#define ADC_Interrupt_Enable()          (PIE1bits.ADIE = 1)
#define ADC_Interrupt_Clear_Flag()          (PIR1bits.ADIF = 0)

#define Timer0_Interrupt_Enable()           (INTCONbits.TMR0IE = 1)
#define Timer0_Clear_Interrupt_Flag()       (INTCONbits.TMR0IF = 0)

#define Timer1_Interrupt_Enable()           (PIE1bits.TMR1IE = 1)
#define Timer1_Clear_Interrupt_Flag()       (PIR1bits.TMR1IF = 0)

#define Timer2_Interrupt_Enable()           (PIE1bits.TMR2IE = 1)
#define Timer2_Clear_Interrupt_Flag()       (PIR1bits.TMR2IF = 0)

#define Timer3_Interrupt_Enable()           (PIE2bits.TMR3IE = 1)
#define Timer3_Clear_Interrupt_Flag()       (PIR2bits.TMR3IF = 0)

#define CCP1_Interrupt_Enable()             (PIE1bits.CCP1IE = 1)
#define CCP1_Clear_Interrupt_Flag()         (PIR1bits.CCP1IF = 0)

#define CCP2_Interrupt_Enable()             (PIE2bits.CCP2IE = 1)
#define CCP2_Clear_Interrupt_Flag()         (PIR2bits.CCP2IF = 0)

#define EUSART_Transmitter_Interrupt_Enable()           (PIE1bits.TXIE = 1)
#define EUSART_Receiver_Interrupt_Enable()              (PIE1bits.RCIE   = 1)

#endif

#define ADC_Interrupt_Disable()              (PIE1bits.ADIE = 0)
#define Timer0_Interrupt_Disable()           (INTCONbits.TMR0IE = 0)
#define Timer1_Interrupt_Disable()           (PIE1bits.TMR1IE = 0)
#define Timer2_Interrupt_Disable()           (PIE1bits.TMR2IE = 0)
#define Timer3_Interrupt_Disable()           (PIE2bits.TMR3IE = 0)
#define CCP1_Interrupt_Disable()             (PIE1bits.CCP1IE = 0)
#define CCP2_Interrupt_Disable()             (PIE2bits.CCP2IE = 0)
#define EUSART_Transmitter_Interrupt_Disable()        (PIE1bits.TXIE   = 0)
#define EUSART_Receiver_Interrupt_Disable()           (PIE1bits.RCIE   = 0)

#define CCP1_Clear_Interrupt_Flag()         (PIR1bits.CCP1IF = 0)
#define CCP2_Clear_Interrupt_Flag()         (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
#define ADC_Interrupt_SetHighPriority()     (IPR1bits.ADIP = 1)
#define ADC_Interrupt_SetLowPriority()      (IPR1bits.ADIP = 0)

#define Timer0_High_Priority_Set()          (INTCON2bits.TMR0IP = 1)
#define Timer0_Low_Priority_Set()           (INTCON2bits.TMR0IP = 0)

#define Timer1_High_Priority_Set()          (IPR1bits.TMR1IP = 1)
#define Timer1_Low_Priority_Set()           (IPR1bits.TMR1IP = 0)

#define Timer2_High_Priority_Set()          (IPR1bits.TMR2IP = 1)
#define Timer2_Low_Priority_Set()           (IPR1bits.TMR2IP = 0)

#define Timer3_High_Priority_Set()          (IPR2bits.TMR3IP = 1)
#define Timer3_Low_Priority_Set()           (IPR2bits.TMR3IP = 0)

#define CCP1_High_Priority_Set()            (IPR1bits.CCP1IP = 1)
#define CCP1_Low_Priority_Set()             (IPR1bits.CCP1IP = 0)

#define CCP2_High_Priority_Set()            (IPR2bits.CCP2IP = 1)
#define CCP2_Low_Priority_Set()             (IPR2bits.CCP2IP = 0)

#define EUSART_Transmitter_High_Priority_Set()          (IPR1bits.TXIP = 1)
#define EUSART_Transmitter_Low_Priority_Set()          (IPR1bits.TXIP  = 0)

#define EUSART_Receiver_High_Priority_Set()          (IPR1bits.RCIP = 1)
#define EUSART_Receiver_Low_Priority_Set()          (IPR1bits.RCIP  = 0)

#endif



/*Section: Data Type Declaration*/



/*Section: Function Prototypes*/
void ADC_ISR(void);
void Timer0_ISR(void);
void Timer1_ISR(void);
void Timer2_ISR(void);
void Timer3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void EUSART_TX_Isr(void);
void EUSART_RX_Isr(void);

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

