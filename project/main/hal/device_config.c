// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file device_configuration.c
 *
 * @brief This file includes configuration fuse settings to configure device 
 * operation of Main and Secondary core 
 * 
 * Definitions in the file are for dsPIC33CH512MP508 MC DIM plugged onto 
 * Motor Control Development board from Microchip
 *
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
#include <stdint.h>
// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc=" Configuration Bit Settings ">

// 'C' source line config statements

// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Flash Page Address Limit bits (Enter Hexadecimal value)

// FSIGN

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Source Selection (Internal Fast RC (FRC))
#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE            // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config FCKSM = CSECMD           // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)
#pragma config PLLKEN = PLLKEN_ON       // PLL Lock Status Control (PLL lock signal will be used to disable PLL clock output if lock is lost)
#pragma config XTCFG = G0               // XT Config (4-8 MHz crystals)
#pragma config XTBST = DISABLE          // XT Boost (Default kick-start)

// FWDT
#pragma config RWDTPS = PS1048576       // Run Mode Watchdog Timer Post Scaler select bits (1:1048576)
#pragma config RCLKSEL = LPRC           // Watchdog Timer Clock Select bits (Always use LPRC)
#pragma config WINDIS = ON              // Watchdog Timer Window Enable bit (Watchdog Timer operates in Non-Window mode)
#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config SWDTPS = PS1048576       // Sleep Mode Watchdog Timer Post Scaler select bits (1:1048576)
#pragma config FWDTEN = ON_SW           // Watchdog Timer Enable bit (WDT controlled via SW, use WDTCON.ON bit)

// FPOR
#pragma config BISTDIS = DISABLED       // Memory BIST Feature Disable (mBIST on reset feature disabled)

// FICD
#pragma config ICS = PGD3               // ICD Communication Channel Select bits (Communicate on PGC3 and PGD3)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config NOBTSWP = OFF            // BOOTSWP instruction disable bit (BOOTSWP instruction is disabled)

// FDMTIVTL
#pragma config DMTIVTL = 0x0            // Dead Man Timer Interval low word (Enter Hexadecimal value)

// FDMTIVTH
#pragma config DMTIVTH = 0x0            // Dead Man Timer Interval high word (Enter Hexadecimal value)

// FDMTCNTL
#pragma config DMTCNTL = 0x0            // Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMTCNTH
#pragma config DMTCNTH = 0x0            // Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMT
#pragma config DMTDIS = OFF             // Dead Man Timer Disable bit (Dead Man Timer is Disabled and can be enabled by software)

// FDEVOPT
#pragma config ALTI2C1 = OFF            // Alternate I2C1 Pin bit (I2C1 mapped to SDA1/SCL1 pins)
#pragma config ALTI2C2 = OFF            // Alternate I2C2 Pin bit (I2C2 mapped to SDA2/SCL2 pins)
#pragma config SMBEN = SMBUS            // SM Bus Enable (SMBus input threshold is enabled)
#pragma config SPI2PIN = PPS            // SPI2 Pin Select bit (SPI2 uses I/O remap (PPS) pins)

// FALTREG
#pragma config CTXT1 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits (Not Assigned)
#pragma config CTXT2 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits (Not Assigned)
#pragma config CTXT3 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits (Not Assigned)
#pragma config CTXT4 = OFF              // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits (Not Assigned)

// FMBXM
#pragma config MBXM0 = S2M              // Mailbox 0 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM1 = S2M              // Mailbox 1 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM2 = S2M              // Mailbox 2 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM3 = S2M              // Mailbox 3 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM4 = S2M              // Mailbox 4 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM5 = S2M              // Mailbox 5 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM6 = S2M              // Mailbox 6 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM7 = S2M              // Mailbox 7 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM8 = S2M              // Mailbox 8 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM9 = S2M              // Mailbox 9 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM10 = S2M             // Mailbox 10 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM11 = S2M             // Mailbox 11 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM12 = S2M             // Mailbox 12 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM13 = S2M             // Mailbox 13 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM14 = S2M             // Mailbox 14 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))
#pragma config MBXM15 = S2M             // Mailbox 15 data direction (Mailbox register configured for Main data read (Secondary to Main data transfer))

// FMBXHS1
#pragma config MBXHSA = MBX15           // Mailbox handshake protocol block A register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block A)
#pragma config MBXHSB = MBX15           // Mailbox handshake protocol block B register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block B)
#pragma config MBXHSC = MBX15           // Mailbox handshake protocol block C register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block C)
#pragma config MBXHSD = MBX15           // Mailbox handshake protocol block D register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block D)

// FMBXHS2
#pragma config MBXHSE = MBX15           // Mailbox handshake protocol block E register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block E)
#pragma config MBXHSF = MBX15           // Mailbox handshake protocol block F register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block F)
#pragma config MBXHSG = MBX15           // Mailbox handshake protocol block G register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block G)
#pragma config MBXHSH = MBX15           // Mailbox handshake protocol block H register assignment (MSIxMBXD15 assigned to mailbox handshake protocol block H)

