/**
 * ADC Generated Driver File
 * 
 * @file adc.c
 * 
 * @ingroup  adc
 * 
 * @brief This file contains the API implementations for the ADC driver.
 *
 * @version ADC Driver Version 2.0.1
 * 
 * @version ADC Package Version 2.1.0
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <xc.h>
#include "../adc.h"
#include "../adc_types.h"


static void (*ADC_ConversionDoneCallback)(void);
static void (*ADC_ThresholdCallback)(void);

void ADC_Initialize(void)
{
    ADCON0bits.ON = ADC_BIT_CLEAR;
    PIE6bits.ADIE = ADC_BIT_CLEAR;
    PIE6bits.ADTIE = ADC_BIT_CLEAR;
    
    PIR6bits.ADIF = ADC_BIT_CLEAR;
    PIR6bits.ADTIF = ADC_BIT_CLEAR;

    ADC_ConversionDoneCallback = NULL;
    ADC_ThresholdCallback = NULL;

    ADLTHL = (0 << _ADLTHL_ADLTH_POSITION);	/* ADLTH 0x0(0) */
    ADLTHH = (0 << _ADLTHH_ADLTH_POSITION);	/* ADLTH 0x0(0) */
    ADUTHL = (0 << _ADUTHL_ADUTH_POSITION);	/* ADUTH 0x0(0) */
    ADUTHH = (0 << _ADLTHH_ADLTH_POSITION);	/* ADLTH 0x0(0) */
    ADACT = (0 << _ADACT_ADACT_POSITION);	/* ADACT disabled(0) */
    ADCG1A = (0 << _ADCG1A_CGA0_POSITION)	/* CGA0 disabled(0) */
			|(0 << _ADCG1A_CGA1_POSITION)	/* CGA1 disabled(0) */
			|(0 << _ADCG1A_CGA2_POSITION)	/* CGA2 disabled(0) */
			|(0 << _ADCG1A_CGA4_POSITION)	/* CGA4 disabled(0) */
			|(0 << _ADCG1A_CGA5_POSITION);	/* CGA5 disabled(0) */
    ADCG1C = (0 << _ADCG1C_CGC0_POSITION)	/* CGC0 disabled(0) */
			|(0 << _ADCG1C_CGC1_POSITION)	/* CGC1 disabled(0) */
			|(0 << _ADCG1C_CGC2_POSITION)	/* CGC2 disabled(0) */
			|(0 << _ADCG1C_CGC3_POSITION)	/* CGC3 disabled(0) */
			|(0 << _ADCG1C_CGC4_POSITION)	/* CGC4 disabled(0) */
			|(0 << _ADCG1C_CGC5_POSITION);	/* CGC5 disabled(0) */
    ADCON1 = (0 << _ADCON1_ADDSEN_POSITION)	/* ADDSEN disabled(0) */
			|(0 << _ADCON1_ADPCSC_POSITION)	/* ADPCSC internal sampling capacitor and ext i/o pin(0) */
			|(0 << _ADCON1_ADGPOL_POSITION)	/* ADGPOL digital_low(0) */
			|(0 << _ADCON1_ADIPEN_POSITION)	/* ADIPEN disabled(0) */
			|(0 << _ADCON1_ADPPOL_POSITION);	/* ADPPOL Vss(0) */
    ADCON2 = (0 << _ADCON2_ADMD_POSITION)	/* ADMD Basic_mode(0) */
			|(1 << _ADCON2_ADACLR_POSITION)	/* ADACLR enabled(1) */
			|(1 << _ADCON2_ADCRS_POSITION)	/* ADCRS 0x1(1) */
			|(0 << _ADCON2_ADPSIS_POSITION);	/* ADPSIS RES(0) */
    ADCON3 = (0 << _ADCON3_ADTMD_POSITION)	/* ADTMD disabled(0) */
			|(0 << _ADCON3_ADSOI_POSITION)	/* ADSOI ADGO not cleared(0) */
			|(1 << _ADCON3_ADCALC_POSITION);	/* ADCALC Actual result vs setpoint(1) */
    ADSTAT = (0 << _ADSTAT_ADMATH_POSITION);	/* ADMATH registers not updated(0) */
    ADCLK = (7 << _ADCLK_ADCS_POSITION);	/* ADCS FOSC/16(7) */
    ADREF = (0 << _ADREF_ADPREF_POSITION);	/* ADPREF VDD(0) */
    ADPCH = (5 << _ADPCH_ADPCH_POSITION);	/* ADPCH ANA5(5) */
    ADNCH = (58 << _ADNCH_ADNCH_POSITION);	/* ADNCH VSS(58) */
    ADPREL = (0 << _ADPREL_ADPRE_POSITION);	/* ADPRE 0x0(0) */
    ADPREH = (0 << _ADPREH_ADPRE_POSITION);	/* ADPRE 0x0(0) */
    ADACQL = (0 << _ADACQL_ADACQ_POSITION);	/* ADACQ 0x0(0) */
    ADACQH = (0 << _ADACQH_ADACQ_POSITION);	/* ADACQ 0x0(0) */
    ADCAP = (0 << _ADCAP_ADCAP_POSITION);	/* ADCAP Additional uC disabled(0) */
    ADRPT = (0 << _ADRPT_ADRPT_POSITION);	/* ADRPT 0x0(0) */
    ADCNT = (0 << _ADCNT_ADCNT_POSITION);	/* ADCNT 0x0(0) */
    ADRESH = (0 << _ADRESH_ADRES_POSITION);	/* ADRES 0x0(0) */
    ADACCL = (0 << _ADACCL_ADACC_POSITION);	/* ADACC 0x0(0) */
    ADACCH = (0 << _ADACCH_ADACC_POSITION);	/* ADACC 0x0(0) */
    ADACCU = (0 << _ADACCU_ADACC_POSITION);	/* ADACC 0x0(0) */
    ADSTPTL = (0 << _ADSTPTL_ADSTPT_POSITION);	/* ADSTPT 0x0(0) */
    ADSTPTH = (0 << _ADSTPTH_ADSTPT_POSITION);	/* ADSTPT 0x0(0) */

    PIE6bits.ADIE  = ADC_BIT_CLEAR;
    PIE6bits.ADTIE = ADC_BIT_CLEAR;
    
    ADCON0 = (0 << _ADCON0_GO_POSITION)	/* GO stop(0) */
			|(0 << _ADCON0_IC_POSITION)	/* IC single-ended mode(0) */
			|(1 << _ADCON0_FM_POSITION)	/* FM right justified(1) */
			|(0 << _ADCON0_CS_POSITION)	/* CS FOSC(0) */
			|(0 << _ADCON0_CONT_POSITION)	/* CONT disabled(0) */
			|(1 << _ADCON0_ON_POSITION);	/* ON enabled(1) */;
}

