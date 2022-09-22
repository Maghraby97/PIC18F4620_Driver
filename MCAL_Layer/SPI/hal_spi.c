/* 
 * File:   hal_spi.c
 * Author: Maghraby
 *
 * Created on August 12, 2022, 2:18 PM
 */

#include "hal_spi.h"



STD_ReturnType mcal_spi_init(const spi_cfg_t *spi_obj){
    STD_ReturnType status = E_OK;
    /*Initialize the SPI mode: slave or master*/
    if(spi_obj != NULL){
        /*Enable serial port*/
        if(spi_obj->serial_port_enable ==  ENABLE_SERIAL_PORT){
            SPI_Serial_Port_Enable();
        }
        else if (spi_obj->serial_port_enable == DISABLE_SERIAL_PORT){
            SPI_Serial_Port_Disable();
        }
        else{
            status = E_NOT_OK;
        }
        TRISCbits.RC5 = 0;  //(SDO) is cleared to be output pin
        switch(spi_obj->spi_mode){
            case SPI_Master_Clock_Fosc_Div_By_4:
                SPI_Serial_Port_Mode_Config(SPI_Master_Clock_Fosc_Div_By_4);
                TRISCbits.RC3 = 0; //SCK cleared in master mode to be output
                TRISAbits.RA5 = 0; //SS is cleared in master mode to be output
                break;
                
            case SPI_Master_Clock_Fosc_Div_By_16:
                SPI_Serial_Port_Mode_Config(SPI_Master_Clock_Fosc_Div_By_16);
                TRISCbits.RC3 = 0; //SCK cleared in master mode to be output
                TRISAbits.RA5 = 0; //SS is cleared in master mode to be output
                break;
                
            case SPI_Master_Clock_Fosc_Div_By_64:
                SPI_Serial_Port_Mode_Config(SPI_Master_Clock_Fosc_Div_By_64);
                TRISCbits.RC3 = 0; //SCK cleared in master mode to be output
                TRISAbits.RA5 = 0; //SS is cleared in master mode to be output
                break;
                
            case SPI_Master_Clock_TMR2_Div_By_2:
                SPI_Serial_Port_Mode_Config(SPI_Master_Clock_TMR2_Div_By_2);
                TRISCbits.RC3 = 0; //SCK cleared in master mode to be output
                TRISAbits.RA5 = 0; //SS is cleared in master mode to be output
                break;
                
            case SPI_Slave_SS_Pin_Enabled:
                SPI_Serial_Port_Mode_Config(SPI_Slave_SS_Pin_Enabled);
                TRISCbits.RC3 = 1; //SCK cleared in master mode to be input
                TRISAbits.RA5 = 1; //SS is cleared in master mode to be input
                break;
                
            case SPI_Slave_SS_Pin_Disabled:
                SPI_Serial_Port_Mode_Config(SPI_Slave_SS_Pin_Disabled);
                TRISCbits.RC3 = 1; //SCK cleared in master mode to be input
                TRISAbits.RA5 = 1; //SS is cleared in master mode to be input
                break;
                
            default:
                status = E_NOT_OK;
                break;
        }
        
        /*Configure the clock phase*/
        if(spi_obj->spi_clock_phase == SPI_Transmit_On_Trans_From_Idle_To_Active){
            SPI_Clock_Phase_Config(SPI_Transmit_On_Trans_From_Idle_To_Active);
        }
        else if(spi_obj->spi_clock_phase == SPI_Transmit_On_Trans_From_Active_To_Idle){
            SPI_Clock_Phase_Config(SPI_Transmit_On_Trans_From_Active_To_Idle);
        }
        else{
            status = E_NOT_OK;  
        }
        
        /*Configure clock polarity*/
        if(spi_obj->spi_clock_Polarity == Idle_State_Low){
            SPI_Clock_Polarity_Config(Idle_State_Low);
        }
        else if(spi_obj->spi_clock_Polarity == Idle_State_High){
            SPI_Clock_Polarity_Config(Idle_State_High);
        }
        else{
            status = E_NOT_OK;            
        }
        
        /*Configure data sampling mode*/
        if(spi_obj->spi_sample_data == SPI_Data_Sampled_At_Middle_Of_Output){
            SPI_Data_Sampling_Config(SPI_Data_Sampled_At_Middle_Of_Output);
        }
        else if(spi_obj->spi_sample_data == SPI_Data_Sampled_At_End_Of_Output){
            SPI_Data_Sampling_Config(SPI_Data_Sampled_At_End_Of_Output);
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
STD_ReturnType mcal_spi_deinit(const spi_cfg_t *spi_obj){
    
    
}
STD_ReturnType mcal_spi_select_slave(uint8 slave_pin){
    STD_ReturnType status = E_OK;
    if(slave_pin < 8 && slave_pin >= 0){
        LATA &= ~(1 << slave_pin);
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}

STD_ReturnType mcal_spi_send_byte_blocking(uint8 data){
    STD_ReturnType status = E_OK;
    uint8 dummyData ;
    SSPBUF = data;
    //while(!PIR1bits.SSPIF);
     while(!SSPSTATbits.BF);
    dummyData = SSPBUF;
    return status;
}
STD_ReturnType mcal_spi_receive_byte_blocking(uint8 *data){
    STD_ReturnType status = E_OK;
    
    while(!SSPSTATbits.BF);
    *data = SSPBUF;
    return status;
}

STD_ReturnType mcal_spi_send_string_blocking(uint8 *str){
    STD_ReturnType status = E_OK;
    if(str != NULL){
        while(*str != '\0'){
            mcal_spi_send_byte_blocking(*str);
            str++;
        }
        mcal_spi_send_byte_blocking('\0');
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
STD_ReturnType mcal_spi_receive_string_blocking(uint8 *str){
    STD_ReturnType status = E_OK;
    uint8 check = 5;
    if(str != NULL){        
        do{
            mcal_spi_receive_byte_blocking(str);
            check = *str;
            str++;
        }while(check != '\0');
        
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}