/******************************************************************************
*
* Copyright (C) 2014 - 2018 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
*******************************************************************************/
/*****************************************************************************/
/**
*
* @file xsecure_rsa.h
* @addtogroup xsecure_rsa_apis XilSecure RSA APIs
* @{
* @cond xsecure_internal
* This file contains hardware interface related information for RSA device
*
* This driver supports the following features:
*
* - RSA 4096 based decryption
* - verification/authentication of decrypted data
*
* <b>Initialization & Configuration</b>
*
* The Rsa driver instance can be initialized
* in the following way:
*
*   - XSecure_RsaInitialize(XSecure_Rsa *InstancePtr, u8* EncText,
*					u8 *Mod, u8 *ModExt, u8 *ModExpo)
*
* The method used for RSA decryption needs precalculated value off R^2 mod N
* which is generated by bootgen and is present in the signature along with
* modulus and exponent.
*
* @note
*	-The format of the public key( modulus, exponent and precalculated
*	 R^2 mod N should be same as specified by the bootgen
*
*	-For matching, PKCS paddding scheme has to be applied in the manner
*	 specified by the bootgen.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date        Changes
* ----- ---- -------- -------------------------------------------------------
* 1.0   ba   10/10/14 Initial release
* 2.2   vns  07/06/17 Added doxygen tags
*       vns  17/08/17 Added APIs XSecure_RsaPublicEncrypt and
*                     XSecure_RsaPrivateDecrypt.As per functionality
*                     XSecure_RsaPublicEncrypt is same as XSecure_RsaDecrypt.
* 3.1   vns  11/04/18 Added support for 512, 576, 704, 768, 992, 1024, 1152,
*                     1408, 1536, 1984, 3072 key sizes, where previous verision
*                     has support only 2048 and 4096 key sizes.
* 3.2   vns  04/30/18 Added error code XSECURE_RSA_DATA_VALUE_ERROR
* 4.0 	arc  18/12/18 Fixed MISRA-C violations.
*
* </pre>
*
* @endcond
******************************************************************************/

#ifndef XSECURE_RSA_H_
#define XSECURE_RSA_H_

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#include "xsecure_hw.h"
#include "xil_assert.h"
#include "xil_io.h"
#include "xstatus.h"
#include "xplatform_info.h"
/************************** Constant Definitions ****************************/
/** @cond xsecure_internal
@{
*/
/* Key size in bytes */
#define XSECURE_RSA_512_KEY_SIZE	(512U/8U)	 /**< RSA 512 key size */
#define XSECURE_RSA_576_KEY_SIZE	(576U/8U)	 /**< RSA 576 key size */
#define XSECURE_RSA_704_KEY_SIZE	(704U/8U)	 /**< RSA 704 key size */
#define XSECURE_RSA_768_KEY_SIZE	(768U/8U)	 /**< RSA 768 key size */
#define XSECURE_RSA_992_KEY_SIZE	(992U/8U)	 /**< RSA 992 key size */
#define XSECURE_RSA_1024_KEY_SIZE	(1024U/8U) /**< RSA 1024 key size */
#define XSECURE_RSA_1152_KEY_SIZE	(1152U/8U) /**< RSA 1152 key size */
#define XSECURE_RSA_1408_KEY_SIZE	(1408U/8U) /**< RSA 1408 key size */
#define XSECURE_RSA_1536_KEY_SIZE	(1536U/8U) /**< RSA 1536 key size */
#define XSECURE_RSA_1984_KEY_SIZE	(1984U/8U) /**< RSA 1984 key size */
#define XSECURE_RSA_2048_KEY_SIZE	(2048U/8U) /**< RSA 2048 key size */
#define XSECURE_RSA_3072_KEY_SIZE	(3072U/8U) /**< RSA 3072 key size */
#define XSECURE_RSA_4096_KEY_SIZE	(4096U/8U) /**< RSA 4096 key size */

/* Key size in words */
#define XSECURE_RSA_512_SIZE_WORDS	(16)	/**< RSA 512 Size in words */
#define XSECURE_RSA_576_SIZE_WORDS	(18)	/**< RSA 576 Size in words */
#define XSECURE_RSA_704_SIZE_WORDS	(22)	/**< RSA 704 Size in words */
#define XSECURE_RSA_768_SIZE_WORDS	(24)	/**< RSA 768 Size in words */
#define XSECURE_RSA_992_SIZE_WORDS	(31)	/**< RSA 992 Size in words */
#define XSECURE_RSA_1024_SIZE_WORDS	(32)	/**< RSA 1024 Size in words */
#define XSECURE_RSA_1152_SIZE_WORDS	(36)	/**< RSA 1152 Size in words */
#define XSECURE_RSA_1408_SIZE_WORDS	(44)	/**< RSA 1408 Size in words */
#define XSECURE_RSA_1536_SIZE_WORDS	(48)	/**< RSA 1536 Size in words */
#define XSECURE_RSA_1984_SIZE_WORDS	(62)	/**< RSA 1984 Size in words */
#define XSECURE_RSA_2048_SIZE_WORDS	(64)	/**< RSA 2048 Size in words */
#define XSECURE_RSA_3072_SIZE_WORDS	(96)	/**< RSA 3072 Size in words */
#define XSECURE_RSA_4096_SIZE_WORDS	(128U)	/**< RSA 4096 Size in words */

/** @name Control Register
 *
 * The Control register (CR) controls the major functions of the device.
 * It is used to set the function to be implemented by the RSA device in
 * the next iteration.
 *
 * Control Register Bit Definition
 */
