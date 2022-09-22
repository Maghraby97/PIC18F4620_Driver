/* 
 * File:   ecu_dc_motor.h
 * Author: Maghraby
 *
 * Created on March 22, 2022, 3:29 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H


/* Section: Includes*/
#include "ecu_dc_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/*Section: Macro Definitions*/

#define MOTOR_ON_STATUS     0x01U
#define MOTOR_OFF_STATUS    0x00U

#define MOTOR_PIN_0         0x00U
#define MOTOR_PIN_1         0x01U

/*Section: Data Type Declaration*/
typedef struct{
    Pin_Config_t motor_pin;
}dc_motor_pin_t ;

typedef struct{
    dc_motor_pin_t motor[2];
    uint8          motor_status; 
}dc_motor_t;
/*Section: Function Like Macros*/


/*Section: Function Prototypes*/

STD_ReturnType dc_motor_initialize(const dc_motor_t *motor);
STD_ReturnType dc_motor_forward(const dc_motor_t *motor);
STD_ReturnType dc_motor_reverse(const dc_motor_t *motor);
STD_ReturnType dc_motor_stop(const dc_motor_t *motor);


#endif	/* ECU_DC_MOTOR_H */

