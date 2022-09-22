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
#include "MCAL_Layer/EUSART/hal_eusart.h"
#include "MCAL_Layer/SPI/hal_spi.h"
#include "string.h"
#define _XTAL_FREQ 8000000






/*Slave 
 chr_lcd_8bit_t lcd_8 = {
 .lcd_rs.port = PORTA_INDEX,
 .lcd_rs.pin = PIN0,
 .lcd_rs.direction = OUTPUT,
 .lcd_rs.logic = LOW,
 
 .lcd_en.port =PORTA_INDEX,
 .lcd_en.pin = PIN1,
 .lcd_en.direction = OUTPUT,
 .lcd_en.logic = HIGH,
 
 .lcd_data[0].port = PORTB_INDEX,
 .lcd_data[0].pin = PIN0,
 .lcd_data[0].direction= OUTPUT,
 .lcd_data[0].logic = LOW,
 
 .lcd_data[1].port = PORTB_INDEX,
 .lcd_data[1].pin = PIN1,
 .lcd_data[1].direction= OUTPUT,
 .lcd_data[1].logic = LOW,
 
 .lcd_data[2].port = PORTB_INDEX,
 .lcd_data[2].pin = PIN2,
 .lcd_data[2].direction= OUTPUT,
 .lcd_data[2].logic = LOW,
 
 .lcd_data[3].port = PORTB_INDEX,
 .lcd_data[3].pin = PIN3,
 .lcd_data[3].direction= OUTPUT,
 .lcd_data[3].logic = LOW,
 
 .lcd_data[4].port = PORTB_INDEX,
 .lcd_data[4].pin = PIN4,
 .lcd_data[4].direction= OUTPUT,
 .lcd_data[4].logic = LOW,
 
 .lcd_data[5].port = PORTB_INDEX,
 .lcd_data[5].pin = PIN5,
 .lcd_data[5].direction= OUTPUT,
 .lcd_data[5].logic = LOW,
 
 .lcd_data[6].port = PORTB_INDEX,
 .lcd_data[6].pin = PIN6,
 .lcd_data[6].direction= OUTPUT,
 .lcd_data[6].logic = LOW,
 
 .lcd_data[7].port = PORTB_INDEX,
 .lcd_data[7].pin = PIN7,
 .lcd_data[7].direction= OUTPUT,
 .lcd_data[7].logic = LOW,
 };
 
 
 uint8 receivedBuffer[30] = {0};
 */





#define SECONDS_R_SEGMENT  1
#define SECONDS_L_SEGMENT  2
#define MINUTES_R_SEGMENT  3
#define MINUTES_L_SEGMENT  4
#define HOURS_R_SEGMENT  5
#define HOURS_L_SEGMENT  6



#define TOTAL_NUMBER_OF_7_SEGMENTS  6



//define timer0 configuration

void TMR_ISR(void);

timer0_t tmr0 ={
    .TMR0_Handler = TMR_ISR,
    .mode = TIMER0_TIMER_MODE,
    .register_size = TIMER0_REGISTER_16BIT,
    .clocksrc = TIMER0_CLOCK_SOURCE_INTERNAL,
    .edge_incr = TIMER0_INCREMENT_ON_RISING_EDGE,
    .prescaler_enable_bit = TIMER0_PRESCALER_ENABLED,
    .prescaler_value = TIMER0_PSF_DIV_BY_32,
    .preloaded_value = 3036
};

Pin_Config_t rd0={
    .port = PORTD_INDEX,
    .pin = PIN0,
    .direction = OUTPUT,
    .logic = LOW
};
Pin_Config_t rd1={
    .port = PORTD_INDEX,
    .pin = PIN1,
    .direction = OUTPUT,
    .logic = LOW
};
Pin_Config_t rd2={
    .port = PORTD_INDEX,
    .pin = PIN2,
    .direction = OUTPUT,
    .logic = LOW
};
Pin_Config_t rd3={
    .port = PORTD_INDEX,
    .pin = PIN3,
    .direction = OUTPUT,
    .logic = LOW
};

