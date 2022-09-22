/* 
 * File:   hal_spi.h
 * Author: Maghraby
 *
 * Created on August 12, 2022, 2:18 PM
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H
/* Section: Includes*/
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "hal_spi_cfg.h"


/*Section: Macro Definitions*/
#define RECEIVE_COMPLETE      1
#define RECEIVE_NOT_COMPLETE  0

#define SSPBUF_IS_FULL        1
#define SSPBUF_IS_EMPTY       0

#define ENABLE_SERIAL_PORT    1
#define DISABLE_SERIAL_PORT   0

#define WRITE_COLLISION_OCCURED     1
#define WRITE_COLLISION_NOT_OCCURED 0


/*Section: Function Like Macros*/

#define SPI_Serial_Port_Enable() (SSPCON1bits.SSPEN = 1)
#define SPI_Serial_Port_Disable() (SSPCON1bits.SSPEN = 0)


#define SPI_Data_Sampling_Config(mode) (SSPSTATbits.SMP = mode) /*@ref : spi_data_sampling_t*/

#define SPI_Clock_Polarity_Config(clk_pol) (SSPCON1bits.CKP = clk_pol)  /*@ref : spi_clock_polairty_t*/

#define SPI_Clock_Phase_Config(clk_phas) (SSPSTATbits.CKE = clk_phas)   /*@ref : spi_clock_phase_t */

#define SPI_Serial_Port_Mode_Config(serial_mode) (SSPCON1bits.SSPM = serial_mode) /*@ref : spi_serial_mode_t*/


/*Section: Data Type Declaration*/
typedef enum{
    SPI_Transmit_On_Trans_From_Idle_To_Active = 0,
            SPI_Transmit_On_Trans_From_Active_To_Idle        
            
}spi_clock_phase_t;

typedef enum{
    Idle_State_Low = 0,
            Idle_State_High
}spi_clock_polairty_t;

typedef enum{
    SPI_Data_Sampled_At_Middle_Of_Output = 0,
            SPI_Data_Sampled_At_End_Of_Output        
}spi_data_sampling_t;

typedef enum{
    SPI_Master_Clock_Fosc_Div_By_4 = 0,
            SPI_Master_Clock_Fosc_Div_By_16,        
            SPI_Master_Clock_Fosc_Div_By_64,
            SPI_Master_Clock_TMR2_Div_By_2,        
            SPI_Slave_SS_Pin_Enabled,                  
            SPI_Slave_SS_Pin_Disabled            
}spi_serial_mode_t;


typedef struct{
    
   spi_serial_mode_t spi_mode;
   spi_clock_phase_t spi_clock_phase;
   spi_clock_polairty_t spi_clock_Polarity;
   spi_data_sampling_t spi_sample_data;
   uint8 serial_port_enable;
    
}spi_cfg_t;

/*Section: Function Prototypes*/
STD_ReturnType mcal_spi_init(const spi_cfg_t *spi_obj);
STD_ReturnType mcal_spi_deinit(const spi_cfg_t *spi_obj);
STD_ReturnType mcal_spi_select_slave(uint8 slave_pin);
STD_ReturnType mcal_spi_send_byte_blocking(uint8 data);
STD_ReturnType mcal_spi_receive_byte_blocking(uint8 *data);
STD_ReturnType mcal_spi_send_string_blocking(uint8 *str);
STD_ReturnType mcal_spi_receive_string_blocking(uint8 *str);


#endif	/* HAL_SPI_H */

