/* 
 * File:   ecu_button.h
 * Author: Maghraby
 *
 * Created on March 18, 2022, 2:16 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H


/* Section: Includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include"ecu_button_cfg.h"




/*Section: Macro Definitions*/
typedef enum{
    button_released = 0,
    button_pressed
}Button_State_t;

typedef enum{
    button_active_low = 0,
    button_active_high
}Button_Logic_t;

typedef struct{
    Pin_Config_t    button_pin;
    Button_State_t  button_state;
    Button_Logic_t  button_logic;
}Button_t;


/*Section: Function Like Macros*/


/*Section: Data Type Declaration*/



/*Section: Function Prototypes*/
STD_ReturnType button_initialize(const Button_t *button);
STD_ReturnType button_read_state(const Button_t *button,Button_State_t *state);



#endif	/* ECU_BUTTON_H */

