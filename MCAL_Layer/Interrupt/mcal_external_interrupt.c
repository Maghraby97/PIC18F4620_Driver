/* 
 * File:   mcal_external_interrupt.c
 * Author: Maghraby
 *
 * Created on May 11, 2022, 1:56 AM
 */
#include "mcal_external_interrupt.h"

static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;

//void (*RB4_InterruptHandler_High)(void) = NULL;
//void (*RB4_InterruptHandler_Low)(void) = NULL;
//void (*RB5_InterruptHandler_High)(void) = NULL;
//void (*RB5_InterruptHandler_Low)(void) = NULL;
//void (*RB6_InterruptHandler_High)(void) = NULL;
//void (*RB6_InterruptHandler_Low)(void) = NULL;
//void (*RB7_InterruptHandler_High)(void) = NULL;
//void (*RB7_InterruptHandler_Low)(void) = NULL;

static Int_Handler_High RB4_InterruptHandler_High = NULL;
static Int_Handler_Low  RB4_InterruptHandler_Low  = NULL;
static Int_Handler_High RB5_InterruptHandler_High = NULL;
static Int_Handler_Low  RB5_InterruptHandler_Low  = NULL;
static Int_Handler_High RB6_InterruptHandler_High = NULL;
static Int_Handler_Low  RB6_InterruptHandler_Low  = NULL;
static Int_Handler_High RB7_InterruptHandler_High = NULL;
static Int_Handler_Low  RB7_InterruptHandler_Low  = NULL;






static STD_ReturnType External_Interrupt_Global_Enable(const interrupt_INTx_t* int_obj);
static STD_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t* int_obj);
static STD_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t* int_obj);
static STD_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t* int_obj);
static STD_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t* int_obj);
static STD_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t* int_obj);
static STD_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t* int_obj);
static STD_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);
static STD_ReturnType INT0_SetInterruptHandler(void(*IntHandler)(void));
static STD_ReturnType INT1_SetInterruptHandler(void(*IntHandler)(void));
static STD_ReturnType INT2_SetInterruptHandler(void(*IntHandler)(void));


static STD_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t* int_obj);
static STD_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t* int_obj);
static STD_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t* int_obj);
static STD_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t* int_obj);
static STD_ReturnType Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj);
static STD_ReturnType RB4_SetInterruptHandler_High(Int_Handler_High IntHandler_High);
static STD_ReturnType RB4_SetInterruptHandler_Low(Int_Handler_Low IntHandler_Low);
static STD_ReturnType RB5_SetInterruptHandler_High(Int_Handler_High IntHandler_High);
static STD_ReturnType RB5_SetInterruptHandler_Low(Int_Handler_Low IntHandler_Low);
static STD_ReturnType RB6_SetInterruptHandler_High(Int_Handler_High IntHandler_High);
static STD_ReturnType RB6_SetInterruptHandler_Low(Int_Handler_Low IntHandler_Low);
static STD_ReturnType RB7_SetInterruptHandler_High(Int_Handler_High IntHandler_High);
static STD_ReturnType RB7_SetInterruptHandler_Low(Int_Handler_Low IntHandler_Low);

/**
 * 
 * @param int_obj
 * @return 
 */
STD_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        //1-disable external interrupt
        Interrupt_INTx_Disable(int_obj);
        //2-clear external interrupt flag
        Interrupt_INTx_Clear_Flag(int_obj);
        //3-configure edge
        Interrupt_INTx_Edge_Init(int_obj);
        #if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
            //4-configure priority
            Interrupt_INTx_Priority_Init(int_obj);
        #endif
        //5-configure I/O pin
        Interrupt_INTx_Pin_Init(int_obj);
        //6-configure Callback
        Interrupt_INTx_SetInterruptHandler(int_obj);
        //7-enable external interrupt
        Interrupt_INTx_Enable(int_obj);
        //8-enable the global interrupt 
        External_Interrupt_Global_Enable(int_obj);
        
        
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
}
/**
 * 
 * @param int_obj
 * @return 
 */
