// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file pwm.c
 *
 * @brief This module configures and enables the PWM Module of SecondaryController
 * 
 * Definitions in the file are for dsPIC33CH512MP508 MC DIM plugged onto 
 * Motor Control Development board from Microchip
 *
 * Component: PWM - Secondary Core
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
#include "pwm.h"

// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc="Function Declarations">
void InitPWMGenerator1 (void);
void InitPWMGenerator2 (void);
void InitPWMGenerator3 (void);
void InitPWMGenerator5 (void);
void InitPWMGenerator6 (void);
void InitPWMGenerator7 (void);
void InitPWMGenerator8 (void);

void InitDutyPWM123Generators(void);
void InitDutyPWM678Generators(void);
   
void ChargeBootstarpCapacitorsMC1(void);
void ChargeBootstarpCapacitorsMC2(void);
void InitPWMGenerators(void);

// </editor-fold>
  
// <editor-fold defaultstate="expanded" desc="INTERFACE FUNCTIONS ">
/**
* <B> Function: void InitPWMGenerators(void)  </B>
*
* @brief InitPWMGenerators() function,initializes  and enable the PWM Module 
 * after configuration.
 * @param None.
 * @return None.
 * @example
 * <code>
 * InitPWMGenerators();
 * </code>
*/
void InitPWMGenerators(void)
{

    PCLKCON      = 0x0000;
    /* PWM Clock Divider Selection bits
       0b11 = 1:16 ; 0b10 = 1:8 ;0b01 = 1:4 ; 0b00 = 1:2*/
    PCLKCONbits.DIVSEL = 0;
    /* PWM Master Clock Selection bits
       0b11 = AFPLLO ; 0b10 = FPLLO ; 0b01 = AFVCO/2 ; 0b00 = FOSC */
    PCLKCONbits.MCLKSEL = 0;
    /* Lock bit: 0 = Write-protected registers and bits are unlocked   */
    PCLKCONbits.LOCK = 0;

    /* Initialize Master Phase Register */
    MPHASE       = 0x0000;
    /* Initialize Master Duty Cycle */
    MDC          = 0x0000;
    /* Initialize Master Period Register */
    MPER         = LOOPTIME_TCY;
    
    /* Initialize FREQUENCY SCALE REGISTER*/
    FSCL          = 0x0000;
    /* Initialize FREQUENCY SCALING MINIMUM PERIOD REGISTER */
    FSMINPER     = 0x0000;
    /* Initialize Linear Feedback Shift Register */
    LFSR         = 0x0000;
    /* Initialize Combinational Trigger Register Low */
    CMBTRIGL     = 0x0000;
    /* Initialize Combinational Trigger Register High */
    CMBTRIGH     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER A */
    LOGCONA     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER B*/
    LOGCONB     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER C */
    LOGCONC     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER D */
    LOGCOND     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER E*/
    LOGCONE     = 0x0000;
    /* Initialize LOGIC CONTROL REGISTER F */
    LOGCONF     = 0x0000;
    /* Initialize EVENT CONTROL REGISTER A */
    PWMEVTA     = 0x0000;    
    /* Initialize EVENT CONTROL REGISTER B */
    PWMEVTB     = 0x0000;
    /* Initialize EVENT CONTROL REGISTER C */
    PWMEVTC     = 0x0000;
    /* Initialize EVENT CONTROL REGISTER D */
    PWMEVTD     = 0x0000;
    /* Initialize EVENT CONTROL REGISTER E */
    PWMEVTE     = 0x0000;
    /* Initialize EVENT CONTROL REGISTER F */
    PWMEVTF     = 0x0000;
 
    /* PWM Event Output Enable bit  
       1 = Event output signal is output on PWMEy pin
       0 = Event output signal is internal only */
    PWMEVTAbits.EVTAOEN  = 1;
    /* EVTyPOL: PWM Event Output Polarity bit
       1 = Event output signal is active-low
       0 = Event output signal is active-high */
    PWMEVTAbits.EVTAPOL  = 0;
    /* EVTySTRD: PWM Event Output Stretch Disable bit
       1 = Event output signal pulse width is not stretched
       0 = Event output signal is stretched to eight PWM clock cycles minimum */
    PWMEVTAbits.EVTASTRD = 1; 
    /* EVTySYNC: PWM Event Output Sync bit
       1 = Event output signal is synchronized to the system clock
       0 = Event output is not synchronized to the system clock
       Event output signal pulse will be two system clocks when this bit is set and EVTySTRD = 1 */
    PWMEVTAbits.EVTASYNC = 1;
    /* EVTySEL[3:0]: PWM Event Selection bits
       1111-1010 = Reserved
       1001 = ADC Trigger 2 signal
       1000 = ADC Trigger 1 signal
       0111 = STEER signal (available in Push-Pull Output modes only)(4)
       0110 = CAHALF signal (available in Center-Aligned modes only)(4)
       0101 = PCI Fault active output signal
       0100 = PCI Current limit active output signal
       0011 = PCI Feed-forward active output signal
       0010 = PCI Sync active output signal
       0001 = PWM Generator output signal(3)
       0000 = Source is selected by the PGTRGSEL[2:0] bits */
    PWMEVTAbits.EVTASEL  = 0b0001;
    /* EVTyPGS[2:0]: PWM Event Source Selection bits
       111-100 = Reserved
       011 = PWM Generator 4
       ...
       000 = PWM Generator 1 */
    PWMEVTAbits.EVTAPGS  = 6;

    /* Initialize PWM generators */
    InitPWMGenerator5 ();    
        
    InitPWMGenerator1 ();
    InitPWMGenerator2 ();
    InitPWMGenerator3 (); 
    
    InitPWMGenerator6 ();
    InitPWMGenerator7 ();
    InitPWMGenerator8 ();
    
    InitDutyPWM123Generators();
    InitDutyPWM678Generators();

    IFS4bits.PWM1IF = 0;
    IEC4bits.PWM1IE = 1;
    IPC16bits.PWM1IP = 7;
    
	PG1CONLbits.ON = 1;      // Enable PWM module 1 after initializing generators
    PG2CONLbits.ON = 1;      // Enable PWM module 2 after initializing generators
    PG3CONLbits.ON = 1;      // Enable PWM module 3 after initializing generators
    
    PG6CONLbits.ON = 1;      // Enable PWM module 6 after initializing generators
    PG7CONLbits.ON = 1;      // Enable PWM module 7 after initializing generators
    PG8CONLbits.ON = 1;      // Enable PWM module 8 after initializing generators

    PG5CONLbits.ON = 1;      // Enable PWM module 5 after initializing generators
    
    /* Bootstrap capacitors charging routine */
    ChargeBootstarpCapacitorsMC1();
    ChargeBootstarpCapacitorsMC2();
}

/**
 * <B> Function: InitDutyPWM123Generators()  </B>
 * @brief Routine to initialize Duty cycle of PWM generators 1,2,3
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = InitDutyPWM123Generators();
 * </code>
 */
void InitDutyPWM123Generators(void)
{
    /* Enable PWMs only on PWMxL ,to charge bootstrap capacitors initially. 
    Hence PWMxH is over-ridden to "LOW" */
    PG3IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM3H,L, if Override is Enabled
    PG2IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM2H,L, if Override is Enabled
    PG1IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM1H,L, if Override is Enabled

    PG3IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM3H
    PG2IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM2H
    PG1IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM1H

    PG3IOCONLbits.OVRENL = 1;  // 0 = PWM generator provides data for PWM3L pin
    PG2IOCONLbits.OVRENL = 1;  // 0 = PWM generator provides data for PWM2L pin
    PG1IOCONLbits.OVRENL = 1;  // 0 = PWM generator provides data for PWM1L pin

    /* Set PWM Duty Cycles */
    PG3DC = 0;
    PG2DC = 0;      
    PG1DC = 0;
}

/**
 * <B> Function: InitDutyPWM678Generators()  </B>
 * @brief Routine to initialize Duty cycle of PWM generators 6,7,8
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = InitDutyPWM678Generators();
 * </code>
 */
void InitDutyPWM678Generators(void)
{
    /* Enable PWMs only on PWMxL ,to charge bootstrap capacitors initially. 
    Hence PWMxH is over-ridden to "LOW" */
    PG6IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM6H,L, if Override is Enabled
    PG7IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM7H,L, if Override is Enabled
    PG8IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM8H,L, if Override is Enabled

    PG6IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM6H
    PG7IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM7H
    PG8IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM8H

    PG6IOCONLbits.OVRENL = 1;  // 0 = PWM generator provides data for PWM6L pin
    PG7IOCONLbits.OVRENL = 1;  // 0 = PWM generator provides data for PWM7L pin
    PG8IOCONLbits.OVRENL = 1;  // 0 = PWM generator provides data for PWM8L pin

    /* Set PWM Duty Cycles */
    PG6DC = 0;
    PG7DC = 0;      
    PG8DC = 0;
}

/**
 * <B> Function: ChargeBootstarpCapacitorsMC1()  </B>
 * @brief Function to charge bootstrap capacitors of MC1 inverter at the beginning
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = ChargeBootstarpCapacitorsMC1();
 * </code>
 */
