/*
 * Copyright 2022 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  Standard C Included Files */
#include <string.h>
/*  SDK Included Files */
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i3c_edma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_MASTER             I3C0
#define EXAMPLE_I2C_BAUDRATE       400000
#define EXAMPLE_I3C_OD_BAUDRATE    2000000
#define EXAMPLE_I3C_PP_BAUDRATE    4000000
#define I3C_MASTER_CLOCK_FREQUENCY CLOCK_GetI3CFClkFreq()
#define I3C_MASTER_SLAVE_ADDR_7BIT 0x1E
#define WAIT_TIME                  1000
#define I3C_DATA_LENGTH            33
#define EXAMPLE_DMA                    DMA0
#define EXAMPLE_I3C_TX_DMA_CHANNEL     (0U)
#define EXAMPLE_I3C_RX_DMA_CHANNEL     (1U)
#define EXAMPLE_I3C_TX_DMA_CHANNEL_MUX (kDma0RequestMuxI3c0Tx)
#define EXAMPLE_I3C_RX_DMA_CHANNEL_MUX (kDma0RequestMuxI3c0Rx)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void i3c_master_ibi_callback(I3C_Type *base,
                                    i3c_master_edma_handle_t *handle,
                                    i3c_ibi_type_t ibiType,
                                    i3c_ibi_state_t ibiState);
static void i3c_master_dma_callback(I3C_Type *base, i3c_master_edma_handle_t *handle, status_t status, void *userData);
/*******************************************************************************
 * Variables
 ******************************************************************************/
AT_NONCACHEABLE_SECTION(uint8_t g_master_txBuff[I3C_DATA_LENGTH]);
AT_NONCACHEABLE_SECTION(uint8_t g_master_rxBuff[I3C_DATA_LENGTH]);
uint8_t g_master_ibiBuff[10];
i3c_master_edma_handle_t g_i3c_m_handle;
edma_handle_t g_tx_edma_handle;
edma_handle_t g_rx_edma_handle;
const i3c_master_edma_callback_t masterCallback = {
    .slave2Master = NULL, .ibiCallback = i3c_master_ibi_callback, .transferComplete = i3c_master_dma_callback};
volatile bool g_masterCompletionFlag = false;
volatile bool g_ibiWonFlag           = false;
volatile status_t g_completionStatus = kStatus_Success;
#define I3C_TIME_OUT_INDEX 100000000U
static uint8_t g_ibiUserBuff[10U];
static uint8_t g_ibiUserBuffUsed = 0;
static edma_config_t config;

/*******************************************************************************
 * Code
 ******************************************************************************/
static void i3c_master_ibi_callback(I3C_Type *base,
                                    i3c_master_edma_handle_t *handle,
                                    i3c_ibi_type_t ibiType,
                                    i3c_ibi_state_t ibiState)
{
    switch (ibiType)
    {
        case kI3C_IbiNormal:
            if (ibiState == kI3C_IbiDataBuffNeed)
            {
                handle->ibiBuff = g_master_ibiBuff;
            }
            else
            {
                memcpy(g_ibiUserBuff, (void *)handle->ibiBuff, handle->ibiPayloadSize);
                g_ibiUserBuffUsed = handle->ibiPayloadSize;
            }
            break;

        default:
            assert(false);
            break;
    }
}

static void i3c_master_dma_callback(I3C_Type *base, i3c_master_edma_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        g_masterCompletionFlag = true;
    }

    if (status == kStatus_I3C_IBIWon)
    {
        g_ibiWonFlag = true;
    }

    g_completionStatus = status;
}

