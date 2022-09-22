/* 
 * File:   ecu_relay.h
 * Author: Maghraby
 *
 * Created on March 20, 2022, 8:37 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section: Includes*/

#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"


/*Section: Function Like Macros*/


/*Section: Data Type Declaration*/


        //typedef uint8 Relay_Status_t;

typedef enum{
    Relay_Off,
    Relay_On
}Relay_Status_t;

typedef struct{
    uint8 relay_port   :3;
    uint8 relay_pin    :3;
    uint8 relay_status :1;
    uint8 reserved     :1;
}Relay_t;



/*Section: Macro Definitions*/

        
        //#define RELAY_OFF_STATUS   ((Relay_Status_t)0)
        //#define RELAY_ON_STATUS    ((Relay_Status_t)1)


/*Section: Function Prototypes*/

STD_ReturnType relay_initialize(const Relay_t *relay);
STD_ReturnType relay_On(const Relay_t *relay);
STD_ReturnType relay_Off(const Relay_t *relay);


#endif	/* ECU_RELAY_H */

