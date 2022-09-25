/* 
 * File:   MCAL_I2C.c
 * Author: Maghraby
 *
 * Created on September 20, 2022, 6:25 PM
 */




#include "MCAL_I2C.h"


static inline STD_ReturnType mcal_i2c_send_start_condition(void);
static inline STD_ReturnType mcal_i2c_send_stop_condition(void);
static inline STD_ReturnType mcal_i2c_send_repeated_start_condition(void);





STD_ReturnType mcal_i2c_initialize(mcal_i2c_config_t *i2c_obj){
    STD_ReturnType status = E_OK;
    if(i2c_obj != NULL){
        
        /*Enabling or disabling serial port*/
        if(i2c_obj->serial_port_enable == MCAL_I2C_ENABLE_SERIAL_PORT){
            MCAL_I2C_CONFIG_ENABLE_SERIAL_PORT();
        }
        else if(i2c_obj->serial_port_enable == MCAL_I2C_DISABLE_SERIAL_PORT){
            MCAL_I2C_CONFIG_DISABLE_SERIAL_PORT();
        }
        else{
            status = E_NOT_OK;
        }
        
        
        /*Configure the I2C mode whether slave or master*/
        switch(i2c_obj->i2c_mode){
            case MCAL_I2C_Slave_Mode_7Bit_Address:
                MCAL_I2C_CONFIG_I2C_MODE_OF_OPERATION(MCAL_I2C_Slave_Mode_7Bit_Address);
                break;
            case MCAL_I2C_Slave_Mode_10Bit_Address:
                MCAL_I2C_CONFIG_I2C_MODE_OF_OPERATION(MCAL_I2C_Slave_Mode_10Bit_Address);
                break;
            case MCAL_I2C_Master_Mode:
                MCAL_I2C_CONFIG_I2C_MODE_OF_OPERATION(MCAL_I2C_Master_Mode);
                break;
            case MCAL_I2C_Firmware_Controlled_Master_Mode:
                MCAL_I2C_CONFIG_I2C_MODE_OF_OPERATION(MCAL_I2C_Firmware_Controlled_Master_Mode);
                break;
            case MCAL_I2C_Slave_Mode_7Bit_Address_Start_Stop_Interrupts_Enabled:
                MCAL_I2C_CONFIG_I2C_MODE_OF_OPERATION(MCAL_I2C_Slave_Mode_7Bit_Address_Start_Stop_Interrupts_Enabled);
                break;
            case MCAL_I2C_Slave_Mode_10Bit_Address_Start_Stop_Interrupts_Enabled:
                MCAL_I2C_CONFIG_I2C_MODE_OF_OPERATION(MCAL_I2C_Slave_Mode_10Bit_Address_Start_Stop_Interrupts_Enabled);
                break;
            default:
                status = E_NOT_OK;
                break;    
        }
        
        /*Configure i2c master or slave*/
        if(i2c_obj->i2c_master != NULL){
            
            /*Calculate the BRG value*/
            SSPADD = (uint8_t)(((_XTAL_FREQ)/(4.0 * i2c_obj->i2c_master->clock_speed)) - 1.0);
            
            /*Enable or disable the ACK sequence on master*/
            if(i2c_obj->i2c_master->ack_Sequence_enable == MCAL_I2C_ACK_ENABLED){
                MCAL_I2C_CONFIG_ENABLE_ACK_SEQUENCE_ON_MASTER();
            }
            else if(i2c_obj->i2c_master->ack_Sequence_enable == MCAL_I2C_ACK_DISABLED){
                MCAL_I2C_CONFIG_DISABLE_ACK_SEQUENCE_ON_MASTER();
            }
            else{
                status = E_NOT_OK;
            }
            
            /*Enable or disable receive mode for master*/
            if(i2c_obj->i2c_master->receive_enable == MCAL_I2C_MASTER_RECEIVE_MODE_ENABLED){
                MCAL_I2C_CONFIG_ENABLE_MASTER_RECEIVE();
            }
            else if(i2c_obj->i2c_master->receive_enable == MCAL_I2C_MASTER_RECEIVE_MODE_IDLE){
                MCAL_I2C_CONFIG_DISABLEL_MASTER_RECEIVE();
            }
            else{
                status = E_NOT_OK;
            }
            
            /*Enable or disable stop condition*/
            if(i2c_obj->i2c_master->stop_condition_enable == MCAL_I2C_MASTER_STOP_CONDITION){
                MCAL_I2C_CONFIG_ENABLE_STOP_CONDITION();
            }
            else if(i2c_obj->i2c_master->stop_condition_enable == MCAL_I2C_MASTER_STOP_CONDITION_IDLE){
                MCAL_I2C_CONFIG_DISABLEL_STOP_CONDITION();
            }
            else{
                status = E_NOT_OK;
            }

            /*Enable or disable start condition*/
            if(i2c_obj->i2c_master->start_condition_enable == MCAL_I2C_MASTER_START_CONDITION){
                MCAL_I2C_CONFIG_ENABLE_START_CONDITION();
            }
            else if(i2c_obj->i2c_master->start_condition_enable == MCAL_I2C_MASTER_START_CONDITION_IDLE){
                MCAL_I2C_CONFIG_DISABLE_START_CONDITION();
            }
            else{
                status = E_NOT_OK;
            }

            /*Enable or disable repeated stasrt condition*/
            if(i2c_obj->i2c_master->repeated_start_condition_enable == MCAL_I2C_MASTER_REPEATED_START_CONDITION){
                MCAL_I2C_CONFIG_ENABLE_REPEATED_START_CONDITION();
            }
            else if(i2c_obj->i2c_master->repeated_start_condition_enable == MCAL_I2C_MASTER_REPEATED_START_CONDITION_IDLE){
                MCAL_I2C_CONFIG_DISABLEL_REPEATED_START_STOP_CONDITION();
            }
            else{
                status = E_NOT_OK;
            }
            
            
        }
        else if(i2c_obj->i2c_slave != NULL){
            
        }
        else{
            status = E_NOT_OK;
        }
        
        
    }
    else{
        status = E_NOT_OK;
    }

    return status;
}
STD_ReturnType mcal_i2c_deinitialize(mcal_i2c_config_t *i2c_obj){
    STD_ReturnType status = E_OK;
    if(i2c_obj != NULL){
        
    }
    else{
        status = E_NOT_OK;
    }

    return status;
    
    
}

STD_ReturnType mcal_i2c_send_slave_address(uint8_t slave_address, uint8_t read_write_bit,mcal_ack_status_t *ack_status){
    STD_ReturnType status = E_OK;
    
    SSPBUF = (slave_address << 1) | (read_write_bit);
    
    
    return status;
}

STD_ReturnType mcal_i2c_master_send_data(uint8_t data, mcal_ack_status_t *ack_status){
    STD_ReturnType status = E_OK;
    if(ack_status != NULL){
        
    }
    else{
        status = E_NOT_OK;
    }

    return status;
    
}
STD_ReturnType mcal_i2c_master_receive_data(uint8_t *data, mcal_ack_status_t ack_status){
    
    
    
}

STD_ReturnType mcal_i2c_slave_send_data(uint8_t data, mcal_ack_status_t *ack_status){
    
    
}
STD_ReturnType mcal_i2c_slave_receive_data(uint8_t *data, mcal_ack_status_t ack_status){
    
    
    
}










static inline STD_ReturnType mcal_i2c_send_start_condition(void){
    
    
    
}
static inline STD_ReturnType mcal_i2c_send_stop_condition(void){
    
    
}
static inline STD_ReturnType mcal_i2c_send_repeated_start_condition(void){
    
    
}