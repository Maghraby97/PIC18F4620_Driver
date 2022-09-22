/* 
 * File:   application.h
 * Author: Maghraby
 *
 * Created on February 26, 2022, 3:59 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section: Includes*/

#include "ECU_Layer/ecu_layer_init.h"


//don`t forget to remove the following 2 include lines , you just have put them to test the interrupt driver.
//remove these 2 lines after finishing testing the driver.
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include "MCAL_Layer/GPIO/hal_gpio.h"



/*Section: Macro Definitions*/


/*Section: Function Like Macros*/


/*Section: Data Type Declaration*/



/*Section: Function Prototypes*/

void application_initialize(void);




#endif	/* APPLICATION_H */

