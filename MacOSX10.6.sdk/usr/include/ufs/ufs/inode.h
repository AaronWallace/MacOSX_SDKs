/*
 * Copyright (c) 2000-2008 Apple, Inc. All rights reserved.
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
/* Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved */
/*
 * Copyright (c) 1982, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)inode.h	8.9 (Berkeley) 5/14/95
 */
#ifndef _UFS_INDOE_H_
#define _UFS_INDOE_H_

#include <sys/appleapiopts.h>

#ifdef __APPLE_API_PRIVATE
#include <ufs/ufs/dir.h>
#include <ufs/ufs/dinode.h>
#include <sys/queue.h>
#include <sys/event.h>
#include <sys/lock.h>
#include <sys/quota.h>

/*
 * The inode is used to describe each active (or recently active) file in the
 * UFS filesystem. It is composed of two types of information. The first part
 * is the information that is needed only while the file is active (such as
 * the identity of the file and linkage to speed its lookup). The second part
 * is * the permanent meta-data associated with the file which is read in
 * from the permanent dinode from long term storage when the file becomes
 * active, and is put back when the file is no longer being used.
 */
struct inode {
	LIST_ENTRY(inode) i_hash;/* Hash chain. */
	struct	vnode  *i_vnode;/* Vnode associated with this inode. */
	struct	vnode  *i_devvp;/* Vnode for block I/O. */
	u_int32_t i_flag;	/* flags, see below */
	dev_t	  i_dev;	/* Device associated with the inode. */
	ino_t	  i_number;	/* The identity of the inode. */

	union {			/* Associated filesystem. */
		struct	fs *fs;		/* FFS */
	} inode_u;
#define	i_fs	inode_u.fs

	struct	 dquot *i_dquot[MAXQUOTAS]; /* Dquot structures. */
	u_quad_t i_modrev;	/* Revision level for NFS lease. */
	void	 *i_lockf;	/* DEPRECATED */

	/*
	 * Side effects; used during directory lookup.
	 */
	int32_t	  i_count;	/* Size of free slot in directory. */
	doff_t	  i_endoff;	/* End of useful stuff in directory. */
	doff_t	  i_diroff;	/* Offset in dir, where we found last entry. */
	doff_t	  i_offset;	/* Offset of free space in directory. */
	ino_t	  i_ino;	/* Inode number of found directory. */
	u_int32_t i_reclen;	/* Size of found directory entry. */
        daddr_t	  i_lastr;	/* last read... read-ahead */
	/*
	 * The on-disk dinode itself.
	 */
	struct	dinode i_din;	/* 128 bytes of the on-disk dinode. */
};

#define	i_atime		i_din.di_atime
#define	i_atimensec	i_din.di_atimensec
#define	i_blocks	i_din.di_blocks
#define	i_ctime		i_din.di_ctime
#define	i_ctimensec	i_din.di_ctimensec
#define	i_db		i_din.di_db
#define	i_flags		i_din.di_flags
#define	i_gen		i_din.di_gen
#define	i_gid		i_din.di_gid
#define	i_ib		i_din.di_ib
#define	i_mode		i_din.di_mode
#define	i_mtime		i_din.di_mtime
#define	i_mtimensec	i_din.di_mtimensec
#define	i_nlink		i_din.di_nlink
#define	i_rdev		i_din.di_rdev
#define	i_shortlink	i_din.di_shortlink
#define	i_size		i_din.di_size
#define	i_uid		i_din.di_uid
#define	i_spare		i_din.di_spare
#define	i_oldids	i_din.di_u.oldids
#define	i_inumber	i_din.di_u.inumber

/* These flags are kept in i_flag. */
#define	IN_ACCESS	0x0001		/* Access time update request. */
#define	IN_CHANGE	0x0002		/* Inode change time update request. */
#define	IN_UPDATE	0x0004		/* Modification time update request. */
#define	IN_MODIFIED	0x0008		/* Inode has been modified. */
#define	IN_RENAME	0x0010		/* Inode is being renamed. */
#define	IN_SHLOCK	0x0020		/* File has shared lock. */
#define	IN_EXLOCK	0x0040		/* File has exclusive lock. */
#define	IN_TRANSIT	0x0080		/* inode is getting recycled  */
#define	IN_WTRANSIT	0x0100		/* waiting for inode getting recycled  */
#define	IN_ALLOC	0x0200		/* being allocated */
#define	IN_WALLOC	0x0400		/* waiting for allocation to be done */


#endif /* __APPLE_API_PRIVATE */
#endif /* ! _UFS_INDOE_H_ */