// FMBXHSEN
#pragma config HSAEN = OFF              // Mailbox A data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled.)
#pragma config HSBEN = OFF              // Mailbox B data flow control protocol block enable (Mailbox data flow control handshake protocol block disabled.)
#pragma config HSCEN = ON               // Mailbox C data flow control protocol block enable (Mailbox data flow control handshake protocol block enabled)
#pragma config HSDEN = ON               // Mailbox D data flow control protocol block enable (Mailbox data flow control handshake protocol block enabled)
#pragma config HSEEN = ON               // Mailbox E data flow control protocol block enable (Mailbox data flow control handshake protocol block enabled)
#pragma config HSFEN = ON               // Mailbox F data flow control protocol block enable (Mailbox data flow control handshake protocol block enabled)
#pragma config HSGEN = ON               // Mailbox G data flow control protocol block enable (Mailbox data flow control handshake protocol block enabled)
#pragma config HSHEN = ON               // Mailbox H data flow control protocol block enable (Mailbox data flow control handshake protocol block enabled)

// FCFGPRA0
#pragma config CPRA0 = MAIN             // Pin RA0 Ownership Bits (Main core owns pin.)
#pragma config CPRA1 = SEC1             // Pin RA1 Ownership Bits (Secondary core owns pin.)
#pragma config CPRA2 = SEC1             // Pin RA2 Ownership Bits (Secondary core owns pin.)
#pragma config CPRA3 = SEC1             // Pin RA3 Ownership Bits (Secondary core owns pin.)
#pragma config CPRA4 = SEC1             // Pin RA4 Ownership Bits (Secondary core owns pin.)

// FCFGPRB0
#pragma config CPRB0 = SEC1             // Pin RB0 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB1 = SEC1             // Pin RB1 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB2 = SEC1             // Pin RB2 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB3 = SEC1             // Pin RB3 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB4 = SEC1             // Pin RB4 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB5 = SEC1             // Pin RB5 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB6 = SEC1             // Pin RB6 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB7 = SEC1             // Pin RB7 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB8 = SEC1             // Pin RB8 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB9 = MAIN             // Pin RB9 Ownership Bits (Main core owns pin.)
#pragma config CPRB10 = SEC1            // Pin RB10 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB11 = SEC1            // Pin RB11 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB12 = MAIN            // Pin RB12 Ownership Bits (Main core owns pin.)
#pragma config CPRB13 = MAIN            // Pin RB13 Ownership Bits (Main core owns pin.)
#pragma config CPRB14 = SEC1            // Pin RB14 Ownership Bits (Secondary core owns pin.)
#pragma config CPRB15 = SEC1            // Pin RB15 Ownership Bits (Secondary core owns pin.)

// FCFGPRC0
#pragma config CPRC0 = MAIN             // Pin RC0 Ownership Bits (Main core owns pin.)
#pragma config CPRC1 = SEC1             // Pin RC1 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC2 = SEC1             // Pin RC2 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC3 = SEC1             // Pin RC3 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC4 = SEC1             // Pin RC4 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC5 = SEC1             // Pin RC5 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC6 = SEC1             // Pin RC6 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC7 = SEC1             // Pin RC7 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC8 = SEC1             // Pin RC8 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC9 = SEC1             // Pin RC9 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC10 = SEC1            // Pin RC10 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC11 = SEC1            // Pin RC11 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC12 = MAIN            // Pin RC12 Ownership Bits (Main core owns pin.)
#pragma config CPRC13 = SEC1            // Pin RC13 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC14 = SEC1            // Pin RC14 Ownership Bits (Secondary core owns pin.)
#pragma config CPRC15 = SEC1            // Pin RC15 Ownership Bits (Secondary core owns pin.)

// FCFGPRD0
#pragma config CPRD0 = SEC1             // Pin RD0 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD1 = SEC1             // Pin RD1 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD2 = SEC1             // Pin RD2 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD3 = SEC1             // Pin RD3 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD4 = SEC1             // Pin RD4 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD5 = SEC1             // Pin RD5 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD6 = SEC1             // Pin RD6 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD7 = SEC1             // Pin RD7 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD8 = SEC1             // Pin RD8 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD9 = SEC1             // Pin RD9 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD10 = SEC1            // Pin RD10 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD11 = SEC1            // Pin RD11 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD12 = SEC1            // Pin RD12 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD13 = SEC1            // Pin RD13 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD14 = SEC1            // Pin RD14 Ownership Bits (Secondary core owns pin.)
#pragma config CPRD15 = SEC1            // Pin RD15 Ownership Bits (Secondary core owns pin.)