void ADC_Deinitialize(void)
{
    ADCON0 = 0x2;
    ADLTHL = 0x0;
    ADLTHH = 0x0;
    ADUTHL = 0x0;
    ADUTHH = 0x0;
    ADACT = 0x0;
    ADCG1A = 0x0;
    ADCG1C = 0x0;
    ADCON1 = 0x0;
    ADCON2 = 0x0;
    ADCON3 = 0x0;
    ADSTAT = 0x0;
    ADCLK = 0x0;
    ADREF = 0x0;
    ADPCH = 0x0;
    ADNCH = 0x0;
    ADPREL = 0x0;
    ADPREH = 0x0;
    ADACQL = 0x0;
    ADACQH = 0x0;
    ADCAP = 0x0;
    ADRPT = 0x0;
    ADCNT = 0x0;
    ADFLTRL = 0x0;
    ADFLTRH = 0x0;
    ADRESH = 0x0;
    ADPREVL = 0x0;
    ADPREVH = 0x0;
    ADACCL = 0x0;
    ADACCH = 0x0;
    ADACCU = 0x0;
    ADSTPTL = 0x0;
    ADSTPTH = 0x0;
    ADERRL = 0x0;
    ADERRH = 0x0;

    PIE6bits.ADIE = ADC_BIT_CLEAR;
    PIE6bits.ADTIE = ADC_BIT_CLEAR;
    
    PIR6bits.ADTIF = ADC_BIT_CLEAR;
    PIR6bits.ADIF = ADC_BIT_CLEAR;
}

