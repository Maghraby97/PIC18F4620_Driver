/* 
 * File:   hal_eusart.h
 * Author: Maghraby
 *
 * Created on July 31, 2022, 10:30 PM
 */

#ifndef HAL_EUSART_H
#define	HAL_EUSART_H

/* Section: Includes*/
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"


/*Section: Macro Definitions*/
#define EUSART_ASYNCHRONOUS_MODE   0
#define EUSART_SYNCHRONOUS_MODE    1

#define EUSART_TX_TSR_EMPTY     0
#define EUSART_TX_TSR_FULL      1

#define EUSART_ASYNCHRONOUS_LOW_SPEED_MODE   0
#define EUSART_ASYNCHRONOUS_HIGH_SPEED_MODE  1

#define EUSART_TX_DISABLED   0
#define EUSART_TX_ENABLED    1

#define EUSART_TX_INTERRUPT_DISABLE    0
#define EUSART_TX_INTERRUPT_ENABLE     1

#define EUSART_TX_9BIT_NOT_SELECTED  0
#define EUSART_TX_9BIT_SELECTED      1

#define EUSART_OVERRUN_ERROR_NOT_OCCURED      0
#define EUSART_OVERRUN_ERROR_OCCURED          1

#define EUSART_RX_FRAME_ERROR_NOT_OCCURED      0
#define EUSART_RX_FRAME_ERROR_OCCURED          1

#define EUSART_RX_DISABLED   0
#define EUSART_RX_ENABLED    1

#define EUSART_RX_9BIT_NOT_SELECTED  0
#define EUSART_RX_9BIT_SELECTED      1

#define EUSART_RX_INTERRUPT_DISABLE    0
#define EUSART_RX_INTERRUPT_ENABLE     1

#define EUSART_SERIAL_PORT_DISABLED  0
#define EUSART_SERIAL_PORT_ENABLED   1

#define EUSART_BAUDRATE_GENERATOR_8BIT_SELECTED  0
#define EUSART_BAUDRATE_GENERATOR_16BIT_SELECTED 1



/*Section: Function Like Macros*/
#define EUSART_Asynchronous_Mode()    (TXSTAbits.SYNC  = EUSART_ASYNCHRONOUS_MODE)
#define EUSART_Synchronous_Mode()     (TXSTAbits.SYNC  = EUSART_SYNCHRONOUS_MODE)

#define EUSART_Transmitter_Enabled()  (TXSTAbits.TXEN = EUSART_TX_ENABLED)
#define EUSART_Transmitter_Disabled() (TXSTAbits.TXEN = EUSART_TX_DISABLED)

#define EUSART_Transmitter_9bit_Transmission_Enabled()      (TXSTAbits.TX9 = EUSART_TX_9BIT_SELECTED)
#define EUSART_Transmitter_9bit_Transmission_Disabled()     (TXSTAbits.TX9 = EUSART_TX_9BIT_NOT_SELECTED)


#define EUSART_Receiver_Enabled()     (RCSTAbits.CREN = EUSART_RX_ENABLED)
#define EUSART_Receiver_Disabled()    (RCSTAbits.CREN = EUSART_RX_DISABLED)

#define EUSART_Receiver_9bit_Reception_Enabled()      (RCSTAbits.RX9 = EUSART_RX_9BIT_SELECTED)
#define EUSART_Receiver_9bit_Reception_Disabled()     (RCSTAbits.RX9 = EUSART_RX_9BIT_NOT_SELECTED)

#define EUSART_BaudRate_Generator_16Bit_Select()  (BAUDCONbits.BRG16 = EUSART_BAUDRATE_GENERATOR_16BIT_SELECTED)
#define EUSART_BaudRate_Generator_8Bit_Select()   (BAUDCONbits.BRG16 = EUSART_BAUDRATE_GENERATOR_8BIT_SELECTED)

#define EUSART_BaudRate_HighSpeed_Select()        (TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED_MODE)
#define EUSART_BaudRate_LowSpeed_Select()         (TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED_MODE)



/*Section: Data Type Declaration*/

typedef enum{
    EUSART_Asynchronous_8bit_LowSpeed = 0,
    EUSART_Asynchronous_8bit_HighSpeed,        
    EUSART_Asynchronous_16bit_LowSpeed,
    EUSART_Asynchronous_16bit_HighSpeed,
    EUSART_Synchronous_8bit,
    EUSART_Synchronous_16bit           
}baudrate_cfg_bits_t;


typedef struct{
    uint8  eusart_tx_enabled           :1;
    uint8  eusart_9bit_transmission    :1;  
    uint8  eusart_tx_interrupt_enabled :1;
    uint8  eusart_tx_reserved          :5;
    void   (*Int_Tx_Handler_Var)(void);
    interrupt_priority_cfg eusart_tx_priority;
}eusart_tx_t;



typedef struct{
    uint8  eusart_rx_enabled           :1;
    uint8  eusart_9bit_reception       :1;  
    uint8  eusart_rx_interrupt_enabled :1;
    uint8  eusart_rx_reserved          :5;
    void   (*Int_Rx_Handler_Var)(void); 
    interrupt_priority_cfg eusart_rx_priority;
}eusart_rx_t;

typedef struct{
    uint8  mode_of_operation;  /*@ref : EUSART_ASYNCHRONOUS_MODE or EUSART_SYNCHRONOUS_MODE */
    uint32 baudrate_value;
    baudrate_cfg_bits_t baudrate_cfg;    /*@ref : baudrate_cfg_bits_t*/
    eusart_tx_t  *eusart_tx_cfg;          /*@ref : eusart_tx_t*/
    eusart_rx_t  *eusart_rx_cfg;          /*@ref : eusart_rx_t*/
}eusart_t;
/*Section: Function Prototypes*/
STD_ReturnType mcal_eusart_asynchronous_init(const eusart_t *eusart_obj);
STD_ReturnType mcal_eusart_synchronous_init(const eusart_t *eusart_obj);
STD_ReturnType mcal_eusart_deinit(void);
STD_ReturnType mcal_eusart_send_byte_blocking(uint8 data);
STD_ReturnType mcal_eusart_send_byte_non_blocking(uint8 data);
STD_ReturnType mcal_eusart_receive_byte_blocking(uint8 *data);
STD_ReturnType mcal_eusart_receive_byte_non_blocking(uint8  *data);
STD_ReturnType mcal_eusart_send_string_blocking(uint8 *str , uint8 str_length);
//STD_ReturnType mcal_eusart_send_string_non_blocking(uint8 *str , uint8 str_length);

STD_ReturnType mcal_eusart_send_string_non_blocking(void);

STD_ReturnType mcal_eusart_receive_string_blocking(uint8 *str , uint8 str_length);
STD_ReturnType mcal_eusart_receive_string_non_blocking(uint8 *str , uint8 str_length);
#endif	/* HAL_EUSART_H */

