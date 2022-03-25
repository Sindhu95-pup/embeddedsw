/******************************************************************************
* Copyright (c) 2018 - 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

#ifndef XPM_POWERDOMAIN_H_
#define XPM_POWERDOMAIN_H_

#include "xpm_power.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct XPm_PowerDomain XPm_PowerDomain;

#define XPM_POLL_TIMEOUT			(0X1000000U)
#define XPM_DOMAIN_INIT_STATUS_REG		PMC_GLOBAL_PERS_GLOB_GEN_STORAGE0
#define MAX_POWERDOMAINS			6U

/**
 * The power domain node class.  This is the base class for all the power domain
 * classes.
 */
struct XPm_PowerDomainOps {
	XStatus (*InitStart)(XPm_PowerDomain *PwrDomain, const u32 *Args, u32 NumOfArgs);
	XStatus (*InitFinish)(const XPm_PowerDomain *PwrDomain, const u32 *Args, u32 NumOfArgs);
	const u16 InitMask;	/**< Mask to indicate which Ops are present */
};

struct XPm_PowerDomain {
	XPm_Power Power; /**< Power: Power node base class */
	const struct XPm_PowerDomainOps *DomainOps; /**< house cleaning operations */
	u32 Parents[MAX_POWERDOMAINS]; /**< List of Parent Rail Ids */
	u32 Children[MAX_POWERDOMAINS]; /**< List of depedent children Ids */
	u16 InitFlag; /**< Flag to indicate which Ops are performed */
	u32 HcDisableMask; /**< Mask for skipping housecleaning operations */
};

/************************** Function Prototypes ******************************/
XStatus XPmPowerDomain_Init(XPm_PowerDomain *PowerDomain, u32 Id,
			    u32 BaseAddress, XPm_Power *Parent,
			    struct XPm_PowerDomainOps const *Ops);
XStatus XPmPowerDomain_AddParent(u32 Id, const u32 *ParentNodes, u32 NumParents);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* XPM_POWERDOMAIN_H_ */