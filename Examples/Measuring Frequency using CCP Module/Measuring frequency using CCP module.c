/*
 * File:   application.c
 * Author: Maghraby
 *
 * Created on February 26, 2022, 2:43 PM
 */
#include "application.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/Interrupt/mcal_interrupt_manager.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/Timer0/hal_timer0.h"
#include "MCAL_Layer/Timer1/hal_timer1.h"
#include "MCAL_Layer/Timer2/hal_timer2.h"
#include "MCAL_Layer/Timer3/hal_timer3.h"
#include "MCAL_Layer/CCP1/hal_ccp1.h"
#define _XTAL_FREQ 4000000

volatile uint16_t ovf = 0;
volatile uint16_t last_ovf = 0;
volatile uint16_t start = 0;
volatile uint16_t end = 0;
volatile uint8_t st_en_flag = 0;
volatile uint8_t second_edge_flag = 0;
volatile uint32_t period = 0;
volatile uint32_t freq = 0;
void timer1_app_isr(void);
void ccp1_app_isr(void);
chr_lcd_8bit_t lcd8bit = {
    .lcd_rs.direction = OUTPUT,
    .lcd_rs.logic = LOW,
    .lcd_rs.pin = PIN0,
    .lcd_rs.port = PORTD_INDEX,
    
    .lcd_en.direction = OUTPUT,
    .lcd_en.logic = LOW ,
    .lcd_en.pin = PIN1,
    .lcd_en.port = PORTD_INDEX,
    
    .lcd_data[0].direction = OUTPUT,
    .lcd_data[0].port = PORTB_INDEX,
    .lcd_data[0].pin = PIN0,
    .lcd_data[0].logic = LOW,
    
    .lcd_data[1].direction = OUTPUT,
    .lcd_data[1].port = PORTB_INDEX,
    .lcd_data[1].pin = PIN1,
    .lcd_data[1].logic = LOW,
    
    .lcd_data[2].direction = OUTPUT,
    .lcd_data[2].port = PORTB_INDEX,
    .lcd_data[2].pin = PIN2,
    .lcd_data[2].logic = LOW,
    
    .lcd_data[3].direction = OUTPUT,
    .lcd_data[3].port = PORTB_INDEX,
    .lcd_data[3].pin = PIN3,
    .lcd_data[3].logic = LOW,
    
    .lcd_data[4].direction = OUTPUT,
    .lcd_data[4].port = PORTB_INDEX,
    .lcd_data[4].pin = PIN4,
    .lcd_data[4].logic = LOW,
    
    .lcd_data[5].direction = OUTPUT,
    .lcd_data[5].port = PORTB_INDEX,
    .lcd_data[5].pin = PIN5,
    .lcd_data[5].logic = LOW,
    
    .lcd_data[6].direction = OUTPUT,
    .lcd_data[6].port = PORTB_INDEX,
    .lcd_data[6].pin = PIN6,
    .lcd_data[6].logic = LOW,
    
    .lcd_data[7].direction = OUTPUT,
    .lcd_data[7].port = PORTB_INDEX,
    .lcd_data[7].pin = PIN7,
    .lcd_data[7].logic = LOW,
};

Pin_Config_t ccp1_pin = {
    .direction = INPUT,
    .pin = PIN2,
    .port = PORTC_INDEX
};

ccp_t ccp1obj = {
    .CCP1_Handler = ccp1_app_isr,
    .ccp1_interrupt_priority_level = INTERRUPT_PRIORITY_HIGH,
    .ccp_mode = CCP_CAPTURE_MODE_,
    .ccp_submode = CCP_CAPTURE_MODE_EVERY_RISING_EDGE ,
    .cpp_instance = CCP1_INSTANCE,
};

timer1_t tmr1 = {
    
    .TMR1_Handler = timer1_app_isr,
    .timer1_interrupt_priority_level = INTERRUPT_PRIORITY_HIGH,
    .timer1_preload_value = 0,
    .timer1_mode = TIMER1_TIMER_MODE,
    .timer1_clock_source = TIMER1_INTERNAL_CLOCK_SOURCE,
    .timer1_prescaler = TIMER1_PRESCALER_DIV_BY_1,
    .timer1_rw_mode = TIMER1_RW_REG_16Bit_MODE
};



void ccp1_app_isr(){
    second_edge_flag++;
    if(st_en_flag == 0){
        TMR1 = 0;
        start = 0;
        hal_timer1_enable(&tmr1);                  
    }
    else if(st_en_flag == 1){  
        last_ovf = ovf;
        ovf = 0;     
        hal_ccp_readCaptureValue(&ccp1obj,&end);
        hal_timer1_disable(&tmr1);                 
    }
    st_en_flag ^= 1;
}
void timer1_app_isr(){
    ovf++;
}
int main(void){  

    
    lcd_8bit_initialize(&lcd8bit);   
    hal_ccp_init(&ccp1obj);
    gpio_pin_direction_initialize(&ccp1_pin);
    hal_timer1_initialize(&tmr1);
    /*Selecting timer1 as the capture source for CCP1 module*/
    T3CONbits.T3CCP2 = 0;
    T3CONbits.T3CCP1 = 0;
    
    char arr[4]={0};
    lcd_8bit_send_string(&lcd8bit,"Frequency");
    lcd_8bit_send_char_data(&lcd8bit,'=');
    while(1){
        if(second_edge_flag == 2){
            period = end + (last_ovf * 65536);
            freq = (uint32_t)(1 / (period / 1000000.0));
            second_edge_flag = 0;            
        }
        
        convert_byte_to_string(freq,arr);
        lcd_8bit_send_string_pos(&lcd8bit,1,11,arr);
        
        
    }
    
    
    
    
    return (EXIT_SUCCESS);
}
