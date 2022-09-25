/* 
 * File:   MCAL_I2C.h
 * Author: Maghraby
 *
 * Created on September 20, 2022, 6:25 PM
 */

#ifndef MCAL_I2C_H
#define	MCAL_I2C_H


/* Section: Includes*/
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "MCAL_I2C_Config.h"

/*Section: Macro Definitions*/


/*
 BF: Buffer Full Status bit
 In Transmit mode:
 1 = SSPBUF is full
 0 = SSPBUF is empty
 In Receive mode:
 1 = SSPBUF is full (does not include the ACK and Stop bits)
 0 = SSPBUF is empty (does not include the ACK and Stop bits)
 
 */
#define MCAL_I2C_SSPBUF_IS_EMPTY     0
#define MCAL_I2C_SSPBUF_IS_FULL      1


/*
 R/W: Read/Write Information bit
 In Slave mode:
 1 = Read
 0 = Write
 In Master mode:
 1 = Transmit is in progress
 0 = Transmit is not in progress
 */
#define MCAL_I2C_MASTER_WRITE        0
#define MCAL_I2C_MASTER_READ         1

/*
 S: Start bit(1)
 1 = Indicates that a Start bit has been detected last
 0 = Start bit was not detected last 
 
 */
#define MCAL_I2C_START_BIT_NOT_DETECTED  0
#define MCAL_I2C_START_BIT_DETECTED      1

/*
 P: Stop bit(1)
 1 = Indicates that a Stop bit has been detected las
 0 = Stop bit was not detected last
 */
#define MCAL_I2C_STOP_BIT_NOT_DETECTED  0
#define MCAL_I2C_STOP_BIT_DETECTED      1

/*
 D/A: Data/Address bit
 In Master mode:
 Reserved.
 In Slave mode:
 1 = Indicates that the last byte received or transmitted was data
 0 = Indicates that the last byte received or transmitted was address
 */
#define MCAL_I2C_LAST_BYTE_WAS_ADDRESS     0
#define MCAL_I2C_LAST_BYTE_WAS_DATA        1

/*
 CKP: SCK Release Control bit
    In Slave mode:
        1 = Releases clock
        0 = Holds clock low (clock stretch), used to ensure data setup time
 */
#define MCAL_I2C_STRETCH_CLOCK  0
#define MCAL_I2C_RELEASE_CLOCK  1

/*
 SSPEN: Master Synchronous Serial Port Enable bit(1)
    1 = Enables the serial port and configures the SDA and SCL pins as th
    0 = Disables serial port and configures these pins as I/O port pins
 */
#define MCAL_I2C_DISABLE_SERIAL_PORT    0
#define MCAL_I2C_ENABLE_SERIAL_PORT     1

/*
 SSPOV: Receive Overflow Indicator bit
    In Receive mode:
        1 = A byte is received while the SSPBUF register is still holding the previous byte (must be cleared in
            software)
        0 = No overflow
 */
#define MCAL_I2C_OVERFLOW_NOT_OCCURED  0
#define MCAL_I2C_OVERFLOW_OCCURED  1

/*
 WCOL: Write Collision Detect bit
    In Master Transmit mode:
        1 = A write to the SSPBUF register was attempted while the I2C conditions were not valid for a
            transmission to be started (must be cleared in software)
        0 = No collision
    In Slave Transmit mode:
        1 = The SSPBUF register is written while it is still transmitting the previous word (must be cleared in
            software)
        0 = No collision
    In Receive mode (Master or Slave modes):
        This is a ?don?t care? bit.
 */
#define MCAL_I2C_WRITE_COLLISION_NOT_OCCURED   0
#define MCAL_I2C_WRITE_COLLISION_OCCURED       1

/*
 SEN: Start Condition Enable/Stretch Enable bit(1)
    In Master mode:
        1 = Initiates Start condition on SDA and SCL pins. Automatically cleared by hardware.
        0 = Start condition Idle
    In Slave mode:
        1 = Clock stretching is enabled for both slave transmit and slave receive (stretch enabled)
        0 = Clock stretching is disabled
 */
#define MCAL_I2C_MASTER_START_CONDITION_IDLE 0
#define MCAL_I2C_MASTER_START_CONDITION  1

#define MCAL_I2C_CLOCK_STRETCH_DISABLED 0
#define MCAL_I2C_CLOCK_STRETCH_ENABLED  1

/*
 RSEN: Repeated Start Condition Enable bit (Master mode only)(1)
    1 = Initiates Repeated Start condition on SDA and SCL pins. Automatically cleared by hardware.
    0 = Repeated Start condition Idle
 */