void ADC_Enable(void)
{
    ADCON0bits.ON = ADC_BIT_SET;
}

void ADC_Disable(void)
{
    ADCON0bits.ON = ADC_BIT_CLEAR;
}

void ADC_ChannelSelect(adc_channel_t channel)
{
    ADPCH = channel; 
}

void ADC_ConversionStart(void)
{
   ADCON0bits.GO = ADC_BIT_SET;
}

bool ADC_IsConversionDone(void)
{
    return ((bool)(!ADCON0bits.GO));
}

void ADC_ConversionStop(void)
{
    ADCON0bits.GO = ADC_BIT_CLEAR;
}

adc_result_t ADC_ConversionResultGet(void)
{
    return ((adc_result_t)((ADRESH << 8U) | ADRESL));
}

void ADC_ComputationModeSet(adc_computation_mode_t computationMode)
{
    ADCON2bits.ADMD = computationMode;
}

void ADC_ThresholdModeSet(adc_threshold_mode_t thresholdMode)
{
    ADCON3bits.ADTMD = thresholdMode;
}

void ADC_SampleRepeatCountSet(adc_repeat_count_t repeatCount)
{
    ADRPT = repeatCount;
}

void ADC_UpperThresholdSet(adc_threshold_t upperThreshold)
{
    ADUTHH = (uint8_t) ((uint16_t)upperThreshold >> 8U);
    ADUTHL = (uint8_t) upperThreshold;
}

void ADC_LowerThresholdSet(adc_threshold_t lowerThreshold)
{
    ADLTHH = (uint8_t) ((uint16_t)lowerThreshold >> 8U);
    ADLTHL = (uint8_t) lowerThreshold;
}

adc_accumulate_t ADC_AccumulatedResultGet(void)
{
    return (adc_accumulate_t)(((uint32_t)ADACCU << 16U) + ((uint32_t)ADACCH << 8U) + ADACCL);
}

adc_result_t ADC_ChannelSelectAndConvert(adc_channel_t channel)
{
    ADPCH = channel;
    ADCON0bits.CONT = ADC_BIT_CLEAR;
    ADCON0bits.GO = ADC_BIT_SET;
    while(true == ADCON0bits.GO)
    {
    }

    return (adc_result_t)(((ADRESH << 8U) | ADRESL));
}


void ADC_StopOnInterruptEnable(void)
{
    ADCON3bits.ADSOI = ADC_BIT_SET;
}

void ADC_StopOnInterruptDisable(void)
{
    ADCON3bits.ADSOI = ADC_BIT_CLEAR;
}

void ADC_SampleCapacitorDischarge(void)
{
     ADPCH = ADC_CHANNEL_VSS;
}


void ADC_AcquisitionTimeSet(uint16_t acquisitionValue)
{
    ADACQH = (uint8_t)(acquisitionValue >> 8U);
    ADACQL = (uint8_t)(acquisitionValue);
}

void ADC_PrechargeTimeSet(uint16_t prechargeTime)
{
    ADPREH = (uint8_t)(prechargeTime >> 8U);
    ADPREL = (uint8_t)(prechargeTime);
}

adc_repeat_count_t ADC_CurrentConversionCountGet(void)
{
    return ((adc_repeat_count_t)ADCNT);
}

void ADC_AccumulatorClear(void)
{
    ADCON2bits.ADACLR = ADC_BIT_SET;
}

bool ADC_IsAccumulatorClearComplete(void)
{
    return ((bool)(!ADCON2bits.ADACLR));
}

bool ADC_HasAccumulatorOverflowed(void)
{
    return ADSTATbits.ADAOV;
}

