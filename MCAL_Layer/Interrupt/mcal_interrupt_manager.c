/* 
 * File:   mcal_interrupt_manager.c
 * Author: Maghraby
 *
 * Created on May 11, 2022, 1:57 AM
 */


#include "mcal_interrupt_manager.h"
#define _XTAL_FREQ 8000000

static uint8_t RB4_Flag = 1;
static uint8_t RB5_Flag = 1;
static uint8_t RB6_Flag = 1;
static uint8_t RB7_Flag = 1;



#if INTERRUPT_FEATURE_USED == INTERRUPT_ENABLE
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE

void __interrupt() InterruptManagerHigh(void){
   if((INTCONbits.INT0IE == INTERRUPT_ENABLE)&&(INTCONbits.INT0IF == INTERRUPT_OCCURED)){
        INT0_ISR();
    }

    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE)&&(INTCON3bits.INT2IF == INTERRUPT_OCCURED)){
        INT2_ISR();
    }
    
}
void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE)&&(INTCON3bits.INT1IF == INTERRUPT_OCCURED)){
        INT1_ISR();
    }
    

}

#else

void __interrupt() InterruptManager(void){
    
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE)&&(INTCONbits.INT0IF == INTERRUPT_OCCURED)){
        INT0_ISR();
    }
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE)&&(INTCON3bits.INT1IF == INTERRUPT_OCCURED)){
        INT1_ISR();
    }
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE)&&(INTCON3bits.INT2IF == INTERRUPT_OCCURED)){
        INT2_ISR();
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURED)&&(PORTBbits.RB4 == HIGH) && (RB4_Flag == 1)){
        RB4_Flag = 0;
        RB4_ISR(0);  
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURED)&& (PORTBbits.RB4 == LOW) && (RB4_Flag == 0)){
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURED)&&(PORTBbits.RB5 == HIGH) && (RB5_Flag == 1)){
        RB5_Flag = 0;
        RB5_ISR(0);  
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURED)&& (PORTBbits.RB5 == LOW) && (RB5_Flag == 0)){
        RB5_Flag = 1;
       RB5_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURED)&&(PORTBbits.RB6 == HIGH) && (RB6_Flag == 1)){
        RB6_Flag = 0;
        RB6_ISR(0);  
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURED)&& (PORTBbits.RB6 == LOW) && (RB6_Flag == 0)){
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURED)&&(PORTBbits.RB7 == HIGH) && (RB7_Flag == 1)){
        RB7_Flag = 0;
        RB7_ISR(0);  
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_OCCURED)&& (PORTBbits.RB7 == LOW) && (RB7_Flag == 0)){
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF == INTERRUPT_OCCURED)){
        ADC_ISR();
    }
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCURED == INTCONbits.TMR0IF)){
        Timer0_ISR();
    }
    if((INTERRUPT_ENABLE == PIE1bits.TMR1IE) && (INTERRUPT_OCCURED == PIR1bits.TMR1IF)){
        Timer1_ISR();
    }
    if((INTERRUPT_ENABLE == PIE1bits.TMR2IE) && (INTERRUPT_OCCURED == PIR1bits.TMR2IF)){
        Timer2_ISR();
    }
    if((INTERRUPT_ENABLE == PIE2bits.TMR3IE) && (INTERRUPT_OCCURED == PIR2bits.TMR3IF)){
        Timer3_ISR();
    }
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCURED == PIR1bits.CCP1IF)){
        CCP1_ISR();
    }
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCURED == PIR2bits.CCP2IF)){
        CCP2_ISR();
    }
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCURED == PIR1bits.TXIF)){
        EUSART_TX_Isr();
    }
    
}


#endif
#endif