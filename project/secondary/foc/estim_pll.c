// <editor-fold defaultstate="collapsed" desc="Description/Instruction ">
/**
 * @file estim_pll.c
 *
 * @brief This module implements PLL Estimator.
 * This is a sensor-less speed observer based on motor back EMF.
 *
 * Component: ESTIMATOR
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

/* _Q15abs and _Q15sqrt function use */
#include <libq.h>
#include "estim_pll.h"

// </editor-fold>

// <editor-fold defaultstate="collapsed" desc="Definitions ">

// </editor-fold>

/**
* <B> Function: void MCAPP_EstimatorPLLInit(MCAPP_PLL_ESTIMATOR_T *)  </B>
*
* @brief Function to reset PLL Estimator Data Structure variables.
*
* @param    pointer to the data structure containing PLL Estimator parameters.
* @return   none.
* @example
* <CODE> MMCAPP_EstimatorPLLInit(&estimator); </CODE>
*
*/
void MCAPP_EstimatorPLLInit(MCAPP_ESTIMATOR_PLL_T *pEstim)
{
    pEstim->qDiCounter = 0;
    pEstim->qEsdStateVar = 0;
    pEstim->qEsqStateVar = 0;
            
    pEstim->qThetaStateVar = 0;
    pEstim->qTheta = 0;
    
    pEstim->qOmegaFilt = 0;
    pEstim->qOmegaStateVar = 0;
}