Pin_Config_t rd4={
    .port = PORTD_INDEX,
    .pin = PIN4,
    .direction = OUTPUT,
    .logic = LOW
};   

Pin_Config_t rd5={
    .port = PORTD_INDEX,
    .pin = PIN5,
    .direction = OUTPUT,
    .logic = LOW
};


//pin of port C 


Pin_Config_t rc0={
    .port = PORTC_INDEX,
    .pin = PIN0,
    .direction = OUTPUT,
    .logic = LOW
};
Pin_Config_t rc1={
    .port = PORTC_INDEX,
    .pin = PIN1,
    .direction = OUTPUT,
    .logic = LOW
};
Pin_Config_t rc2={
    .port = PORTC_INDEX,
    .pin = PIN2,
    .direction = OUTPUT,
    .logic = LOW
};
Pin_Config_t rc3={
    .port = PORTC_INDEX,
    .pin = PIN3,
    .direction = OUTPUT,
    .logic = LOW
};

Pin_Config_t rc4={
    .port = PORTC_INDEX,
    .pin = PIN4,
    .direction = OUTPUT,
    .logic = LOW
};   

Pin_Config_t rc5={
    .port = PORTC_INDEX,
    .pin = PIN5,
    .direction = OUTPUT,
    .logic = LOW
};

Pin_Config_t rc6={
    .port = PORTC_INDEX,
    .pin = PIN6,
    .direction = OUTPUT,
    .logic = LOW
};


//keypad pins configuration]

Keypad_t keypad1 = {
    .keypad_rows[0].port = PORTB_INDEX,
    .keypad_rows[0].pin = PIN0,
    .keypad_rows[0].direction = OUTPUT,
    .keypad_rows[0].logic = LOW,
    
    .keypad_rows[1].port = PORTB_INDEX,
    .keypad_rows[1].pin = PIN1,
    .keypad_rows[1].direction = OUTPUT,
    .keypad_rows[1].logic = LOW,
    
    .keypad_rows[2].port = PORTB_INDEX,
    .keypad_rows[2].pin = PIN2,
    .keypad_rows[2].direction = OUTPUT,
    .keypad_rows[2].logic = LOW,  
    
    .keypad_rows[3].port = PORTB_INDEX,
    .keypad_rows[3].pin = PIN3,
    .keypad_rows[3].direction = OUTPUT,
    .keypad_rows[3].logic = LOW,  
    
    
    .keypad_columns[0].port = PORTB_INDEX,
    .keypad_columns[0].pin = PIN4,
    .keypad_columns[0].direction = INPUT,
    .keypad_columns[0].logic = LOW, 
    
    .keypad_columns[1].port = PORTB_INDEX,
    .keypad_columns[1].pin = PIN5,
    .keypad_columns[1].direction = INPUT,
    .keypad_columns[1].logic = LOW,
    
    .keypad_columns[2].port = PORTB_INDEX,
    .keypad_columns[2].pin = PIN6,
    .keypad_columns[2].direction = INPUT,
    .keypad_columns[2].logic = LOW,
    
    .keypad_columns[3].port = PORTB_INDEX,
    .keypad_columns[3].pin = PIN7,
    .keypad_columns[3].direction = INPUT,
    .keypad_columns[3].logic = LOW
};