void ChargeBootstarpCapacitorsMC1(void)
{
    uint16_t i = BOOTSTRAP_CHARGING_COUNTS;
    uint16_t prevStatusCAHALF = 0,currStatusCAHALF = 0;
    uint16_t k = 0;
    
    // Enable PWMs only on PWMxL ,to charge bootstrap capacitors at the beginning
    // Hence PWMxH is over-ridden to "LOW"
    PG3IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM3H,L, if Override is Enabled
    PG2IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM2H,L, if Override is Enabled
    PG1IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM1H,L, if Override is Enabled

    PG3IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM3H
    PG2IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM2H
    PG1IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM1H

    PG3IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM3L
    PG2IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM2L
    PG1IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM1L
    
    // PDCx: PWMx GENERATOR DUTY CYCLE REGISTER
    // Initialize the PWM duty cycle for charging
    MC1_PWM_PDC3 = LOOPTIME_TCY - (DDEADTIME/2 + 5);
    MC1_PWM_PDC2 = LOOPTIME_TCY - (DDEADTIME/2 + 5);
    MC1_PWM_PDC1 = LOOPTIME_TCY - (DDEADTIME/2 + 5);
    
    while(i)
    {
        prevStatusCAHALF = currStatusCAHALF;
        currStatusCAHALF = PG1STATbits.CAHALF;
        if(prevStatusCAHALF != currStatusCAHALF)
        {
            if(currStatusCAHALF == 0)
            {
                i--; 
                k++;
                if(i == (BOOTSTRAP_CHARGING_COUNTS - 50))
                {
                    // 0 = PWM generator provides data for PWM1L pin
                    PG1IOCONLbits.OVRENL = 0;
                }
                else if(i == (BOOTSTRAP_CHARGING_COUNTS - 150))
                {
                    // 0 = PWM generator provides data for PWM2L pin
                    PG2IOCONLbits.OVRENL = 0;  
                }
                else if(i == (BOOTSTRAP_CHARGING_COUNTS - 250))
                {
                    // 0 = PWM generator provides data for PWM3L pin
                    PG3IOCONLbits.OVRENL = 0;  
                }
                if(k > 25)
                {
                    if(PG3IOCONLbits.OVRENL == 0)
                    {
                        if(MC1_PWM_PDC3 > 2)
                        {
                            MC1_PWM_PDC3 -= 2;
                        }
                        else
                        {
                           MC1_PWM_PDC3 = 0; 
                        }
                    }
                    if(PG2IOCONLbits.OVRENL == 0)
                    {
                        if(MC1_PWM_PDC2 > 2)
                        {
                            MC1_PWM_PDC2 -= 2;
                        }
                        else
                        {
                            MC1_PWM_PDC2 = 0; 
                        }
                    }
                    if(PG1IOCONLbits.OVRENL == 0)
                    {
                        if(MC1_PWM_PDC1 > 2)
                        {
                            MC1_PWM_PDC1 -= 2;
                        }
                        else
                        {
                            MC1_PWM_PDC1 = 0; 
                        }
                    }
                    k = 0;
                } 
            }
        }
    }

    // PDCx: PWMx GENERATOR DUTY CYCLE REGISTER
    // Initialize the PWM duty cycle for charging
    MC1_PWM_PDC3 = 0;
    MC1_PWM_PDC2 = 0;
    MC1_PWM_PDC1 = 0;

    PG3IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM3H pin
    PG2IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM2H pin
    PG1IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM1H pin
}

/**
 * <B> Function: ChargeBootstarpCapacitorsMC2()  </B>
 * @brief Function to charge bootstrap capacitors of MC2 inverter at the beginning
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = ChargeBootstarpCapacitorsMC2();
 * </code>
 */
void ChargeBootstarpCapacitorsMC2(void)
{
    uint16_t i = BOOTSTRAP_CHARGING_COUNTS;
    uint16_t prevStatusCAHALF = 0,currStatusCAHALF = 0;
    uint16_t k = 0;
    
    // Enable PWMs only on PWMxL ,to charge bootstrap capacitors at the beginning
    // Hence PWMxH is over-ridden to "LOW"
    PG8IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM8H,L, if Override is Enabled
    PG7IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM7H,L, if Override is Enabled
    PG6IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM6H,L, if Override is Enabled

    PG8IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM8H
    PG7IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM7H
    PG6IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM6H

    PG8IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM8L
    PG7IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM7L
    PG6IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM6L

    // PDCx: PWMx GENERATOR DUTY CYCLE REGISTER
    // Initialize the PWM duty cycle for charging
    PG8DC = LOOPTIME_TCY - (DDEADTIME/2 + 5);
    PG7DC = LOOPTIME_TCY - (DDEADTIME/2 + 5);
    PG6DC = LOOPTIME_TCY - (DDEADTIME/2 + 5);
    
    while(i)
    {
        prevStatusCAHALF = currStatusCAHALF;
        currStatusCAHALF = PG6STATbits.CAHALF;
        if(prevStatusCAHALF != currStatusCAHALF)
        {
            if(currStatusCAHALF == 0)
            {
                i--; 
                k++;
                if(i == (BOOTSTRAP_CHARGING_COUNTS - 50))
                {
                    // 0 = PWM generator provides data for PWM6L pin
                    PG6IOCONLbits.OVRENL = 0;
                }
                else if(i == (BOOTSTRAP_CHARGING_COUNTS - 150))
                {
                    // 0 = PWM generator provides data for PWM7L pin
                    PG7IOCONLbits.OVRENL = 0;  
                }
                else if(i == (BOOTSTRAP_CHARGING_COUNTS - 250))
                {
                    // 0 = PWM generator provides data for PWM8L pin
                    PG8IOCONLbits.OVRENL = 0;  
                }
                if(k > 25)
                {
                    if(PG8IOCONLbits.OVRENL == 0)
                    {
                        if(MC2_PWM_PDC3 > 2)
                        {
                            MC2_PWM_PDC3 -= 2;
                        }
                        else
                        {
                           MC2_PWM_PDC3 = 0; 
                        }
                    }
                    if(PG7IOCONLbits.OVRENL == 0)
                    {
                        if(MC2_PWM_PDC2 > 2)
                        {
                            MC2_PWM_PDC2 -= 2;
                        }
                        else
                        {
                            MC2_PWM_PDC2 = 0; 
                        }
                    }
                    if(PG6IOCONLbits.OVRENL == 0)
                    {
                        if(MC2_PWM_PDC1 > 2)
                        {
                            MC2_PWM_PDC1 -= 2;
                        }
                        else
                        {
                            MC2_PWM_PDC1 = 0; 
                        }
                    }
                    k = 0;
                } 
            }
        }
    }

    // PDCx: PWMx GENERATOR DUTY CYCLE REGISTER
    // Initialize the PWM duty cycle for charging
    MC2_PWM_PDC3 = 2000;
    MC2_PWM_PDC2 = 2000;
    MC2_PWM_PDC1 = 2000;

    PG8IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM8H pin
    PG7IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM7H pin
    PG6IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM6H pin
}

/**
* <B> Function: void InitPWMGenerator1(void)  </B>
*
*  @brief Function to configure PWM Module # 1 
 * @param None.
 * @return None.
 * @example
 * <code>
 * InitPWMGenerator1();
 * </code>
*/
void InitPWMGenerator1 (void)
{

    /* Initialize PWM GENERATOR 1 CONTROL REGISTER LOW */
    PG1CONL      = 0x0000;
    /* PWM Generator 1 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* Ensuring PWM Generator is disabled prior to configuring module */
    PG1CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG1CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
    PG1CONLbits.MODSEL = 4;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG1CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 1 CONTROL REGISTER HIGH */
    PG1CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG1DC
       0 = Macro uses the PG1DC register*/
    PG1CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG1PER
       0 = Macro uses the PG1PER register */
    PG1CONHbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG1PHASE
       0 = Macro uses the PG1PHASE register */
    PG1CONHbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG1CONHbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       0b000 = SOC update
       0b010 = Slaved SOC Update Data registers at start of next cycle if a 
       master update request is received. A master update request will be 
       transmitted if MSTEN = 1 and UPDATE = 1 for the requesting PWM
       Generator. */
    PG1CONHbits.UPDMOD = 0b010;
    /* PWM Generator Trigger Mode Selection bits
       1 = PWM Generator operates in Retriggerable mode
       0 = PWM Generator operates in Single Trigger mode   */
    PG1CONHbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC
       0001 = PWM1(5) PG1 or PG5 trigger output selected by PGTRGSEL (PGxEVTL)
       1111 = TRIG bit or PCI Sync function only (no hardware 
              trigger source is selected) */
    PG1CONHbits.SOCS = 0xF;
    
    /* Clear PWM GENERATOR 1 STATUS REGISTER*/
    PG1STAT      = 0x0000;
    /* Initialize PWM GENERATOR 1 I/O CONTROL REGISTER LOW */
    PG1IOCONL    = 0x0000;
    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG1IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM1H and PWM1L Device Pins bit 
       0 = PWM1H/L signals are mapped to their respective pins */
    PG1IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM1H Pin bit
       0 = PWM Generator provides data for the PWM1H pin*/
    PG1IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM1L Pin bit
       0 = PWM Generator provides data for the PWM1L pin*/
    PG1IOCONLbits.OVRENL = 0;
    /* Data for PWM1H/PWM1L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM1H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM1L */
    PG1IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       10 = User output overrides, via the OVRENH/L and OVRDAT bits, occur when 
            specified by the UPDMOD[2:0] bits in the PGxCONH register
       01 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, occur 
            immediately (as soon as possible)
       00 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, are 
            synchronized to the local PWM time base (next Start-of-Cycle) */
    PG1IOCONLbits.OSYNC = 2;
    /* Data for PWM1H/PWM1L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM1H.
       If Fault is active, then FLTDAT<0> provides data for PWM1L.*/
    PG1IOCONLbits.FLTDAT = 0;
    /* Data for PWM1H/PWM1L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM1H.
       If current limit is active, then CLDAT<0> provides data for PWM1L.*/
    PG1IOCONLbits.CLDAT = 0;
    /* Data for PWM1H/PWM1L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM1H.
       If feed-forward is active, then FFDAT<0> provides data for PWM1L.*/
    PG1IOCONLbits.FFDAT = 0;
    /* Data for PWM1H/PWM1L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM1H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM1L data. */
    PG1IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 1 I/O CONTROL REGISTER HIGH */    
    PG1IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG1IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG1IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG1IOCONHbits.PMOD = 0;
    /* PWM1H Output Port Enable bit
       1 = PWM Generator controls the PWM1H output pin
       0 = PWM Generator does not control the PWM1H output pin */
    PG1IOCONHbits.PENH = 1;
    /* PWM1L Output Port Enable bit
       1 = PWM Generator controls the PWM1L output pin
       0 = PWM Generator does not control the PWM1L output pin */
    PG1IOCONHbits.PENL = 1;
    /* PWM1H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG1IOCONHbits.POLH = 0;
    /* PWM1L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG1IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 1 EVENT REGISTER LOW*/
    PG1EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG1EVTLbits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG1TRIGC Compare Event Enable bit
       0 = PG1TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG1EVTLbits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG1TRIGB Compare Event Enable bit
       0 = PG1TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG1EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG1TRIGA Compare Event Enable bit
       1 = PG1TRIGA register compare event is enabled as trigger source for 
           ADC Trigger 1 */
    PG1EVTLbits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the PG1DC register automatically sets the UPDATE bit
       00 = User must set the UPDATE bit manually */
    PG1EVTLbits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG1EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 1 EVENT REGISTER HIGH */
    PG1EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled 
       1 = Fault interrupt is enabled*/
    PG1EVTHbits.FLTIEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG1EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG1EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG1EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG1EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 2 Source is PG1TRIGC Compare Event Enable bit
       0 = PG1TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG1EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG1TRIGB Compare Event Enable bit
       0 = PG1TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG1EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG1TRIGA Compare Event Enable bit
       0 = PG1TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG1EVTHbits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG1EVTHbits.ADTR1OFS = 0;
    
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG1FPCIL     = 0x0000;
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG1FPCIH     = 0x0000;
#else
       /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG1FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG1FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG1FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG1FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG1FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG1FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 0 = Not inverted 1 = Inverted */
    PG1FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG1FPCILbits.PSS = 28;
    
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG1FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG1FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG1FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG1FPCIHbits.ACP   = 3;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG1FPCIHbits.PCIGT  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG1FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced to ?1?b1?)(3)*/
    PG1FPCIHbits.TQSS  = 0;
