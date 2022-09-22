/* 
 * File:   mcal_interrupt_config.h
 * Author: Maghraby
 *
 * Created on May 11, 2022, 1:56 AM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H


/* Section: Includes*/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"    


/*Section: Macro Declarations*/
#define INTERRUPT_ENABLE          1
#define INTERRUPT_DISABLE         0
#define INTERRUPT_OCCURED         1
#define INTERRUPT_NOT_OCCURED     0

#define INTERRUPT_PRIORITY_HIGH  1
#define INTERRUPT_PRIORITY_LOW   0

#define INTERRUPT_PRIORITY_ENABLE      1
#define INTERRUPT_PRIORITY_DISABLE     0

#define INTERRUPT_EXTERNAL_ENABLE      1
#define ITNERRUPT_EXTERNAL_DISABLE     0

#define INTERRUPT_ON_CHANGE_ENABLE      1
#define INTERRUPT_ON_CHANGE_DISABLE     0

#define INTERRUPT_FEATURE_USED              INTERRUPT_ENABLE
#define INTERRUPT_PRIORITY_FEATURE_USED     INTERRUPT_PRIORITY_DISABLE
#define INTERRUPT_EXTERNAL_FEATURE_USED     INTERRUPT_EXTERNAL_ENABLE
#define INTERRUPT_ON_CHANGE_FEATURE_USED    INTERRUPT_ON_CHANGE_ENABLE






/*Section: Function Like Macros*/
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE

#define INTERRUPT_PriorityLevelsEnable()            (RCONbits.IPEN = 1 )
#define INTERRUPT_PriorityLevelsDisable()           (RCONbits.IPEN = 0)

#define  INTERRUPT_GlobalInterruptHighEnable()      (INTCONbits.GIEH = 1)
#define  INTERRUPT_GlobalInterruptHighDisable()     (INTCONbits.GIEH = 0)

#define  INTERRUPT_GlobalInterruptLowEnable()       (INTCONbits.GIEL = 1)
#define  INTERRUPT_GlobalInterruptLowDisable()      (INTCONbits.GIEL = 0)

#else

#define INTERRUPT_GlobalInterruptEnable()           (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalInterruptDisable()          (INTCONbits.GIE = 0)

#define INTERRUPT_PeripheralInterruptEnable()       (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralInterruptDisable()      (INTCONbits.PEIE = 0)

#endif





/*Section: Data Type Declaration*/

typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;

/*Section: Function Prototypes*/




#endif	/* MCAL_INTERRUPT_CONFIG_H */

