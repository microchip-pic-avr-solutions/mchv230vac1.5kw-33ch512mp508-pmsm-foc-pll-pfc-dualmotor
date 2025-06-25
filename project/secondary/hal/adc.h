// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file adc.h
 *
 * @brief This header file lists the functions and definitions - to configure 
 * and enable ADC Module and its features 
 * 
 * Definitions in the file are for dsPIC33CH512MP508 MC DIM plugged onto 
 * Motor Control Development board from Microchip
 *
 * Component: ADC
 *
 */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Disclaimer ">

/*******************************************************************************
* SOFTWARE LICENSE AGREEMENT
* 
* © [2024] Microchip Technology Inc. and its subsidiaries
* 
* Subject to your compliance with these terms, you may use this Microchip 
* software and any derivatives exclusively with Microchip products. 
* You are responsible for complying with third party license terms applicable to
* your use of third party software (including open source software) that may 
* accompany this Microchip software.
* 
* Redistribution of this Microchip software in source or binary form is allowed 
* and must include the above terms of use and the following disclaimer with the
* distribution and accompanying materials.
* 
* SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL 
* MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR 
* CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO
* THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE 
* POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY
* LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL
* NOT EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR THIS
* SOFTWARE
*
* You agree that you are solely responsible for testing the code and
* determining its suitability.  Microchip has no obligation to modify, test,
* certify, or support the code.
*
*******************************************************************************/
// </editor-fold>

#ifndef _ADC_H
#define _ADC_H

#ifdef __cplusplus  // Provide C++ Compatability
    extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">        
#include <xc.h>
#include <stdint.h>
// </editor-fold>         

// <editor-fold defaultstate="collapsed" desc="DEFINITIONS/MACROS ">

#define MC_ADCBUF_VDC         (int16_t)( ADCBUF10 >> 1)
/* MC1 ADC Buffer Definitions */
#define MC1_ADCBUF_IPHASE1    (int16_t)(-ADCBUF0)   
#define MC1_ADCBUF_IPHASE2    (int16_t)(-ADCBUF1)
#define MC1_ADCBUF_IBUS       ADCBUF13      
#define MC1_ADCBUF_POT        (int16_t)(ADCBUF15 >> 1)
   
/* MC2 ADC Buffer definitions */
#define MC2_ADCBUF_IPHASE1    (int16_t)(-ADCBUF0)   
#define MC2_ADCBUF_IPHASE2    (int16_t)(-ADCBUF1)
#define MC2_ADCBUF_IBUS       ADCBUF18
/*
 .....
 */        

/* MC1 ADC Interrupt definitions */
#define MC1_ADC_INTERRUPT   _ADCAN15Interrupt            
#define MC1_EnableADCInterrupt()   _ADCAN15IE = 1
#define MC1_DisableADCInterrupt()  _ADCAN15IE = 0
#define MC1_ClearADCIF()           _ADCAN15IF = 0
#define MC1_ClearADCIF_ReadADCBUF() ADCBUF15

/* MC2 ADC Interrupt definitions */        
#define MC2_ADC_INTERRUPT   _ADCAN18Interrupt    // change     
#define MC2_EnableADCInterrupt()   _ADCAN18IE = 1
#define MC2_DisableADCInterrupt()  _ADCAN18IE = 0
#define MC2_ClearADCIF()           _ADCAN18IF = 0
#define MC2_ClearADCIF_ReadADCBUF() ADCBUF18      

// </editor-fold> 
        
// <editor-fold defaultstate="collapsed" desc="INTERFACE FUNCTIONS ">  

void InitializeADCs(void);

// </editor-fold> 

#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif
#endif      // end of ADC_H

