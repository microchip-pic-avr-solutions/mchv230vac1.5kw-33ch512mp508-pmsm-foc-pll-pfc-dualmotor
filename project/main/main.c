#include <xc.h>
#include <libpic30.h>
#include "mcapp_pmsm.h"
#include "clock.h"

#include "board_service.h"
#include "diagnostics.h"
#include "pfc.h"
// *****************************************************************************
/* Function:
   main()

  Summary:
    main() function

  Description:
    program entry point, calls the system initialization function group 
    containing the buttons polling loop

  Precondition:
    None.

  Parameters:
    None

  Returns:
    None.

  Remarks:
    None.
 */
int main(void) 
{
    /* Disable Watch Dog Timer */
    RCONbits.SWDTEN = 0;
    
    MSI1CONbits.MTSIRQ = 0;
      
    /* Routine Program SecondaryCore */
    _program_secondary(1,0,mcapp_pmsm);

    /* Routine to start SecondaryCore */
    _start_secondary();
    
    /* Clock Configuration */
    InitOscillator(); 
    SetupGPIOPorts();
    
#ifdef ENABLE_DIAGNOSTICS
    DiagnosticsInit();
#endif
    HAL_InitPeripherals();

    LED1 = 1;
    PFC_ServiceInit();
    
    while(1)
    {
        
#ifdef ENABLE_DIAGNOSTICS
        DiagnosticsStepMain();
#endif
        BoardService();
        if(IsPressed_Button1())
        {
            
        }
    }
}
/**
* <B> Function: _T1Interrupt  </B>
*
* @brief T1 Interrupt Vector
*        Executes the DiagnosticsStepIsr() for Data visualization 
*        through X2C Scope
*
*/
void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt (void)
{
    #ifdef ENABLE_DIAGNOSTICS
        DiagnosticsStepIsr();
    #endif
    BoardServiceStepIsr();
    TIMER1_InterruptFlagClear();
}
// </editor-fold>