// FCFGPRE0
#pragma config CPRE0 = SEC1             // Pin RE0 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE1 = MAIN             // Pin RE1 Ownership Bits (Main core owns pin.)
#pragma config CPRE2 = SEC1             // Pin RE2 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE3 = SEC1             // Pin RE3 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE4 = SEC1             // Pin RE4 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE5 = SEC1             // Pin RE5 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE6 = SEC1             // Pin RE6 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE7 = SEC1             // Pin RE7 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE8 = SEC1             // Pin RE8 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE9 = SEC1             // Pin RE9 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE10 = SEC1            // Pin RE10 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE11 = SEC1            // Pin RE11 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE12 = SEC1            // Pin RE12 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE13 = SEC1            // Pin RE13 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE14 = SEC1            // Pin RE14 Ownership Bits (Secondary core owns pin.)
#pragma config CPRE15 = SEC1            // Pin RE15 Ownership Bits (Secondary core owns pin.)

// FS1OSCSEL
#pragma config S1FNOSC = FRC            // Oscillator Source Selection (Internal Fast RC (FRC))
#pragma config S1IESO = OFF             // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FS1OSC
#pragma config S1OSCIOFNC = ON          // Secondary OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config S1FCKSM = CSECMD         // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)
#pragma config S1PLLKEN = S1PLLKEN_ON   // S1PLLKEN (S1PLLKEN_ON)

// FS1WDT
#pragma config S1RWDTPS = PS1048576     // Run Mode Watchdog Timer Post Scaler select bits (1:1048576)
#pragma config S1RCLKSEL = LPRC         // Watchdog Timer Clock Select bits (Always use LPRC)
#pragma config S1WINDIS = OFF           // Watchdog Timer Window Enable bit (Watchdog Timer operates in Window mode)
#pragma config S1WDTWIN = WIN25         // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config S1SWDTPS = PS1048576     // Sleep Mode Watchdog Timer Post Scaler select bits (1:1048576)
#pragma config S1FWDTEN = ON_SW         // Watchdog Timer Enable bit (WDT controlled via WDTCON.ON bit)

// FS1POR
#pragma config S1BISTDIS = DISABLED     // Secondary BIST on reset disable bit (Secondary BIST on reset feature disabled)

// FS1ICD
#pragma config S1ICS = PGD1             // ICD Communication Channel Select bits (Communicate on PGC1 and PGD1)
#pragma config S1ISOLAT = ON            // Isolate the Secondary core subsystem from the Main subsystem during Debug (The Secondary can operate (in debug mode) even if the SLVEN bit in the MSI is zero.)
#pragma config S1NOBTSWP = OFF          // BOOTSWP Instruction Enable/Disable bit (BOOTSWP instruction is disabled)

// FS1DEVOPT
#pragma config S1ALTI2C1 = OFF          // Alternate I2C1 Pin bit (I2C1 mapped to SDA1/SCL1 pins)
#pragma config S1SPI1PIN = PPS          // S1 SPI1 Pin Select bit (Secondary SPI1 uses I/O remap (PPS) pins)
#pragma config S1SSRE = ON              // Secondary Secondary Reset Enable (Secondary generated resets will reset the Secondary Enable Bit in the MSI module)
#pragma config S1MSRE = ON              // Main Secondary Reset Enable (The Main software oriented RESET events (RESET Op-Code, Watchdog timeout, TRAP reset, illegalInstruction) will also cause the Secondary subsystem to reset.)

// FS1ALTREG
#pragma config S1CTXT1 = OFF            // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits (Not Assigned)
#pragma config S1CTXT2 = OFF            // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits (Not Assigned)
#pragma config S1CTXT3 = OFF            // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits (Not Assigned)
#pragma config S1CTXT4 = OFF            // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits (Not Assigned)

// FS1DMTIVTL
#pragma config S1DMTIVTL = 0xFFFF       // Secondary Dead Man Timer Interval low word (Enter Hexadecimal value)

// FS1DMTIVTH
#pragma config S1DMTIVTH = 0xFFFF       // Secondary Dead Man Timer Interval high word (Enter Hexadecimal value)

// FS1DMTCNTL
#pragma config S1DMTCNTL = 0xFFFF       // Secondary DMT instruction count time-out value low word (Enter Hexadecimal value)

// FS1DMTCNTH
#pragma config S1DMTCNTH = 0xFFFF       // Secondary DMT instruction count time-out value high word (Enter Hexadecimal value)

// FS1DMT
#pragma config S1DMTDIS = OFF           // Secondary Dead Man Timer Disable bit (Secondary Dead Man Timer is Disabled and can be enabled by software)

// FBTSEQ
#pragma config BSEQ = 0xFFF             // Relative value defining which partition will be active after devie Reset; the partition containing a lower boot number will be active. (Enter Hexadecimal value)
#pragma config IBSEQ = 0xFFF            // The one's complement of BSEQ; must be calculated by the user and written during device programming. (Enter Hexadecimal value)

// </editor-fold> 