adc_result_t ADC_FilterValueGet(void)
{
    return ((adc_result_t)((ADFLTRH << 8U) | ADFLTRL));
}

adc_result_t ADC_PreviousResultGet(void)
{
    return ((adc_result_t)((ADPREVH << 8U) | ADPREVL));
}

void ADC_SetPointDefine(adc_threshold_t setPoint)
{
    ADSTPTH = (uint8_t) ((uint16_t)setPoint >> 8U);
    ADSTPTL = (uint8_t) setPoint;
}

adc_result_t ADC_ErrorCalculationGet(void)
{
    return (adc_result_t)((ADERRH << 8U) | ADERRL);
}

void ADC_DoubleSamplingEnable(void)
{
    ADCON1bits.ADDSEN = ADC_BIT_SET;
}

void ADC_DoubleSamplingDisable(void)
{
    ADCON1bits.ADDSEN = ADC_BIT_CLEAR;
}

void ADC_ContinuousConversionEnable(void)
{
    ADCON0bits.CONT = ADC_BIT_SET;
}

void ADC_ContinuousConversionDisable(void)
{
    ADCON0bits.CONT = ADC_BIT_CLEAR;
}

bool ADC_IsErrorGreaterThanUpperThreshold(void)
{
    return ADSTATbits.ADUTHR;
}

bool ADC_IsErrorLesserThanLowerThreshold(void)
{
    return ADSTATbits.ADLTHR;
}

adc_conversion_stage_t ADC_ConversionStageStatusGet(void)
{
    return (adc_conversion_stage_t)ADSTATbits.ADSTAT;
}

void ADC_ErrorCalculationModeSet(adc_calculation_mode_t errorCalculationMode)
{
    ADCON3bits.ADCALC = errorCalculationMode;    
}  

void ADC_CalculationRightShiftSet(uint8_t rightShiftValue)
{
    ADCON2bits.ADCRS = rightShiftValue;
}

void ADC_ThresholdInterruptFlagClear(void)
{
    PIR6bits.ADTIF = ADC_BIT_CLEAR;
}

bool ADC_IsThresholdInterruptFlagSet(void)
{
    return PIR6bits.ADTIF;
}

void ADC_AutoTriggerSourceSet(adc_trigger_source_t triggerSource)
{
    ADACT = triggerSource;
}

uint8_t ADC_ResolutionGet(void)
{
    return ADC_RESOLUTION;
}

void ADC_ConversionDoneInterruptFlagClear(void)
{
    PIR6bits.ADIF = ADC_BIT_CLEAR;
}

bool ADC_IsConversionDoneInterruptFlagSet(void)
{
    return PIR6bits.ADIF; 
}

void ADC_ConversionDoneCallbackRegister(void (*callback)(void))
{
    ADC_ConversionDoneCallback = callback;
}

void ADC_ThresholdCallbackRegister(void (*callback)(void))
{
    ADC_ThresholdCallback = callback;
}

void ADC_ConversionDoneInterruptEnable(void)
{
    PIE6bits.ADIE = ADC_BIT_SET;
}

void ADC_ConversionDoneInterruptDisable(void)
{
    PIE6bits.ADIE = ADC_BIT_CLEAR;
}

void ADC_ThresholdInterruptEnable(void)
{
    PIE6bits.ADTIE = ADC_BIT_SET;    
}

void ADC_ThresholdInterruptDisable(void)
{
    PIE6bits.ADTIE = ADC_BIT_CLEAR;    
}

void ADC_ISR(void)
{
    PIR6bits.ADIF = ADC_BIT_CLEAR;

    if (NULL != ADC_ConversionDoneCallback)
    {
        ADC_ConversionDoneCallback();
    }
    else
    {
        // Do nothing
    }
}

void ADC_ThresholdISR(void)
{
    PIR6bits.ADTIF = ADC_BIT_CLEAR;

    if (NULL != ADC_ThresholdCallback)
    {
        ADC_ThresholdCallback();
    }
    else
    {
        // Do nothing
    }
}