STD_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
}
/**
 * 
 * @param int_obj
 * @return 
 */
STD_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        EXT_RBx_InterruptDisable();
        EXT_RBx_InterruptFlagClear();
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_GlobalInterruptLowEnable();
                    EXT_RBx_LowPrioritySet();
                }
                else if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_GlobalInterruptHighEnable();
                    EXT_RBx_HighPrioritySet();
                }
                else{
                    status = E_NOT_OK;
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();        
#endif        
        Interrupt_RBx_Pin_Init(int_obj);
        Interrupt_RBx_SetInterruptHandler(int_obj);
        EXT_RBx_InterruptEnable();
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
}
/**
 * 
 * @param int_obj
 * @return 
 */
STD_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
    
}



/* Helper Functions Section.*/
/**
 * 
 * @return 
 */
static STD_ReturnType External_Interrupt_Global_Enable(const interrupt_INTx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        switch(int_obj->src){
            case INTERRUPT_EXTERNAL_INT0:
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
                INTERRUPT_GlobalInterruptHighEnable();        
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();         
#endif
                break;
                
            case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{
                    status = E_NOT_OK;
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();        
#endif
                break;
                
            case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY){
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else{
                    status = E_NOT_OK;
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();        
#endif
                break;
            default:
                status = E_NOT_OK;
                break;
        }
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        switch(int_obj->src){
            case INTERRUPT_EXTERNAL_INT0:  
                EXT_INT0_InterruptEnable();
                break;
                
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptEnable();
                break;
                
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptEnable();
                break;
            default:
                status = E_NOT_OK;
                break;
        }
    }
    else{
        status = E_NOT_OK;
    }
    return status;
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        switch(int_obj->src){
            case INTERRUPT_EXTERNAL_INT0:  
                EXT_INT0_InterruptDisable();
                break;
                
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptDisable();
                break;
                
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptDisable();
                break;
            default:
                status = E_NOT_OK;
                break;
        }
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
#if INTERRUPT_PRIORITY_FEATURE_USED == INTERRUPT_PRIORITY_ENABLE
static STD_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        switch(int_obj->src){  
            case INTERRUPT_EXTERNAL_INT1:
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY){
                    EXT_INT1_LowPrioritySet();
                }
                else if (int_obj->priority == INTERRUPT_HIGH_PRIORITY){
                    EXT_INT1_HighPrioritySet();                    
                }
                else{
                    status = E_NOT_OK;
                }
                break;
                
            case INTERRUPT_EXTERNAL_INT2:
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY){
                    EXT_INT2_LowPrioritySet();
                }
                else if (int_obj->priority == INTERRUPT_HIGH_PRIORITY){
                    EXT_INT2_HighPrioritySet();                   
                }
                else{
                    status = E_NOT_OK;
                }
                break;
            default:
                status = E_NOT_OK;
                break;
        }
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
    
}
#endif
/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        switch(int_obj->src){  
            
            case INTERRUPT_EXTERNAL_INT0:
                if(int_obj->priority == INTERRUPT_FALLING_EDGE){
                    EXT_INT0_FallingEdgeSelect();
                }
                else if (int_obj->priority == INTERRUPT_RISING_EDGE){
                    EXT_INT0_RisingEdgeSelect();                     
                }
                else{
                    status = E_NOT_OK;
                }
                break;
                
            case INTERRUPT_EXTERNAL_INT1:
                if(int_obj->priority == INTERRUPT_FALLING_EDGE){
                    EXT_INT1_FallingEdgeSelect(); 
                }
                else if (int_obj->priority == INTERRUPT_RISING_EDGE){
                    EXT_INT1_RisingEdgeSelect();                    
                }
                else{
                    status = E_NOT_OK;
                }
                break;
                
            case INTERRUPT_EXTERNAL_INT2:
                if(int_obj->priority == INTERRUPT_FALLING_EDGE){
                    EXT_INT2_FallingEdgeSelect();
                }
                else if (int_obj->priority == INTERRUPT_RISING_EDGE){
                    EXT_INT2_RisingEdgeSelect();                  
                }
                else{
                    status = E_NOT_OK;
                }
                break;
            default:
                status = E_NOT_OK;
                break;
        }
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
    
}
/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        status = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    }
    else{
        status = E_NOT_OK;
    }
    return status;   
}

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        switch(int_obj->src){
            case INTERRUPT_EXTERNAL_INT0:  
                EXT_INT0_InterruptFlagClear();
                break;
                
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_InterruptFlagClear();
                break;
                
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_InterruptFlagClear();
                break;
            default:
                status = E_NOT_OK;
                break;
        }
    }
    else{
        status = E_NOT_OK;
    }
    return status;   
}