#endif    

    /* PWM GENERATOR 1 Current Limit PCI REGISTER LOW */
    PG1CLPCIL    = 0x0000;
    /* PWM GENERATOR 1 Current Limit PCI REGISTER HIGH */
    PG1CLPCIH    = 0x0000;
    /* PWM GENERATOR 1 Feed Forward PCI REGISTER LOW */
    PG1FFPCIL    = 0x0000;
    /* PWM GENERATOR 1 Feed Forward  PCI REGISTER HIGH */
    PG1FFPCIH    = 0x0000;
    
    /* PWM GENERATOR 1 Sync PCI REGISTER LOW */
    PG1SPCIL     = 0x0000;  
    PG1SPCILbits.PPS = 0;
    PG1SPCILbits.PSS = 1;
    
    /* PWM GENERATOR 1 Sync PCI REGISTER HIGH */
    PG1SPCIH     = 0x0000;
    PG1SPCIHbits.ACP = 0;
    
    /* Initialize PWM GENERATOR 1 LEADING-EDGE BLANKING REGISTER LOW */
    PG1LEBL      = 0x0000;
   
    /* Initialize PWM GENERATOR 1 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG1LEBH      = 0x0000;
    PG1LEBHbits.PWMPCI = 4;
    
    /* Initialize PWM GENERATOR 1 PHASE REGISTER */
    PG1PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 1 DUTY CYCLE REGISTER */
    PG1DC        = MIN_DUTY;
    /* Initialize PWM GENERATOR 1 DUTY CYCLE ADJUSTMENT REGISTER */
    PG1DCA       = 0x0000;
    /* Initialize PWM GENERATOR 1 PERIOD REGISTER */
    PG1PER       = 0x0000;
    /* Initialize PWM GENERATOR 1 DEAD-TIME REGISTER LOW */
    PG1DTL       = DDEADTIME;
    /* Initialize PWM GENERATOR 1 DEAD-TIME REGISTER HIGH */
    PG1DTH       = DDEADTIME;

    /* Initialize PWM GENERATOR 1 TRIGGER A REGISTER */
    PG1TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 1 TRIGGER B REGISTER */
    PG1TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 1 TRIGGER C REGISTER */
    PG1TRIGC     = 0x0000;
   
}
    
/**
* <B> Function: void InitPWMGenerator2(void)  </B>
*
*  @brief Function to configure PWM Module # 2 
 * @param None.
 * @return None.
 * @example
 * <code>
 * InitPWMGenerator2();
 * </code>
*/
void InitPWMGenerator2 (void)
{
    /* Initialize PWM GENERATOR 2 CONTROL REGISTER LOW */
    PG2CONL      = 0x0000;
    /* PWM Generator 2 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* PWM Generator is disabled prior to configuring module */
    PG2CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG2CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
    PG2CONLbits.MODSEL = 4;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG2CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 2 CONTROL REGISTER HIGH */
    PG2CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG2DC
       0 = Macro uses the PG2DC register*/
    PG2CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG2PER
       0 = Macro uses the PG2PER register */
    PG2CONHbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG2PHASE
       0 = Macro uses the PG2PHASE register */
    PG2CONHbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG2CONHbits.MSTEN = 0;
     /* PWM Buffer Update Mode Selection bits 
       0b000 = SOC update
       0b010 = Slaved SOC Update Data registers at start of next cycle if a 
       master update request is received. A master update request will be 
       transmitted if MSTEN = 1 and UPDATE = 1 for the requesting PWM
       Generator. */
	PG2CONHbits.UPDMOD = 0b010;
    /* PWM Generator Trigger Mode Selection bits
       1 = PWM Generator operates in Retriggerable mode
       0 = PWM Generator operates in Single Trigger mode   */

    PG2CONHbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0001 = PWM1 trigger o/p selected by PG1 PGTRGSEL<2:0> bits(PGxEVT<2:0>)
       1111 = TRIG bit or PCI Sync function only (no hardware trigger source is selected)*/
    PG2CONHbits.SOCS = 0xF;
    
    /* Clear PWM GENERATOR 2 STATUS REGISTER*/
    PG2STAT      = 0x0000;
    /* Initialize PWM GENERATOR 2 I/O CONTROL REGISTER LOW */
    PG2IOCONL    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG2IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM2H and PWM2L Device Pins bit 
       0 = PWM2H/L signals are mapped to their respective pins */
    PG2IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM2H Pin bit
       0 = PWM Generator provides data for the PWM2H pin*/
    PG2IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM2L Pin bit
       0 = PWM Generator provides data for the PWM2L pin*/
    PG2IOCONLbits.OVRENL = 0;
    /* Data for PWM2H/PWM2L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM2H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM2L */
    PG2IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       10 = User output overrides, via the OVRENH/L and OVRDAT bits, occur when 
            specified by the UPDMOD[2:0] bits in the PGxCONH register
       01 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, occur 
            immediately (as soon as possible)
       00 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, are 
            synchronized to the local PWM time base (next Start-of-Cycle) */
    PG2IOCONLbits.OSYNC = 2;
    /* Data for PWM2H/PWM2L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM2H.
       If Fault is active, then FLTDAT<0> provides data for PWM2L.*/
    PG2IOCONLbits.FLTDAT = 0;
    /* Data for PWM2H/PWM2L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM2H.
       If current limit is active, then CLDAT<0> provides data for PWM2L.*/
    PG2IOCONLbits.CLDAT = 0;
    /* Data for PWM2H/PWM2L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM2H.
       If feed-forward is active, then FFDAT<0> provides data for PWM2L.*/
    PG2IOCONLbits.FFDAT = 0;
    /* Data for PWM2H/PWM2L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM2H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM2L data. */
    PG2IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 2 I/O CONTROL REGISTER HIGH */    
    PG2IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG2IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG2IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG2IOCONHbits.PMOD = 0;
    /* PWM2H Output Port Enable bit
       1 = PWM Generator controls the PWM2H output pin
       0 = PWM Generator does not control the PWM2H output pin */
    PG2IOCONHbits.PENH = 1;
    /* PWM2L Output Port Enable bit
       1 = PWM Generator controls the PWM2L output pin
       0 = PWM Generator does not control the PWM2L output pin */
    PG2IOCONHbits.PENL = 1;
    /* PWM2H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG2IOCONHbits.POLH = 0;
    /* PWM2L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG2IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 2 EVENT REGISTER LOW*/
    PG2EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG2EVTLbits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG2TRIGC Compare Event Enable bit
       0 = PG2TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG2EVTLbits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG2TRIGB Compare Event Enable bit
       0 = PG2TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG2EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG2TRIGA Compare Event Enable bit
       0 = PG2TRIGA register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG2EVTLbits.ADTR1EN1 = 0;
    /* Update Trigger Select bits
       01 = A write of the PG2DC register automatically sets the UPDATE bit
       00 = User must set the UPDATE bit manually*/
    PG2EVTLbits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG2EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 2 EVENT REGISTER HIGH */
    PG2EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled */
    PG2EVTHbits.FLTIEN = 0;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG2EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG2EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG2EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG2EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 2 Source is PG2TRIGC Compare Event Enable bit
       0 = PG2TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG2EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG2TRIGB Compare Event Enable bit
       0 = PG2TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG2EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG2TRIGA Compare Event Enable bit
       0 = PG2TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG2EVTHbits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG2EVTHbits.ADTR1OFS = 0;
    
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG2FPCIL     = 0x0000;
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG2FPCIH     = 0x0000;
#else
       /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG2FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG2FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG2FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG2FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG2FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG2FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 0 = Not inverted 1 = Inverted*/
    PG2FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG2FPCILbits.PSS = 28;
    
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG2FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG2FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG2FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG2FPCIHbits.ACP   = 3;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG2FPCIHbits.PCIGT  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG2FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced to ?1?b1?)(3)*/
    PG2FPCIHbits.TQSS  = 0;
