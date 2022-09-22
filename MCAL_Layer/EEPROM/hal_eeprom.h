/* 
 * File:   hal_eeprom.h
 * Author: Maghraby
 *
 * Created on May 20, 2022, 10:14 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H


/* Section: Includes*/
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"

/*Section: Macro Declarations*/
#define ACCESS_FLASH_PROGRAM_MEMORY             1
#define ACCESS_EEPROM_PROGRAM_MEMORY            0
#define ACCESS_CONFIG_REGISTERS                 1
#define ACCESS_FLASH_EEPROM_MEMORY              0
#define ALLOW_WRITE_CYCLES_TO_FLASH_EEPROM      1
#define INHIBITS_WRITE_CYCLES_TO_FLASH_EEPROM   0
#define INITIATE_DATA_EEPROM_WRITE_ERASE        1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED       0
#define INITIATE_DATA_EEPROM_READ               1

/*Section: Function Like Macros*/


/*Section: Data Type Declaration*/



/*Section: Function Prototypes*/

STD_ReturnType Data_EEPROM_WriteByte(uint16_t bAdd , uint8_t bData);
STD_ReturnType Data_EEPROM_ReadByte(uint16_t bAdd , uint8_t* bData);

#endif	/* HAL_EEPROM_H */