//LCD Configuration
chr_lcd_8bit_t lcd_8 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = PIN4,
    .lcd_rs.direction = OUTPUT,
    .lcd_rs.logic = LOW,
    
    .lcd_en.port =PORTC_INDEX,
    .lcd_en.pin = PIN5,
    .lcd_en.direction = OUTPUT,
    .lcd_en.logic = HIGH,
    
    
    .lcd_data[0].port = PORTE_INDEX,
    .lcd_data[0].pin = PIN0,
    .lcd_data[0].direction= OUTPUT,
    .lcd_data[0].logic = LOW,
    
    .lcd_data[1].port = PORTE_INDEX,
    .lcd_data[1].pin = PIN1,
    .lcd_data[1].direction= OUTPUT,
    .lcd_data[1].logic = LOW,
    
    .lcd_data[2].port = PORTA_INDEX,
    .lcd_data[2].pin = PIN0,
    .lcd_data[2].direction= OUTPUT,
    .lcd_data[2].logic = LOW,
    
    .lcd_data[3].port = PORTA_INDEX,
    .lcd_data[3].pin = PIN1,
    .lcd_data[3].direction= OUTPUT,
    .lcd_data[3].logic = LOW,
    
    .lcd_data[4].port = PORTC_INDEX,
    .lcd_data[4].pin = PIN6,
    .lcd_data[4].direction= OUTPUT,
    .lcd_data[4].logic = LOW,
    
    .lcd_data[5].port = PORTC_INDEX,
    .lcd_data[5].pin = PIN7,
    .lcd_data[5].direction= OUTPUT,
    .lcd_data[5].logic = LOW,
    
    .lcd_data[6].port = PORTD_INDEX,
    .lcd_data[6].pin = PIN6,
    .lcd_data[6].direction= OUTPUT,
    .lcd_data[6].logic = LOW,
    
    .lcd_data[7].port = PORTD_INDEX,
    .lcd_data[7].pin = PIN7,
    .lcd_data[7].direction= OUTPUT,
    .lcd_data[7].logic = LOW,
    
    
};    

