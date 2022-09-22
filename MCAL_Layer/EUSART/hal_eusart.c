/* 
 * File:   hal_eusart.c
 * Author: Maghraby
 *
 * Created on July 31, 2022, 10:30 PM
 */

#include "hal_eusart.h"

static STD_ReturnType eusart_baudrate_configuration_bits_init(const eusart_t *eusart_obj);
static STD_ReturnType eusart_tx_init(const eusart_tx_t *eusart_tx_obj);
static STD_ReturnType eusart_rx_init(const eusart_rx_t *eusart_rx_obj);

static void (*TX_Handler)(void) = NULL;
static void (*RX_Handler)(void) = NULL;

STD_ReturnType mcal_eusart_asynchronous_init(const eusart_t *eusart_obj){
    STD_ReturnType Status = E_OK;
    if(eusart_obj){        
        RCSTAbits.SPEN = 1;
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;        
        eusart_baudrate_configuration_bits_init(eusart_obj);
        
        
        /*Init the Transmitter*/
        if(eusart_obj->eusart_tx_cfg != NULL){
            eusart_tx_init(eusart_obj->eusart_tx_cfg);
        }else{
            Status = E_NOT_OK;
        }
        
        
        /*Init the Receiver*/
        if(eusart_obj->eusart_rx_cfg != NULL){
            eusart_rx_init(eusart_obj->eusart_rx_cfg);
        }else{
            Status = E_NOT_OK;
        }
        
    }
    else{
        Status = E_NOT_OK;
    }    
    return Status;
}

STD_ReturnType mcal_eusart_synchronous_init(const eusart_t *eusart_obj){
    
    
}

STD_ReturnType mcal_eusart_deinit(void){
    STD_ReturnType Status = E_OK;   
    
    return Status;
    
}


STD_ReturnType mcal_eusart_send_byte_blocking(uint8 data){
    STD_ReturnType Status = E_OK;   
    while(TXSTAbits.TRMT == 0);  //as long as TRMT = 0 it means the TSR register is full
    TXREG = data;
    return Status;
}

/*This function enables the interrupt after writing the TXREG.*/
STD_ReturnType mcal_eusart_send_byte_non_blocking(uint8 data){
    STD_ReturnType Status = E_OK;  
        TXREG = data;
        EUSART_Transmitter_Interrupt_Enable();
    return Status;    
}





STD_ReturnType mcal_eusart_send_string_blocking(uint8 *str , uint8 str_length){
    STD_ReturnType Status = E_OK;   
    uint8 str_length_copied = str_length;
    uint8 *str_copied = str;
    while(*str_copied != '\0'){
        mcal_eusart_send_byte_blocking(*str_copied);
        str_copied++;
    }
    mcal_eusart_send_byte_blocking('\0');
    return Status;
}


//STD_ReturnType mcal_eusart_send_string_non_blocking(uint8 *str , uint8 str_length){
//    STD_ReturnType Status = E_OK;   
//    uint8 str_length_copied = str_length;
//    uint8 *str_copied = str;
//    while(str_length_copied--){
//        mcal_eusart_send_byte_non_blocking(*str_copied);
//        //__delay_ms(5);
//        str_copied++;
//    }
//
//    return Status;
//    
//}

STD_ReturnType mcal_eusart_send_string_non_blocking(void){
    STD_ReturnType Status = E_OK;   
    EUSART_Transmitter_Enabled();
    

    return Status;
    
}


STD_ReturnType mcal_eusart_receive_byte_blocking(uint8 *data){
    STD_ReturnType Status = E_OK;   
    while(!PIR1bits.RCIF);
    *data = RCREG;
    return Status;    
}
STD_ReturnType mcal_eusart_receive_byte_non_blocking(uint8  *data){
    STD_ReturnType Status = E_OK;   
    if(PIR1bits.RCIF){
        *data = RCREG;
    }
    else{
        Status = E_NOT_OK;
    }
    return Status;    
}
STD_ReturnType mcal_eusart_receive_string_blocking(uint8 *str , uint8 str_length){
    STD_ReturnType Status = E_OK;   
    uint8 str_length_copied = str_length;
    uint8 *str_copied = str;
    while(RCREG!='\r'){
        mcal_eusart_receive_byte_blocking(str_copied);
        str_copied++;
        
    }
    *(str_copied++)='\r';
    *(str_copied++)='\0';
    RCREG = '\0';
    
    return Status;
}
STD_ReturnType mcal_eusart_receive_string_non_blocking(uint8 *str , uint8 str_length){
    STD_ReturnType Status = E_OK;   
    
    
    return Status;    
    
}