int main(void)
{
    status_t result  = kStatus_Success;
    volatile uint32_t timeout = 0U;
    i3c_master_config_t masterConfig;
    i3c_master_transfer_t masterXfer;

    RESET_PeripheralReset(kDMA_RST_SHIFT_RSTn);

    /* Attach 24M clock to I3C */
    CLOCK_SetClockDiv(kCLOCK_DivI3C0_FCLK, 4U);
    CLOCK_AttachClk(kFRO_HF_DIV_to_I3C0FCLK);

    BOARD_InitPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    PRINTF("\r\nI3C board2board EDMA example -- Master transfer.");

    /* I3C mode: Set up i3c master to work in I3C mode, send data to slave. */
    /* First data in txBuff is data length of the transmitting data. */
    g_master_txBuff[0] = I3C_DATA_LENGTH - 1U;
    for (uint32_t i = 1U; i < I3C_DATA_LENGTH; i++)
    {
        g_master_txBuff[i] = i - 1;
    }

    PRINTF("\r\nMaster will send data :");
    for (uint32_t i = 0U; i < I3C_DATA_LENGTH - 1U; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_txBuff[i + 1]);
    }
    PRINTF("\r\n");

    I3C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Hz.i2cBaud          = EXAMPLE_I2C_BAUDRATE;
    masterConfig.baudRate_Hz.i3cPushPullBaud  = EXAMPLE_I3C_PP_BAUDRATE;
    masterConfig.baudRate_Hz.i3cOpenDrainBaud = EXAMPLE_I3C_OD_BAUDRATE;
    masterConfig.enableOpenDrainStop          = false;
    I3C_MasterInit(EXAMPLE_MASTER, &masterConfig, I3C_MASTER_CLOCK_FREQUENCY);

    EDMA_GetDefaultConfig(&config);
#if defined(BOARD_GetEDMAConfig)
    BOARD_GetEDMAConfig(config);
