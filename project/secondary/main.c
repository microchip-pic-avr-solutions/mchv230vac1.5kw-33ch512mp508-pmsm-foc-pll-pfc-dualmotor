// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file main.c
 *
 * @brief This is the main entry to the application.
 *
 * Component: APPLICATION
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

// <editor-fold defaultstate="collapsed" desc="HEADER FILES ">

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#include "board_service.h"

#include "diagnostics.h"

#include "mc1_service.h"
#include "mc2_service.h"

#include "mc2_user_params.h"
// </editor-fold>

// <editor-fold defaultstate="collapsed" desc=" Global Variables ">

int16_t runCmdMC1, qTargetVelocityMC1;
int16_t runCmdMC2, qTargetVelocityMC2;
// </editor-fold>

/**
* <B> Function: int main (void)  </B>
*
* @brief main() function,entry point of the application.
*
*/
int main (void)
{
    InitOscillator();
    SetupGPIOPorts();
    
    /* Turn on LED1 to indicate the device is programmed */
    LED1 = 1;
        
    /* Initialize Peripherals */
    HAL_InitPeripherals();
    
#ifdef ENABLE_DIAGNOSTICS
    DiagnosticsInit();
#endif
    
    BoardServiceInit();

    MCAPP_MC1ServiceInit();
    MCAPP_MC2ServiceInit();
    
    runCmdMC1  = 0;
    runCmdMC2  = 0;
    
    while(1)
    {
        
    #ifdef ENABLE_DIAGNOSTICS
        DiagnosticsStepMain();
    #endif

    }
}



/**
* <B> Function: _T1Interrupt()  </B>
*
* @brief Timer interrupt 
* 
*/
void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt (void)
{
    BoardService();
            
    if(IsPressed_Button1())
    {
        if(runCmdMC1 == 1)
        {
            runCmdMC1 = 0;
        }
        else
        {
            runCmdMC1 = 1;
        }
    }
    
    LED2 = runCmdMC1;
    
#ifdef ENABLE_SECOND_MOTOR
    if(IsPressed_Button2())
    {
        if(runCmdMC2 == 1)
        {
            runCmdMC2 = 0;
        }
        else
        {
            runCmdMC2 = 1;
        }
    }
#else
    runCmdMC2 = 0;
#endif
	
    qTargetVelocityMC1 = MCAPP_MC1GetTargetVelocity();
    qTargetVelocityMC2 = MCAPP_MC2GetTargetVelocity();
    
    MCAPP_MC1InputBufferSet(runCmdMC1, qTargetVelocityMC1);
    MCAPP_MC2InputBufferSet(runCmdMC2, qTargetVelocityMC2);
    
    BoardServiceStepIsr();
    TIMER1_InterruptFlagClear();
}

/**
* <B> Function: _PWMInterrupt()  </B>
*
* @brief PWM interrupt 
* 
*/
void __attribute__((__interrupt__,no_auto_psv)) _MC1PWMInterrupt()
{
    HAL_MC1PWMDisableOutputs();
    runCmdMC1 = 0;
    MCAPP_MC1ServiceInit();
    ClearMC1PWMIF();
}

/**
* <B> Function: _PWMInterrupt()  </B>
*
* @brief PWM interrupt 
* 
*/
void __attribute__((__interrupt__,no_auto_psv)) _MC2PWMInterrupt()
{
    /*
      HAL_MC2PWMDisableOutputs();
      runCmdMC2 = 0;
      MCAPP_MC2ServiceInit();
     */
    ClearMC2PWMIF();
}