/*Helper Functions */
static STD_ReturnType eusart_baudrate_configuration_bits_init(const eusart_t *eusart_obj){
    STD_ReturnType Status = E_OK;   
    float baudrate_val = 0;
    if(eusart_obj){
        switch(eusart_obj->baudrate_cfg){
            case EUSART_Asynchronous_8bit_LowSpeed:
                EUSART_Asynchronous_Mode();
                EUSART_BaudRate_Generator_8Bit_Select();
                EUSART_BaudRate_LowSpeed_Select();
                baudrate_val = ((_XTAL_FREQ/(float)eusart_obj->baudrate_value)/64)-1;
                SPBRG = (uint8)((uint32)baudrate_val);
                SPBRGH = (uint8)(((uint32)baudrate_val) >> 8);                
                break;
                
            case EUSART_Asynchronous_8bit_HighSpeed:
                EUSART_Asynchronous_Mode();
                EUSART_BaudRate_Generator_8Bit_Select();
                EUSART_BaudRate_HighSpeed_Select();
                baudrate_val = ((_XTAL_FREQ/(float)eusart_obj->baudrate_value)/16)-1;
                SPBRG = (uint8)((uint32)baudrate_val);
                SPBRGH = (uint8)(((uint32)baudrate_val) >> 8);  
                break;                
                
            case EUSART_Asynchronous_16bit_LowSpeed:
                EUSART_Asynchronous_Mode();
                EUSART_BaudRate_Generator_16Bit_Select();
                EUSART_BaudRate_LowSpeed_Select();
                baudrate_val = ((_XTAL_FREQ/(float)eusart_obj->baudrate_value)/16)-1;
                SPBRG = (uint8)((uint32)baudrate_val);
                SPBRGH = (uint8)(((uint32)baudrate_val) >> 8);                  
                break;
                
            case EUSART_Asynchronous_16bit_HighSpeed:
                EUSART_Asynchronous_Mode();
                EUSART_BaudRate_Generator_16Bit_Select();
                EUSART_BaudRate_HighSpeed_Select();
                baudrate_val = ((_XTAL_FREQ/(float)eusart_obj->baudrate_value)/4)-1;
                SPBRG = (uint8)((uint32)baudrate_val);
                SPBRGH = (uint8)(((uint32)baudrate_val) >> 8);                
                break;
                
            case EUSART_Synchronous_8bit:
                EUSART_Synchronous_Mode();
                EUSART_BaudRate_Generator_8Bit_Select();
                baudrate_val = ((_XTAL_FREQ/(float)eusart_obj->baudrate_value)/4)-1;
                SPBRG = (uint8)((uint32)baudrate_val);
                SPBRGH = (uint8)(((uint32)baudrate_val) >> 8);
                break;
                
            case EUSART_Synchronous_16bit:
                EUSART_Synchronous_Mode();
                EUSART_BaudRate_Generator_16Bit_Select();
                baudrate_val = ((_XTAL_FREQ/(float)eusart_obj->baudrate_value)/4)-1;
                SPBRG = (uint8)((uint32)baudrate_val);
                SPBRGH = (uint8)(((uint32)baudrate_val) >> 8);                
                break;
                
            default:
                
                break;   
        }             
    }
    else{
        Status = E_NOT_OK;        
    }
    return Status;    
    
}

