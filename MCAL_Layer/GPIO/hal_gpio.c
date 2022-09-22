/* 
 * File:   hal_gpio.c
 * Author: Maghraby
 *
 * Created on February 26, 2022, 2:43 PM
 */

#include "hal_gpio.h"

volatile uint8 *tris_registers[]=   {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE}; 
volatile uint8 *lat_registers[] =   {&LATA , &LATB , &LATC , &LATD , &LATE}; 
volatile uint8 *port_registers[]=   {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE}; 

/**
 * @brief Initialize the direction of a specific pin
 * @param pin_config pointer to the configuration @ref Pin_Config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */

#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
STD_ReturnType gpio_pin_direction_initialize(const Pin_Config_t * pin_config){
    STD_ReturnType Status = E_OK;
    if(pin_config != NULL && pin_config->pin < PORT_PIN_MAX_NUMBER){
        switch(pin_config->direction){
            case OUTPUT:
              CLEAR_BIT(*tris_registers[pin_config->port],pin_config->pin);
                break;
            case INPUT:
              SET_BIT(*tris_registers[pin_config->port],pin_config->pin);
                break;    
            default:
                Status = E_NOT_OK;
                break;
        }
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;
}

#endif
/**
 * 
 * @param pin_config
 * @param direction_status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS   == CONFIG_ENABLE
STD_ReturnType gpio_pin_get_direction_status(const Pin_Config_t * pin_config , Direction_t * direction_status){
    STD_ReturnType Status = E_OK;
    if(pin_config != NULL  && direction_status != NULL && pin_config->pin < PORT_PIN_MAX_NUMBER){
           *direction_status = READ_BIT(*tris_registers[pin_config->port],pin_config->pin);
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;
}
#endif
/**
 * 
 * @param pin_config
 * @param logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS   == CONFIG_ENABLE
STD_ReturnType gpio_pin_write_logic(const Pin_Config_t * pin_config , Logic_t logic){
    STD_ReturnType Status = E_OK;
    if(pin_config != NULL && pin_config->pin < PORT_PIN_MAX_NUMBER){
        switch(logic){
            case HIGH:
                SET_BIT(*lat_registers[pin_config->port],pin_config->pin);
                break;
            case LOW:
                CLEAR_BIT(*lat_registers[pin_config->port],pin_config->pin);
                break;
            default:
                Status = E_NOT_OK;
                break;
        }
    }
    else{
        Status = E_NOT_OK;
    }    
    return Status;    
    
}
#endif
/**
 * 
 * @param pin_config
 * @param logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS   == CONFIG_ENABLE
STD_ReturnType gpio_pin_read_logic(const Pin_Config_t * pin_config , Logic_t * logic){
    STD_ReturnType Status = E_OK;
    if(pin_config != NULL  && logic != NULL && pin_config->pin < PORT_PIN_MAX_NUMBER){
           *logic = READ_BIT(*port_registers[pin_config->port],pin_config->pin);        
    }
    else{
        Status = E_NOT_OK;
    }    
    return Status;    
    
}
#endif
/**
 * 
 * @param pin_config
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */
#if GPIO_PORT_PIN_CONFIGURATIONS   == CONFIG_ENABLE
STD_ReturnType gpio_pin_toggle_logic(const Pin_Config_t * pin_config){
    STD_ReturnType Status = E_OK;
    if(pin_config != NULL && pin_config->pin < PORT_PIN_MAX_NUMBER){
        TOGGLE_BIT(*lat_registers[pin_config->port],pin_config->pin);
    }
    else{
        Status = E_NOT_OK;
    }    
    return Status;   
    
}
#endif





#if GPIO_PORT_PIN_CONFIGURATIONS   == CONFIG_ENABLE
/**
 * 
 * @param pin_config
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */
STD_ReturnType gpio_pin_initialize(const Pin_Config_t * pin_config){
    STD_ReturnType Status = E_OK;
    if(pin_config != NULL && pin_config->pin < PORT_PIN_MAX_NUMBER){
        Status = gpio_pin_direction_initialize(pin_config);
        Status = gpio_pin_write_logic(pin_config,pin_config->logic);
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;    

}
#endif
/**
 * 
 * @param port
 * @param direction
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
STD_ReturnType gpio_port_direction_initialize(Port_Index_t port , uint8 direction){
    STD_ReturnType Status = E_OK;
    if(port > PORT_MAX_NUMBER-1 ){
        Status = E_NOT_OK;
    }
    else{
        *tris_registers[port] = direction;
    }

    return Status;    
    
}
/**
 * 
 * @param port
 * @param direction_status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */
STD_ReturnType gpio_port_get_direction_status(Port_Index_t port , uint8 * direction_status){
    STD_ReturnType Status = E_OK;
    if(direction_status != NULL){
        if(port > PORT_MAX_NUMBER-1 ){
            Status = E_NOT_OK;
        }
        else{
            *direction_status = *tris_registers[port];
        }
    }
    else{
        Status = E_NOT_OK;
    }    
    return Status;    
    
}
/**
 * 
 * @param port
 * @param logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */
STD_ReturnType gpio_port_write_logic(Port_Index_t port,uint8 logic){
    STD_ReturnType Status = E_OK;
    
    if(port > PORT_MAX_NUMBER-1 ){
        Status = E_NOT_OK;
    }
    else{
        *lat_registers[port] = logic;
    }

    return Status;    
    
}
/**
 * 
 * @param port
 * @param logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */
STD_ReturnType gpio_port_read_logic(Port_Index_t port,uint8 * logic){
    STD_ReturnType Status = E_OK;
    if(logic != NULL){
        if(port > PORT_MAX_NUMBER-1 ){
            Status = E_NOT_OK;
        }
        else{
            *logic = *lat_registers[port];
        }
    }
    else{
        Status = E_NOT_OK;
    }     
    return Status;    
    
}
/**
 * 
 * @param port
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform the action
 */
STD_ReturnType gpio_port_toggle_logic(Port_Index_t port){
    STD_ReturnType Status = E_OK;
    if(port > PORT_MAX_NUMBER-1 ){
            Status = E_NOT_OK;
        }
        else{
            *lat_registers[port] ^= PORTC_MASK;
        }
    return Status;    
    
}
#endif