#endif
    
    /* PWM GENERATOR 2 Current Limit PCI REGISTER LOW */
    PG2CLPCIL    = 0x0000;
    /* PWM GENERATOR 2 Current Limit PCI REGISTER HIGH */
    PG2CLPCIH    = 0x0000;
    /* PWM GENERATOR 2 Feed Forward PCI REGISTER LOW */
    PG2FFPCIL    = 0x0000;
    /* PWM GENERATOR 2 Feed Forward  PCI REGISTER HIGH */
    PG2FFPCIH    = 0x0000;
    
    /* PWM GENERATOR 2 Sync PCI REGISTER LOW */
    PG2SPCIL     = 0x0000; 
    PG2SPCILbits.PPS = 0;
    PG2SPCILbits.PSS = 1;
    
    /* PWM GENERATOR 2 Sync PCI REGISTER HIGH */
    PG2SPCIH     = 0x0000;
    PG2SPCIHbits.ACP = 0;
    
    /* Initialize PWM GENERATOR 2 LEADING-EDGE BLANKING REGISTER LOW */
    PG2LEBL      = 0x0000;
    
    /* Initialize PWM GENERATOR 2 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG2LEBH      = 0x0000;
    PG2LEBHbits.PWMPCI = 4;
    
    /* Initialize PWM GENERATOR 2 PHASE REGISTER */
    PG2PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 2 DUTY CYCLE REGISTER */
    PG2DC        = MIN_DUTY;
    /* Initialize PWM GENERATOR 2 DUTY CYCLE ADJUSTMENT REGISTER */
    PG2DCA       = 0x0000;
    /* Initialize PWM GENERATOR 2 PERIOD REGISTER */
    PG2PER       = 0x0000;
    /* Initialize PWM GENERATOR 2 DEAD-TIME REGISTER LOW */
    PG2DTL       = DDEADTIME;
    /* Initialize PWM GENERATOR 2 DEAD-TIME REGISTER HIGH */
    PG2DTH       = DDEADTIME;

    /* Initialize PWM GENERATOR 2 TRIGGER A REGISTER */
    PG2TRIGA     = 0x0000;
    /* Initialize PWM GENERATOR 2 TRIGGER B REGISTER */
    PG2TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 2 TRIGGER C REGISTER */
    PG2TRIGC     = 0x0000;
    
}
    
/**
* <B> Function: void InitPWMGenerator3(void)  </B>
*
*  @brief Function to configure PWM Module # 3 
 * @param None.
 * @return None.
 * @example
 * <code>
 * InitPWMGenerator3();
 * </code>
*/
void InitPWMGenerator3 (void)
{
    /* Initialize PWM GENERATOR 3 CONTROL REGISTER LOW */
    PG3CONL      = 0x0000;
    /* PWM Generator 3 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* PWM Generator is disabled prior to configuring module */
    PG3CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG3CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
    PG3CONLbits.MODSEL = 4;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG3CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 3 CONTROL REGISTER HIGH */
    PG3CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG3DC
       0 = Macro uses the PG3DC register*/
    PG3CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG3PER
       0 = Macro uses the PG3PER register */
    PG3CONHbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG3PHASE
       0 = Macro uses the PG3PHASE register */
    PG3CONHbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG3CONHbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       0b000 = SOC update
       0b010 = Slaved SOC Update Data registers at start of next cycle if a 
       master update request is received. A master update request will be 
       transmitted if MSTEN = 1 and UPDATE = 1 for the requesting PWM
       Generator.. */
	PG3CONHbits.UPDMOD = 0b010;
    /* PWM Generator Trigger Mode Selection bits
       1 = PWM Generator operates in Retriggerable mode
       0 = PWM Generator operates in Single Trigger mode   */
    PG3CONHbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0001 = PWM1 trigger o/p selected by PG1 PGTRGSEL<2:0> bits(PGxEVT<2:0>)
       1111 = TRIG bit or PCI Sync function only (no hardware trigger source is selected)*/
    PG3CONHbits.SOCS = 0xF;
    
    /* Clear PWM GENERATOR 3 STATUS REGISTER*/
    PG3STAT      = 0x0000;
    /* Initialize PWM GENERATOR 3 I/O CONTROL REGISTER LOW */
    PG3IOCONL    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG3IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM3H and PWM3L Device Pins bit 
       0 = PWM3H/L signals are mapped to their respective pins */
    PG3IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM3H Pin bit
       0 = PWM Generator provides data for the PWM3H pin*/
    PG3IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM3L Pin bit
       0 = PWM Generator provides data for the PWM3L pin*/
    PG3IOCONLbits.OVRENL = 0;
    /* Data for PWM3H/PWM3L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM3H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM3L */
    PG3IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       10 = User output overrides, via the OVRENH/L and OVRDAT bits, occur when 
            specified by the UPDMOD[2:0] bits in the PGxCONH register
       01 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, occur 
            immediately (as soon as possible)
       00 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, are 
            synchronized to the local PWM time base (next Start-of-Cycle) */

    PG3IOCONLbits.OSYNC = 2;
    /* Data for PWM3H/PWM3L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM3H.
       If Fault is active, then FLTDAT<0> provides data for PWM3L.*/
    PG3IOCONLbits.FLTDAT = 0;
    /* Data for PWM3H/PWM3L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM3H.
       If current limit is active, then CLDAT<0> provides data for PWM3L.*/
    PG3IOCONLbits.CLDAT = 0;
    /* Data for PWM3H/PWM3L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM3H.
       If feed-forward is active, then FFDAT<0> provides data for PWM3L.*/
    PG3IOCONLbits.FFDAT = 0;
    /* Data for PWM3H/PWM3L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM3H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM3L data. */
    PG3IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 3 I/O CONTROL REGISTER HIGH */    
    PG3IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG3IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG3IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG3IOCONHbits.PMOD = 0;
    /* PWM3H Output Port Enable bit
       1 = PWM Generator controls the PWM3H output pin
       0 = PWM Generator does not control the PWM3H output pin */
    PG3IOCONHbits.PENH = 1;
    /* PWM3L Output Port Enable bit
       1 = PWM Generator controls the PWM3L output pin
       0 = PWM Generator does not control the PWM3L output pin */
    PG3IOCONHbits.PENL = 1;
    /* PWM3H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG3IOCONHbits.POLH = 0;
    /* PWM3L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG3IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 3 EVENT REGISTER LOW*/
    PG3EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG3EVTLbits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG3TRIGC Compare Event Enable bit
       0 = PG3TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG3EVTLbits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG3TRIGB Compare Event Enable bit
       0 = PG3TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG3EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG3TRIGA Compare Event Enable bit
       0 = PG3TRIGA register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG3EVTLbits.ADTR1EN1 = 0;
    /* Update Trigger Select bits
       01 = A write of the PG3DC register automatically sets the UPDATE bit
       00 = User must set the UPDATE bit manually*/
    PG3EVTLbits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG3EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 3 EVENT REGISTER HIGH */
    PG3EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled */
    PG3EVTHbits.FLTIEN = 0;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG3EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG3EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG3EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG3EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 3 Source is PG3TRIGC Compare Event Enable bit
       0 = PG3TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG3EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG3TRIGB Compare Event Enable bit
       0 = PG3TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG3EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG3TRIGA Compare Event Enable bit
       0 = PG3TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG3EVTHbits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG3EVTHbits.ADTR1OFS = 0;
    
    /* PWM GENERATOR 3 Fault PCI REGISTER LOW */
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG3FPCIL     = 0x0000;
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG3FPCIH     = 0x0000;
#else
    /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG3FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG3FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG3FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 0 = Not inverted 1 = Inverted*/
    PG3FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG3FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG3FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 0 = Not inverted 1 = Inverted*/
    PG3FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG3FPCILbits.PSS = 28;
    
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG3FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG3FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG3FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG3FPCIHbits.ACP   = 3;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG3FPCIHbits.PCIGT  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG3FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced '1')*/
    PG3FPCIHbits.TQSS  = 0;
#endif
    
    /* PWM GENERATOR 3 Current Limit PCI REGISTER LOW */
    PG3CLPCIL    = 0x0000;
    /* PWM GENERATOR 3 Current Limit PCI REGISTER HIGH */
    PG3CLPCIH    = 0x0000;
    /* PWM GENERATOR 3 Feed Forward PCI REGISTER LOW */
    PG3FFPCIL    = 0x0000;
    /* PWM GENERATOR 3 Feed Forward  PCI REGISTER HIGH */
    PG3FFPCIH    = 0x0000;
    /* PWM GENERATOR 3 Sync PCI REGISTER LOW */
    PG3SPCIL     = 0x0000;
    PG3SPCILbits.PPS = 0;
    PG3SPCILbits.PSS = 1;
    
    /* PWM GENERATOR 3 Sync PCI REGISTER HIGH */
    PG3SPCIH     = 0x0000;
    PG1SPCIHbits.ACP = 0;
    
    /* Initialize PWM GENERATOR 3 LEADING-EDGE BLANKING REGISTER LOW */
    PG3LEBL      = 0x0000;
    /* Initialize PWM GENERATOR 3 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG3LEBH      = 0x0000;
    PG3LEBHbits.PWMPCI = 4;
    
    /* Initialize PWM GENERATOR 3 PHASE REGISTER */
    PG3PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 3 DUTY CYCLE REGISTER */
    PG3DC        = MIN_DUTY;
    /* Initialize PWM GENERATOR 3 DUTY CYCLE ADJUSTMENT REGISTER */
    PG3DCA       = 0x0000;
    /* Initialize PWM GENERATOR 3 PERIOD REGISTER */
    PG3PER       = 0x0000;
    /* Initialize PWM GENERATOR 3 DEAD-TIME REGISTER LOW */
    PG3DTL       = DDEADTIME;
    /* Initialize PWM GENERATOR 3 DEAD-TIME REGISTER HIGH */
    PG3DTH       = DDEADTIME;

    /* Initialize PWM GENERATOR 3 TRIGGER A REGISTER */
    PG3TRIGA     = 0x0000;
    /* Initialize PWM GENERATOR 3 TRIGGER B REGISTER */
    PG3TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 3 TRIGGER C REGISTER */
    PG3TRIGC     = 0x0000;
    
}


