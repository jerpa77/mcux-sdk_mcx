/*
 * Copyright 2023 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v14.0
processor: MCXA153
package_id: MCXA153VLH
mcu_data: ksdk2_0
processor_version: 0.14.4
pin_labels:
- {pin_num: '16', pin_signal: P2_2/TRIG_IN6/LPUART0_RTS_B/LPUART2_TXD/CT_INP12/CT2_MAT2/ADC0_A4/CMP0_IN0, label: ADC0, identifier: ADC0}
- {pin_num: '5', pin_signal: P1_11/WUU0_IN11/TRIG_OUT2/LPUART1_CTS_B/LPI2C0_SCLS/CT2_MAT1/I3C0_PUR/ADC0_A9, label: I3C0_PUR}
- {pin_num: '55', pin_signal: P0_17/LPI2C0_SCL/LPSPI0_PCS3/CT0_MAT1/UTICK_CAP3/I3C0_SCL, label: I3C0_SCL}
- {pin_num: '2', pin_signal: P1_8/WUU0_IN10/LPUART1_RXD/LPI2C0_SDA/CT_INP8/CT0_MAT2/I3C0_SDA, label: UART_RXD, identifier: UART_RXD}
- {pin_num: '38', pin_signal: P3_12/LPUART2_RTS_B/CT1_MAT2/PWM0_X0, label: LED_RED, identifier: LED_RED}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm33_core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '52', peripheral: LPUART0, signal: TX, pin_signal: P0_3/TDI/LPUART0_TXD/LPSPI0_SDO/CT0_MAT1/UTICK_CAP1/CMP0_OUT/CMP1_IN1, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: up, pull_enable: enable, input_buffer: enable, invert_input: normal}
  - {pin_num: '51', peripheral: LPUART0, signal: RX, pin_signal: P0_2/TDO/SWO/LPUART0_RXD/LPSPI0_SCK/CT0_MAT0/UTICK_CAP0/I3C0_PUR, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: up, pull_enable: enable, input_buffer: enable, invert_input: normal}
  - {pin_num: '55', peripheral: I3C0, signal: SCL, pin_signal: P0_17/LPI2C0_SCL/LPSPI0_PCS3/CT0_MAT1/UTICK_CAP3/I3C0_SCL, slew_rate: fast, open_drain: disable, drive_strength: low,
    drive_strength1: normal, pull_select: down, pull_enable: disable, passive_filter: disable, input_buffer: enable, invert_input: normal}
  - {pin_num: '54', peripheral: I3C0, signal: SDA, pin_signal: P0_16/WUU0_IN2/LPI2C0_SDA/LPSPI0_PCS2/CT0_MAT0/UTICK_CAP2/I3C0_SDA, slew_rate: fast, open_drain: disable,
    drive_strength: low, drive_strength1: normal, pull_select: down, pull_enable: disable, passive_filter: disable, pull_value: low, input_buffer: enable, invert_input: normal}
  - {pin_num: '5', peripheral: I3C0, signal: PUR, pin_signal: P1_11/WUU0_IN11/TRIG_OUT2/LPUART1_CTS_B/LPI2C0_SCLS/CT2_MAT1/I3C0_PUR/ADC0_A9, slew_rate: fast, open_drain: disable,
    drive_strength: low, pull_select: down, pull_enable: disable, input_buffer: enable, invert_input: normal}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Write to PORT0: Peripheral clock is enabled */
    CLOCK_EnableClock(kCLOCK_GatePORT0);
    /* Write to PORT1: Peripheral clock is enabled */
    CLOCK_EnableClock(kCLOCK_GatePORT1);
    /* I3C0 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kI3C0_RST_SHIFT_RSTn);
    /* PORT0 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kPORT0_RST_SHIFT_RSTn);
    /* LPUART0 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kLPUART0_RST_SHIFT_RSTn);
    /* PORT1 peripheral is released from reset */
    RESET_ReleasePeripheralReset(kPORT1_RST_SHIFT_RSTn);

    const port_pin_config_t port0_16_pin54_config = {/* Internal pull-up/down resistor is disabled */
                                                     kPORT_PullDisable,
                                                     /* Low internal pull resistor value is selected. */
                                                     kPORT_LowPullResistor,
                                                     /* Fast slew rate is configured */
                                                     kPORT_FastSlewRate,
                                                     /* Passive input filter is disabled */
                                                     kPORT_PassiveFilterDisable,
                                                     /* Open drain output is disabled */
                                                     kPORT_OpenDrainDisable,
                                                     /* Low drive strength is configured */
                                                     kPORT_LowDriveStrength,
                                                     /* Normal drive strength is configured */
                                                     kPORT_NormalDriveStrength,
                                                     /* Pin is configured as I3C0_SDA */
                                                     kPORT_MuxAlt10,
                                                     /* Digital input enabled */
                                                     kPORT_InputBufferEnable,
                                                     /* Digital input is not inverted */
                                                     kPORT_InputNormal,
                                                     /* Pin Control Register fields [15:0] are not locked */
                                                     kPORT_UnlockRegister};
    /* PORT0_16 (pin 54) is configured as I3C0_SDA */
    PORT_SetPinConfig(PORT0, 16U, &port0_16_pin54_config);

    const port_pin_config_t port0_17_pin55_config = {/* Internal pull-up/down resistor is disabled */
                                                     kPORT_PullDisable,
                                                     /* Low internal pull resistor value is selected. */
                                                     kPORT_LowPullResistor,
                                                     /* Fast slew rate is configured */
                                                     kPORT_FastSlewRate,
                                                     /* Passive input filter is disabled */
                                                     kPORT_PassiveFilterDisable,
                                                     /* Open drain output is disabled */
                                                     kPORT_OpenDrainDisable,
                                                     /* Low drive strength is configured */
                                                     kPORT_LowDriveStrength,
                                                     /* Normal drive strength is configured */
                                                     kPORT_NormalDriveStrength,
                                                     /* Pin is configured as I3C0_SCL */
                                                     kPORT_MuxAlt10,
                                                     /* Digital input enabled */
                                                     kPORT_InputBufferEnable,
                                                     /* Digital input is not inverted */
                                                     kPORT_InputNormal,
                                                     /* Pin Control Register fields [15:0] are not locked */
                                                     kPORT_UnlockRegister};
    /* PORT0_17 (pin 55) is configured as I3C0_SCL */
    PORT_SetPinConfig(PORT0, 17U, &port0_17_pin55_config);

    const port_pin_config_t port0_2_pin51_config = {/* Internal pull-up resistor is enabled */
                                                    kPORT_PullUp,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Normal drive strength is configured */
                                                    kPORT_NormalDriveStrength,
                                                    /* Pin is configured as LPUART0_RXD */
                                                    kPORT_MuxAlt2,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT0_2 (pin 51) is configured as LPUART0_RXD */
    PORT_SetPinConfig(PORT0, 2U, &port0_2_pin51_config);

    const port_pin_config_t port0_3_pin52_config = {/* Internal pull-up resistor is enabled */
                                                    kPORT_PullUp,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Normal drive strength is configured */
                                                    kPORT_NormalDriveStrength,
                                                    /* Pin is configured as LPUART0_TXD */
                                                    kPORT_MuxAlt2,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT0_3 (pin 52) is configured as LPUART0_TXD */
    PORT_SetPinConfig(PORT0, 3U, &port0_3_pin52_config);

    const port_pin_config_t port1_11_pin5_config = {/* Internal pull-up/down resistor is disabled */
                                                    kPORT_PullDisable,
                                                    /* Low internal pull resistor value is selected. */
                                                    kPORT_LowPullResistor,
                                                    /* Fast slew rate is configured */
                                                    kPORT_FastSlewRate,
                                                    /* Passive input filter is disabled */
                                                    kPORT_PassiveFilterDisable,
                                                    /* Open drain output is disabled */
                                                    kPORT_OpenDrainDisable,
                                                    /* Low drive strength is configured */
                                                    kPORT_LowDriveStrength,
                                                    /* Normal drive strength is configured */
                                                    kPORT_NormalDriveStrength,
                                                    /* Pin is configured as I3C0_PUR */
                                                    kPORT_MuxAlt10,
                                                    /* Digital input enabled */
                                                    kPORT_InputBufferEnable,
                                                    /* Digital input is not inverted */
                                                    kPORT_InputNormal,
                                                    /* Pin Control Register fields [15:0] are not locked */
                                                    kPORT_UnlockRegister};
    /* PORT1_11 (pin 5) is configured as I3C0_PUR */
    PORT_SetPinConfig(PORT1, 11U, &port1_11_pin5_config);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/