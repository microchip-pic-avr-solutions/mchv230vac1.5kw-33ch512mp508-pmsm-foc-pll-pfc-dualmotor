// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file board_service.c
 *
 * @brief This module implements the board service routines 
 * 
 * Definitions in the file are for dsPIC33CK64MC105 MC DIM plugged onto 
 * Motor Control Development board from Microchip
 *
 * Component: BOARD SERVICE
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
#include <stdint.h>
#include <stdbool.h>
#include "delay.h"
#include "port_config.h"
#include "board_service.h"
#include "adc.h"
#include "pwm.h"
// </editor-fold> 

// <editor-fold defaultstate="collapsed" desc="Definitions ">
#define Q15_OVER_CURRENT_THRESHOLD 31000
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Global Variables  ">
BUTTON_T buttonStartStop, button2;
uint16_t boardServiceISRCounter = 0;
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="INTERFACE FUNCTIONS ">
static void ButtonGroupInitialize(void);
static void ButtonScan(BUTTON_T * ,bool);

bool IsPressed_Button1(void)
{
    if(buttonStartStop.status)
    {
        buttonStartStop.status = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool IsPressed_Button2(void)
{
    if (button2.status)
    {
        button2.status = false;
        return true;
    }
    else
    {
        return false;
    }
}

void BoardServiceStepIsr(void)
{
    if (boardServiceISRCounter <  BOARD_SERVICE_TICK_COUNT)
    {
        boardServiceISRCounter += 1;
    }
}

void BoardService(void)
{
    if (boardServiceISRCounter ==  BOARD_SERVICE_TICK_COUNT)
    {
        /* Button scanning loop for Button 1 to start Motor 1 */
        ButtonScan(&buttonStartStop,BUTTON_START_STOP);
        
        /* Button scanning loop for Button 2 to start Motor 2 */
        ButtonScan(&button2,BUTTON_2);
        
        boardServiceISRCounter = 0;
    }
}

void BoardServiceInit(void)
{
    ButtonGroupInitialize();
    boardServiceISRCounter = BOARD_SERVICE_TICK_COUNT;
}

void ButtonScan(BUTTON_T *pButton,bool button) 
{
    if (button == true) 
    {
        if (pButton->debounceCount < BUTTON_DEBOUNCE_COUNT) 
        {
            pButton->debounceCount--;
            pButton->state = BUTTON_DEBOUNCE;
        }
    } 
    else 
    {
        if (pButton->debounceCount < BUTTON_DEBOUNCE_COUNT) 
        {
            pButton->state = BUTTON_NOT_PRESSED;
        } 
        else 
        {
            pButton->state = BUTTON_PRESSED;
            pButton->status = true;
        }
        pButton->debounceCount = 0;
    }
}

void ButtonGroupInitialize(void)
{
    buttonStartStop.state = BUTTON_NOT_PRESSED;
    buttonStartStop.debounceCount = 0;
    buttonStartStop.state = false;
    
    button2.state = BUTTON_NOT_PRESSED;
    button2.debounceCount = 0;
    button2.state = false;
}

/**
 * <B> Function: HAL_InitPeripherals()  </B>
 * @brief Function to initialize the peripherals.
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = HAL_InitPeripherals();
 * </code>
 */
void HAL_InitPeripherals(void)
{                
    InitializeADCs();
    
    InitPWMGenerators();
    
    TIMER1_Initialize();
    TIMER1_InputClockSet();
    TIMER1_PeriodSet(TIMER1_PERIOD_COUNT);
    TIMER1_InterruptPrioritySet(5);
    TIMER1_InterruptFlagClear();
    TIMER1_InterruptEnable(); 
    TIMER1_ModuleStart();
}


/**
 * <B> Function: HAL_MC1PWMEnableOutputs()  </B>
 * @brief Function to enable PWM outputs for MC1.
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = HAL_MC1PWMEnableOutputs();
 * </code>
 */
void HAL_MC1PWMEnableOutputs(void)
{
    /* Set PWM Duty Cycles */
    MC1_PWM_PDC3 = 0;
    MC1_PWM_PDC2 = 0;
    MC1_PWM_PDC1 = 0;
    
    PG3IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM3H pin
    PG2IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM2H pin
    PG1IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM1H pin

    PG3IOCONLbits.OVRENL = 0;  // 0 = PWM generator provides data for PWM3L pin
    PG2IOCONLbits.OVRENL = 0;  // 0 = PWM generator provides data for PWM2L pin
    PG1IOCONLbits.OVRENL = 0;  // 0 = PWM generator provides data for PWM1L pin
}
/**
 * <B> Function: HAL_MC2PWMEnableOutputs()  </B>
 * @brief Function to enable PWM outputs for MC1.
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = HAL_MC2PWMEnableOutputs();
 * </code>
 */
void HAL_MC2PWMEnableOutputs(void)
{
    /* Set PWM Duty Cycles */
    MC2_PWM_PDC3 = 0;
    MC2_PWM_PDC2 = 0;
    MC2_PWM_PDC1 = 0;
    
    PG8IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM8H pin
    PG7IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM7H pin
    PG6IOCONLbits.OVRENH = 0;  // 0 = PWM generator provides data for PWM6H pin

    PG8IOCONLbits.OVRENL = 0;  // 0 = PWM generator provides data for PWM8L pin
    PG7IOCONLbits.OVRENL = 0;  // 0 = PWM generator provides data for PWM7L pin
    PG6IOCONLbits.OVRENL = 0;  // 0 = PWM generator provides data for PWM6L pin
}

/**
 * <B> Function: HAL_MC1PWMDisableOutputs()  </B>
 * @brief Function to override PWM outputs to 0 for MC1.
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = HAL_MC1PWMDisableOutputs();
 * </code>
 */
void HAL_MC1PWMDisableOutputs(void)
{
    /* Set PWM Duty Cycles */
    MC1_PWM_PDC3 = 0;
    MC1_PWM_PDC2 = 0;
    MC1_PWM_PDC1 = 0;
    
    PG3IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM3H,L, if Override is Enabled
    PG2IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM2H,L, if Override is Enabled
    PG1IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM1H,L, if Override is Enabled

    PG3IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM3H
    PG2IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM2H
    PG1IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM1H

    PG3IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM3L
    PG2IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM2L
    PG1IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM1L
}

/**
 * <B> Function: HAL_MC2PWMDisableOutputs()  </B>
 * @brief Function to override PWM outputs to 0 for MC2.
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = HAL_MC2PWMDisableOutputs();
 * </code>
 */
void HAL_MC2PWMDisableOutputs(void)
{
    /* Set PWM Duty Cycles */
    MC2_PWM_PDC3 = 0;
    MC2_PWM_PDC2 = 0;
    MC2_PWM_PDC1 = 0;
    
    PG8IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM8H,L, if Override is Enabled
    PG7IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM7H,L, if Override is Enabled
    PG6IOCONLbits.OVRDAT = 0;  // 0b00 = State for PWM6H,L, if Override is Enabled

    PG8IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM3H
    PG7IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM2H
    PG6IOCONLbits.OVRENH = 1;  // 1 = OVRDAT<1> provides data for output on PWM1H

    PG8IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM3L
    PG7IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM2L
    PG6IOCONLbits.OVRENL = 1;  // 1 = OVRDAT<0> provides data for output on PWM1L
}

/**
 * Writes three unique duty cycle values to the PWM duty cycle registers
 * corresponding to Motor #1.
 * Summary: Writes to the PWM duty cycle registers corresponding to Motor #1.
 * @param pdc Pointer to the array that holds duty cycle values
 * @example
 * <code>
 * HAL_MC1PWMSetDutyCycles(&pdcMotor1);
 * </code>
 */
void HAL_MC1PWMSetDutyCycles(MC_DUTYCYCLEOUT_T *pdc)
{
    if(pdc->dutycycle3 < MIN_DUTY)
    {
        pdc->dutycycle3 = MIN_DUTY;
    }
    if(pdc->dutycycle2 < MIN_DUTY)
    {
        pdc->dutycycle2 = MIN_DUTY;
    }
    if(pdc->dutycycle1 < MIN_DUTY)
    {
        pdc->dutycycle1 = MIN_DUTY;
    }
    
    MC1_PWM_PDC3 = pdc->dutycycle3;
    MC1_PWM_PDC2 = pdc->dutycycle2;
    MC1_PWM_PDC1 = pdc->dutycycle1;
}

/**
 * Writes three unique duty cycle values to the PWM duty cycle registers
 * corresponding to Motor #2.
 * Summary: Writes to the PWM duty cycle registers corresponding to Motor #2.
 * @param pdc Pointer to the array that holds duty cycle values
 * @example
 * <code>
 * HAL_MC2PWMSetDutyCycles(&pdcMotor1);
 * </code>
 */
void HAL_MC2PWMSetDutyCycles(MC_DUTYCYCLEOUT_T *pdc)
{
    if(pdc->dutycycle3 < MIN_DUTY)
    {
        pdc->dutycycle3 = MIN_DUTY;
    }
    if(pdc->dutycycle2 < MIN_DUTY)
    {
        pdc->dutycycle2 = MIN_DUTY;
    }
    if(pdc->dutycycle1 < MIN_DUTY)
    {
        pdc->dutycycle1 = MIN_DUTY;
    }
    
    MC2_PWM_PDC3 = pdc->dutycycle3;
    MC2_PWM_PDC2 = pdc->dutycycle2;
    MC2_PWM_PDC1 = pdc->dutycycle1;
}

/**
 * <B> Function: HAL_TrapHandler()  </B>
 * @brief Function to perform trap handling.
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = HAL_TrapHandler();
 * </code>
 */
void HAL_TrapHandler(void)
{
    HAL_MC1PWMDisableOutputs();
    while (1)
    {
        Nop();
        Nop();
        Nop();
    }
}

/**
 * <B> Function: HAL_MC1ADCSwitchChannels()  </B>
 * @brief Function to switch ADC channel .
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = HAL_MC1ADCSwitchChannels();
 * </code>
 */
void HAL_MC1ADCSwitchChannels(void)
{
    /* C0CHS[1:0]: Dedicated ADC Core 0 Input Channel Selection bits
        01 = S1ANA0
        00 = S1AN0  */
    ADCON4Hbits.C0CHS = 0b01;
    /* C1CHS[1:0]: Dedicated ADC Core 1 Input Channel Selection bits
        01 = S1ANA1
        00 = S1AN1 */
    ADCON4Hbits.C1CHS = 0b01;
    
    /* Trigger Source Selection for Corresponding Analog Inputs bits 
        01101 = Slave PWM6 Trigger 1 :(ADC Sampling ponit -PG6TRIGA)  */ 
    ADTRIG0Lbits.TRGSRC0 = 0b01101;
    ADTRIG0Lbits.TRGSRC1 = 0b01101;
}

/**
 * <B> Function: HAL_MC2ADCSwitchChannels()  </B>
 * @brief Function to switch ADC channel .
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = HAL_MC2ADCSwitchChannels();
 * </code>
 */
void HAL_MC2ADCSwitchChannels(void)
{
    /* C0CHS[1:0]: Dedicated ADC Core 0 Input Channel Selection bits
        01 = S1ANA0
        00 = S1AN0  */
    ADCON4Hbits.C0CHS = 0b00;
    /* C1CHS[1:0]: Dedicated ADC Core 1 Input Channel Selection bits
        01 = S1ANA1
        00 = S1AN1 */
    ADCON4Hbits.C1CHS = 0b00;
    
    /* Trigger Source Selection for Corresponding Analog Inputs bits 
        00100 = Slave PWM1 Trigger 1 :(ADC Sampling ponit -PG1TRIGA) */ 
    ADTRIG0Lbits.TRGSRC0 = 0b00100;
    ADTRIG0Lbits.TRGSRC1 = 0b00100;
}

/**
 * <B> Function: HAL_MC1MotorInputsRead(MCAPP_MEASURE_T *)  </B>
 * @brief Function to read motor inputs.
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = HAL_MC1MotorInputsRead(&motorInputs);
 * </code>
 */
void HAL_MC1MotorInputsRead(MCAPP_MEASURE_T *pMotorInputs)
{
    pMotorInputs->measureCurrent.Ia = MC1_ADCBUF_IPHASE1;
    pMotorInputs->measureCurrent.Ib = MC1_ADCBUF_IPHASE2;
    pMotorInputs->measureCurrent.Ibus = MC1_ADCBUF_IBUS;
    pMotorInputs->measurePot = MC1_ADCBUF_POT;
    pMotorInputs->measureVdc.value =  MC_ADCBUF_VDC;
    
    HAL_MC1ADCSwitchChannels();
}

/**
 * <B> Function: HAL_MC2MotorInputsRead(MCAPP_MEASURE_T *)  </B>
 * @brief Function to read motor inputs.
 * @param None.
 * @return None.
 * @example
 * <code>
 * status = HAL_MC2MotorInputsRead(pMotorInputs);
 * </code>
 */
void HAL_MC2MotorInputsRead(MCAPP_MEASURE_T *pMotorInputs)
{
    pMotorInputs->measureCurrent.Ia = MC2_ADCBUF_IPHASE1;
    pMotorInputs->measureCurrent.Ib = MC2_ADCBUF_IPHASE2;
    pMotorInputs->measureCurrent.Ibus = MC2_ADCBUF_IBUS;
    pMotorInputs->measureVdc.value =  MC_ADCBUF_VDC;
    
    HAL_MC2ADCSwitchChannels();
}



void HAL_MC1SetVoltageVector(int16_t vector)
{
    /* Overrides PWM based on vector number in the order of c-b-a */
    
    switch(vector)
    {
        case 0:
            /* c-b-a :: 0-0-0 */
            PG3IOCONL = PWM_BOT_ON;
            PG2IOCONL = PWM_BOT_ON;
            PG1IOCONL = PWM_BOT_ON;
        break;
        
        case 1:
            /* c-b-a :: 0-0-1 */
            PG3IOCONL = PWM_BOT_ON;
            PG2IOCONL = PWM_BOT_ON;
            PG1IOCONL = PWM_TOP_ON;
        break;
        
        case 2:
            /* c-b-a :: 0-1-1 */
            PG3IOCONL = PWM_BOT_ON;
            PG2IOCONL = PWM_TOP_ON;
            PG1IOCONL = PWM_TOP_ON;
        break;
        
        case 3:
            /* c-b-a :: 0-1-0 */
            PG3IOCONL = PWM_BOT_ON;
            PG2IOCONL = PWM_TOP_ON;
            PG1IOCONL = PWM_BOT_ON;
        break;
        
        case 4:
            /* c-b-a :: 1-1-0 */
            PG3IOCONL = PWM_TOP_ON;
            PG2IOCONL = PWM_TOP_ON;
            PG1IOCONL = PWM_BOT_ON;
        break;
        
        case 5:
            /* c-b-a :: 1-0-0 */
            PG3IOCONL = PWM_TOP_ON;
            PG2IOCONL = PWM_BOT_ON;
            PG1IOCONL = PWM_BOT_ON;
        break;
        
        case 6:
             /* c-b-a :: 1-0-1 */
            PG3IOCONL = PWM_TOP_ON;
            PG2IOCONL = PWM_BOT_ON;
            PG1IOCONL = PWM_TOP_ON;
        break;
        
        case 7:
            /* c-b-a :: 1-1-1 */
            PG3IOCONL = PWM_TOP_ON;
            PG2IOCONL = PWM_TOP_ON;
            PG1IOCONL = PWM_TOP_ON;
        break;

        default:
            vector = 0;
        break;
    }
}

void HAL_MC2SetVoltageVector(int16_t vector)
{
    /* Overrides PWM based on vector number in the order of c-b-a */
    switch(vector)
    {
        case 0:
            /* c-b-a :: 0-0-0 */
            PG8IOCONL = PWM_BOT_ON;
            PG7IOCONL = PWM_BOT_ON;
            PG6IOCONL = PWM_BOT_ON;
        break;
        
        case 1:
            /* c-b-a :: 0-0-1 */
            PG8IOCONL = PWM_BOT_ON;
            PG7IOCONL = PWM_BOT_ON;
            PG6IOCONL = PWM_TOP_ON;
        break;
        
        case 2:
            /* c-b-a :: 0-1-1 */
            PG8IOCONL = PWM_BOT_ON;
            PG7IOCONL = PWM_TOP_ON;
            PG6IOCONL = PWM_TOP_ON;
        break;
        
        case 3:
            /* c-b-a :: 0-1-0 */
            PG8IOCONL = PWM_BOT_ON;
            PG7IOCONL = PWM_TOP_ON;
            PG6IOCONL = PWM_BOT_ON;
        break;
        
        case 4:
            /* c-b-a :: 1-1-0 */
            PG8IOCONL = PWM_TOP_ON;
            PG7IOCONL = PWM_TOP_ON;
            PG6IOCONL = PWM_BOT_ON;
        break;
        
        case 5:
            /* c-b-a :: 1-0-0 */
            PG8IOCONL = PWM_TOP_ON;
            PG7IOCONL = PWM_BOT_ON;
            PG6IOCONL = PWM_BOT_ON;
        break;
        
        case 6:
             /* c-b-a :: 1-0-1 */
            PG8IOCONL = PWM_TOP_ON;
            PG7IOCONL = PWM_BOT_ON;
            PG6IOCONL = PWM_TOP_ON;
        break;
        
        case 7:
            /* c-b-a :: 1-1-1 */
            PG8IOCONL = PWM_TOP_ON;
            PG7IOCONL = PWM_TOP_ON;
            PG6IOCONL = PWM_TOP_ON;
        break;

        default:
            vector = 0;
        break;
    }
}

// </editor-fold>