/**
* <B> Function: void InitPWMGenerator5(void)  </B>
*
*  @brief Function to configure PWM Module # 5 as synchronization source
 * @param None.
 * @return None.
 * @example
 * <code>
 * InitPWMGenerator5();
 * </code>
*/
void InitPWMGenerator5 (void)
{

    /* Initialize PWM GENERATOR 5 CONTROL REGISTER LOW */
    PG5CONL      = 0x0000;
    /* PWM Generator 5 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* PWM Generator is disabled prior to configuring module */
    PG5CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG5CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)
       000 = Independent Edge PWM mode    */
    PG5CONLbits.MODSEL = 0;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG5CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 5 CONTROL REGISTER HIGH */
    PG5CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG5DC
       0 = Macro uses the PG5DC register*/
    PG5CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG5PER
       0 = Macro uses the PG5PER register */
    PG5CONHbits.MPERSEL = 0;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG5PHASE
       0 = Macro uses the PG5PHASE register */
    PG5CONHbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG5CONHbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       000 = SOC update
        Data registers at start of next PWM cycle if UPDREQ = 1.*/
	PG5CONHbits.UPDMOD = 0b000;
    /* PWM Generator Trigger Mode Selection bits
       0b00 = PWM Generator operates in Single Trigger mode 
        1 = */
    PG5CONHbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC
       0100 = Trigger output selected by PG5 PGTRGSEL[2:0] bits (PGxEVTL[2:0])
       1111 = TRIG bit or PCI Sync function only (no hardware trigger source is selected)*/
    PG5CONHbits.SOCS = 0xF;
    
    /* Clear PWM GENERATOR 5 STATUS REGISTER*/
    PG5STAT      = 0x0000;
    /* Initialize PWM GENERATOR 5 I/O CONTROL REGISTER LOW */
    PG5IOCONL    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG5IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM5H and PWM5L Device Pins bit 
       0 = PWM5H/L signals are mapped to their respective pins */
    PG5IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM5H Pin bit
       0 = PWM Generator provides data for the PWM5H pin*/
    PG5IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM5L Pin bit
       0 = PWM Generator provides data for the PWM5L pin*/
    PG5IOCONLbits.OVRENL = 0;
    /* Data for PWM5H/PWM5L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM5H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM5L */
    PG5IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       00 = User output overrides via the OVRENL/H and OVRDAT<1:0> bits are 
       synchronized to the local PWM time base (next start of cycle)*/
    PG5IOCONLbits.OSYNC = 0;
    /* Data for PWM5H/PWM5L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM5H.
       If Fault is active, then FLTDAT<0> provides data for PWM5L.*/
    PG5IOCONLbits.FLTDAT = 0;
    /* Data for PWM5H/PWM5L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM5H.
       If current limit is active, then CLDAT<0> provides data for PWM5L.*/
    PG5IOCONLbits.CLDAT = 0;
    /* Data for PWM5H/PWM5L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM5H.
       If feed-forward is active, then FFDAT<0> provides data for PWM5L.*/
    PG5IOCONLbits.FFDAT = 0;
    /* Data for PWM5H/PWM5L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM5H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM5L data. */
    PG5IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 5 I/O CONTROL REGISTER HIGH */    
    PG5IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG5IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG5IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       01 = PWM Generator outputs operate in Independent mode
       00 = PWM Generator outputs operate in Complementary mode*/
    PG5IOCONHbits.PMOD = 1;
    /* PWM5H Output Port Enable bit
       1 = PWM Generator controls the PWM5H output pin
       0 = PWM Generator does not control the PWM5H output pin */
    PG5IOCONHbits.PENH = 1;
    /* PWM5L Output Port Enable bit
       1 = PWM Generator controls the PWM5L output pin
       0 = PWM Generator does not control the PWM5L output pin */
    PG5IOCONHbits.PENL = 0;
    /* PWM5H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG5IOCONHbits.POLH = 0;
    /* PWM5L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG5IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 5 EVENT REGISTER LOW*/
    PG5EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       0b0000 = 1:1 
       0b0011 = 1:4 */
    PG5EVTLbits.ADTR1PS = 0b0011;
    /* ADC Trigger 1 Source is PG5TRIGC Compare Event Enable bit
       0 = PG5TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG5EVTLbits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG5TRIGB Compare Event Enable bit
       0 = PG5TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG5EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG5TRIGA Compare Event Enable bit
       0 = PG5TRIGA register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG5EVTLbits.ADTR1EN1 = 0;
    /* Update Trigger Select bits
       01 = A write of the PG5DC register automatically sets the UPDATE bit
       00 = User must set the UPDATE bit manually*/
    PG5EVTLbits.UPDTRG = 0;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger
       011 = PGxTRIGC compare event is the PWM Generator trigger*/
    PG5EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 5 EVENT REGISTER HIGH */
    PG5EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled */
    PG5EVTHbits.FLTIEN = 0;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG5EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG5EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG5EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG5EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 2 Source is PG5TRIGC Compare Event Enable bit
       0 = PG5TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG5EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG5TRIGB Compare Event Enable bit
       0 = PG5TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG5EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG5TRIGA Compare Event Enable bit
       0 = PG5TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG5EVTHbits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG5EVTHbits.ADTR1OFS = 0;
    
    /* PWM GENERATOR 5 Fault PCI REGISTER LOW */
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 5 Fault PCI REGISTER LOW */
    PG5FPCIL     = 0x0000;
    /* PWM GENERATOR 5 Fault PCI REGISTER HIGH */
    PG5FPCIH     = 0x0000;
#else
       /* PWM GENERATOR 5 Fault PCI REGISTER LOW */
    PG5FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG5FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG5FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG5FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG5FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG5FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG5FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG5FPCILbits.PSS = 19;
    
    /* PWM GENERATOR 5 Fault PCI REGISTER HIGH */
    PG5FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG5FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG5FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG5FPCIHbits.ACP   = 0;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG5FPCIHbits.PCIGT  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG5FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced to ?1?b1?)(3)*/
    PG5FPCIHbits.TQSS  = 3;
#endif
    
    /* PWM GENERATOR 5 Current Limit PCI REGISTER LOW */
    PG5CLPCIL    = 0x0000;
    /* PWM GENERATOR 5 Current Limit PCI REGISTER HIGH */
    PG5CLPCIH    = 0x0000;
    /* PWM GENERATOR 5 Feed Forward PCI REGISTER LOW */
    PG5FFPCIL    = 0x0000;
    /* PWM GENERATOR 5 Feed Forward  PCI REGISTER HIGH */
    PG5FFPCIH    = 0x0000;
    
    /*Initialize PWM GENERATOR 5 Sync PCI REGISTER   */
    PG5SPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG5SPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG5SPCILbits.TERM = 0;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG5SPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG5SPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG5SPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG5SPCILbits.PPS = 0;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
     * 0b10111 = Master PWM Event C
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG5SPCILbits.PSS = 0b10111;
    
    /* Initialize PWM GENERATOR 5 Fault PCI REGISTER HIGH */
    PG5SPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG5SPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG5SPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG5SPCIHbits.ACP   = 0;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG5SPCIHbits.PCIGT  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG5SPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced to ?1?b1?)(3)*/
    PG5SPCIHbits.TQSS  = 0;
    
    
    /* Initialize PWM GENERATOR 5 LEADING-EDGE BLANKING REGISTER LOW */
    PG5LEBL      = 0x0000;
    /* Initialize PWM GENERATOR 5 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG5LEBH      = 0x0000;
    
    /* Initialize PWM GENERATOR 5 PHASE REGISTER */
    PG5PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 5 DUTY CYCLE REGISTER */
    PG5DC        = LOOPTIME_TCY+1;
    /* Initialize PWM GENERATOR 5 DUTY CYCLE ADJUSTMENT REGISTER */
    PG5DCA       = 0x0000;
    /* Initialize PWM GENERATOR 5 PERIOD REGISTER */
    PG5PER       = LOOPTIME_TCY*2+2;
    /* Initialize PWM GENERATOR 5 DEAD-TIME REGISTER LOW */
    PG5DTL       = 0x0000;
    /* Initialize PWM GENERATOR 5 DEAD-TIME REGISTER HIGH */
    PG5DTH       = 0x0000;

    /* Initialize PWM GENERATOR 5 TRIGGER A REGISTER */
    PG5TRIGA     = ADC_SAMPLING_POINT;
    /* Initialize PWM GENERATOR 5 TRIGGER B REGISTER */
    PG5TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 5 TRIGGER C REGISTER */
    PG5TRIGC     = 0x0000;
}

// *****************************************************************************

