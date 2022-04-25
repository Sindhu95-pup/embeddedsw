/******************************************************************************
* Copyright (c) 2019 - 2022 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/


/*****************************************************************************/
/**
*
* @file xplmi_proc.h
*
* This file contains declarations for PROC C file in PLM.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.00  kc   02/07/2019 Initial release
* 1.01  kc   04/09/2019 Added code to register/enable/disable interrupts
*       sn   07/04/2019 Added support for enabling GIC proxy for sysmon
*       kc   07/16/2019 Added PERF macro to print task times
*       kc   07/16/2019 Added logic to determine the IRO frequency
*       kc   08/01/2019 Added PLM and ROM boot times
* 1.02  kc   02/10/2020 Updated scheduler to add/remove tasks
*       ma   02/28/2020 Added support for new error actions
*       kc   03/20/2020 Scheduler frequency is increased to 100ms for QEMU
*       bsv  04/04/2020 Code clean up
*       kc   04/23/2020 Added interrupt support for SEU event
* 1.03  bm   10/14/2020 Code clean up
* 		td   10/19/2020 MISRA C Fixes
* 1.04  td   11/23/2020 MISRA C Rule 10.4 Fixes
*       ma   03/24/2021 Reduced minimum digits of time stamp decimals to 3
*
* </pre>
*
* @note
*
******************************************************************************/

#ifndef XPLMI_PROC_H
#define XPLMI_PROC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "xiomodule.h"
#include "xil_exception.h"
#include "xplmi_gic_interrupts.h"
#include "xplmi_util.h"
#include "xplmi_status.h"

/************************** Constant Definitions *****************************/
#define IOMODULE_DEVICE_ID XPAR_IOMODULE_0_DEVICE_ID
#define MB_IOMODULE_GPO1_PIT1_PRESCALE_SRC_MASK	(0x2U)

/* PMC IRO Frequency related macros */
#define XPLMI_PMC_IRO_FREQ_320_MHZ	(320000000U)
#define XPLMI_PMC_IRO_FREQ_130_MHZ	(130000000U)

/** PIT related macros */
#define XPLMI_PIT1_RESET_VALUE		(0xFFFFFFFDU)
#define XPLMI_PIT2_RESET_VALUE		(0xFFFFFFFEU)
#define XPLMI_PIT1_CYCLE_VALUE		((u64)XPLMI_PIT1_RESET_VALUE + 1U)
#define XPLMI_PIT2_CYCLE_VALUE		(XPLMI_PIT2_RESET_VALUE + 1U)
#define XPLMI_PIT1			(0U)
#define XPLMI_PIT2			(1U)
#define XPLMI_PIT3			(2U)
#define XPLMI_PIT1_SEL			(1U << XPLMI_PIT1)
#define XPLMI_PIT2_SEL			(1U << XPLMI_PIT2)
#define XPLMI_PIT3_SEL			(1U << XPLMI_PIT3)
#define XPLMI_IOMODULE_PMC_PIT3_IRQ	(0x5U)
#define XPLMI_PIT_FREQ_DIVISOR_QEMU	(10U)
#define XPLMI_PIT_FREQ_DIVISOR		(100U)
#define XPLMI_GIGA			(1e9)
#define XPLMI_MEGA			(1e6)
#define XPLMI_MILLI			(1e3)

/**************************** Type Definitions *******************************/
/*
 * PMC IOmodule interrupts
 */
#define XPLMI_IOMODULE_PPU1_HW_INT		(16U)
#define XPLMI_IOMODULE_PPU1_PL_INT		(17U)
#define XPLMI_IOMODULE_ERR_IRQ			(18U)
#define XPLMI_IOMODULE_CFRAME_SEU		(20U)
#define XPLMI_IOMODULE_PMC_IPI			(28U)

#define XPLMI_IOMODULE_MASK			(0xFFU)
#define XPLMI_HW_SW_INTR_MASK			(0xFF00U)
#define XPLMI_HW_SW_INTR_SHIFT			(0x8U)

/* PPU1 HW Interrupts */
#define XPLMI_HW_INT_GIC_IRQ			(0U)

/*
 * External interrupt mapping
 */
enum {
	XPLMI_CFRAME_SEU = 0U,
	XPLMI_IPI_IRQ,	/**< 1U */
	XPLMI_SBI_DATA_RDY, /**< 2U */
	XPLMI_MAX_EXT_INTR, /**< 3U */
};

/*
 * Performance measurement structure
 */
typedef struct {
	u64 TPerfMs;
	u64 TPerfMsFrac;
} XPlmi_PerfTime;

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
int XPlmi_StartTimer(void);
void XPlmi_StopTimer(u8 Timer);
u64 XPlmi_GetTimerValue(void);
int XPlmi_SetUpInterruptSystem(void);
void XPlmi_MeasurePerfTime(u64 TCur, XPlmi_PerfTime *PerfTime);
void XPlmi_PlmIntrEnable(u32 IntrId);
int XPlmi_PlmIntrDisable(u32 IntrId);
int XPlmi_PlmIntrClear(u32 IntrId);
int XPlmi_RegisterHandler(u32 IntrId, GicIntHandler_t Handler, void *Data);
void XPlmi_PrintRomTime(void);
void XPlmi_PrintPlmTimeStamp(void);
void XPlmi_DisableClearIOmodule(void);

/* Handler Table Structure */
struct HandlerTable {
	XInterruptHandler Handler;
};

#ifdef __cplusplus
}
#endif

#endif  /* XPLMI_PROC_H */