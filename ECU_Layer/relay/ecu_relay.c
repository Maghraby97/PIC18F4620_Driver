/* 
 * File:   ecu_relay.C
 * Author: Maghraby
 *
 * Created on March 20, 2022, 8:37 PM
 */

#include "ecu_relay.h"


/**
 * 
 * @param relay
 * @return 
 */
STD_ReturnType relay_initialize(const Relay_t *relay){
    STD_ReturnType Status = E_OK;
    if(relay != NULL){
        Pin_Config_t relay_pin = {
          .port = relay->relay_port,
          .pin  = (*relay).relay_pin,
          .direction = OUTPUT,
          .logic     = relay->relay_status
        };
        gpio_pin_initialize(&relay_pin);
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


/**
 * 
 * @param relay
 * @return 
 */
STD_ReturnType relay_On(const Relay_t *relay){
    STD_ReturnType Status = E_OK;
    if(relay != NULL){
        Pin_Config_t relay_pin = {
          .port = relay->relay_port,
          .pin  = (*relay).relay_pin,
          .direction = OUTPUT,
          .logic     = relay->relay_status
        };
        gpio_pin_write_logic(&relay_pin,HIGH);
        
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


/**
 * 
 * @param relay
 * @return 
 */
STD_ReturnType relay_Off(const Relay_t *relay){
    STD_ReturnType Status = E_OK;
    if(relay != NULL){
       Pin_Config_t relay_pin = {
          .port = relay->relay_port,
          .pin  = (*relay).relay_pin,
          .direction = OUTPUT,
          .logic     = relay->relay_status
        };
        gpio_pin_write_logic(&relay_pin,LOW); 
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