/**
* <B> Function: void InitPWMGenerator6(void)  </B>
*
*  @brief Function to configure PWM Module # 6
 * @param None.
 * @return None.
 * @example
 * <code>
 * InitPWMGenerator6();
 * </code>
*/
void InitPWMGenerator6 (void)
{
    /* Initialize PWM GENERATOR 6 CONTROL REGISTER LOW */
    PG6CONL      = 0x0000;
    /* PWM Generator 6 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* PWM Generator is disabled prior to configuring module */
    PG6CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG6CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
     * 110 = Dual Edge Center-Aligned PWM mode (interrupt/register update once per cycle)
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
    PG6CONLbits.MODSEL = 4;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG6CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 6 CONTROL REGISTER HIGH */
    PG6CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG6DC
       0 = Macro uses the PG6DC register*/
    PG6CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG6PER
       0 = Macro uses the PG6PER register */
    PG6CONHbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG6PHASE
       0 = Macro uses the PG6PHASE register */
    PG6CONHbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG6CONHbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       0b000 = SOC update
       0b010 = Slaved SOC Update Data registers at start of next cycle if a 
       master update request is received. A master update request will be 
       transmitted if MSTEN = 1 and UPDATE = 1 for the requesting PWM
       Generator.. */
	PG6CONHbits.UPDMOD = 0b010;
    /* PWM Generator Trigger Mode Selection bits
       1 = PWM Generator operates in Retriggerable mode
       0 = PWM Generator operates in Single Trigger mode   */
    PG6CONHbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0000 = Local EOC
       0001 = PWM1(5) PG1 or PG5 trigger output selected by PGTRGSEL (PGxEVTL)
       1111 = TRIG bit or PCI Sync function only (no hardware 
              trigger source is selected) */
    PG6CONHbits.SOCS = 0xF;
    
    /* Clear PWM GENERATOR 6 STATUS REGISTER*/
    PG6STAT      = 0x0000;
    /* Initialize PWM GENERATOR 6 I/O CONTROL REGISTER LOW */
    PG6IOCONL    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG6IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM6H and PWM6L Device Pins bit 
       0 = PWM6H/L signals are mapped to their respective pins */
    PG6IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM6H Pin bit
       0 = PWM Generator provides data for the PWM6H pin*/
    PG6IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM6L Pin bit
       0 = PWM Generator provides data for the PWM6L pin*/
    PG6IOCONLbits.OVRENL = 0;
    /* Data for PWM6H/PWM6L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM6H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM6L */
    PG6IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       10 = User output overrides, via the OVRENH/L and OVRDAT bits, occur when 
            specified by the UPDMOD[2:0] bits in the PGxCONH register
       01 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, occur 
            immediately (as soon as possible)
       00 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, are 
            synchronized to the local PWM time base (next Start-of-Cycle) */

    PG6IOCONLbits.OSYNC = 2;
    /* Data for PWM6H/PWM6L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM6H.
       If Fault is active, then FLTDAT<0> provides data for PWM6L.*/
    PG6IOCONLbits.FLTDAT = 0;
    /* Data for PWM6H/PWM6L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM6H.
       If current limit is active, then CLDAT<0> provides data for PWM6L.*/
    PG6IOCONLbits.CLDAT = 0;
    /* Data for PWM6H/PWM6L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM6H.
       If feed-forward is active, then FFDAT<0> provides data for PWM6L.*/
    PG6IOCONLbits.FFDAT = 0;
    /* Data for PWM6H/PWM6L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM6H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM6L data. */
    PG6IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 6 I/O CONTROL REGISTER HIGH */    
    PG6IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG6IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG6IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG6IOCONHbits.PMOD = 0;
    /* PWM6H Output Port Enable bit
       1 = PWM Generator controls the PWM6H output pin
       0 = PWM Generator does not control the PWM6H output pin */
    PG6IOCONHbits.PENH = 1;
    /* PWM6L Output Port Enable bit
       1 = PWM Generator controls the PWM6L output pin
       0 = PWM Generator does not control the PWM6L output pin */
    PG6IOCONHbits.PENL = 1;
    /* PWM6H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG6IOCONHbits.POLH = 0;
    /* PWM6L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG6IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 6 EVENT REGISTER LOW*/
    PG6EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG6EVTLbits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG6TRIGC Compare Event Enable bit
       0 = PG6TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG6EVTLbits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG6TRIGB Compare Event Enable bit
       0 = PG6TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG6EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG6TRIGA Compare Event Enable bit
       0 = PG6TRIGA register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG6EVTLbits.ADTR1EN1 = 1;
    /* Update Trigger Select bits
       01 = A write of the PG6DC register automatically sets the UPDATE bit
       00 = User must set the UPDATE bit manually */
    PG6EVTLbits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG6EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 6 EVENT REGISTER HIGH */
    PG6EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled 
       1 = Fault interrupt is enabled*/
    PG6EVTHbits.FLTIEN = 1;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG6EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG6EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG6EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG6EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 6 Source is PG6TRIGC Compare Event Enable bit
       0 = PG6TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG6EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG6TRIGB Compare Event Enable bit
       0 = PG6TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG6EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG6TRIGA Compare Event Enable bit
       0 = PG6TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG6EVTHbits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG6EVTHbits.ADTR1OFS = 0;
    
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 6 Fault PCI REGISTER LOW */
    PG6FPCIL     = 0x0000;
    /* PWM GENERATOR 6 Fault PCI REGISTER HIGH */
    PG6FPCIH     = 0x0000;
#else
    /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG6FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG6FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG6FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG6FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG6FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG6FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 0 = Not inverted 1 = Inverted */
    PG6FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG6FPCILbits.PSS = 28;
    
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG6FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG6FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG6FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG6FPCIHbits.ACP   = 3;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG6FPCIHbits.PCIGT  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG6FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced '1')*/
    PG6FPCIHbits.TQSS  = 0;
#endif
    
    /* PWM GENERATOR 6 Current Limit PCI REGISTER LOW */
    PG6CLPCIL    = 0x0000;
    /* PWM GENERATOR 6 Current Limit PCI REGISTER HIGH */
    PG6CLPCIH    = 0x0000;
    /* PWM GENERATOR 6 Feed Forward PCI REGISTER LOW */
    PG6FFPCIL    = 0x0000;
    /* PWM GENERATOR 6 Feed Forward  PCI REGISTER HIGH */
    PG6FFPCIH    = 0x0000;
    
    /* PWM GENERATOR 6 Sync PCI REGISTER LOW */
    PG6SPCIL     = 0x0000;   
    PG6SPCILbits.PPS = 1;
    PG6SPCILbits.PSS = 1;
    
    /* PWM GENERATOR 6 Sync PCI REGISTER HIGH */
    PG6SPCIH     = 0x0000;
    PG6SPCIHbits.ACP = 0;
    
    /* Initialize PWM GENERATOR 6 LEADING-EDGE BLANKING REGISTER LOW */
    PG6LEBL      = 0x0000;
    /* Initialize PWM GENERATOR 6 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG6LEBH      = 0x0000;
    PG6LEBHbits.PWMPCI = 4;
    
    /* Initialize PWM GENERATOR 6 PHASE REGISTER */
    PG6PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 6 DUTY CYCLE REGISTER */
    PG6DC        = MIN_DUTY;
    /* Initialize PWM GENERATOR 6 DUTY CYCLE ADJUSTMENT REGISTER */
    PG6DCA       = 0x0000;
    /* Initialize PWM GENERATOR 6 PERIOD REGISTER */
    PG6PER       = 0x0000;
    /* Initialize PWM GENERATOR 6 DEAD-TIME REGISTER LOW */
    PG6DTL       = DDEADTIME;
    /* Initialize PWM GENERATOR 6 DEAD-TIME REGISTER HIGH */
    PG6DTH       = DDEADTIME;

    /* Initialize PWM GENERATOR 6 TRIGGER A REGISTER */
    PG6TRIGA     = ADC_SAMPLING_POINT; 
    /* Initialize PWM GENERATOR 6 TRIGGER B REGISTER */
    PG6TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 6 TRIGGER C REGISTER */
    PG6TRIGC     = 0x0000;
}


/**
* <B> Function: void InitPWMGenerator7(void)  </B>
*
*  @brief Function to configure PWM Module # 7
 * @param None.
 * @return None.
 * @example
 * <code>
 * InitPWMGenerator7();
 * </code>
*/
void InitPWMGenerator7 (void)
{
    /* Initialize PWM GENERATOR 7 CONTROL REGISTER LOW */
    PG7CONL      = 0x0000;
    /* PWM Generator 7 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* PWM Generator is disabled prior to configuring module */
    PG7CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG7CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
    PG7CONLbits.MODSEL = 4;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG7CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 7 CONTROL REGISTER HIGH */
    PG7CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG7DC
       0 = Macro uses the PG7DC register*/
    PG7CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG7PER
       0 = Macro uses the PG7PER register */
    PG7CONHbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG7PHASE
       0 = Macro uses the PG7PHASE register */
    PG7CONHbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG7CONHbits.MSTEN = 0;
     /* PWM Buffer Update Mode Selection bits 
       0b000 = SOC update
       0b010 = Slaved SOC Update Data registers at start of next cycle if a 
       master update request is received. A master update request will be 
       transmitted if MSTEN = 1 and UPDATE = 1 for the requesting PWM
       Generator.. */
	PG7CONHbits.UPDMOD = 0b010;
    /* PWM Generator Trigger Mode Selection bits
       1 = PWM Generator operates in Retriggerable mode
       0 = PWM Generator operates in Single Trigger mode   */

    PG7CONHbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0001 = PWM1 trigger o/p selected by PG1 PGTRGSEL<2:0> bits(PGxEVT<2:0>)
       1111 = TRIG bit or PCI Sync function only (no hardware trigger source is selected)*/
    PG7CONHbits.SOCS = 0xF;
    
    /* Clear PWM GENERATOR 7 STATUS REGISTER*/
    PG7STAT      = 0x0000;
    /* Initialize PWM GENERATOR 7 I/O CONTROL REGISTER LOW */
    PG7IOCONL    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG7IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM7H and PWM7L Device Pins bit 
       0 = PWM7H/L signals are mapped to their respective pins */
    PG7IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM7H Pin bit
       0 = PWM Generator provides data for the PWM7H pin*/
    PG7IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM7L Pin bit
       0 = PWM Generator provides data for the PWM7L pin*/
    PG7IOCONLbits.OVRENL = 0;
    /* Data for PWM7H/PWM7L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM7H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM7L */
    PG7IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       10 = User output overrides, via the OVRENH/L and OVRDAT bits, occur when 
            specified by the UPDMOD[2:0] bits in the PGxCONH register
       01 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, occur 
            immediately (as soon as possible)
       00 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, are 
            synchronized to the local PWM time base (next Start-of-Cycle) */

    PG7IOCONLbits.OSYNC = 2;
    /* Data for PWM7H/PWM7L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM7H.
       If Fault is active, then FLTDAT<0> provides data for PWM7L.*/
    PG7IOCONLbits.FLTDAT = 0;
    /* Data for PWM7H/PWM7L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM7H.
       If current limit is active, then CLDAT<0> provides data for PWM7L.*/
    PG7IOCONLbits.CLDAT = 0;
    /* Data for PWM7H/PWM7L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM7H.
       If feed-forward is active, then FFDAT<0> provides data for PWM7L.*/
    PG7IOCONLbits.FFDAT = 0;
    /* Data for PWM7H/PWM7L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM7H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM7L data. */
    PG7IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 7 I/O CONTROL REGISTER HIGH */    
    PG7IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG7IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG7IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG7IOCONHbits.PMOD = 0;
    /* PWM7H Output Port Enable bit
       1 = PWM Generator controls the PWM7H output pin
       0 = PWM Generator does not control the PWM7H output pin */
    PG7IOCONHbits.PENH = 1;
    /* PWM7L Output Port Enable bit
       1 = PWM Generator controls the PWM7L output pin
       0 = PWM Generator does not control the PWM7L output pin */
    PG7IOCONHbits.PENL = 1;
    /* PWM7H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG7IOCONHbits.POLH = 0;
    /* PWM7L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG7IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 7 EVENT REGISTER LOW*/
    PG7EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG7EVTLbits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG7TRIGC Compare Event Enable bit
       0 = PG7TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG7EVTLbits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG7TRIGB Compare Event Enable bit
       0 = PG7TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG7EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG7TRIGA Compare Event Enable bit
       0 = PG7TRIGA register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG7EVTLbits.ADTR1EN1 = 0;
    /* Update Trigger Select bits
       01 = A write of the PG7DC register automatically sets the UPDATE bit
       00 = User must set the UPDATE bit manually*/
    PG7EVTLbits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG7EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 7 EVENT REGISTER HIGH */
    PG7EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled */
    PG7EVTHbits.FLTIEN = 0;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG7EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG7EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG7EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG7EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 2 Source is PG7TRIGC Compare Event Enable bit
       0 = PG7TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG7EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG7TRIGB Compare Event Enable bit
       0 = PG7TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG7EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG7TRIGA Compare Event Enable bit
       0 = PG7TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG7EVTHbits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG7EVTHbits.ADTR1OFS = 0;
    
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG7FPCIL     = 0x0000;
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG7FPCIH     = 0x0000;
#else
       /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG7FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG7FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG7FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG7FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG7FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG7FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 0 = Not inverted 1 = Inverted*/
    PG7FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG7FPCILbits.PSS = 28;
    
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG7FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG7FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG7FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG7FPCIHbits.ACP   = 3;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG7FPCIHbits.PCIGT  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG7FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced to ?1?b1?)(3)*/
    PG7FPCIHbits.TQSS  = 0;
