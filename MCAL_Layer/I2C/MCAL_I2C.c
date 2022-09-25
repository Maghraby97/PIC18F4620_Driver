/* 
 * File:   MCAL_I2C.c
 * Author: Maghraby
 *
 * Created on September 20, 2022, 6:25 PM
 */




#include "MCAL_I2C.h"





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
                //MCAL_I2C_CONFIG_ENABLE_STOP_CONDITION();
            }
            else if(i2c_obj->i2c_master->stop_condition_enable == MCAL_I2C_MASTER_STOP_CONDITION_IDLE){
                //MCAL_I2C_CONFIG_DISABLEL_STOP_CONDITION();
            }
            else{
                status = E_NOT_OK;
            }
            
            /*Enable or disable start condition*/
            if(i2c_obj->i2c_master->start_condition_enable == MCAL_I2C_MASTER_START_CONDITION){
                // MCAL_I2C_CONFIG_ENABLE_START_CONDITION();
            }
            else if(i2c_obj->i2c_master->start_condition_enable == MCAL_I2C_MASTER_START_CONDITION_IDLE){
                // MCAL_I2C_CONFIG_DISABLE_START_CONDITION();
            }
            else{
                status = E_NOT_OK;
            }
            
            /*Enable or disable repeated stasrt condition*/
            if(i2c_obj->i2c_master->repeated_start_condition_enable == MCAL_I2C_MASTER_REPEATED_START_CONDITION){
                // MCAL_I2C_CONFIG_ENABLE_REPEATED_START_CONDITION();
            }
            else if(i2c_obj->i2c_master->repeated_start_condition_enable == MCAL_I2C_MASTER_REPEATED_START_CONDITION_IDLE){
                //MCAL_I2C_CONFIG_DISABLEL_REPEATED_START_STOP_CONDITION();
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
    
    status = mcal_i2c_send_start_condition();
    
    
    
    /*Write the slave address into the SSPBUF*/
    if(status == E_OK){
        SSPBUF = (slave_address << 1) | (read_write_bit);
    }
    
    /*Wait here until SSPUF is empty*/
    while(MCAL_I2C_IS_SSPBUF_FULL() == MCAL_I2C_SSPBUF_IS_FULL);
    PIR1bits.SSPIF = 0;
    
    if(MCAL_I2C_IS_ACK_RECEIVED() == MCAL_I2C_ACK_RECEIVED){
        status = E_OK;
    }
    else{
        status = E_NOT_OK;
    }
    
    /*Clear the SSPIF flag manually*/
    PIR1bits.SSPIF = 0;
    
    return status;
}

STD_ReturnType mcal_i2c_master_send_data(uint8_t data, mcal_ack_status_t *ack_status){
    STD_ReturnType status = E_OK;
    if(ack_status != NULL){
        SSPBUF = data;
        
        while(MCAL_I2C_IS_SSPBUF_FULL() == MCAL_I2C_SSPBUF_IS_FULL);
        
        PIR1bits.SSPIF = 0;
        
        if(MCAL_I2C_IS_ACK_RECEIVED() == MCAL_I2C_ACK_RECEIVED){
            status = E_OK;
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
STD_ReturnType mcal_i2c_master_receive_data(uint8_t *data, mcal_ack_status_t ack_status){
    
    
    
}

STD_ReturnType mcal_i2c_slave_send_data(uint8_t data, mcal_ack_status_t *ack_status){
    
    
}
STD_ReturnType mcal_i2c_slave_receive_data(uint8_t *data, mcal_ack_status_t ack_status){
    
    
    
}










STD_ReturnType mcal_i2c_send_start_condition(void){
    STD_ReturnType status = E_OK;
    
    /*This function like macro sends a start condition*/
    MCAL_I2C_CONFIG_SEND_START_CONDITION();
    
    /*Wait here until SEN bit is cleared by hardware , if SEN is cleared then Start codition has been sent
     successfully
     */
    
    
    while(MCAL_I2C_CONFIG_GET_START_CONDITION_STATUS());
    
    /*Clear the SSPIF flag*/
    PIR1bits.SSPIF = 0;
    if(MCAL_I2C_IS_THERE_START_CONDITION_DETECTED() == MCAL_I2C_START_BIT_DETECTED){
        status = E_OK;
    }
    else{
        status = E_NOT_OK;
    }
    
    
    
    return status;
}
STD_ReturnType mcal_i2c_send_repeated_start_condition(void){
    STD_ReturnType status = E_OK;
    /*This function like macro sends a repeated start condition*/
    MCAL_I2C_CONFIG_SEND_REPEATED_START_CONDITION();
    
    /*Wait here until SEN bit is cleared by hardware , if SEN is cleared then Start codition has been sent
     successfully
     */
    while(MCAL_I2C_CONFIG_GET_REPEATED_START_STOP_CONDITION_STATUS() == 1);
    
    /*Clear the SSPIF flag*/
    PIR1bits.SSPIF = 0;
    
    return status;
}
STD_ReturnType mcal_i2c_send_stop_condition(void){
    
    STD_ReturnType status = E_OK;
    /*This function like macro sends a stop condition*/
    MCAL_I2C_CONFIG_SEND_STOP_CONDITION();
    
    /*Wait here until SEN bit is cleared by hardware , if SEN is cleared then Start codition has been sent
     successfully
     */
    while(MCAL_I2C_CONFIG_GET_STOP_CONDITION_STATUS() == 1);
    
    /*Clear the SSPIF flag*/
    PIR1bits.SSPIF = 0;
    if(MCAL_I2C_IS_THERE_STOP_CONDITION_DETECTED() == MCAL_I2C_STOP_BIT_DETECTED){
        status = E_OK;
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
    
}