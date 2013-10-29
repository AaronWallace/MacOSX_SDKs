/*
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * @OSF_COPYRIGHT@
 */
/*
 * NOTICE: This file was modified by McAfee Research in 2004 to introduce
 * support for mandatory and extensible security protections.  This notice
 * is included in support of clause 2.2 (b) of the Apple Public License,
 * Version 2.0.
 */

#ifndef _PEXPERT_PPC_BOOT_H_
#define _PEXPERT_PPC_BOOT_H_

#define BOOT_LINE_LENGTH        256

/*
 * Video information.. 
 */

struct Boot_Video {
	unsigned long	v_baseAddr;	/* Base address of video memory */
	unsigned long	v_display;	/* Display Code (if Applicable */
	unsigned long	v_rowBytes;	/* Number of bytes per pixel row */
	unsigned long	v_width;	/* Width */
	unsigned long	v_height;	/* Height */
	unsigned long	v_depth;	/* Pixel Depth */
};

typedef struct Boot_Video	Boot_Video;

/* DRAM Bank definitions - describes physical memory layout.
 */
#define	kMaxDRAMBanks	26		/* maximum number of DRAM banks */

struct DRAMBank
{
	unsigned long	base;		/* physical base of DRAM bank */
	unsigned long	size;		/* size of bank */
};
typedef struct DRAMBank DRAMBank;


/* Boot argument structure - passed into Mach kernel at boot time.
 */
#define kBootArgsRevision		2
#define kBootArgsVersion1		1
#define kBootArgsVersion2		2

typedef struct boot_args {
  unsigned short	Revision;	/* Revision of boot_args structure */
  unsigned short	Version;	/* Version of boot_args structure */
  char		CommandLine[BOOT_LINE_LENGTH];	/* Passed in command line */
  DRAMBank	PhysicalDRAM[kMaxDRAMBanks];	/* base and range pairs for the 26 DRAM banks */
  Boot_Video	Video;		/* Video Information */
    unsigned long	machineType;	/* Machine Type (gestalt) */
    void		*deviceTreeP;	/* Base of flattened device tree */
    unsigned long	deviceTreeLength;/* Length of flattened tree */
    unsigned long	topOfKernelData;/* Highest address used in kernel data area */
  void                  *exdata;
  unsigned long         exdatalen;
} boot_args;

extern boot_args passed_args;

#endif /* _PEXPERT_PPC_BOOT_H_ */