#define MCAL_I2C_MASTER_REPEATED_START_CONDITION_IDLE    0
#define MCAL_I2C_MASTER_REPEATED_START_CONDITION  1

/*
 PEN: Stop Condition Enable bit (Master mode only)(1)
    1 = Initiates Stop condition on SDA and SCL pins. Automatically cleared by hardware.
    0 = Stop condition Idle
 */
#define MCAL_I2C_MASTER_STOP_CONDITION_IDLE  0
#define MCAL_I2C_MASTER_STOP_CONDITION  1

/*
 RCEN: Receive Enable bit (Master mode only)(1)
    1 = Enables Receive mode for I2C
    0 = Receive Idle
 */
#define MCAL_I2C_MASTER_RECEIVE_MODE_IDLE     0
#define MCAL_I2C_MASTER_RECEIVE_MODE_ENABLED  1

/*
 ACKEN: Acknowledge Sequence Enable bit (Master Receive mode only)(1)
    1 = Initiates Acknowledge sequence on SDA and SCL pins and transmit ACKDT data bit. Automatically
        cleared by hardware.
    0 = Acknowledge sequence Idle
 */
#define MCAL_I2C_ACK_DISABLED  0
#define MCAL_I2C_ACK_ENABLED   1

/*
 ACKDT: Acknowledge Data bit (Master Receive mode only)(2)
    1 = Not Acknowledge
    0 = Acknowledge
 */
#define MCAL_I2C_NO_ACK     1
#define MCAL_I2C_SEND_ACK   0

/*
 ACKSTAT: Acknowledge Status bit (Master Transmit mode only)
    1 = Acknowledge was not received from slave
    0 = Acknowledge was received from slave
 */
#define MCAL_I2C_ACK_NOT_RECEIVED 1
#define MCAL_I2C_ACK_RECEIVED  0


/*
 GCEN: General Call Enable bit (Slave mode only)
    1 = Enables interrupt when a general call address (0000h) is received in the SSPSR
    0 = General call address disabled.
 */
#define MCAL_I2C_DISABLE_GENERAL_CALL   0
#define MCAL_I2C_ENABLE_GENERAL_CALL_INTERRUPT  1




/*Section: Function Like Macros*/
#define MCAL_I2C_IS_LAST_DATA_RECEIVED_WAS_ADDRESS_OR_DATA()   (SSPSTATbits.D_nA)
#define MCAL_I2C_IS_STOP_BIT_DETECTED()   (SSPSTATbits.P)
#define MCAL_I2C_IS_START_BIT_DETECTED()   (SSPSTATbits.S)
#define MCAL_I2C_GET_R_W_BIT()        (SSPSTATbits.R_nW)
#define MCAL_I2C_IS_SSPBUF_FULL ()      (SSPSTATbits.BF)

#define MCAL_I2C_IS_WRITE_COLLISION_DETECTED()  (SSPCON1bits.WCOL)
#define MCAL_I2C_IS_RECEIVE_OVERFLOW_DETECTED() (SSPCON1bits.SSPOV)

#define MCAL_I2C_CONFIG_ENABLE_SERIAL_PORT()            (SSPCON1bits.SSPEN = 1)
#define MCAL_I2C_CONFIG_DISABLE_SERIAL_PORT()           (SSPCON1bits.SSPEN = 0)

#define MCAL_I2C_CONFIG_RELEASE_CLOCK()     (SSPCON1bits.CKP = 1)
#define MCAL_I2C_CONFIG_STRETCH_CLOCK()     (SSPCON1bits.CKP = 0)

#define MCAL_I2C_CONFIG_I2C_MODE_OF_OPERATION(config)  (SSPCON1bits.SSPM = config)

#define MCAL_I2C_CONFIG_ENABLE_GENERAL_CALL()     (SSPCON2bits.GCEN = 1)
#define MCAL_I2C_CONFIG_DISABLE_GENERAL_CALL()    (SSPCON2bits.GCEN = 1)

#define MCAL_I2C_IS_ACK_RECEIVED()         (SSPCON2bits.ACKSTAT)

#define MCAL_I2C_CONFIG_SEND_NOT_ACK()     (SSPCON2bits.ACKDT = 1)
#define MCAL_I2C_CONFIG_SEND_ACK()         (SSPCON2bits.ACKDT = 0)

#define MCAL_I2C_CONFIG_ENABLE_ACK_SEQUENCE_ON_MASTER()    (SSPCON2bits.ACKEN = 1)
#define MCAL_I2C_CONFIG_DISABLE_ACK_SEQUENCE_ON_MASTER()   (SSPCON2bits.ACKEN = 0)

