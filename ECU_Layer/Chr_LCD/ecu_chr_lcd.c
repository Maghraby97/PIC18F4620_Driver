/* 
 * File:   ecu_chr_lcd.c
 * Author: Maghraby
 *
 * Created on April 11, 2022, 7:19 AM
 */



#include "ecu_chr_lcd.h"


#define _XTAL_FREQ 8000000

//static STD_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column);
//static STD_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column);


STD_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *lcd){
    STD_ReturnType Status = E_OK;
    uint8 l_data_pins_counter = ZERO_INIT;
    if(lcd != NULL){
        Status = gpio_pin_initialize(&(lcd->lcd_en));
        Status = gpio_pin_initialize(&(lcd->lcd_rs));
        
        for(l_data_pins_counter = 0; l_data_pins_counter < 4 ; l_data_pins_counter++){
            Status = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }        
        
        __delay_ms(20);       
        Status = lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);        
        __delay_ms(5);
        Status = lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        Status = lcd_4bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        
        Status = lcd_4bit_send_command(lcd,_LCD_CLEAR);
        Status = lcd_4bit_send_command(lcd,_LCD_RETUR_HOME);
        Status = lcd_4bit_send_command(lcd,_LCD_ENTRY_MODE);
        Status = lcd_4bit_send_command(lcd,_LCD_CURSOR_OFF_DISPLAY_ON);
        Status = lcd_4bit_send_command(lcd,_LCD_4BIT_MODE_2_LINE);
        Status = lcd_4bit_send_command(lcd,0x80);
        
        
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd,uint8 command){
    STD_ReturnType Status = E_OK;
    uint8 l_lcd_pins_counter = ZERO_INIT;
    if(lcd != NULL){
        gpio_pin_write_logic(&(lcd->lcd_rs),LOW); 
        
        for(l_lcd_pins_counter = 0 ;l_lcd_pins_counter < 4 ; l_lcd_pins_counter++){
            gpio_pin_write_logic(&(lcd->lcd_data[l_lcd_pins_counter]),(command >> (4+l_lcd_pins_counter))&0x01);
        }
        
        gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en),LOW);
        
        for(l_lcd_pins_counter = 0 ;l_lcd_pins_counter < 4 ; l_lcd_pins_counter++){
            gpio_pin_write_logic(&(lcd->lcd_data[l_lcd_pins_counter]),(command >> (l_lcd_pins_counter))&0x01);
            
        }
        
        gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd,uint8 data){
    STD_ReturnType Status = E_OK;
    uint8 l_lcd_pins_counter = ZERO_INIT;
    
    if(lcd != NULL){
        gpio_pin_write_logic(&(lcd->lcd_rs),HIGH); 
        
        for(l_lcd_pins_counter = 0 ;l_lcd_pins_counter < 4 ; l_lcd_pins_counter++){
            gpio_pin_write_logic(&(lcd->lcd_data[l_lcd_pins_counter]),(data >> (4+l_lcd_pins_counter))&0x01);           
        }
        
        gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en),LOW);
        
        for(l_lcd_pins_counter = 0 ;l_lcd_pins_counter < 4 ; l_lcd_pins_counter++){
            gpio_pin_write_logic(&(lcd->lcd_data[l_lcd_pins_counter]),(data >> (l_lcd_pins_counter))&0x01);     
        }
        gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 data){
    STD_ReturnType Status = E_OK;
    if(lcd != NULL){
        Status = lcd_4bit_set_cursor(lcd,row,column);
        Status = lcd_4bit_send_char_data(lcd,data);
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd,uint8 *str){
    STD_ReturnType Status = E_OK;
    if(lcd != NULL && *str!=NULL){
        while(*str != '\0'){
            Status = lcd_4bit_send_char_data(lcd,*str++);
        }
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,uint8 *str){
    STD_ReturnType Status = E_OK;
    if(lcd != NULL && *str!=NULL){
        while(*str){
            Status = lcd_4bit_set_cursor(lcd,row,column);
            Status = lcd_4bit_send_string(lcd,str);
        }
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column,
        const uint8 _char[], uint8 mem_pos){
    STD_ReturnType Status = E_OK;
    if(lcd != NULL){
        
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}

STD_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd,uint8 row,uint8 column){
    STD_ReturnType Status = E_OK;
    
    if(lcd != NULL){
        column--;
        switch(row){
            case ROW1:
                Status = lcd_4bit_send_command(lcd,0x80+column);
                break;
                
                
            case ROW2:
                
                Status = lcd_4bit_send_command(lcd,0xC0+column);
                break;
                
                
            case ROW3:
                Status = lcd_4bit_send_command(lcd,0x94+column);
                break;
                
                
                
            case ROW4:
                Status = lcd_4bit_send_command(lcd,0xD4+column);
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




STD_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *lcd){
    STD_ReturnType Status = E_OK;
    uint8 l_data_pins_counter = ZERO_INIT;
    if(lcd != NULL){
        Status = gpio_pin_initialize(&(lcd->lcd_en));
        Status = gpio_pin_initialize(&(lcd->lcd_rs));
        for(l_data_pins_counter = 0; l_data_pins_counter < 8 ; l_data_pins_counter++){
            Status = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }   
        
        
        __delay_ms(20);       
        Status = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);        
        __delay_ms(5);
        Status = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        Status = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        
        Status = lcd_8bit_send_command(lcd,_LCD_CLEAR);
        Status = lcd_8bit_send_command(lcd,_LCD_RETUR_HOME);
        Status = lcd_8bit_send_command(lcd,_LCD_ENTRY_MODE);
        Status = lcd_8bit_send_command(lcd,_LCD_CURSOR_OFF_DISPLAY_ON);
        Status = lcd_8bit_send_command(lcd,_LCD_8BIT_MODE_2_LINE);
        Status = lcd_8bit_send_command(lcd,0x80);
        
        
        
        
        
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd,uint8 command){
    STD_ReturnType Status = E_OK;
    uint8 l_lcd_pins_counter = ZERO_INIT;
    if(lcd != NULL){
        gpio_pin_write_logic(&(lcd->lcd_rs),LOW); 
        for(l_lcd_pins_counter = 0 ;l_lcd_pins_counter < 8 ; l_lcd_pins_counter++){
            gpio_pin_write_logic(&(lcd->lcd_data[l_lcd_pins_counter]),(command >> l_lcd_pins_counter)& 0x01);
            
        }
        
        gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en),LOW);
        
        
        
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    
    return Status;
}


STD_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd,uint8 data){
    STD_ReturnType Status = E_OK;
    uint8 l_lcd_pins_counter = ZERO_INIT;
    
    if(lcd != NULL){
        gpio_pin_write_logic(&(lcd->lcd_rs),HIGH); 
        for(l_lcd_pins_counter = 0 ;l_lcd_pins_counter < 8 ; l_lcd_pins_counter++){
            gpio_pin_write_logic(&(lcd->lcd_data[l_lcd_pins_counter]),(data >> l_lcd_pins_counter)& 0x01);
            
        }
        
        gpio_pin_write_logic(&(lcd->lcd_en),HIGH);
        __delay_us(5);
        gpio_pin_write_logic(&(lcd->lcd_en),LOW);
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 data){
    STD_ReturnType Status = E_OK;
    if(lcd != NULL){
        Status = lcd_8bit_set_cursor(lcd,row,column);
        Status = lcd_8bit_send_char_data(lcd,data);
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str){
    STD_ReturnType Status = E_OK;
    if(lcd != NULL && str != NULL){
        while(*str != '\0'){
            Status = lcd_8bit_send_char_data(lcd,*str++);
        }
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,uint8 *str){
    STD_ReturnType Status = E_OK;
    if(lcd != NULL && *str!= NULL){
        Status = lcd_8bit_set_cursor(lcd,row,column);
        Status = lcd_8bit_send_string(lcd,str); 
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column,
        const uint8 _char[], uint8 mem_pos){
    STD_ReturnType Status = E_OK;
    if(lcd != NULL){
        
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


STD_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd,uint8 row,uint8 column){
    STD_ReturnType Status = E_OK;
    
    if(lcd != NULL){
        column--;
        switch(row){
            case ROW1:
                Status = lcd_8bit_send_command(lcd,0x80+column);
                break;
                
                
            case ROW2:
                
                Status = lcd_8bit_send_command(lcd,0xC0+column);
                break;
                
                
            case ROW3:
                Status = lcd_8bit_send_command(lcd,0x94+column);
                break;
                
                
                
            case ROW4:
                Status = lcd_8bit_send_command(lcd,0xD4+column);
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



STD_ReturnType convert_byte_to_string(uint8 value,uint8 *str){
    STD_ReturnType Status = E_OK;
    if(str != NULL){
        memset(str,'\0',4);
        sprintf(str,"%i",value);
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;
}




STD_ReturnType convert_short_to_string(uint16 value,uint8 *str){
    STD_ReturnType Status = E_OK;
    if(str != NULL){
        memset(str,'\0',5);
        sprintf(str,"%i",value);
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;
}


STD_ReturnType convert_int_to_string(uint32 value,uint8 *str){
    STD_ReturnType Status = E_OK;
    if(str != NULL){
        memset(str,'\0',11);
        sprintf(str,"%i",value);
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;
}