#define XSECURE_CSU_RSA_CONTROL_512	(0x00U)	/**< RSA 512 Length Code */
#define XSECURE_CSU_RSA_CONTROL_576	(0x10U)	/**< RSA 576 Length Code */
#define XSECURE_CSU_RSA_CONTROL_704	(0x20U)	/**< RSA 704 Length Code */
#define XSECURE_CSU_RSA_CONTROL_768	(0x30U)	/**< RSA 768 Length Code */
#define XSECURE_CSU_RSA_CONTROL_992	(0x40U)	/**< RSA 992 Length Code */
#define XSECURE_CSU_RSA_CONTROL_1024	(0x50U)	/**< RSA 1024 Length Code */
#define XSECURE_CSU_RSA_CONTROL_1152	(0x60U)	/**< RSA 1152 Length Code */
#define XSECURE_CSU_RSA_CONTROL_1408	(0x70U)	/**< RSA 1408 Length Code */
#define XSECURE_CSU_RSA_CONTROL_1536	(0x80U)	/**< RSA 1536 Length Code */
#define XSECURE_CSU_RSA_CONTROL_1984	(0x90U)	/**< RSA 1984 Length Code */
#define XSECURE_CSU_RSA_CONTROL_2048	(0xA0U) /**< RSA 2048 Length Code */
#define XSECURE_CSU_RSA_CONTROL_3072	(0xB0U) /**< RSA 3072 Length Code */
#define XSECURE_CSU_RSA_CONTROL_4096	(0xC0U) /**< RSA 4096 Length Code */
#define XSECURE_CSU_RSA_CONTROL_DCA	(0x08U) /**< Abort Operation */
#define XSECURE_CSU_RSA_CONTROL_NOP	(0x00U) /**< No Operation */
#define XSECURE_CSU_RSA_CONTROL_EXP	(0x01U) /**< Exponentiation Opcode */
#define XSECURE_CSU_RSA_CONTROL_EXP_PRE	(0x05U) /**< Expo. using R*R mod M */
#define XSECURE_CSU_RSA_CONTROL_MASK	(XSECURE_CSU_RSA_CONTROL_4096 + \
					XSECURE_CSU_RSA_CONTROL_EXP_PRE)
/* @} */

/** @name RSA status Register
 *
 * The Status Register(SR) indicates the current state of RSA device.
 *
 * Status Register Bit Definition
 */
#define XSECURE_CSU_RSA_STATUS_DONE		(0x1U) /**< Operation Done */
#define XSECURE_CSU_RSA_STATUS_BUSY		(0x2U) /**< RSA busy */
#define XSECURE_CSU_RSA_STATUS_ERROR	(0x4U) /**< Error */
#define XSECURE_CSU_RSA_STATUS_PROG_CNT	(0xF8U)  /**< Progress Counter */
/* @}*/

#define XSECURE_CSU_RSA_RAM_EXPO	(0U) /**< bit for RSA RAM Exponent */
#define XSECURE_CSU_RSA_RAM_MOD		(1U) /**< bit for RSA RAM modulus */
#define XSECURE_CSU_RSA_RAM_DIGEST	(2U) /**< bit for RSA RAM Digest */
#define XSECURE_CSU_RSA_RAM_SPAD	(3U) /**< bit for RSA RAM SPAD */
#define XSECURE_CSU_RSA_RAM_RES_Y	(4U) /**< bit for RSA RAM Result(Y) */
#define XSECURE_CSU_RSA_RAM_RES_Q	(5U) /**< bit for RSA RAM Result(Q) */

#define XSECURE_CSU_RSA_RAM_WORDS	(6U) /**< Total Locations in RSA RAM */

#define XSECURE_RSA_FAILED		0x1U /**< RSA Failed Error Code */
#define XSECURE_RSA_DATA_VALUE_ERROR	0x2U /**< for RSA private decryption
						* data should be lesser than
						* modulus */

#define XSECURE_HASH_TYPE_SHA3		(48U) /**< SHA-3 hash size */
#define XSECURE_FSBL_SIG_SIZE		(512U) /**< FSBL signature size */

#define XSECURE_RSA_SIGN_ENC		0U
#define XSECURE_RSA_SIGN_DEC		1U

/***************************** Type Definitions ******************************/
/**
 * The RSA driver instance data structure. A pointer to an instance data
 * structure is passed around by functions to refer to a specific driver
 * instance.
 */
typedef struct {
	u32 BaseAddress; /**< Device Base Address */
	u8* Mod; /**< Modulus */
	u8* ModExt; /**< Precalc. R sq. mod N */
	u8* ModExpo; /**< Exponent */
	u8 EncDec; /**< 0 for signature verification and 1 for generation */
	u32 SizeInWords;/** RSA key size in words */
} XSecure_Rsa;
/**
@}
@endcond */
/***************************** Function Prototypes ***************************/

/* Initialization */
s32  XSecure_RsaInitialize(XSecure_Rsa *InstancePtr, u8 *Mod, u8 *ModExt,
				u8 *ModExpo);

/* RSA Decryption */
s32 XSecure_RsaDecrypt(XSecure_Rsa *InstancePtr, u8* EncText, u8* Result);

/* RSA Signature Validation, assuming PKCS padding */
u32 XSecure_RsaSignVerification(u8 *Signature, u8 *Hash, u32 HashLen);

/* XSecure_RsaPublicEncrypt performs same as XSecure_RsaDecrypt API */
s32 XSecure_RsaPublicEncrypt(XSecure_Rsa *InstancePtr, u8 *Input, u32 Size,
								u8 *Result);

s32 XSecure_RsaPrivateDecrypt(XSecure_Rsa *InstancePtr, u8 *Input, u32 Size,
								u8 *Result);

#ifdef __cplusplus
extern "C" }
#endif

#endif /* XSECURE_RSA_H_ */
/* @} */