uint8_t r = 0;
uint8_t l = 0;
volatile uint32_t t_counter = 0;
volatile uint8_t seconds = 55;
volatile uint8_t minutes = 59;
volatile uint8_t hours = 0;
uint8_t   key_pressed = 0;
uint8_t m = 0;
uint8_t set_clock_array[6] = {0};
uint8_t first_digit = 0;
uint8_t second_digit = 0;
uint8_t third_digit = 0;
uint8_t fourth_digit = 0;
uint8_t fifth_digit = 0;
uint8_t sixth_digit = 0;
uint8_t first_digit_done = 0;
uint8_t second_digit_done = 0;
uint8_t third_digit_done = 0;
uint8_t fourth_digit_done = 0;
uint8_t fifth_digit_done = 0;
uint8_t sixth_digit_done = 0;
int main(void){  
    Pin_Config_t _7_Segments_Arr[7]={rc0,rc1,rc2,rc3,rc4,rc5,rc6};
    Pin_Config_t _7_Segments_Arr_Common_Control[6] = {rd0,rd1,rd2,rd3,rd4,rd5};
    lcd_8bit_initialize(&lcd_8);
    lcd_8bit_send_string_pos(&lcd_8,1,1,"initialising");
    for(int i = 0 ; i < 5; i++){
        
        lcd_8bit_send_string_pos(&lcd_8,1,13+i,".");
        __delay_ms(200);
        
    }
    keypad_initialize(&keypad1);
    
    
    gpio_pin_initialize(&rc0);
    gpio_pin_initialize(&rc1);
    gpio_pin_initialize(&rc2);
    gpio_pin_initialize(&rc3);
    gpio_pin_initialize(&rc4);
    gpio_pin_initialize(&rc5);
    gpio_pin_initialize(&rc6);
    
    gpio_pin_initialize(&rd0);
    gpio_pin_initialize(&rd1);
    gpio_pin_initialize(&rd2);
    gpio_pin_initialize(&rd3);
    gpio_pin_initialize(&rd4);
    gpio_pin_initialize(&rd5);
    
    
    hal_timer0_initialize(&tmr0);
    
    lcd_8bit_send_command(&lcd_8,_LCD_CLEAR);
    
    
    int lcd_message  = 1;
    while(1){
        
        keypad_get_pressed_button(&keypad1,&key_pressed);
        if(lcd_message == 1){
            lcd_8bit_send_command(&lcd_8,_LCD_CLEAR);
            lcd_8bit_send_string_pos(&lcd_8,1,1,"Press + To Set Clock");
            lcd_8bit_send_string_pos(&lcd_8,2,1,"Press ON/C To Reset Clock");
            lcd_message = 0;
        }
        if(key_pressed == '#'){
            minutes = 0;
            seconds = 0;
            hours = 0;
            key_pressed = '*';
        }
        else if(key_pressed == '+'){
            lcd_8bit_send_command(&lcd_8,_LCD_CLEAR);
            lcd_8bit_send_string_pos(&lcd_8,1,1,"Setting Clock...");
            hal_timer0_interrupt_disable(&tmr0);
            __delay_ms(300);
            do{
                first_digit_done = keypad_get_pressed_button(&keypad1,&first_digit); 
            }while(first_digit_done == 0);
            set_clock_array[0] = first_digit;
            __delay_ms(300);
            
            
            do{
                second_digit_done = keypad_get_pressed_button(&keypad1,&second_digit); 
            }while(second_digit_done == 0);
            set_clock_array[1] = second_digit;
            __delay_ms(300);
            
            do{
                third_digit_done = keypad_get_pressed_button(&keypad1,&third_digit); 
            }while(third_digit_done == 0);
            set_clock_array[2] = third_digit;
            
            __delay_ms(300);
            
            do{
                fourth_digit_done = keypad_get_pressed_button(&keypad1,&fourth_digit); 
            }while(fourth_digit_done == 0);
            set_clock_array[3] = fourth_digit;
            __delay_ms(300);
            
            do{
                fifth_digit_done = keypad_get_pressed_button(&keypad1,&fifth_digit); 
            }while(fifth_digit_done == 0);
            set_clock_array[4] = fifth_digit;
            __delay_ms(300);
            
            do{
                sixth_digit_done = keypad_get_pressed_button(&keypad1,&sixth_digit); 
            }while(sixth_digit_done == 0);
            set_clock_array[5] = sixth_digit;
            __delay_ms(300);
            
            key_pressed = '.';
            seconds = (second_digit-48)+((first_digit-48)*10);
            minutes = (fourth_digit-48 )+((third_digit-48) *10);
            hours = (sixth_digit-48)+((fifth_digit-48)*10);
            if(seconds >= 60)
                seconds = 0;
            if(minutes >= 60)
                minutes = 0;
            if(hours >= 24)
                hours = 0;
            lcd_message = 1;
            hal_timer0_interrupt_enable(&tmr0);
        }
        else{
            
            r = seconds%10;
            l = seconds/10;
            gpio_pin_write_logic(&rd0,HIGH);
            gpio_port_write_logic(PORTC_INDEX,r);
            __delay_us(100);
            gpio_pin_write_logic(&rd0,LOW);
            __delay_us(100);
            gpio_pin_write_logic(&rd1,HIGH);
            gpio_port_write_logic(PORTC_INDEX,l);
            __delay_us(100);
            gpio_pin_write_logic(&rd1,LOW);    
            __delay_us(100);
            
            
            r = minutes%10;
            l = minutes/10;
            gpio_pin_write_logic(&rd2,HIGH);
            gpio_port_write_logic(PORTC_INDEX,r);
            __delay_us(100);
            gpio_pin_write_logic(&rd2,LOW);
            __delay_us(100);
            gpio_pin_write_logic(&rd3,HIGH);
            gpio_port_write_logic(PORTC_INDEX,l);
            __delay_us(100);
            gpio_pin_write_logic(&rd3,LOW);    
            __delay_us(100);
            
            
            r = hours%10;
            l = hours/10;
            gpio_pin_write_logic(&rd4,HIGH);
            gpio_port_write_logic(PORTC_INDEX,r);
            __delay_us(100);
            gpio_pin_write_logic(&rd4,LOW);
            __delay_us(100);
            gpio_pin_write_logic(&rd5,HIGH);
            gpio_port_write_logic(PORTC_INDEX,l);
            __delay_us(100);
            gpio_pin_write_logic(&rd5,LOW);    
            __delay_us(100);
        }
        
        
    }
    return (EXIT_SUCCESS);
}


void TMR_ISR(void){
    t_counter++;
    seconds++;
    if(seconds >= 60){
        seconds = 0;
        t_counter=0;
        minutes++;
        if(minutes >= 60){
            minutes = 0;
            hours++;
            if(hours >= 24){
                hours = 0;
                
            }
            else{
                
            }
        }
    }
    
}





//void application_init(void){
//    
//    ecu_layer_initialize();
//    
//}
