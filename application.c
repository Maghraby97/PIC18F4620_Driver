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
#include "MCAL_Layer/I2C/MCAL_I2C.h"

#define _XTAL_FREQ 4000000
mcal_i2c_master_config i2c_master = {
    .clock_speed = 100000,
    .ack_Sequence_enable = MCAL_I2C_ACK_DISABLED,
    .receive_enable = MCAL_I2C_MASTER_RECEIVE_MODE_IDLE,
    .stop_condition_enable = MCAL_I2C_MASTER_STOP_CONDITION,
    .start_condition_enable = MCAL_I2C_MASTER_START_CONDITION,
    .repeated_start_condition_enable = MCAL_I2C_MASTER_REPEATED_START_CONDITION
};
mcal_i2c_config_t i2c_ob = {
    .i2c_mode = MCAL_I2C_Master_Mode,
    .serial_port_enable = MCAL_I2C_ENABLE_SERIAL_PORT,
    .i2c_master = &i2c_master,
    .i2c_slave = NULL
};


mcal_ack_status_t ack_status = NOT_ACK;

Pin_Config_t rc3_ = {
    .direction = INPUT,
    .pin = PIN3,
    .port = PORTC_INDEX,
    .logic = LOW

};
Pin_Config_t rc4_ = {
    .direction = INPUT,
    .pin = PIN4,
    .port = PORTC_INDEX,
    .logic = LOW

};

int main(void){  
    mcal_i2c_initialize(&i2c_ob);
    
    
    while(1){
        /*Slave address 0x04
         write bit = 0
         */
        mcal_i2c_send_slave_address(0x04,0,&ack_status);
        //mcal_i2c_send_stop_condition();
        mcal_i2c_master_send_data(0x77,&ack_status);
        
        mcal_i2c_send_repeated_start_condition();
        
        mcal_i2c_master_send_data(0x00,&ack_status);
        mcal_i2c_send_stop_condition();
        __delay_ms(1000);
       
    }
        
        
    
    return (EXIT_SUCCESS);
}







//void application_init(void){
//    
//    ecu_layer_initialize();
//    
//}
