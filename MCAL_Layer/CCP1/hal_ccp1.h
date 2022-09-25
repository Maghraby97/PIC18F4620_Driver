/* 
 * File:   hal_ccp1.h
 * Author: Maghraby
 *
 * Created on June 27, 2022, 5:43 PM
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/* Section: Includes*/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
/*Section: Macro Declarations*/
#define _XTAL_FREQ 4000000

#define CCP1_INSTANCE  ((uint8_t)0)
#define CCP2_INSTANCE  ((uint8_t)1)

#define CCP_MODULE_DISABLE                         ((uint8_t)0)
#define CCP_COMPARE_MODE_TOGGLE_OUTPUT             ((uint8_t)2)
#define CCP_COMPARE_MODE_CCP_PIN_HIGH             ((uint8_t)8)
#define CCP_COMPARE_MODE_CCP_PIN_LOW              ((uint8_t)9)
#define CCP_COMPARE_MODE_GENERATE_SW_INTERRUPT     ((uint8_t)10)
#define CCP_COMPARE_MODE_TRIGGER_SPECIAL_EVENT             ((uint8_t)11)


#define CCP_CAPTURE_MODE_EVERY_FALLING_EDGE            ((uint8_t)4)
#define CCP_CAPTURE_MODE_EVERY_RISING_EDGE             ((uint8_t)5)
#define CCP_CAPTURE_MODE_EVERY_4_RISING_EDGE           ((uint8_t)6)
#define CCP_CAPTURE_MODE_EVERY_16_RISING_EDGE          ((uint8_t)7)

#define CCP_PWM_MODE   ((uint8_t)12)


#define CCP_CAPTURE_NOT_READY    ((uint8_t)0)
#define CCP_CAPTURE_READY        ((uint8_t)1)

#define CCP_COMPARE_NOT_READY    ((uint8_t)0)
#define CCP_COMPARE_READY        ((uint8_t)1)

/*Section: Function Like Macros*/
#define CCP1_Module_Set_Operational_Mode(_CCP1Mode) (CCP1CONbits.CCP1M = _CCP1Mode)   
#define CCP2_Module_Set_Operational_Mode(_CCP2Mode) (CCP2CONbits.CCP2M = _CCP2Mode)

/*Section: Data Type Declaration*/
typedef enum{
    CCP_COMPARE_MODE_ = 0,
    CCP_CAPTURE_MODE_,
    CCP_PWM_MODE_
}ccp_mode_t;

typedef union{
    struct{
      uint8_t ccprL;
      uint8_t ccprH;
    };    
    uint16_t ccpr_Reg;
}CCPR_Reg_t;

typedef struct{
    
    void (*CCP1_Handler)(void);
    void (*CCP2_Handler)(void);
    uint8_t ccp1_interrupt_priority_level;
    uint8_t ccp2_interrupt_priority_level;
    uint8_t cpp_instance;
    
    
    ccp_mode_t ccp_mode;
    uint8_t ccp_submode;
    

    luint64 ccp_pwm_frequency;
    uint8 timer2_prescaler_value:2;
    uint8 timer2_postscaler_value:4;
    uint8_t                        :2;
    uint16_t ccp_pwm_dutycyle;
    
}ccp_t;


/*Section: Function Prototypes*/
STD_ReturnType hal_ccp_init(const ccp_t* ccpobj);
STD_ReturnType hal_ccp_deinit(const ccp_t* ccpobj);



STD_ReturnType hal_ccp_isCaptureReady(const ccp_t* ccpobj,uint8_t *_capture_status);
STD_ReturnType hal_ccp_readCaptureValue(const ccp_t* ccpobj,uint16_t* value);


STD_ReturnType hal_ccp_isCompareComplete(const ccp_t* ccpobj,uint8 *compare_status);
STD_ReturnType hal_ccp_compareModeSetValue(const ccp_t* ccpobj,uint16 compare_value);

STD_ReturnType hal_ccp_setPWMDuty(const ccp_t* ccpobj,const uint8_t duty);
STD_ReturnType hal_ccp_PWMStart(const ccp_t* ccpobj);
STD_ReturnType hal_ccp_PWMStop(const ccp_t* ccpobj);









#endif	/* HAL_CCP1_H */

