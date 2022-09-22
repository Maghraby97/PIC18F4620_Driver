/* 
 * File:   ecu_button.c
 * Author: Maghraby
 *
 * Created on March 18, 2022, 2:16 PM
 */

#include "ecu_button.h"

/**
 * 
 * @param button
 * @return 
 */
STD_ReturnType button_initialize(const Button_t *button){
    STD_ReturnType Status = E_OK;
    if(button != NULL){
        Status = gpio_pin_direction_initialize(&(button->button_pin));
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;
}

/**
 * 
 * @param button
 * @param state
 * @return 
 */
STD_ReturnType button_read_state(const Button_t *button,Button_State_t *state){
    STD_ReturnType Status = E_NOT_OK;
   // Button_State_t btn_state = button_released;
    
    Logic_t pin_logic_status = LOW;
    if(button != NULL && state != NULL){
        gpio_pin_read_logic(&(button->button_pin),&pin_logic_status);
        
        if(button->button_logic == button_active_high){
            if(pin_logic_status == HIGH){
                *state = button_pressed;
            }
            else{
                *state = button_released;
            }
        }
        else if(button->button_logic == button_active_low){
            if(pin_logic_status == HIGH){
                *state = button_released;
            }
            else{
               *state = button_pressed;
            }
            Status = E_OK;
        }
        else{
            /*Nothing*/
        }
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;
}