#endif
    EDMA_Init(EXAMPLE_DMA, &config);
    EDMA_CreateHandle(&g_tx_edma_handle, EXAMPLE_DMA, EXAMPLE_I3C_TX_DMA_CHANNEL);
    EDMA_CreateHandle(&g_rx_edma_handle, EXAMPLE_DMA, EXAMPLE_I3C_RX_DMA_CHANNEL);
    EDMA_SetChannelMux(EXAMPLE_DMA, 0, EXAMPLE_I3C_TX_DMA_CHANNEL_MUX);
    EDMA_SetChannelMux(EXAMPLE_DMA, 1, EXAMPLE_I3C_RX_DMA_CHANNEL_MUX);

    /* Create I3C handle. */
    I3C_MasterTransferCreateHandleEDMA(EXAMPLE_MASTER, &g_i3c_m_handle, &masterCallback, NULL, &g_rx_edma_handle,
                                       &g_tx_edma_handle);

    PRINTF("\r\nI3C master do dynamic address assignment to the I3C slaves on bus.");

    /* Reset dynamic address before DAA */
    memset(&masterXfer, 0, sizeof(masterXfer));
    masterXfer.slaveAddress   = 0x7EU; /* Broadcast address */
    masterXfer.subaddress     = 0x06U; /* CCC command RSTDAA */
    masterXfer.subaddressSize = 1U;
    masterXfer.direction      = kI3C_Write;
    masterXfer.busType        = kI3C_TypeI3CSdr;
    masterXfer.flags          = kI3C_TransferDefaultFlag;
    masterXfer.ibiResponse    = kI3C_IbiRespAckMandatory;
    result                    = I3C_MasterTransferEDMA(EXAMPLE_MASTER, &g_i3c_m_handle, &masterXfer);
    if (kStatus_Success != result)
    {
        return result;
    }

    timeout = 0U;
    /* Wait for transfer completed. */
    while ((!g_ibiWonFlag) && (!g_masterCompletionFlag) && (g_completionStatus == kStatus_Success) &&
           (++timeout < I3C_TIME_OUT_INDEX))
    {
        __NOP();
    }
    g_ibiWonFlag = false;

    result = g_completionStatus;
    if ((result != kStatus_Success) || (timeout == I3C_TIME_OUT_INDEX))
    {
        return -1;
    }
    g_masterCompletionFlag = false;

    uint8_t addressList[8] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37};
    result                 = I3C_MasterProcessDAA(EXAMPLE_MASTER, addressList, 8);
    if (result != kStatus_Success)
    {
        return -1;
    }

    PRINTF("\r\nI3C master dynamic address assignment done.\r\n");

    uint8_t devCount;
    i3c_device_info_t *devList;
    uint8_t slaveAddr = 0x0U;
    devList           = I3C_MasterGetDeviceListAfterDAA(EXAMPLE_MASTER, &devCount);
    for (uint8_t devIndex = 0; devIndex < devCount; devIndex++)
    {
        if (devList[devIndex].vendorID == 0x123U)
        {
            slaveAddr = devList[devIndex].dynamicAddr;
            break;
        }
    }

    PRINTF("\r\nStart to do I3C master transfer in I3C SDR mode.\r\n");
    memset(&masterXfer, 0, sizeof(masterXfer));

    masterXfer.slaveAddress = slaveAddr;
    masterXfer.data         = g_master_txBuff;
    masterXfer.dataSize     = I3C_DATA_LENGTH;
    masterXfer.direction    = kI3C_Write;
    masterXfer.busType      = kI3C_TypeI3CSdr;
    masterXfer.flags        = kI3C_TransferDefaultFlag;
    masterXfer.ibiResponse  = kI3C_IbiRespAckMandatory;
    result                  = I3C_MasterTransferEDMA(EXAMPLE_MASTER, &g_i3c_m_handle, &masterXfer);
    if (kStatus_Success != result)
    {
        return result;
    }

    timeout = 0U;
    /* Wait for transfer completed. */
    while ((!g_ibiWonFlag) && (!g_masterCompletionFlag) && (g_completionStatus == kStatus_Success) &&
           (++timeout < I3C_TIME_OUT_INDEX))
    {
        __NOP();
    }
    g_ibiWonFlag = false;

    result = g_completionStatus;
    if ((result != kStatus_Success) || (timeout == I3C_TIME_OUT_INDEX))
    {
        return -1;
    }
    g_masterCompletionFlag = false;

    i3c_register_ibi_addr_t ibiRecord = {.address = {slaveAddr}, .ibiHasPayload = true};
    I3C_MasterRegisterIBI(EXAMPLE_MASTER, &ibiRecord);

    PRINTF("\r\nI3C master wait for slave IBI event to notify the slave transmit size.");

    /* Wait for IBI event. */
    timeout = 0U;
    while ((!g_ibiWonFlag) && (++timeout < I3C_TIME_OUT_INDEX))
    {
        __NOP();
    }
    if (timeout == I3C_TIME_OUT_INDEX)
    {
        PRINTF("\r\nTimeout.");
        return -1;
    }
    g_ibiWonFlag       = false;
    g_completionStatus = kStatus_Success;

    PRINTF("\r\nI3C master received slave IBI event, data size %d, value 0x%x.\r\n", g_ibiUserBuffUsed,
           g_ibiUserBuff[0]);

    memset(g_master_rxBuff, 0, I3C_DATA_LENGTH);
    masterXfer.slaveAddress = slaveAddr;
    masterXfer.data         = g_master_rxBuff;
    masterXfer.dataSize     = g_ibiUserBuff[0];
    masterXfer.direction    = kI3C_Read;
    masterXfer.busType      = kI3C_TypeI3CSdr;
    masterXfer.flags        = kI3C_TransferDefaultFlag;
    masterXfer.ibiResponse  = kI3C_IbiRespAckMandatory;
    result                  = I3C_MasterTransferEDMA(EXAMPLE_MASTER, &g_i3c_m_handle, &masterXfer);
    if (kStatus_Success != result)
    {
        return result;
    }

    timeout = 0U;
    /* Wait for transfer completed. */
    while ((!g_ibiWonFlag) && (!g_masterCompletionFlag) && (g_completionStatus == kStatus_Success) &&
           (++timeout < I3C_TIME_OUT_INDEX))
    {
        __NOP();
    }

    result = g_completionStatus;
    if ((result != kStatus_Success) || (timeout == I3C_TIME_OUT_INDEX))
    {
        return -1;
    }
    g_masterCompletionFlag = false;

    for (uint32_t i = 0U; i < g_master_txBuff[0]; i++)
    {
        if (g_master_rxBuff[i] != g_master_txBuff[i + 1])
        {
            PRINTF("\r\nError occurred in the transfer! \r\n");
            return -1;
        }
    }

    PRINTF("\r\nI3C master transfer successful in I3C SDR mode.\r\n");

    while (1)
    {
    }
}