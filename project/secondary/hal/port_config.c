// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file port_config.c
 *
 * @brief This module initializes the GPIO pins as analog/digital,input or 
 * output etc. 
 * 
 * Definitions in the file are for dsPIC33CH512MP508 MC DIM plugged onto 
 * Motor Control Development board from Microchip
 *
 * Component: PORTS
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

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">
#include <xc.h>
#include "port_config.h"

// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc="INTERFACE FUNCTIONS ">
/**
 * <B> Function: SetupGPIOPorts()  </B>
 * @brief Function initializes GPIO pins for input or output ports,
 *        analog/digital pins,remap the peripheral functions to desires RPx pins.
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = SetupGPIOPorts();
 * </code>
 */

void SetupGPIOPorts(void)
{
    // Reset all PORTx register (all inputs)
    #ifdef TRISA
        TRISA = 0xFFFF;
        LATA  = 0x0000;
    #endif
    #ifdef ANSELA
        ANSELA = 0x0000;
    #endif

    #ifdef TRISB
        TRISB = 0xFFFF;
        LATB  = 0x0000;
    #endif
    #ifdef ANSELB
        ANSELB = 0x0000;
    #endif

    #ifdef TRISC
        TRISC = 0xFFFF;
        LATC  = 0x0000;
    #endif
    #ifdef ANSELC
        ANSELC = 0x0000;
    #endif

    #ifdef TRISD
        TRISD = 0xFFFF;
        LATD  = 0x0000;
    #endif
    #ifdef ANSELD
        ANSELD = 0x0000;
    #endif

    #ifdef TRISE
        TRISE = 0xFFFF;
        LATE  = 0x0000;
    #endif
    #ifdef ANSELE
        ANSELE = 0x0000;
    #endif

    MapGPIOHWFunction();

    return;
}

/**
 * <B> Function: Map_GPIO_HW_Function()  </B>
 * @brief Routine to setup GPIO pin used as input/output analog/digital etc
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = MapGPIOHWFunction();
 * </code>
 */

