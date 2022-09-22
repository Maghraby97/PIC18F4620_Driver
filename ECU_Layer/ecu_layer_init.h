/* 
 * File:   ecu_layer_init.h
 * Author: Maghraby
 *
 * Created on April 2, 2022, 8:39 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section: Includes*/

#include "button/ecu_button.h"
#include "LED/ecu_led.h"
#include "DC_Motor/ecu_dc_motor.h"
#include "7_Segment/ecu_seven_seg.h"
#include "Keypad/ecu_keypad.h"
#include "Chr_LCD/ecu_chr_lcd.h"

/*Section: Macro Definitions*/


/*Section: Function Like Macros*/


/*Section: Data Type Declaration*/
extern chr_lcd_4bit_t lcd_1 ;
extern chr_lcd_8bit_t lcd_2 ;

/*Section: Function Prototypes*/

void ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INIT_H */

