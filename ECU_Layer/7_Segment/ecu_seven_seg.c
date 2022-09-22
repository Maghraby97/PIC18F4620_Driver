/* 
 * File:   ecu_seven_seg.c
 * Author: Maghraby
 *
 * Created on March 30, 2022, 1:12 PM
 */


/*this driver requires the Binary Coded Decimal (BCD) to work properly*/



#include "ecu_seven_seg.h"

/**
 * 
 * @param segment
 * @return 
 */
STD_ReturnType Seven_Segment_Initialize(const Segment_t *segment ){
    
    STD_ReturnType Status = E_OK;
    if(segment != NULL){
        gpio_pin_initialize(&(segment->segments_pins[SEGMENT_PIN_0]));
        gpio_pin_initialize(&(segment->segments_pins[SEGMENT_PIN_1]));
        gpio_pin_initialize(&(segment->segments_pins[SEGMENT_PIN_2]));
        gpio_pin_initialize(&(segment->segments_pins[SEGMENT_PIN_3]));  
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;
}

/**
 * 
 * @param segment
 * @param number
 * @return 
 */
STD_ReturnType Seven_Sement_Write_Number(const Segment_t *segment , uint8 number){
    
    STD_ReturnType Status = E_OK;
    if(segment != NULL){
        gpio_pin_write_logic(&(segment->segments_pins[SEGMENT_PIN_0]), number&(uint8)0x01);
        gpio_pin_write_logic(&(segment->segments_pins[SEGMENT_PIN_1]),(number >> 1)& (uint8)0x01);
        gpio_pin_write_logic(&(segment->segments_pins[SEGMENT_PIN_2]),(number >> 2)& (uint8)0x01);
        gpio_pin_write_logic(&(segment->segments_pins[SEGMENT_PIN_3]),(number >> 3)& (uint8)0x01);
    }
    else{
        
        Status = E_NOT_OK;
    }
    
    return Status;
    
    
    
}