/* 
 * File:   ecu_keypad.h
 * Author: Maghraby
 *
 * Created on March 31, 2022, 3:36 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H


/* Section: Includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_keypad_cfg.h"

/*Section: Macro Definitions*/

#define KEYPAD_NUMBER_OF_ROWS       ((uint8)4)
#define KEYPAD_NUMBER_OF_COLUMNS    ((uint8)4)


#define FIRST_ROW                   ((uint8)0)
#define SECOND_ROW                  ((uint8)1)
#define THIRD_ROW                   ((uint8)2)
#define FOURTH_ROW                  ((uint8)3)


#define FIRST_COLUMN                   ((uint8)0)
#define SECOND_COLUMN                  ((uint8)1)
#define THIRD_COLUMN                   ((uint8)2)
#define FOURTH_COLUMN                  ((uint8)3)


#define PRESSED                          ((uint8)0x01)
#define NOT_PRESSED                      ((uint8)0x00)


/*Section: Function Like Macros*/


/*Section: Data Type Declaration*/
typedef struct{
    Pin_Config_t keypad_rows[KEYPAD_NUMBER_OF_ROWS];
    Pin_Config_t keypad_columns[KEYPAD_NUMBER_OF_COLUMNS];
    
}Keypad_t;



/*Section: Function Prototypes*/

STD_ReturnType keypad_initialize(const Keypad_t *keypad);
STD_ReturnType keypad_get_pressed_button(const Keypad_t *keypad,uint8 *button_pressed);



#endif	/* ECU_KEYPAD_H */

