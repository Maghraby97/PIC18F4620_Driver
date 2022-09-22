/* 
 * File:   ecu_led.h
 * Author: Maghraby
 *
 * Created on February 26, 2022, 3:51 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section: Includes*/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_config.h"



/*Section: Macro Definitions*/


/*Section: Function Like Macros*/


/*Section: Data Type Declaration*/
typedef enum{
    LED_OFF,
    LED_ON
        
}led_status_t;

typedef struct{
    uint8 port_name  : 3 ;
    uint8 port_pin   : 3 ;
    uint8 led_status : 1 ;
    uint8 reserved   : 1 ;  //for future use
}led_t;

/*Section: Function Prototypes*/

STD_ReturnType led_initialize(const led_t* led);
STD_ReturnType led_turn_on(const led_t* led);
STD_ReturnType led_turn_off(const led_t* led);
STD_ReturnType led_toggle(const led_t* led);


#endif	/* ECU_LED_H */

