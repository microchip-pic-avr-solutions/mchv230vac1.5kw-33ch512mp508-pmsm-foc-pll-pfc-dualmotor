// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file clock.h
 *
 * @brief This header file lists the functions and definitions - to configure 
 * and enable Clock/Oscillator/PLL Module and its features
 * 
 * Definitions in the file are for dsPIC33CH512MP508 MC DIM plugged onto 
 * Motor Control Development board from Microchip
 * 
 * Component: CLOCK/OSCILLATOR
 *
 */
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Disclaimer ">

/*******************************************************************************
* SOFTWARE LICENSE AGREEMENT
* 
* � [2024] Microchip Technology Inc. and its subsidiaries
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

#ifndef _CLOCK_H
#define _CLOCK_H

#ifdef __cplusplus  // Provide C++ Compatability
    extern "C" {
#endif

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">
#include <xc.h>
#include <stdint.h>

        // </editor-fold> 
        
// <editor-fold defaultstate="collapsed" desc="DEFINITIONS/MACROS ">
// Oscillator frequency (Hz) - 200,000,000 Hz
#define FOSC                    200000000UL
// Oscillator frequency (MHz) - 200MHz
#define FOSC_MHZ                200U     
// Instruction cycle frequency (Hz) - 100,000,000 Hz
#define FCY                     100000000UL
// Instruction cycle frequency (MHz) - 100 MHz
#define FCY_MHZ                 100U  

// </editor-fold> 
        
// <editor-fold defaultstate="collapsed" desc="INTERFACE FUNCTIONS ">
void InitOscillator(void);
void EnableREFCLKOutput(uint16_t);        

// </editor-fold>  

#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif
#endif      // end of CLOCK_H