#endif
    
    /* PWM GENERATOR 7 Current Limit PCI REGISTER LOW */
    PG7CLPCIL    = 0x0000;
    /* PWM GENERATOR 7 Current Limit PCI REGISTER HIGH */
    PG7CLPCIH    = 0x0000;
    /* PWM GENERATOR 7 Feed Forward PCI REGISTER LOW */
    PG7FFPCIL    = 0x0000;
    /* PWM GENERATOR 7 Feed Forward  PCI REGISTER HIGH */
    PG7FFPCIH    = 0x0000;

        /* PWM GENERATOR 7 Sync PCI REGISTER LOW */
    PG7SPCIL     = 0x0000;   
    PG7SPCILbits.PPS = 1;
    PG7SPCILbits.PSS = 1;
    
    /* PWM GENERATOR 7 Sync PCI REGISTER HIGH */
    PG7SPCIH     = 0x0000;
    PG7SPCIHbits.ACP = 0;
    
    /* Initialize PWM GENERATOR 7 LEADING-EDGE BLANKING REGISTER LOW */
    PG7LEBL      = 0x0000;
    
    /* Initialize PWM GENERATOR 7 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG7LEBH      = 0x0000;
    PG7LEBHbits.PWMPCI = 4;
    
    /* Initialize PWM GENERATOR 7 PHASE REGISTER */
    PG7PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 7 DUTY CYCLE REGISTER */
    PG7DC        = MIN_DUTY;
    /* Initialize PWM GENERATOR 7 DUTY CYCLE ADJUSTMENT REGISTER */
    PG7DCA       = 0x0000;
    /* Initialize PWM GENERATOR 7 PERIOD REGISTER */
    PG7PER       = 0x0000;
    /* Initialize PWM GENERATOR 7 DEAD-TIME REGISTER LOW */
    PG7DTL       = DDEADTIME;
    /* Initialize PWM GENERATOR 7 DEAD-TIME REGISTER HIGH */
    PG7DTH       = DDEADTIME;

    /* Initialize PWM GENERATOR 7 TRIGGER A REGISTER */
    PG7TRIGA     = 0x0000;
    /* Initialize PWM GENERATOR 7 TRIGGER B REGISTER */
    PG7TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 7 TRIGGER C REGISTER */
    PG7TRIGC     = 0x0000;
    
}

    
/**
* <B> Function: void InitPWMGenerator8(void)  </B>
*
*  @brief Function to configure PWM Module # 8
 * @param None.
 * @return None.
 * @example
 * <code>
 * InitPWMGenerator8();
 * </code>
*/
void InitPWMGenerator8 (void)
{
    /* Initialize PWM GENERATOR 8 CONTROL REGISTER LOW */
    PG8CONL      = 0x0000;
    /* PWM Generator 8 Enable bit : 1 = Is enabled, 0 = Is not enabled */
    /* PWM Generator is disabled prior to configuring module */
    PG8CONLbits.ON = 0;
    /* Clock Selection bits
       0b01 = Macro uses Master clock selected by the PCLKCON.MCLKSEL bits*/
    PG8CONLbits.CLKSEL = 1;
    /* PWM Mode Selection bits
       100 = Center-Aligned PWM mode(interrupt/register update once per cycle)*/
    PG8CONLbits.MODSEL = 4;
    /* Trigger Count Select bits
       000 = PWM Generator produces 1 PWM cycle after triggered */
    PG8CONLbits.TRGCNT = 0;
    
    /* Initialize PWM GENERATOR 8 CONTROL REGISTER HIGH */
    PG8CONH      = 0x0000;
    /* Master Duty Cycle Register Select bit
       1 = Macro uses the MDC register instead of PG8DC
       0 = Macro uses the PG8DC register*/
    PG8CONHbits.MDCSEL = 0;
    /* Master Period Register Select bit
       1 = Macro uses the MPER register instead of PG8PER
       0 = Macro uses the PG8PER register */
    PG8CONHbits.MPERSEL = 1;
    /* MPHSEL: Master Phase Register Select bit
       1 = Macro uses the MPHASE register instead of PG8PHASE
       0 = Macro uses the PG8PHASE register */
    PG8CONHbits.MPHSEL = 0;
    /* Master Update Enable bit
       1 = PWM Generator broadcasts software set/clear of UPDATE status bit and 
           EOC signal to other PWM Generators
       0 = PWM Generator does not broadcast UPDATE status bit or EOC signal */
    PG8CONHbits.MSTEN = 0;
    /* PWM Buffer Update Mode Selection bits 
       0b000 = SOC update
       0b010 = Slaved SOC Update Data registers at start of next cycle if a 
       master update request is received. A master update request will be 
       transmitted if MSTEN = 1 and UPDATE = 1 for the requesting PWM
       Generator. */
    PG8CONHbits.UPDMOD = 0b010;
    /* PWM Generator Trigger Mode Selection bits
       1 = PWM Generator operates in Retriggerable mode
       0 = PWM Generator operates in Single Trigger mode   */
    PG8CONHbits.TRGMOD = 1;
    /* Start of Cycle Selection bits
       0001 = PWM1 trigger o/p selected by PG1 PGTRGSEL<2:0> bits(PGxEVT<2:0>)
       1111 = TRIG bit or PCI Sync function only (no hardware trigger source is selected)*/
    PG8CONHbits.SOCS = 0xF;
    
    /* Clear PWM GENERATOR 8 STATUS REGISTER*/
    PG8STAT      = 0x0000;
    /* Initialize PWM GENERATOR 8 I/O CONTROL REGISTER LOW */
    PG8IOCONL    = 0x0000;

    /* Current Limit Mode Select bit
       0 = If PCI current limit is active, then the CLDAT<1:0> bits define 
       the PWM output levels */
    PG8IOCONLbits.CLMOD = 0;
    /* Swap PWM Signals to PWM8H and PWM8L Device Pins bit 
       0 = PWM8H/L signals are mapped to their respective pins */
    PG8IOCONLbits.SWAP = 0;
    /* User Override Enable for PWM8H Pin bit
       0 = PWM Generator provides data for the PWM8H pin*/
    PG8IOCONLbits.OVRENH = 0;
    /* User Override Enable for PWM8L Pin bit
       0 = PWM Generator provides data for the PWM8L pin*/
    PG8IOCONLbits.OVRENL = 0;
    /* Data for PWM8H/PWM8L Pins if Override is Enabled bits
       If OVERENH = 1, then OVRDAT<1> provides data for PWM8H.
       If OVERENL = 1, then OVRDAT<0> provides data for PWM8L */
    PG8IOCONLbits.OVRDAT = 0;
    /* User Output Override Synchronization Control bits
       10 = User output overrides, via the OVRENH/L and OVRDAT bits, occur when 
            specified by the UPDMOD[2:0] bits in the PGxCONH register
       01 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, occur 
            immediately (as soon as possible)
       00 = User output overrides, via the OVRENH/L and OVRDAT[1:0] bits, are 
            synchronized to the local PWM time base (next Start-of-Cycle) */
    PG8IOCONLbits.OSYNC = 2;
    /* Data for PWM8H/PWM8L Pins if FLT Event is Active bits
       If Fault is active, then FLTDAT<1> provides data for PWM8H.
       If Fault is active, then FLTDAT<0> provides data for PWM8L.*/
    PG8IOCONLbits.FLTDAT = 0;
    /* Data for PWM8H/PWM8L Pins if CLMT Event is Active bits
       If current limit is active, then CLDAT<1> provides data for PWM8H.
       If current limit is active, then CLDAT<0> provides data for PWM8L.*/
    PG8IOCONLbits.CLDAT = 0;
    /* Data for PWM8H/PWM8L Pins if Feed-Forward Event is Active bits
       If feed-forward is active, then FFDAT<1> provides data for PWM8H.
       If feed-forward is active, then FFDAT<0> provides data for PWM8L.*/
    PG8IOCONLbits.FFDAT = 0;
    /* Data for PWM8H/PWM8L Pins if Debug Mode is Active and PTFRZ = 1 bits
       If Debug mode is active and PTFRZ=1,then DBDAT<1> provides PWM8H data.
       If Debug mode is active and PTFRZ=1,then DBDAT<0> provides PWM8L data. */
    PG8IOCONLbits.DBDAT = 0;
    
    /* Initialize PWM GENERATOR 8 I/O CONTROL REGISTER HIGH */    
    PG8IOCONH    = 0x0000;
    /* Time Base Capture Source Selection bits
       000 = No hardware source selected for time base capture ? software only*/
    PG8IOCONHbits.CAPSRC = 0;
    /* Dead-Time Compensation Select bit 
       0 = Dead-time compensation is controlled by PCI Sync logic */
    PG8IOCONHbits.DTCMPSEL = 0;
    /* PWM Generator Output Mode Selection bits
       00 = PWM Generator outputs operate in Complementary mode*/
    PG8IOCONHbits.PMOD = 0;
    /* PWM8H Output Port Enable bit
       1 = PWM Generator controls the PWM8H output pin
       0 = PWM Generator does not control the PWM8H output pin */
    PG8IOCONHbits.PENH = 1;
    /* PWM8L Output Port Enable bit
       1 = PWM Generator controls the PWM8L output pin
       0 = PWM Generator does not control the PWM8L output pin */
    PG8IOCONHbits.PENL = 1;
    /* PWM8H Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG8IOCONHbits.POLH = 0;
    /* PWM3L Output Polarity bit
       1 = Output pin is active-low
       0 = Output pin is active-high*/
    PG8IOCONHbits.POLL = 0;
    
    /* Initialize PWM GENERATOR 8 EVENT REGISTER LOW*/
    PG8EVTL      = 0x0000;
    /* ADC Trigger 1 Post-scaler Selection bits
       00000 = 1:1 */
    PG8EVTLbits.ADTR1PS = 0;
    /* ADC Trigger 1 Source is PG8TRIGC Compare Event Enable bit
       0 = PG8TRIGC register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG8EVTLbits.ADTR1EN3  = 0;
    /* ADC Trigger 1 Source is PG8TRIGB Compare Event Enable bit
       0 = PG8TRIGB register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG8EVTLbits.ADTR1EN2 = 0;
    /* ADC Trigger 1 Source is PG8TRIGA Compare Event Enable bit
       0 = PG8TRIGA register compare event is disabled as trigger source for 
           ADC Trigger 1 */
    PG8EVTLbits.ADTR1EN1 = 0;
    /* Update Trigger Select bits
       01 = A write of the PG8DC register automatically sets the UPDATE bit
       00 = User must set the UPDATE bit manually*/
    PG8EVTLbits.UPDTRG = 1;
    /* PWM Generator Trigger Output Selection bits
       000 = EOC event is the PWM Generator trigger*/
    PG8EVTLbits.PGTRGSEL = 0;
    
    /* Initialize PWM GENERATOR 8 EVENT REGISTER HIGH */
    PG8EVTH      = 0x0000;
    /* FLTIEN: PCI Fault Interrupt Enable bit
       0 = Fault interrupt is disabled */
    PG8EVTHbits.FLTIEN = 0;
    /* PCI Current Limit Interrupt Enable bit
       0 = Current limit interrupt is disabled */
    PG8EVTHbits.CLIEN = 0;
    /* PCI Feed-Forward Interrupt Enable bit
       0 = Feed-forward interrupt is disabled */
    PG8EVTHbits.FFIEN = 0;
    /* PCI Sync Interrupt Enable bit
       0 = Sync interrupt is disabled */
    PG8EVTHbits.SIEN = 0;
    /* Interrupt Event Selection bits
       00 = Interrupts CPU at EOC
       01 = Interrupts CPU at TRIGA compare event
       10 = Interrupts CPU at ADC Trigger 1 event
       11 = Time base interrupts are disabled */
    PG8EVTHbits.IEVTSEL = 3;
    /* ADC Trigger 3 Source is PG8TRIGC Compare Event Enable bit
       0 = PG8TRIGC register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG8EVTHbits.ADTR2EN3 = 0;
    /* ADC Trigger 2 Source is PG8TRIGB Compare Event Enable bit
       0 = PG8TRIGB register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG8EVTHbits.ADTR2EN2 = 0;
    /* ADC Trigger 2 Source is PG8TRIGA Compare Event Enable bit
       0 = PG8TRIGA register compare event is disabled as 
           trigger source for ADC Trigger 2 */
    PG8EVTHbits.ADTR2EN1 = 0;
    /* ADC Trigger 1 Offset Selection bits
       00000 = No offset */
    PG8EVTHbits.ADTR1OFS = 0;
    
#ifndef ENABLE_PWM_FAULT
    /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG8FPCIL     = 0x0000;
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG8FPCIH     = 0x0000;
#else
       /* PWM GENERATOR 1 Fault PCI REGISTER LOW */
    PG8FPCIL     = 0x0000;
    /* Termination Synchronization Disable bit
       1 = Termination of latched PCI occurs immediately
       0 = Termination of latched PCI occurs at PWM EOC */
    PG8FPCILbits.TSYNCDIS = 0;
    /* Termination Event Selection bits
       001 = Auto-Terminate: Terminate when PCI source transitions from 
             active to inactive */
    PG8FPCILbits.TERM = 1;
    /* Acceptance Qualifier Polarity Select bit: 1 = Inverted 0 = Not inverted*/
    PG8FPCILbits.AQPS = 0;
    /* Acceptance Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to 0)
       110 = Selects PCI Source #9
       101 = Selects PCI Source #8
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)        
       000 = No acceptance qualifier is used (qualifier forced to 1) */
    PG8FPCILbits.AQSS = 0;
    /* PCI Synchronization Control bit
       1 = PCI source is synchronized to PWM EOC
       0 = PCI source is not synchronized to PWM EOC*/
    PG8FPCILbits.PSYNC = 0;
    /* PCI Polarity Select bit 0 = Not inverted 1 = Inverted*/
    PG8FPCILbits.PPS = 1;
    /* PCI Source Selection bits
       11111 = PCI Source #31
       ? ?
       00001 = PCI Source #1
       00000 = Software PCI control bit (SWPCI) only*/
    PG8FPCILbits.PSS = 28;
    
    /* PWM GENERATOR 1 Fault PCI REGISTER HIGH */
    PG8FPCIH     = 0x0000;
    /* PCI Bypass Enable bit
       0 = PCI function is not bypassed */
    PG8FPCIHbits.BPEN   = 0;
    /* PCI Bypass Source Selection bits(1)
       000 = PCI control is sourced from PG1 PCI logic when BPEN = 1 */
    PG8FPCIHbits.BPSEL   = 0;
    /* PCI Acceptance Criteria Selection bits
       101 = Latched any edge(2)
       100 = Latched rising edge
       011 = Latched
       010 = Any edge
       001 = Rising edge
       000 = Level-sensitive*/
    PG8FPCIHbits.ACP   = 3;
    /* PCI SR Latch Mode bit
       1 = SR latch is Reset-dominant in Latched Acceptance modes
       0 = SR latch is Set-dominant in Latched Acceptance modes*/
    PG8FPCIHbits.PCIGT  = 0;
    /* Termination Qualifier Polarity Select bit 1 = Inverted 0 = Not inverted*/
    PG8FPCIHbits.TQPS   = 0;
    /* Termination Qualifier Source Selection bits
       111 = SWPCI control bit only (qualifier forced to ?1?b0?)(3)
       110 = Selects PCI Source #9 (pwm_pci[9] input port)
       101 = Selects PCI Source #8 (pwm_pci[8] input port)
       100 = Selects PCI Source #1 (PWM Generator output selected by the PWMPCI<2:0> bits)
       011 = PWM Generator is triggered
       010 = LEB is active
       001 = Duty cycle is active (base PWM Generator signal)
       000 = No termination qualifier used (qualifier forced '1')*/
    PG8FPCIHbits.TQSS  = 0;
#endif
    
    /* PWM GENERATOR 8 Current Limit PCI REGISTER LOW */
    PG8CLPCIL    = 0x0000;
    /* PWM GENERATOR 8 Current Limit PCI REGISTER HIGH */
    PG8CLPCIH    = 0x0000;
    /* PWM GENERATOR 8 Feed Forward PCI REGISTER LOW */
    PG8FFPCIL    = 0x0000;
    /* PWM GENERATOR 8 Feed Forward  PCI REGISTER HIGH */
    PG8FFPCIH    = 0x0000;

        /* PWM GENERATOR 8 Sync PCI REGISTER LOW */
    PG8SPCIL     = 0x0000;  
    PG8SPCILbits.PPS = 1;
    PG8SPCILbits.PSS = 1;
    
    /* PWM GENERATOR 8 Sync PCI REGISTER LOW */
    PG8SPCIH     = 0x0000;
    PG8SPCIHbits.ACP = 0;
    
    /* Initialize PWM GENERATOR 1 LEADING-EDGE BLANKING REGISTER LOW */
    PG8LEBL      = 0x0000;
    /* Initialize PWM GENERATOR 1 LEADING-EDGE BLANKING REGISTER HIGH*/
    PG8LEBH      = 0x0000;
    PG8LEBHbits.PWMPCI = 4;
    
    /* Initialize PWM GENERATOR 8 PHASE REGISTER */
    PG8PHASE     = 0x0000;
    /* Initialize PWM GENERATOR 8 DUTY CYCLE REGISTER */
    PG8DC        = MIN_DUTY;
    /* Initialize PWM GENERATOR 8 DUTY CYCLE ADJUSTMENT REGISTER */
    PG8DCA       = 0x0000;
    /* Initialize PWM GENERATOR 8 PERIOD REGISTER */
    PG8PER       = 0x0000;
    /* Initialize PWM GENERATOR 8 DEAD-TIME REGISTER LOW */
    PG8DTL       = DDEADTIME;
    /* Initialize PWM GENERATOR 8 DEAD-TIME REGISTER HIGH */
    PG8DTH       = DDEADTIME;

    /* Initialize PWM GENERATOR 8 TRIGGER A REGISTER */
    PG8TRIGA     = 0x0000;
    /* Initialize PWM GENERATOR 8 TRIGGER B REGISTER */
    PG8TRIGB     = 0x0000;
    /* Initialize PWM GENERATOR 8 TRIGGER C REGISTER */
    PG8TRIGC     = 0x0000;
    
}

// </editor-fold> 