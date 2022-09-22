/* 
 * File:   hal_eeprom.c
 * Author: Maghraby
 *
 * Created on May 20, 2022, 10:14 PM
 */

#include "hal_eeprom.h"

/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
STD_ReturnType Data_EEPROM_WriteByte(uint16_t bAdd , uint8_t bData){
    STD_ReturnType status = E_OK;
    /*Read the Interrupt Status "Enabled or Disabled" */
    uint8_t globalInterruptStatus = INTCONbits.GIE;
    
    /*Update the Address registers*/
    EEADRH = (uint8_t)((bAdd >> 8)& 0x03);
    EEADR  = (uint8_t)(bAdd & 0xFF);
    
    /*Update the data registers*/
    EEDATA = bData;
    
    /*Select ACcess data EEPROM memory*/
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY; 
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    
    /*Allows write cycles to flash program/data EEPROM*/
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_TO_FLASH_EEPROM;
    
    /*Disable all interrupts "General Interrupt" */
    INTERRUPT_GlobalInterruptDisable();
    
    /*Write the required sequence : 0x55 -> 0xAA*/
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    /*Initiates a data EEPROM erase/write cycle*/
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    
    /*wait for writting process to complete*/
    while(EECON1bits.WR);
    
    /*Inhibits a data EEPROM erase/write cycle*/
    EECON1bits.WREN = INHIBITS_WRITE_CYCLES_TO_FLASH_EEPROM;
    
    /*Restore the Interrupt Status "Enabled or Disabled" */
    INTCONbits.GIE = globalInterruptStatus;
    return status;
}
/**
 * 
 * @param bAdd
 * @param bData
 * @return 
 */
STD_ReturnType Data_EEPROM_ReadByte(uint16_t bAdd , uint8_t* bData){
    STD_ReturnType status = E_OK;
    if(bData != NULL){
        /*Update the Address registers*/
        EEADRH = (uint8_t)((bAdd >> 8)& 0x03);
        EEADR  = (uint8_t)(bAdd & 0xFF);
        /*Select ACcess data EEPROM memory*/
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY; 
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        
        /*Initiate Data EEPROM read*/
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        
        /*It`s prefered to execute to nop() operations. NOP is prefered in high frequency with crystals above 40 MHZ*/
        NOP();   
        NOP();
        
        /*Return the data from data register*/
        *bData = EEDATA;
        
    }else{
        status = E_NOT_OK;
    } 
    return status;   
}