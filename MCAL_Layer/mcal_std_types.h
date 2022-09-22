 /* 
 * File:   mcal_std_types.h
 * Author: Maghraby
 *
 * Created on February 26, 2022, 3:44 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section: Includes*/

#include "std_libraries.h"
#include "compiler.h"





/*Section: Data Type Declaration*/
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;
typedef unsigned long int    luint64; 

typedef signed char     sint8;
typedef signed short    sint16;
typedef signed int      sint32;
typedef signed long int    lsint64; 

typedef  uint8          STD_ReturnType;
        
/*Section: Macro Definitions*/
#define STD_HIGH       0x01
#define STD_LOW        0x00


#define STD_ON         0x01
#define STD_OFF        0x00

#define STD_ACTIVE     0x01
#define STD_IDLE       0x00

#define  E_OK           (STD_ReturnType)0x01
#define  E_NOT_OK       (STD_ReturnType)0x00 

#define  ZERO_INIT      0x00
/*Section: Function Like Macros*/


/*Section: Function Prototypes*/




#endif	/* MCAL_STD_TYPES_H */

