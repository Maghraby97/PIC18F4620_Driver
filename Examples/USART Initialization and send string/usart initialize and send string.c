uint8* tx_buffer = "I hate this\r";
static volatile uint8 char_index = 0;
uint8 number_of_char_in_tx_buffer = 12;
uint8 volatile num_of_char_transmitter = 0;
volatile uint32 tx_flag = 0;
void tx_isr(void);


//uint8 compare_2_strings(uint8 *str1,uint8 *str2);




eusart_tx_t eusartTX = {
  .Int_Tx_Handler_Var = tx_isr,
  .eusart_tx_enabled = EUSART_TX_ENABLED,
  .eusart_9bit_transmission = EUSART_TX_9BIT_NOT_SELECTED,
  .eusart_tx_interrupt_enabled = EUSART_TX_INTERRUPT_ENABLE

};
eusart_rx_t eusartRX = {
  .Int_Rx_Handler_Var = NULL,
  .eusart_rx_enabled = EUSART_RX_ENABLED,
  .eusart_9bit_reception = EUSART_RX_9BIT_NOT_SELECTED,
  .eusart_rx_interrupt_enabled = EUSART_RX_INTERRUPT_DISABLE


};

eusart_t eusart = {
    .baudrate_cfg = EUSART_Asynchronous_8bit_HighSpeed,
    .baudrate_value = 9600,
    .mode_of_operation = EUSART_ASYNCHRONOUS_MODE,
    .eusart_tx_cfg = &eusartTX,
    .eusart_rx_cfg = &eusartRX
};

Pin_Config_t rc0 = {
  .direction = OUTPUT,
  .port = PORTC_INDEX,
  .pin = PIN0,
  .logic = LOW
};

/*The Interrupt service routine for the transmitter.
 * when an interrupt is issued the next character is sent
 */

void tx_isr(void) {

    if (*(tx_buffer + (char_index - 1)) != '\0') {
        TXREG = *(tx_buffer + char_index);
        char_index++;
    }
    else {
        TXREG = '\0';
        char_index = 0;
        EUSART_Transmitter_Disabled();
    }


}



//sint32 compare_fun_flag = 5;
int main(void) {
    mcal_eusart_asynchronous_init(&eusart);
    gpio_pin_direction_initialize(&rc0);
    //mcal_eusart_send_string_non_blocking();

    while (1) {


        mcal_eusart_send_string_non_blocking();
        //        EUSART_Transmitter_Enabled();
        //        mcal_eusart_send_byte_blocking('\r');
        //        EUSART_Transmitter_Disabled();
        __delay_ms(2000);



    }




    return (EXIT_SUCCESS);
}


//void application_init(void){
//    
//    ecu_layer_initialize();
//    
//}