/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        
    }
    else{
        status = E_NOT_OK;
    }
    
    return status;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t* int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){  
        status = gpio_pin_direction_initialize(&(int_obj->mcu_pin));  
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        switch(int_obj->src){
            case INTERRUPT_EXTERNAL_INT0:
                status = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                break;
            case INTERRUPT_EXTERNAL_INT1:
                status = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);                
                break;                
            case INTERRUPT_EXTERNAL_INT2:
                status = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);                
                break;                
            default:
                status = E_NOT_OK;
                break;
        }
    }
    else{
        status = E_NOT_OK;
    }
    
    
    return status;
}


/**
 * 
 * @param IntHandler
 * @return 
 */
static STD_ReturnType INT0_SetInterruptHandler(void(*IntHandler)(void)){
    STD_ReturnType status = E_OK;
    if(IntHandler != NULL){
        INT0_InterruptHandler = IntHandler;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
/**
 * 
 * @param IntHandler
 * @return 
 */
static STD_ReturnType INT1_SetInterruptHandler(void(*IntHandler)(void)){
    STD_ReturnType status = E_OK;
    if(IntHandler != NULL){
        INT1_InterruptHandler = IntHandler;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
/**
 * 
 * @param IntHandler
 * @return 
 */
static STD_ReturnType INT2_SetInterruptHandler(void(*IntHandler)(void)){
    STD_ReturnType status = E_OK;
    if(IntHandler != NULL){
        INT2_InterruptHandler = IntHandler;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}

void INT0_ISR(void){
    EXT_INT0_InterruptFlagClear();
    if(INT0_InterruptHandler){
        INT0_InterruptHandler();
    }
}
void INT1_ISR(void){
    EXT_INT1_InterruptFlagClear();
    if(INT1_InterruptHandler){
        INT1_InterruptHandler();
    }
}
void INT2_ISR(void){
    EXT_INT2_InterruptFlagClear();
    if(INT2_InterruptHandler){
        INT2_InterruptHandler();
    }
}
/**
 * 
 * @param int_obj
 * @return 
 */
static STD_ReturnType Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj){
    STD_ReturnType status = E_OK;
    if(int_obj != NULL){
        switch(int_obj->mcu_pin.pin){
            case PIN4:
                status = RB4_SetInterruptHandler_High(int_obj->EXT_InterruptHandler_High);
                status = RB4_SetInterruptHandler_Low(int_obj->EXT_InterruptHandler_Low);
                break;
            case PIN5:
                status = RB5_SetInterruptHandler_High(int_obj->EXT_InterruptHandler_High);
                status = RB5_SetInterruptHandler_Low(int_obj->EXT_InterruptHandler_Low);               
                break;                
            case PIN6:
                status = RB6_SetInterruptHandler_High(int_obj->EXT_InterruptHandler_High);
                status = RB6_SetInterruptHandler_Low(int_obj->EXT_InterruptHandler_Low);                
                break;
            case PIN7:
                status = RB7_SetInterruptHandler_High(int_obj->EXT_InterruptHandler_High);
                status = RB7_SetInterruptHandler_Low(int_obj->EXT_InterruptHandler_Low);                
                break;     
            default:
                status = E_NOT_OK;
                break;
        }
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}

static STD_ReturnType RB4_SetInterruptHandler_High(Int_Handler_High IntHandler_High){
    STD_ReturnType status = E_OK;
    if(RB4_InterruptHandler_High == NULL && IntHandler_High != NULL){
        RB4_InterruptHandler_High = IntHandler_High;
    }
    else{
        status = E_NOT_OK;
    }
    return status;        
}
static STD_ReturnType RB4_SetInterruptHandler_Low(Int_Handler_Low IntHandler_Low){
    STD_ReturnType status = E_OK;
    if(RB4_InterruptHandler_Low == NULL && IntHandler_Low != NULL){
        RB4_InterruptHandler_Low = IntHandler_Low;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
static STD_ReturnType RB5_SetInterruptHandler_High(Int_Handler_High IntHandler_High){
    STD_ReturnType status = E_OK;
    if(RB5_InterruptHandler_High == NULL && IntHandler_High != NULL){
        RB5_InterruptHandler_High = IntHandler_High;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
static STD_ReturnType RB5_SetInterruptHandler_Low(Int_Handler_Low IntHandler_Low){
    STD_ReturnType status = E_OK;
    if(RB5_InterruptHandler_Low == NULL && IntHandler_Low != NULL){
        RB5_InterruptHandler_Low = IntHandler_Low;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
static STD_ReturnType RB6_SetInterruptHandler_High(Int_Handler_High IntHandler_High){
    STD_ReturnType status = E_OK;
    if(RB6_InterruptHandler_High == NULL && IntHandler_High != NULL){
        RB6_InterruptHandler_High = IntHandler_High;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
static STD_ReturnType RB6_SetInterruptHandler_Low(Int_Handler_Low IntHandler_Low){
    STD_ReturnType status = E_OK;
    if(RB6_InterruptHandler_Low == NULL && IntHandler_Low != NULL){
        RB6_InterruptHandler_Low = IntHandler_Low;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
static STD_ReturnType RB7_SetInterruptHandler_High(Int_Handler_High IntHandler_High){
    STD_ReturnType status = E_OK;
    if(RB7_InterruptHandler_High == NULL && IntHandler_High != NULL){
        RB7_InterruptHandler_High = IntHandler_High;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}
static STD_ReturnType RB7_SetInterruptHandler_Low(Int_Handler_Low IntHandler_Low){
    STD_ReturnType status = E_OK;
    if(RB7_InterruptHandler_Low == NULL && IntHandler_Low != NULL){
        RB7_InterruptHandler_Low = IntHandler_Low;
    }
    else{
        status = E_NOT_OK;
    }
    return status;
}


void RB4_ISR(uint8_t source){
    EXT_RBx_InterruptFlagClear();
    if(source == 0){
      if(RB4_InterruptHandler_High){RB4_InterruptHandler_High();}  
    }
    else if(source == 1){
      if(RB4_InterruptHandler_Low){RB4_InterruptHandler_Low();}  
    } 
}
void RB5_ISR(uint8_t source){
    EXT_RBx_InterruptFlagClear();
    if(source == 0){
      if(RB5_InterruptHandler_High){RB5_InterruptHandler_High();}  
    }
    else if(source == 1){
      if(RB5_InterruptHandler_Low){RB5_InterruptHandler_Low();}  
    } 
}
void RB6_ISR(uint8_t source){
    EXT_RBx_InterruptFlagClear();
    if(source == 0){
      if(RB6_InterruptHandler_High){RB6_InterruptHandler_High();}  
    }
    else if(source == 1){
      if(RB6_InterruptHandler_Low){RB6_InterruptHandler_Low();}  
    } 
}
void RB7_ISR(uint8_t source){
    EXT_RBx_InterruptFlagClear();
    if(source == 0){
      if(RB7_InterruptHandler_High){RB7_InterruptHandler_High();}  
    }
    else if(source == 1){
      if(RB7_InterruptHandler_Low){RB7_InterruptHandler_Low();}  
    } 
}