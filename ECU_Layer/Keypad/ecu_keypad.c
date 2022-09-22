/* 
 * File:   ecu_keypad.?
 * Author: Maghraby
 *
 * Created on March 31, 2022, 3:36 PM
 */
#include "ecu_keypad.h"



/**
 * 
 * @param keypad
 * @return 
 */

static const uint8 keypad_btns[KEYPAD_NUMBER_OF_ROWS][KEYPAD_NUMBER_OF_COLUMNS]={
    
    {'7','8','9','/'},
    {'4','5','6','*'},
    {'1','2','3','-'},
    {'#','0','=','+'}  
};

STD_ReturnType keypad_initialize(const Keypad_t *keypad){
    STD_ReturnType Status = E_OK;
    if(keypad != NULL){
        for(uint8 row_counter = ZERO_INIT ; row_counter < KEYPAD_NUMBER_OF_ROWS ; row_counter++){
            gpio_pin_initialize(&(keypad->keypad_rows[row_counter]));
        }
        for(uint8 column_counter = ZERO_INIT ; column_counter < KEYPAD_NUMBER_OF_COLUMNS ; column_counter++){
            gpio_pin_direction_initialize(&(keypad->keypad_columns[column_counter]));
        }
    }
    else{
        Status = E_NOT_OK;
    }
    
    return Status;
}


/**
 * 
 * @param keypad
 * @param button_pressed
 * @return 
 */
STD_ReturnType keypad_get_pressed_button(const Keypad_t *keypad,uint8 *button_pressed){
    
    STD_ReturnType Status = E_NOT_OK;
    Logic_t logic = NOT_PRESSED;
    
    if(keypad != NULL && button_pressed != NULL){   
        for(uint8 row_number = ZERO_INIT ; row_number < KEYPAD_NUMBER_OF_ROWS ; row_number++){
            for(uint8 l_counter = ZERO_INIT; l_counter < KEYPAD_NUMBER_OF_ROWS ; l_counter++){
                gpio_pin_write_logic(&(keypad->keypad_rows[l_counter]),LOW);
            }
            gpio_pin_write_logic(&(keypad->keypad_rows[row_number]),HIGH);
            
            for(uint8 column_number = ZERO_INIT ; column_number < KEYPAD_NUMBER_OF_COLUMNS ; column_number++){
                gpio_pin_read_logic(&(keypad->keypad_columns[column_number]),&logic);
                if(logic == PRESSED){
                    *button_pressed = keypad_btns[row_number][column_number];
                    Status = E_OK;
                    logic = NOT_PRESSED;
                }
            }
            
        }
        
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
    
    
    
}