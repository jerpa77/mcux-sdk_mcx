/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/*
 * Motor Control - Configuration File
 */

#ifndef _MC_PERIPH_INIT_H_
#define _MC_PERIPH_INIT_H_

#include "fsl_device_registers.h"
#include "mcdrv_pwm3ph_epwm.h"
#include "mcdrv_adc_mcax.h"
#include "fsl_clock.h"
#include "fsl_lpcmp.h"
#include "fsl_inputmux.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
  
  /* Structure used during clocks and modulo calculations */
typedef struct _clock_setup
{
    uint32_t ui32FastPeripheralClock;
    uint32_t ui32CpuFrequency;
    uint32_t ui32BusClock;
    uint32_t ui32SysPllClock;
    uint16_t ui16M1SpeedLoopFreq;
    uint16_t ui16M1SpeedLoopModulo;
    uint16_t ui16M1PwmFreq;
    uint16_t ui16M1PwmModulo;
    uint16_t ui16M1PwmDeadTime;
} clock_setup_t;   
      
/******************************************************************************
 * Timing
 ******************************************************************************/
#define M1_PWM_FREQ (16000)         /* PWM frequency - 16kHz */
#define M1_FOC_FREQ_VS_PWM_FREQ (1) /* FOC calculation is called every n-th PWM reload */
#define M1_SPEED_LOOP_FREQ (1000)   /* Speed loop frequency */
#define M1_PWM_DEADTIME (500)       /* Output PWM deadtime value in nanoseconds */

#define M1_FAST_LOOP_TS ((float_t)1.0 / (float_t)(M1_PWM_FREQ / M1_FOC_FREQ_VS_PWM_FREQ))
#define M1_SLOW_LOOP_TS ((float_t)1.0 / (float_t)(M1_SLOW_LOOP_FREQ))
#define M1_TIME_ONESEC_COUNT (M1_PWM_FREQ / M1_FOC_FREQ_VS_PWM_FREQ)

/* Fast loop frequency in Hz */
#define M1_FAST_LOOP_FREQ       (M1_PWM_FREQ / M1_FOC_FREQ_VS_PWM_FREQ)
/* Slow control loop frequency */
#define M1_SLOW_LOOP_FREQ       (1000U)

 /******************************************************************************
  * Output control
  ******************************************************************************/
/* Assignment of FTM channels to motor phases */
#define M1_PWM_PAIR_PHA         (0U)
#define M1_PWM_PAIR_PHB         (2U)
#define M1_PWM_PAIR_PHC         (4U)

/* Output PWM deadtime prescaler */
#define M1_PWM_DEADTIME_LENGTH_DTPS     (1U)
/* Output PWM deadtime register value */
#define M1_PWM_DEADTIME_LENGTH_DTVAL    (67U)

/* Over-current Fault enable */
/* For enable Over-current fault is needed connect J6_8 with J1_7 by wire
 (PIO0_23 with PIO0_13) */
#define M1_FAULT_ENABLE         (1U)
/* Over-current Fault detection number */
#define M1_FAULT_NUM            (0U)
/* Over-current Fault detection polarity */
#define M1_FAULT_POL            (0U)
/* Over-current Fault detection threshold */
#define M1_FAULT_CMP_THRESHOLD  (25U)
/* Over-current CMP input channel */   
#define CMP_INPUT_CHANNEL       (0U)
/* CMP DAC input channel */ 
#define CMP_DAC_CHANNEL         (7U)
/* CMP Overcurrent threshold */
#define CMP_THRESHOLD           (250U)

/* DC bus braking resistor control */
#define M1_BRAKE_SET()          
#define M1_BRAKE_CLEAR()        
/* DC bus braking threshold hysteresis */
#define M1_U_DCB_HYSTERESIS             (0.05F)
#define M1_U_DCB_UPPER_THRESHOLD        (frac16_t)((M1_U_DCB_TRIP) * (1.0F + (M1_U_DCB_HYSTERESIS)))
#define M1_U_DCB_LOWER_THRESHOLD        (frac16_t)((M1_U_DCB_TRIP) * (1.0F - (M1_U_DCB_HYSTERESIS)))

/******************************************************************************
 * ADC measurement definition
 ******************************************************************************/
/* Configuration of ADC channels according to the input pin signal */
#define CUR_A_CHANNEL_NUMBER    20U
#define CUR_B_CHANNEL_NUMBER    21U
#define CUR_C_CHANNEL_NUMBER    2U
#define VOLT_DCB_CHANNEL_NUMBER 1U     

/******************************************************************************
 * Define motor ADC control functions
 ******************************************************************************/
#define M1_MCDRV_ADC_GET(par) MCDRV_CurrAndVoltDcBusGet(par)
#define M1_MCDRV_CURR_3PH_CHAN_ASSIGN(par)
#define M1_MCDRV_CURR_3PH_CALIB_INIT(par) (MCDRV_Curr3Ph2ShCalibInit(par))
#define M1_MCDRV_CURR_3PH_CALIB(par) (MCDRV_Curr3Ph2ShCalib(par))
#define M1_MCDRV_CURR_3PH_CALIB_SET(par) (MCDRV_Curr3Ph2ShCalibSet(par))

/******************************************************************************
 * Define 3-ph PWM control functions for motor 1
 ******************************************************************************/
#define M1_MCDRV_PWM_PERIPH_INIT() (M1_InitPWM())
#define M1_MCDRV_PWM3PH_SET(par) (MCDRV_eFlexPwm3PhSet(par))
#define M1_MCDRV_PWM3PH_EN(par) (MCDRV_eFlexPwm3PhOutEn(par))
#define M1_MCDRV_PWM3PH_DIS(par) (MCDRV_eFlexPwm3PhOutDis(par))
#define M1_MCDRV_PWM3PH_FLT_GET(par) (MCDRV_eFlexPwm3PhFltGet(par))
    
/******************************************************************************
 * global variable definitions
 ******************************************************************************/
extern mcdrv_pwm3ph_pwma_t g_sM1Pwm3ph;
extern mcdrv_adc_t g_sM1AdcSensor;

/*******************************************************************************
 * API
 ******************************************************************************/

void MCDRV_Init_M1(void);
void MCDRV_Calib_ADC(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _MC_PERIPH_INIT_H_  */