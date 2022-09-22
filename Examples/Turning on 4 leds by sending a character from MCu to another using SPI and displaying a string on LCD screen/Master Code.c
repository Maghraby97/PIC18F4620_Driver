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
#define _XTAL_FREQ 8000000

spi_cfg_t _spi = {
    .serial_port_enable = ENABLE_SERIAL_PORT,
    .spi_clock_Polarity = Idle_State_Low,
    .spi_clock_phase = SPI_Transmit_On_Trans_From_Idle_To_Active,
    .spi_mode = SPI_Master_Clock_Fosc_Div_By_4,
    .spi_sample_data = SPI_Data_Sampled_At_Middle_Of_Output,
};


int main(void) {

    mcal_spi_init(&_spi);



    while (1) {

        mcal_spi_select_slave(5);
        mcal_spi_send_byte_blocking('M');
        __delay_ms(3000);
        mcal_spi_select_slave(5);
        mcal_spi_send_byte_blocking('S');
        __delay_ms(3000);


    }




    return (EXIT_SUCCESS);
}