/* 
 * File:   ecu_led.c
 * Author: Maghraby
 *
 * Created on February 26, 2022, 3:51 PM
 */

#include "ecu_led.h"


/**
 * 
 * @param led
 * @return 
 */
STD_ReturnType led_initialize(const led_t* led){
    STD_ReturnType Status = E_OK;
    
    if(led != NULL){
        Pin_Config_t pin_obj={
            .port      = led->port_name,
            .pin       = led->port_pin,
            .direction = OUTPUT,
            .logic     = led->led_status
        };
        gpio_pin_initialize(&pin_obj);
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;
}


/**
 * 
 * @param led
 * @return 
 */
STD_ReturnType led_turn_on(const led_t* led){
    STD_ReturnType Status = E_OK;
    
    if(led != NULL){
        Pin_Config_t pin_obj={
            .port      = led->port_name,
            .pin       = led->port_pin,
            .direction = OUTPUT,
            .logic     = led->led_status
        };       
        gpio_pin_write_logic(&pin_obj,HIGH);
    }
    else{
        Status = E_NOT_OK;
        
    }
    return Status;
}


/**
 * 
 * @param led
 * @return 
 */
STD_ReturnType led_turn_off(const led_t* led){
    STD_ReturnType Status = E_OK;
    
    if(led != NULL){
        Pin_Config_t pin_obj={
            .port      = led->port_name,
            .pin       = led->port_pin,
            .direction = OUTPUT,
            .logic     = led->led_status
        };       
        gpio_pin_write_logic(&pin_obj,LOW);   
    }
    else{
        Status = E_NOT_OK;
        
        
    }
    return Status;
}


/**
 * 
 * @param led
 * @return 
 */
STD_ReturnType led_toggle(const led_t* led){
    STD_ReturnType Status = E_OK;
    
    if(led != NULL){
        Pin_Config_t pin_obj={
            .port      = led->port_name,
            .pin       = led->port_pin,
            .direction = OUTPUT,
            .logic     = led->led_status
        };       
        gpio_pin_toggle_logic(&pin_obj);        
    }
    else{
        Status = E_NOT_OK;
        
    }
    return Status;
}