/**
* <B> Function: void MCAPP_EstimatorPLL(MCAPP_PLL_ESTIMATOR_T *)  </B>
*
* @brief Observer to determine rotor speed and position based on
* motor parameters and feedbacks.
*
* @param    pointer to the data structure containing PLL Estimator parameters.
* @return   none.
* @example
* <CODE> MCAPP_EstimatorPLL(&estimator); </CODE>
*
*/
void MCAPP_EstimatorPLL(MCAPP_ESTIMATOR_PLL_T *pEstim)
{
    const MCAPP_MOTOR_T *pMotor = pEstim->pMotor;
    const MC_ALPHABETA_T *pIAlphaBeta = pEstim->pIAlphaBeta;
 
    MC_SINCOS_T     estimSinCos;        /* Sine-cosine for estimator */  
    
    int16_t deltaEs;
    
    pEstim->qValpha = pEstim->pVAlphaBeta->alpha;
    pEstim->qVbeta  = pEstim->pVAlphaBeta->beta;
    
    uint16_t index = (pEstim->qDiCounter - 3)&0x0003;
    /* dIalpha = Ialpha-oldIalpha,  dIbeta  = Ibeta-oldIbeta
       For lower speed the granularity of difference is higher - the
       difference is made between 2 sampled values @ 4 ADC ISR cycles */
    if (_Q15abs(pEstim->qOmegaFilt) < pEstim->qThresholdSpeedDerivative) 
    {
        pEstim->qDIalpha = (pIAlphaBeta->alpha - pEstim->qLastIalphaHS[index]);
        /* The current difference can exceed the maximum value per 4 ADC ISR
           cycle .The following limitation assures a limitation per low speed -
           up to the nominal speed */
        if (pEstim->qDIalpha > pEstim->qDIlimitLS) 
        {
            pEstim->qDIalpha = pEstim->qDIlimitLS;
        }
        if (pEstim->qDIalpha < -pEstim->qDIlimitLS) 
        {
            pEstim->qDIalpha = -pEstim->qDIlimitLS;
        }
        pEstim->qVIndalpha = (int16_t) (__builtin_mulss(pMotor->qLsDt,
                pEstim->qDIalpha) >> (pMotor->qLsDtScale+2));

        pEstim->qDIbeta = (pIAlphaBeta->beta - pEstim->qLastIbetaHS[index]);
        /* The current difference can exceed the maximum value per 4 ADC ISR cycle
           the following limitation assures a limitation per low speed - up to
           the nominal speed */
        if (pEstim->qDIbeta > pEstim->qDIlimitLS) 
        {
            pEstim->qDIbeta = pEstim->qDIlimitLS;
        }
        if (pEstim->qDIbeta < -pEstim->qDIlimitLS) 
        {
            pEstim->qDIbeta = -pEstim->qDIlimitLS;
        }
        pEstim->qVIndbeta = (int16_t) (__builtin_mulss(pMotor->qLsDt,
                pEstim->qDIbeta) >> (pMotor->qLsDtScale+2));
    }
    else
    {
        pEstim->qDIalpha = (pIAlphaBeta->alpha - pEstim->qLastIalphaHS[(pEstim->qDiCounter)]);
        /* The current difference can exceed the maximum value per 1 ADC ISR cycle
           the following limitation assures a limitation per high speed - up to
           the maximum speed */
        if (pEstim->qDIalpha > pEstim->qDIlimitHS) 
        {
            pEstim->qDIalpha = pEstim->qDIlimitHS;
        }
        if (pEstim->qDIalpha < -pEstim->qDIlimitHS) 
        {
            pEstim->qDIalpha = -pEstim->qDIlimitHS;
        }
        pEstim->qVIndalpha = (int16_t) (__builtin_mulss(pMotor->qLsDt,
                        pEstim->qDIalpha) >> pMotor->qLsDtScale);

        pEstim->qDIbeta = (pIAlphaBeta->beta - pEstim->qLastIbetaHS[(pEstim->qDiCounter)]);

        /* The current difference can exceed the maximum value per 1 ADC ISR cycle
           the following limitation assures a limitation per high speed - up to
           the maximum speed */
        if (pEstim->qDIbeta > pEstim->qDIlimitHS) 
        {
            pEstim->qDIbeta = pEstim->qDIlimitHS;
        }
        if (pEstim->qDIbeta < -pEstim->qDIlimitHS) 
        {
            pEstim->qDIbeta = -pEstim->qDIlimitHS;
        }
        pEstim->qVIndbeta = (int16_t) (__builtin_mulss(pMotor->qLsDt,
                        pEstim->qDIbeta) >> pMotor->qLsDtScale);
    }    
   
    /* Update the sample history of Ialpha and Ibeta */
    pEstim->qDiCounter = (pEstim->qDiCounter + 1) & 0x0003;
    pEstim->qLastIalphaHS[pEstim->qDiCounter] = pIAlphaBeta->alpha;
    pEstim->qLastIbetaHS[pEstim->qDiCounter] = pIAlphaBeta->beta;

   /* Calculate the BEMF voltage:
    *  Ealphabeta = Valphabeta - Rs*Ialphabeta - Ls*(dIalphabeta/dt)  */
    
    pEstim->BEMFAlphaBeta.alpha =  (pEstim->qValpha 
        -(int16_t) (__builtin_mulss(pMotor->qRs, pIAlphaBeta->alpha) >> pMotor->qRsScale) 
        - pEstim->qVIndalpha);
    
    pEstim->BEMFAlphaBeta.beta =   (pEstim->qVbeta 
        -(int16_t) (__builtin_mulss(pMotor->qRs, pIAlphaBeta->beta) >> pMotor->qRsScale) 
        - pEstim->qVIndbeta);
    
    
    /* Calculate sine and cosine components of the rotor flux angle */
    MC_CalculateSineCosine_Assembly_Ram((pEstim->qTheta ), &estimSinCos);

    /*  Park_BEMF.d =  Clark_BEMF.alpha*cos(Angle) + Clark_BEMF.beta*sin(Rho)
       Park_BEMF.q = -Clark_BEMF.alpha*sin(Angle) + Clark_BEMF.beta*cos(Rho)*/
    MC_TransformPark_Assembly(&pEstim->BEMFAlphaBeta, &estimSinCos, &pEstim->BEMFdq);

    const int16_t ddiff = (int16_t) (pEstim->BEMFdq.d - pEstim->qEsdf);
    pEstim->qEsdStateVar += __builtin_mulss(ddiff, pEstim->qKfilterEsdq);
    pEstim->qEsdf = (int16_t) (pEstim->qEsdStateVar >> 15);

    const int16_t qdiff = (int16_t) (pEstim->BEMFdq.q - pEstim->qEsqf);
    pEstim->qEsqStateVar += __builtin_mulss(qdiff, pEstim->qKfilterEsdq);
    pEstim->qEsqf = (int16_t) (pEstim->qEsqStateVar >> 15);
    
     /*  For stability the condition for low speed */
    if (_Q15abs(pEstim->qOmegaFilt) > pEstim->qThresholdSpeedBEMF) 
    {
        /* At speed greater than decimation speed, calculate the estimated
         * velocity based on:
         * OmegaMr = Invpsi * (Eqfiltered - sgn(Eqfiltered) * Edfiltered)
         */
        if (pEstim->qEsqf > 0) 
        {
            deltaEs = (int16_t) (pEstim->qEsqf - pEstim->qEsdf);
            pEstim->qOmega =  (int16_t) (__builtin_mulss(pEstim->qInvKfiConst,
                                    deltaEs) >> (pEstim->qInvKfiConstScale) );
        } 
        else 
        {
            deltaEs = (int16_t) (pEstim->qEsqf + pEstim->qEsdf);
            pEstim->qOmega = (int16_t) (__builtin_mulss(pEstim->qInvKfiConst,
                                    deltaEs) >> (pEstim->qInvKfiConstScale));
        }
    }        
    /* if estimator speed<decimation speed => condition VelRef<>0 */
    else 
    {
        /* At speed lower than or equal to decimation speed, calculate the estimated
         * velocity based on:
         *  OmegaMr = (1/ke) * (Eqfiltered - sgn(omega) * Edfiltered)
         * to improve stability.
         */
        if (pEstim->qOmegaFilt > 0) 
        {
            deltaEs = (int16_t) (pEstim->qEsqf - pEstim->qEsdf);
            pEstim->qOmega = (int16_t) (__builtin_mulss(pEstim->qInvKfiConst,
                                    deltaEs) >> (pEstim->qInvKfiConstScale));
        } 
        else 
        {
            deltaEs = (int16_t) (pEstim->qEsqf + pEstim->qEsdf);
            pEstim->qOmega = (int16_t) (__builtin_mulss(pEstim->qInvKfiConst,
                                    deltaEs) >> (pEstim->qInvKfiConstScale));
        }
    }
 
     
    /* Integrate the estimated rotor flux velocity to get estimated rotor angle */  
    pEstim->qThetaStateVar += __builtin_mulss(pEstim->qOmega, pEstim->qDeltaT);
    pEstim->qTheta = (int16_t) (pEstim->qThetaStateVar >> 15);
    
            
    /* Filter the estimated  rotor velocity using a first order low-pass filter */
    const int16_t Omegadiff = (int16_t) (pEstim->qOmega - pEstim->qOmegaFilt);
    pEstim->qOmegaStateVar += __builtin_mulss(Omegadiff, pEstim->qOmegaFiltConst);
    pEstim->qOmegaFilt = (int16_t) (pEstim->qOmegaStateVar >> 15);  
}