#define MCAL_I2C_CONFIG_ENABLE_MASTER_RECEIVE()    (SSPCON2bits.RCEN = 1)
#define MCAL_I2C_CONFIG_DISABLEL_MASTER_RECEIVE()  (SSPCON2bits.RCEN = 0)

#define MCAL_I2C_CONFIG_ENABLE_STOP_CONDITION()    (SSPCON2bits.RCEN = 1)
#define MCAL_I2C_CONFIG_DISABLEL_STOP_CONDITION()  (SSPCON2bits.RCEN = 0)

#define MCAL_I2C_CONFIG_ENABLE_REPEATED_START_CONDITION()    (SSPCON2bits.RSEN = 1)
#define MCAL_I2C_CONFIG_DISABLEL_REPEATED_START_STOP_CONDITION()  (SSPCON2bits.RSEN = 0)

#define MCAL_I2C_CONFIG_ENABLE_START_CONDITION()    (SSPCON2bits.SEN = 1)
#define MCAL_I2C_CONFIG_DISABLE_START_CONDITION()   (SSPCON2bits.SEN = 0)

#define MCAL_I2C_CONFIG_ENABLE_CLOCK_STRETCH_ON_SLAVE()    (SSPCON2bits.SEN = 1)
#define MCAL_I2C_CONFIG_DISABLE_CLOCK_STRETCH_ON_SLAVE()   (SSPCON2bits.SEN = 0)



/*Section: Data Type Declaration*/


/*
 SSPM3:SSPM0: Master Synchronous Serial Port Mode Select bits(2)
    1111 = I2C Slave mode, 10-bit address with Start and Stop bit interrupts enabled
    1110 = I2C Slave mode, 7-bit address with Start and Stop bit interrupts enabled
    1011 = I2C Firmware Controlled Master mode (Slave Idle)
    1000 = I2C Master mode, clock = FOSC/(4 * (SSPADD + 1))
    0111 = I2C Slave mode, 10-bit address
    0110 = I2C Slave mode, 7-bit address

 */
typedef enum{
    MCAL_I2C_Slave_Mode_7Bit_Address = 6,
            MCAL_I2C_Slave_Mode_10Bit_Address,        
            MCAL_I2C_Master_Mode,
            MCAL_I2C_Firmware_Controlled_Master_Mode = 11,
            MCAL_I2C_Slave_Mode_7Bit_Address_Start_Stop_Interrupts_Enabled = 14,
            MCAL_I2C_Slave_Mode_10Bit_Address_Start_Stop_Interrupts_Enabled = 15   
}mcal_i2c_mode_t;

typedef enum{
    ACK = 0,
            NOT_ACK
}mcal_ack_status_t;


typedef struct{
    uint32_t clock_speed;
    uint8_t ack_Sequence_enable;   /*this is used in Master Receive mode only*/
    uint8_t receive_enable;  /*this is used in Master Receive mode only*/
    uint8_t stop_condition_enable;
    uint8_t start_condition_enable;
    uint8_t repeated_start_condition_enable;
    
}mcal_i2c_master_config;

typedef struct{
    uint8_t slave_address;
    uint8_t general_call_enable;
    uint8_t clock_stretch_enable;
}mcal_i2c_slave_config;

typedef struct{
    mcal_i2c_mode_t i2c_mode;  /*@ref: mcal_i2c_mode_t*/
    uint8_t serial_port_enable;
    mcal_i2c_master_config *i2c_master;
    mcal_i2c_slave_config *i2c_slave;
}mcal_i2c_config_t;



/*Section: Function Prototypes*/

STD_ReturnType mcal_i2c_initialize(mcal_i2c_config_t *i2c_obj);
STD_ReturnType mcal_i2c_deinitialize(mcal_i2c_config_t *i2c_obj);

STD_ReturnType mcal_i2c_master_send_data(uint8_t data, mcal_ack_status_t *ack_status);
STD_ReturnType mcal_i2c_master_receive_data(uint8_t *data, mcal_ack_status_t ack_status);

STD_ReturnType mcal_i2c_slave_send_data(uint8_t data, mcal_ack_status_t *ack_status);
STD_ReturnType mcal_i2c_slave_receive_data(uint8_t *data, mcal_ack_status_t ack_status);

STD_ReturnType mcal_i2c_send_slave_address(uint8_t slave_address, uint8_t read_write_bit,mcal_ack_status_t *ack_status);




#endif	/* MCAL_I2C_H */

