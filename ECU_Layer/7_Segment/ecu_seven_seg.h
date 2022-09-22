/* 
 * File:   ecu_seven_seg.h
 * Author: Maghraby
 *
 * Created on March 30, 2022, 1:12 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/* Section: Includes*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_seven_seg_cfg.h"


/*Section: Macro Definitions*/

#define SEGMENT_PIN_0  ((uint8)0)
#define SEGMENT_PIN_1  ((uint8)1)
#define SEGMENT_PIN_2  ((uint8)2)
#define SEGMENT_PIN_3  ((uint8)3)


#define SEGMENT_MAX_NUMBER_DISPLAYED   ((uint8)9)

/*Section: Function Like Macros*/


/*Section: Data Type Declaration*/
typedef enum{
    Common_Anode,
            Common_Cathode
}Segment_Type_t;

typedef struct{
    Pin_Config_t segments_pins[4];
    Segment_Type_t segment_type;
}Segment_t;



/*Section: Function Prototypes*/

STD_ReturnType Seven_Segment_Initialize(const Segment_t *segment );
STD_ReturnType Seven_Sement_Write_Number(const Segment_t *segment , uint8 number);

#endif	/* ECU_SEVEN_SEG_H */

