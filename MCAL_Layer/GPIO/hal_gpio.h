/* 
 * File:   hal_gpio.h
 * Author: Maghraby
 *
 * Created on February 26, 2022, 3:29 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section: Includes*/

#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"
#include "hal_gpio_cfg.h"

/*Section: Macro Declarations*/
#define  BIT_MASK                        ((uint8)1)
#define  PORT_PIN_MAX_NUMBER             ((uint8)8)
#define  PORT_MAX_NUMBER                 ((uint8)5)

#define  PORTC_MASK                      ((uint8)0xFF)

#define GPIO_PORT_PIN_CONFIGURATIONS         CONFIG_ENABLE
#define GPIO_PORT_CONFIGURATIONS             CONFIG_ENABLE

/*Section: Function Like Macros*/
#define HWREG8(_X)                      (*((volatile uint8 *)(_X)))

#define SET_BIT(REG,BIT_POSN)           (REG |=  (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG,BIT_POSN)         (REG &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG,BIT_POSN)        (REG ^=  (BIT_MASK << BIT_POSN))
#define READ_BIT(REG,BIT_POSN)          ((REG >> BIT_POSN) & BIT_MASK)
    
/*Section: Data Type Declaration*/
typedef enum{
    LOW = 0,
    HIGH
}Logic_t;


typedef enum{
    OUTPUT = 0,
    INPUT
}Direction_t;

typedef enum{
    PIN0 = 0,
    PIN1,
    PIN2,       
    PIN3,        
    PIN4,        
    PIN5,        
    PIN6,
    PIN7,        
}Pin_Index_t;



typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}Port_Index_t;

typedef struct{
    uint8 port          : 3;    /*@ref Port_Index_t*/
    uint8 pin           : 3;    /*@ref Pin_Index_t*/
    uint8 direction     : 1;    /*@ref Direction_t*/
    uint8 logic         : 1;    /*@ref Logic_t*/
}Pin_Config_t;

/*Section: Function Prototypes*/

STD_ReturnType gpio_pin_direction_initialize(const Pin_Config_t * pin_config);
STD_ReturnType gpio_pin_get_direction_status(const Pin_Config_t * pin_config , Direction_t * direction_status);
STD_ReturnType gpio_pin_write_logic(const Pin_Config_t * pin_config , Logic_t logic);
STD_ReturnType gpio_pin_read_logic(const Pin_Config_t * pin_config , Logic_t * logic);
STD_ReturnType gpio_pin_toggle_logic(const Pin_Config_t * pin_config);
STD_ReturnType gpio_pin_initialize(const Pin_Config_t * pin_config);


STD_ReturnType gpio_port_direction_initialize(Port_Index_t port , uint8 direction);
STD_ReturnType gpio_port_get_direction_status(Port_Index_t port , uint8 * direction_status);
STD_ReturnType gpio_port_write_logic(Port_Index_t port,uint8 logic);
STD_ReturnType gpio_port_read_logic(Port_Index_t port,uint8 * logic);
STD_ReturnType gpio_port_toggle_logic(Port_Index_t port);



#endif	/* HAL_GPIO_H */