void MapGPIOHWFunction(void)
{
    
    /* ANALOG SIGNALS */

    /* Configure MC1 analog ports */
    // IA_EXT(S1AN0) : DIM #19
    ANSELAbits.ANSELA3 = 1;
    TRISAbits.TRISA3 = 1;    // PIN21 : S1AN0/S1CMP1A/S1PGA1P1/S1RA3

    // IB_EXT(S1AN1) : DIM #27
    ANSELAbits.ANSELA4 = 1;
    TRISAbits.TRISA4 = 1;    // PIN23: S1MCLR3/S1AN1/S1CMP2A/S1PGA2P1/S1PGA3P2/S1RA4
    
    //IBUS_EXT(S1AN13):DIM #35
    ANSELDbits.ANSELD10 = 1;
    TRISDbits.TRISD10 = 1;   //PIN38:S1AN13/S1CMP2B/S1RD10

    // Potentiometer #1 input - used as Speed Reference
    // POT1 : DIM #28
    TRISAbits.TRISA1 = 1;          // PIN18: S1AN15/S1RA1
    ANSELAbits.ANSELA1 = 1;  
    
    /* Configure MC2 analog ports */
    //DIM:096	XPRO1_SPI_SS_B	M2_IA_EXT
    ANSELCbits.ANSELC2 = 1;
    TRISCbits.TRISC2 = 1;    // PIN29 : S1ANA0/S1RP50/S1RC2

    //DIM:098	XPRO1_I2C_SDA	M2_IB_EXT
    ANSELCbits.ANSELC1 = 1;
    TRISCbits.TRISC1 = 1;    // PIN28: S1ANA1/S1RP49/S1RC1
	
    //DIM:094	XPRO1_IRQ	M2_IBUS_EXT
    ANSELBbits.ANSELB3 = 1;
    TRISBbits.TRISB3 = 1;   //S1PGD2/S1AN18/S1CMP3A/S1PGA3P1/S1RP35/S1RB3
    
    /*DC Bus Voltage Signals*/
    // Vbus : DIM #039
    TRISCbits.TRISC0 = 1;          // PIN15: S1AN10/S1RP48/S1RC0
    ANSELCbits.ANSELC0 = 1;
    
    /* Digital SIGNALS */   
    // DIGITAL INPUT/OUTPUT PINS

    // MC1 PWM Outputs
    // PWM1H : DIM #01  RP58/RC10 S1RP58/S1PWM1H/S1RC10
    // PWM1L : DIM #03  RP59/RC11/S1RP59/S1PWM1L/S1RC11
    // PWM2H : DIM #05  RP52/RC4 S1RP52/S1PWM2H/S1RC4
    // PWM2L : DIM #07  RP53/RC5 S1RP53/S1PWM2L/S1RC5
    // PWM3H : DIM #02  RP68/RD4 S1RP68/S1PWM3H/S1RD4
    // PWM3L : DIM #04  RP67/RD3 S1RP67/S1PWM3L/S1RD3
    TRISCbits.TRISC10 = 0 ;          
    TRISCbits.TRISC11 = 0 ;         
    TRISCbits.TRISC4 = 0 ;          
    TRISCbits.TRISC5 = 0 ;           
    TRISDbits.TRISD4 = 0 ;          
    TRISDbits.TRISD3 = 0 ; 
    
    /* MC2 PWM Outputs */
    // PWM6H : DIM:089  S1RP70/S1PWM6H/S1RD6
    // PWM6L : DIM:090  S1RP69/S1PWM6L/S1RD5
    // PWM7H : DIM:102  S1RP62/S1PWM7H/S1RC14
    // PWM7L : DIM:104  S1RP63/S1PWM7L/S1RC15
    // PWM8H : DIM:091  S1RP71/S1PWM8H/S1RD7
    // PWM8L : DIM:092  S1RP66/S1PWM8L/S1RD2
    TRISDbits.TRISD6 = 0 ;          
    TRISDbits.TRISD5 = 0 ;         
    TRISCbits.TRISC14 = 0 ;          
    TRISCbits.TRISC15 = 0 ;           
    TRISDbits.TRISD7 = 0 ;          
    TRISDbits.TRISD2 = 0 ;
    /* PWM for synchronization 
       PWM5H : DIM:081 S1MCLR1/S1AN6/S1RP39/S1PWM5H/S1RB7 */
    TRISBbits.TRISB7 = 0;
    
    //EVENTA
    TRISBbits.TRISB11 = 0; //event B11
    _RP43R = 36; //EVENTA
    
    // FAULT Pins
    // FAULT : DIM #40
    TRISDbits.TRISD15 = 1;         // PIN:10  S1PCI22/S1RD15

    // Debug LEDs
    // LED1 : DIM #30
    TRISEbits.TRISE2 = 0;          // PIN:17 - RE2 S1RE2
    // LED2 : DIM #32
    TRISEbits.TRISE3 = 0;          // PIN:19 - RE3 S1RE3

    // Push button Switches
    // SW1 : DIM #34
    TRISEbits.TRISE4 = 1;            // PIN:22 RE4 S1RE4
    // SW2 : DIM #36
    TRISEbits.TRISE5 = 1;            // PIN:24 RE5 S1RE5  
//    //Configuring RP76 as PCI9 input for M1_FAULT_IPM
//	_PCI9R = 76; //CHANGE
	
	/** Diagnostic Interface for MCLV-2,MCHV-2/3,LVMCDB etc.
        Re-map UART Channels to the device pins connected to the following 
        PIM pins on the Motor Control Development Boards .
        UART_RX : DIM #54 (Input)  RP47/PWM1L/RB15
        UART_TX : DIM #52 (Output) RP46/PWM1H/RB14  */
    _U1RXR = 47;
    _RP46R = 0b000001;
    
}
// </editor-fold> 