static STD_ReturnType eusart_tx_init(const eusart_tx_t *eusart_tx_obj){
    STD_ReturnType Status = E_OK;
    if(eusart_tx_obj != NULL){
        
        /*Enable the TX*/
//        if(eusart_tx_obj->eusart_tx_enabled == EUSART_TX_ENABLED){
//            EUSART_Transmitter_Enabled();
//        }
//        else if(eusart_tx_obj->eusart_tx_enabled == EUSART_TX_DISABLED){
//            EUSART_Transmitter_Disabled();
//        }
//        else{
//            Status = E_NOT_OK; 
//        }
        
        /*Init Tx 9 bit transmission*/
        if(eusart_tx_obj->eusart_9bit_transmission == EUSART_TX_9BIT_SELECTED){
            EUSART_Transmitter_9bit_Transmission_Enabled();
        }
        else if(eusart_tx_obj->eusart_9bit_transmission == EUSART_TX_9BIT_NOT_SELECTED){
            EUSART_Transmitter_9bit_Transmission_Disabled();
        }
        else{
            Status = E_NOT_OK; 
        }
        
        
        /*Init Tx Interrupt*/
        if(eusart_tx_obj->eusart_tx_interrupt_enabled == EUSART_TX_INTERRUPT_ENABLE){
            /*Disable Interrupt first*/
            EUSART_Transmitter_Interrupt_Disable();                      
            /*Don`t forget to add the priority handling here and the interrupt handler init*/
            TX_Handler = eusart_tx_obj->Int_Tx_Handler_Var;
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if(eusart_tx_obj->eusart_tx_priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_GlobalInterruptHighEnable();
                EUSART_Transmitter_High_Priority_Set();
            }
            else if(eusart_tx_obj->eusart_tx_priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_GlobalInterruptLowEnable();
                EUSART_Transmitter_Low_Priority_Set();
            }
            else{
                Status = E_NOT_OK;
            }
#else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
#endif
            /*Enable Interrupt for Transmitter*/
            EUSART_Transmitter_Interrupt_Enable();   
        }
        else if(eusart_tx_obj->eusart_tx_interrupt_enabled == EUSART_TX_INTERRUPT_DISABLE){
            EUSART_Transmitter_Interrupt_Disable(); 
        }
        else{
            Status = E_NOT_OK;
        }
        
        
        
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;
}


static STD_ReturnType eusart_rx_init(const eusart_rx_t *eusart_rx_obj){
    STD_ReturnType Status = E_OK;
    if(eusart_rx_obj != NULL){
        if(eusart_rx_obj->eusart_rx_enabled == EUSART_RX_ENABLED){
            EUSART_Receiver_Enabled();
        }
        else if(eusart_rx_obj->eusart_rx_enabled == EUSART_RX_DISABLED){
            EUSART_Receiver_Disabled();
        }
        else{
            Status = E_NOT_OK;
        }
        
        
        if(eusart_rx_obj->eusart_9bit_reception == EUSART_RX_9BIT_SELECTED){
            EUSART_Receiver_9bit_Reception_Enabled();
        }
        else if(eusart_rx_obj->eusart_9bit_reception == EUSART_RX_9BIT_NOT_SELECTED){
            EUSART_Receiver_9bit_Reception_Disabled();
        }
        else{
            Status = E_NOT_OK; 
        }
        
        
        if(eusart_rx_obj->eusart_rx_interrupt_enabled == EUSART_RX_INTERRUPT_ENABLE){
            EUSART_Receiver_Interrupt_Enable();
            RX_Handler = eusart_rx_obj->Int_Rx_Handler_Var;
            /*Don`t forget to add the priority handling here and the interrupt handler init*/
            
        }
        else if(eusart_rx_obj->eusart_rx_interrupt_enabled == EUSART_RX_INTERRUPT_DISABLE){
            EUSART_Receiver_Interrupt_Disable();
        }
        else{
            Status = E_NOT_OK;
        }
        
    }
    else{
        Status = E_NOT_OK;
    }
    
    
    return Status;    
}
/*this function disables the interrupt before calling the TX isr from the application layer and then 
 * calls the TX Isr. */
void EUSART_TX_Isr(void){
    //EUSART_Transmitter_Interrupt_Disable();
    if(TX_Handler){
        TX_Handler();
    }
}
void EUSART_RX_Isr(void){
    if(RX_Handler){
        RX_Handler();
    }
}