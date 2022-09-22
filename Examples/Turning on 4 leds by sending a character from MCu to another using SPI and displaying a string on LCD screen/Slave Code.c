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
    .spi_sample_data = SPI_Data_Sampled_At_Middle_Of_Output,
    .spi_mode = SPI_Slave_SS_Pin_Enabled
};

chr_lcd_8bit_t lcd_8 = {
  .lcd_rs.port = PORTA_INDEX,
  .lcd_rs.pin = PIN0,
  .lcd_rs.direction = OUTPUT,
  .lcd_rs.logic = LOW,
  
  .lcd_en.port =PORTA_INDEX,
  .lcd_en.pin = PIN1,
  .lcd_en.direction = OUTPUT,
  .lcd_en.logic = HIGH,
  
  .lcd_data[0].port = PORTB_INDEX,
  .lcd_data[0].pin = PIN0,
  .lcd_data[0].direction= OUTPUT,
  .lcd_data[0].logic = LOW,
  
  .lcd_data[1].port = PORTB_INDEX,
  .lcd_data[1].pin = PIN1,
  .lcd_data[1].direction= OUTPUT,
  .lcd_data[1].logic = LOW,
  
  .lcd_data[2].port = PORTB_INDEX,
  .lcd_data[2].pin = PIN2,
  .lcd_data[2].direction= OUTPUT,
  .lcd_data[2].logic = LOW,
  
  .lcd_data[3].port = PORTB_INDEX,
  .lcd_data[3].pin = PIN3,
  .lcd_data[3].direction= OUTPUT,
  .lcd_data[3].logic = LOW,
  
  .lcd_data[4].port = PORTB_INDEX,
  .lcd_data[4].pin = PIN4,
  .lcd_data[4].direction= OUTPUT,
  .lcd_data[4].logic = LOW,
  
  .lcd_data[5].port = PORTB_INDEX,
  .lcd_data[5].pin = PIN5,
  .lcd_data[5].direction= OUTPUT,
  .lcd_data[5].logic = LOW,
  
  .lcd_data[6].port = PORTB_INDEX,
  .lcd_data[6].pin = PIN6,
  .lcd_data[6].direction= OUTPUT,
  .lcd_data[6].logic = LOW,
  
  .lcd_data[7].port = PORTB_INDEX,
  .lcd_data[7].pin = PIN7,
  .lcd_data[7].direction= OUTPUT,
  .lcd_data[7].logic = LOW,
};

dc_motor_t m1 = {
    .motor[0].motor_pin.port = PORTD_INDEX,
    .motor[0].motor_pin.pin = PIN4,
    .motor[0].motor_pin.direction = OUTPUT ,
    .motor[0].motor_pin.logic = LOW,
    
    .motor[1].motor_pin.port = PORTD_INDEX,
    .motor[1].motor_pin.pin = PIN5,
    .motor[1].motor_pin.direction = OUTPUT ,
    .motor[1].motor_pin.logic = LOW,
    
};
uint8 receivedByte = 0;

int main(void) {


     Pin_Config_t rd0={
     .port = PORTD_INDEX,
     .pin = PIN0,
     .direction = OUTPUT,
     .logic = LOW
     };
     Pin_Config_t rd1={
     .port = PORTD_INDEX,
     .pin = PIN1,
     .direction = OUTPUT,
     .logic = LOW
     };
     Pin_Config_t rd2={
     .port = PORTD_INDEX,
     .pin = PIN2,
     .direction = OUTPUT,
     .logic = LOW
     };
     Pin_Config_t rd3={
     .port = PORTD_INDEX,
     .pin = PIN3,
     .direction = OUTPUT,
     .logic = LOW
     };

     Pin_Config_t arr[4]={rd0,rd1,rd2,rd3};


     gpio_pin_initialize(&rd0);
     gpio_pin_initialize(&rd1);
     gpio_pin_initialize(&rd2);
     gpio_pin_initialize(&rd3);

     lcd_8bit_initialize(&lcd_8);

     dc_motor_initialize(&m1);




    mcal_spi_init(&_spi);



    while (1) {

        Slave code
         mcal_spi_receive_byte_blocking(&receivedByte);
         if(receivedByte == 'M'){
         for(int i = 0 ; i < 4 ; i++){
         lcd_8bit_send_command(&lcd_8,_LCD_CLEAR);
         lcd_8bit_send_string_pos(&lcd_8,1,1,"Leds are ON");
         lcd_8bit_send_string_pos(&lcd_8,2,1,"Motor forward");
         dc_motor_forward(&m1);
         gpio_pin_write_logic(&arr[i],HIGH);
         __delay_ms(100);
         }
         }
         else if(receivedByte == 'S'){
         for(int i = 0 ; i < 4 ; i++){
         lcd_8bit_send_command(&lcd_8,_LCD_CLEAR);
         lcd_8bit_send_string_pos(&lcd_8,1,3,"Leds are OFF");
         lcd_8bit_send_string_pos(&lcd_8,2,1,"Motor reverse");
         dc_motor_reverse(&m1);
         gpio_pin_write_logic(&arr[i],LOW);
         __delay_ms(100);
         }
         }

         receivedByte = 0;

      

    }




    return (EXIT_SUCCESS);
}
