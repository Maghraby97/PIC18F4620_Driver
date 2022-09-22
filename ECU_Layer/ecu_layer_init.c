/* 
 * File:   ecu_layer_init.c
 * Author: Maghraby
 *
 * Created on April 2, 2022, 8:39 PM
 */


#include "ecu_layer_init.h"
#include "Keypad/ecu_keypad.h"



chr_lcd_4bit_t lcd_1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = PIN0,
    .lcd_rs.direction = OUTPUT,
    .lcd_rs.logic = LOW,
    
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = PIN1,
    .lcd_en.direction = OUTPUT,
    .lcd_en.logic = LOW,
    
    .lcd_data[0].port =PORTC_INDEX ,
    .lcd_data[0].pin = PIN2,
    .lcd_data[0].direction = OUTPUT,
    .lcd_data[0].logic = LOW,
    
    .lcd_data[1].port =PORTC_INDEX ,
    .lcd_data[1].pin = PIN3,
    .lcd_data[1].direction = OUTPUT,
    .lcd_data[1].logic = LOW,
    
    .lcd_data[2].port =PORTC_INDEX ,
    .lcd_data[2].pin = PIN4,
    .lcd_data[2].direction = OUTPUT,
    .lcd_data[2].logic = LOW,
    
    .lcd_data[3].port =PORTC_INDEX ,
    .lcd_data[3].pin = PIN5,
    .lcd_data[3].direction = OUTPUT,
    .lcd_data[3].logic = LOW,

};


chr_lcd_8bit_t lcd_2 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = PIN6,
    .lcd_rs.direction = OUTPUT,
    .lcd_rs.logic = LOW,
    
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = PIN7,
    .lcd_en.direction = OUTPUT,
    .lcd_en.logic = LOW,
    
    .lcd_data[0].port =PORTD_INDEX ,
    .lcd_data[0].pin = PIN0,
    .lcd_data[0].direction = OUTPUT,
    .lcd_data[0].logic = LOW,
    
    .lcd_data[1].port =PORTD_INDEX ,
    .lcd_data[1].pin = PIN1,
    .lcd_data[1].direction = OUTPUT,
    .lcd_data[1].logic = LOW,
    
    .lcd_data[2].port =PORTD_INDEX ,
    .lcd_data[2].pin = PIN2,
    .lcd_data[2].direction = OUTPUT,
    .lcd_data[2].logic = LOW,
    
    .lcd_data[3].port =PORTD_INDEX ,
    .lcd_data[3].pin = PIN3,
    .lcd_data[3].direction = OUTPUT,
    .lcd_data[3].logic = LOW,
    
    .lcd_data[4].port =PORTD_INDEX ,
    .lcd_data[4].pin = PIN4,
    .lcd_data[4].direction = OUTPUT,
    .lcd_data[4].logic = LOW,
    
    .lcd_data[5].port =PORTD_INDEX ,
    .lcd_data[5].pin = PIN5,
    .lcd_data[5].direction = OUTPUT,
    .lcd_data[5].logic = LOW,
    
    .lcd_data[6].port =PORTD_INDEX ,
    .lcd_data[6].pin = PIN6,
    .lcd_data[6].direction = OUTPUT,
    .lcd_data[6].logic = LOW,
    
    .lcd_data[7].port =PORTD_INDEX ,
    .lcd_data[7].pin = PIN7,
    .lcd_data[7].direction = OUTPUT,
    .lcd_data[7].logic = LOW,
    
    

    

};




//
//Keypad_t  keypad ={
//    .keypad_rows[0].port = PORTC_INDEX,  
//    .keypad_rows[0].pin = PIN0,  
//    .keypad_rows[0].direction = OUTPUT,  
//    .keypad_rows[0].logic = LOW,  
//    
//    .keypad_rows[1].port = PORTC_INDEX,  
//    .keypad_rows[1].pin = PIN1,  
//    .keypad_rows[1].direction = OUTPUT,  
//    .keypad_rows[1].logic = LOW,
//    
//    .keypad_rows[2].port = PORTC_INDEX,  
//    .keypad_rows[2].pin = PIN2,  
//    .keypad_rows[2].direction = OUTPUT,  
//    .keypad_rows[2].logic = LOW,
//    
//    .keypad_rows[3].port = PORTC_INDEX,  
//    .keypad_rows[3].pin = PIN3,  
//    .keypad_rows[3].direction = OUTPUT,  
//    .keypad_rows[3].logic = LOW,
//    
//    
//    .keypad_columns[0].port = PORTC_INDEX,
//    .keypad_columns[0].pin = PIN4,    
//    .keypad_columns[0].direction = INPUT,    
//    .keypad_columns[0].logic = LOW,
//    
//    .keypad_columns[1].port = PORTC_INDEX,
//    .keypad_columns[1].pin = PIN5,    
//    .keypad_columns[1].direction = INPUT,    
//    .keypad_columns[1].logic = LOW,    
//    
//    .keypad_columns[2].port = PORTC_INDEX,
//    .keypad_columns[2].pin = PIN6,    
//    .keypad_columns[2].direction = INPUT,    
//    .keypad_columns[2].logic = LOW,    
//    
//    .keypad_columns[3].port = PORTC_INDEX,
//    .keypad_columns[3].pin = PIN7,    
//    .keypad_columns[3].direction = INPUT,    
//    .keypad_columns[3].logic = LOW,        
//    
//};




/**
 * 
 */
void ecu_layer_initialize(void){
    
    lcd_8bit_initialize(&lcd_2);
        lcd_4bit_initialize(&lcd_1);

}
