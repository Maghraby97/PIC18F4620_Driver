/* 
 * File:   ecu_dc_motor.c
 * Author: Maghraby
 *
 * Created on March 22, 2022, 3:30 PM
 */

#include "ecu_dc_motor.h"

/**
 * 
 * @param motor
 * @return 
 */
STD_ReturnType dc_motor_initialize(const dc_motor_t *_motor_){
    STD_ReturnType status = E_OK;
    if(_motor_!= NULL){
        status = gpio_pin_direction_initialize(&(_motor_->motor[MOTOR_PIN_0]));
        status = gpio_pin_direction_initialize(&(_motor_->motor[MOTOR_PIN_1]));
    }
    else{
        status = E_NOT_OK;
    }
    return status;
    
}


/**
 * 
 * @param motor
 * @return 
 */
STD_ReturnType dc_motor_forward(const dc_motor_t *_motor_){
    STD_ReturnType status = E_OK;
    if(_motor_ != NULL){
        
        status = gpio_pin_write_logic(&(_motor_->motor[MOTOR_PIN_1]),HIGH);
        status = gpio_pin_write_logic(&(_motor_->motor[MOTOR_PIN_0]),LOW);
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
}

/**
 * 
 * @param motor
 * @return 
 */
STD_ReturnType dc_motor_reverse(const dc_motor_t *_motor_){
    STD_ReturnType status = E_OK;
    if(_motor_ != NULL){
        status = gpio_pin_write_logic(&(_motor_->motor[MOTOR_PIN_1]),LOW);
        status = gpio_pin_write_logic(&(_motor_->motor[MOTOR_PIN_0]),HIGH);
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
}

/**
 * 
 * @param motor
 * @return 
 */
STD_ReturnType dc_motor_stop(const dc_motor_t *_motor_){
    STD_ReturnType status = E_OK;
    if(_motor_ != NULL){
        status = gpio_pin_write_logic(&(_motor_->motor[MOTOR_PIN_0]),LOW);
        status = gpio_pin_write_logic(&(_motor_->motor[MOTOR_PIN_0]),LOW);
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
}