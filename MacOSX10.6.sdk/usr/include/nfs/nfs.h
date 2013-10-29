/*
 * Copyright (c) 2000-2009 Apple Inc.  All rights reserved.
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
 * Copyright (c) 1989, 1993, 1995
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
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
 *	@(#)nfs.h	8.4 (Berkeley) 5/1/95
 * FreeBSD-Id: nfs.h,v 1.32 1997/10/12 20:25:38 phk Exp $
 */

#ifndef _NFS_NFS_H_
#define _NFS_NFS_H_

#include <sys/appleapiopts.h>
#include <sys/cdefs.h>

#ifdef __APPLE_API_PRIVATE
/*
 * Tunable constants for nfs
 */

#define NFS_TICKINTVL	5		/* Desired time for a tick (msec) */
#define NFS_HZ		(hz / nfs_ticks) /* Ticks/sec */
__private_extern__ int nfs_ticks;
#define	NFS_TIMEO	(1 * NFS_HZ)	/* Default timeout = 1 second */
#define	NFS_MINTIMEO	(1 * NFS_HZ)	/* Min timeout to use */
#define	NFS_MAXTIMEO	(60 * NFS_HZ)	/* Max timeout to backoff to */
#define	NFS_MINIDEMTIMEO (5 * NFS_HZ)	/* Min timeout for non-idempotent ops*/
#define	NFS_MAXREXMIT	100		/* Stop counting after this many */
#define	NFS_RETRANS	10		/* Num of retrans for soft mounts */
#define	NFS_TRYLATERDEL	4		/* Initial try later delay (sec) */
#define	NFS_MAXGRPS	16		/* Max. size of groups list */
#define	NFS_MINATTRTIMO 5		/* Attribute cache timeout in sec */
#define	NFS_MAXATTRTIMO 60
#define	NFS_MINDIRATTRTIMO 5		/* directory attribute cache timeout in sec */
#define	NFS_MAXDIRATTRTIMO 60
#define	NFS_IOSIZE	(1024 * 1024)	/* suggested I/O size */
#define	NFS_RWSIZE	32768		/* Def. read/write data size <= 32K */
#define	NFS_WSIZE	NFS_RWSIZE	/* Def. write data size <= 32K */
#define	NFS_RSIZE	NFS_RWSIZE	/* Def. read data size <= 32K */
#define	NFS_DGRAM_WSIZE	8192		/* UDP Def. write data size <= 8K */
#define	NFS_DGRAM_RSIZE	8192		/* UDP Def. read data size <= 8K */
#define NFS_READDIRSIZE	32768		/* Def. readdir size */
#define	NFS_DEFRAHEAD	16		/* Def. read ahead # blocks */
#define	NFS_MAXRAHEAD	128		/* Max. read ahead # blocks */
#define	NFS_DEFMAXASYNCWRITES 	128	/* Def. max # concurrent async write RPCs */
#define	NFS_DEFASYNCTHREAD 	16	/* Def. # nfsiod threads */
#define	NFS_MAXASYNCTHREAD 	64	/* max # nfsiod threads */
#define	NFS_ASYNCTHREADMAXIDLE	60	/* Seconds before idle nfsiods are reaped */
#define	NFS_DEFSTATFSRATELIMIT 	10	/* Def. max # statfs RPCs per second */
#define NFS_REQUESTDELAY	10	/* ms interval to check request queue */
#define NFSRV_DEADSOCKDELAY	5	/* Seconds before dead sockets are reaped */
#define NFSRV_MAXWGATHERDELAY	100	/* Max. write gather delay (msec) */
#ifndef NFSRV_WGATHERDELAY
#define NFSRV_WGATHERDELAY	1	/* Default write gather delay (msec) */
#endif
#define	NFS_DIRBLKSIZ	4096		/* size of NFS directory buffers */
#if defined(KERNEL) && !defined(DIRBLKSIZ)
#define	DIRBLKSIZ	512		/* XXX we used to use ufs's DIRBLKSIZ */
 					/* can't be larger than NFS_FABLKSIZE */
#endif

/* default values for unresponsive mount timeouts */
#define NFS_TPRINTF_INITIAL_DELAY	12
#define NFS_TPRINTF_DELAY		30

/*
 * Oddballs
 */
#define NFS_CMPFH(n, f, s) \
	((n)->n_fhsize == (s) && !bcmp((caddr_t)(n)->n_fhp, (caddr_t)(f), (s)))
#define NFSRV_NDMAXDATA(n) \
		(((n)->nd_vers == NFS_VER3) ? (((n)->nd_nam2) ? \
		 NFS_MAXDGRAMDATA : NFSRV_MAXDATA) : NFS_V2MAXDATA)

/*
 * The IO_METASYNC flag should be implemented for local file systems.
 * (Until then, it is nothin at all.)
 */
#ifndef IO_METASYNC
#define IO_METASYNC	0
#endif

/*
 * Expected allocation sizes for major data structures. If the actual size
 * of the structure exceeds these sizes, then malloc() will be allocating
 * almost twice the memory required. This is used in nfs_init() to warn
 * the sysadmin that the size of a structure should be reduced.
 * (These sizes are always a power of 2. If the kernel malloc() changes
 *  to one that does not allocate space in powers of 2 size, then this all
 *  becomes bunk!).
 * Note that some of these structures come out of there own nfs zones.
*/
#define NFS_NODEALLOC	1024
#define NFS_MNTALLOC	1024
#define NFS_SVCALLOC	512

/*
 * Arguments to mount NFS
 */
#define NFS_ARGSVERSION	6		/* change when nfs_args changes */
struct nfs_args {
	int		version;	/* args structure version number */
	struct sockaddr	*addr;		/* file server address */
	int		addrlen;	/* length of address */
	int		sotype;		/* Socket type */
	int		proto;		/* and Protocol */
	u_char		*fh;		/* File handle to be mounted */
	int		fhsize;		/* Size, in bytes, of fh */
	int		flags;		/* flags */
	int		wsize;		/* write size in bytes */
	int		rsize;		/* read size in bytes */
	int		readdirsize;	/* readdir size in bytes */
	int		timeo;		/* initial timeout in .1 secs */
	int		retrans;	/* times to retry send */
	int		maxgrouplist;	/* Max. size of group list */
	int		readahead;	/* # of blocks to readahead */
	int		leaseterm;	/* obsolete: Term (sec) of lease */
	int		deadthresh;	/* obsolete: Retrans threshold */
	char		*hostname;	/* server's name */
	/* NFS_ARGSVERSION 3 ends here */
	int		acregmin;	/* reg file min attr cache timeout */
	int		acregmax;	/* reg file max attr cache timeout */
	int		acdirmin;	/* dir min attr cache timeout */
	int		acdirmax;	/* dir max attr cache timeout */
	/* NFS_ARGSVERSION 4 ends here */
	uint32_t	auth;		/* security mechanism flavor */
	/* NFS_ARGSVERSION 5 ends here */
	uint32_t	deadtimeout;	/* secs until unresponsive mount considered dead */
};
struct nfs_args5 {
	int		version;	/* args structure version number */
	struct sockaddr	*addr;		/* file server address */
	int		addrlen;	/* length of address */
	int		sotype;		/* Socket type */
	int		proto;		/* and Protocol */
	u_char		*fh;		/* File handle to be mounted */
	int		fhsize;		/* Size, in bytes, of fh */
	int		flags;		/* flags */
	int		wsize;		/* write size in bytes */
	int		rsize;		/* read size in bytes */
	int		readdirsize;	/* readdir size in bytes */
	int		timeo;		/* initial timeout in .1 secs */
	int		retrans;	/* times to retry send */
	int		maxgrouplist;	/* Max. size of group list */
	int		readahead;	/* # of blocks to readahead */
	int		leaseterm;	/* obsolete: Term (sec) of lease */
	int		deadthresh;	/* obsolete: Retrans threshold */
	char		*hostname;	/* server's name */
	/* NFS_ARGSVERSION 3 ends here */
	int		acregmin;	/* reg file min attr cache timeout */
	int		acregmax;	/* reg file max attr cache timeout */
	int		acdirmin;	/* dir min attr cache timeout */
	int		acdirmax;	/* dir max attr cache timeout */
	/* NFS_ARGSVERSION 4 ends here */
	uint32_t	auth;		/* security mechanism flavor */
};
struct nfs_args4 {
	int		version;	/* args structure version number */
	struct sockaddr	*addr;		/* file server address */
	int		addrlen;	/* length of address */
	int		sotype;		/* Socket type */
	int		proto;		/* and Protocol */
	u_char		*fh;		/* File handle to be mounted */
	int		fhsize;		/* Size, in bytes, of fh */
	int		flags;		/* flags */
	int		wsize;		/* write size in bytes */
	int		rsize;		/* read size in bytes */
	int		readdirsize;	/* readdir size in bytes */
	int		timeo;		/* initial timeout in .1 secs */
	int		retrans;	/* times to retry send */
	int		maxgrouplist;	/* Max. size of group list */
	int		readahead;	/* # of blocks to readahead */
	int		leaseterm;	/* obsolete: Term (sec) of lease */
	int		deadthresh;	/* obsolete: Retrans threshold */
	char		*hostname;	/* server's name */
	/* NFS_ARGSVERSION 3 ends here */
	int		acregmin;	/* reg file min attr cache timeout */
	int		acregmax;	/* reg file max attr cache timeout */
	int		acdirmin;	/* dir min attr cache timeout */
	int		acdirmax;	/* dir max attr cache timeout */
};

struct nfs_args3 {
	int		version;	/* args structure version number */
	struct sockaddr	*addr;		/* file server address */
	int		addrlen;	/* length of address */
	int		sotype;		/* Socket type */
	int		proto;		/* and Protocol */
	u_char		*fh;		/* File handle to be mounted */
	int		fhsize;		/* Size, in bytes, of fh */
	int		flags;		/* flags */
	int		wsize;		/* write size in bytes */
	int		rsize;		/* read size in bytes */
	int		readdirsize;	/* readdir size in bytes */
	int		timeo;		/* initial timeout in .1 secs */
	int		retrans;	/* times to retry send */
	int		maxgrouplist;	/* Max. size of group list */
	int		readahead;	/* # of blocks to readahead */
	int		leaseterm;	/* obsolete: Term (sec) of lease */
	int		deadthresh;	/* obsolete: Retrans threshold */
	char		*hostname;	/* server's name */
};


/*
 * NFS mount option flags
 */
#define	NFSMNT_SOFT		0x00000001  /* soft mount (hard is default) */
#define	NFSMNT_WSIZE		0x00000002  /* set write size */
#define	NFSMNT_RSIZE		0x00000004  /* set read size */
#define	NFSMNT_TIMEO		0x00000008  /* set initial timeout */
#define	NFSMNT_RETRANS		0x00000010  /* set number of request retries */
#define	NFSMNT_MAXGRPS		0x00000020  /* set maximum grouplist size */
#define	NFSMNT_INT		0x00000040  /* allow interrupts on hard mount */
#define	NFSMNT_NOCONN		0x00000080  /* Don't Connect the socket */
#define	NFSMNT_NONEGNAMECACHE	0x00000100  /* Don't do negative name caching */
#define	NFSMNT_NFSV3		0x00000200  /* Use NFS Version 3 protocol */
#define	NFSMNT_NFSV4		0x00000400  /* Use NFS Version 4 protocol */
#define	NFSMNT_DUMBTIMR		0x00000800  /* Don't estimate rtt dynamically */
#define	NFSMNT_DEADTIMEOUT	0x00001000  /* unmount after a period of unresponsiveness */
#define	NFSMNT_READAHEAD	0x00002000  /* set read ahead */
#define	NFSMNT_CALLUMNT		0x00004000  /* call MOUNTPROC_UMNT on unmount */
#define	NFSMNT_RESVPORT		0x00008000  /* Allocate a reserved port */
#define	NFSMNT_RDIRPLUS		0x00010000  /* Use Readdirplus for V3 */
#define	NFSMNT_READDIRSIZE	0x00020000  /* Set readdir size */
#define	NFSMNT_NOLOCKS		0x00040000  /* don't support file locking */
#define	NFSMNT_LOCALLOCKS	0x00080000  /* do file locking locally on client */
#define	NFSMNT_ACREGMIN		0x00100000  /* reg min attr cache timeout */
#define	NFSMNT_ACREGMAX		0x00200000  /* reg max attr cache timeout */
#define	NFSMNT_ACDIRMIN		0x00400000  /* dir min attr cache timeout */
#define	NFSMNT_ACDIRMAX		0x00800000  /* dir max attr cache timeout */
#define	NFSMNT_SECFLAVOR	0x01000000  /* Use security flavor */
#define	NFSMNT_SECSYSOK		0x02000000  /* Server can support auth sys */
#define	NFSMNT_MUTEJUKEBOX	0x04000000  /* don't treat jukebox errors as unresponsive */

/*
 * Structures for the nfssvc(2) syscall. Not that anyone but nfsd
 * should ever try and use it.
 */
struct nfsd_args {
	int	sock;		/* Socket to serve */
	caddr_t	name;		/* Client addr for connection based sockets */
	int	namelen;	/* Length of name */
};


/*
 * NFS Server File Handle structures
 */

/* NFS export handle identifies which NFS export */
#define	NFS_FH_VERSION	0x4e580000		/* 'NX00' */
struct nfs_exphandle {
	uint32_t	nxh_version;		/* data structure version */
	uint32_t	nxh_fsid;		/* File System Export ID */
	uint32_t	nxh_expid;		/* Export ID */
	uint16_t	nxh_flags;		/* export handle flags */
	uint8_t		nxh_reserved;		/* future use */
	uint8_t		nxh_fidlen;		/* length of File ID */
};

/* nxh_flags */
#define NXHF_INVALIDFH		0x0001		/* file handle is invalid */

#define	NFS_MAX_FID_SIZE	(NFS_MAX_FH_SIZE - sizeof(struct nfs_exphandle))
#define	NFSV4_MAX_FID_SIZE	(NFSV4_MAX_FH_SIZE - sizeof(struct nfs_exphandle))
#define	NFSV3_MAX_FID_SIZE	(NFSV3_MAX_FH_SIZE - sizeof(struct nfs_exphandle))
#define	NFSV2_MAX_FID_SIZE	(NFSV2_MAX_FH_SIZE - sizeof(struct nfs_exphandle))

/* NFS server internal view of fhandle_t */
/* The first sizeof(fhandle_t) bytes must match what goes into fhandle_t. */
/* (fhp is used to allow use of an external buffer) */
struct nfs_filehandle {
	uint32_t		nfh_len;	/* total length of file handle */
	struct nfs_exphandle	nfh_xh;		/* export handle */
	unsigned char		nfh_fid[NFS_MAX_FID_SIZE]; /* File ID */
	unsigned char		*nfh_fhp;	/* pointer to file handle */
};

/*
 * NFS export data structures
 */

/* Structure to hold an array of security flavors */
#define NX_MAX_SEC_FLAVORS 5
struct nfs_sec {
	int count;
	uint32_t flavors[NX_MAX_SEC_FLAVORS];
}; 

struct nfs_export_net_args {
	uint32_t		nxna_flags;	/* export flags */
	struct xucred		nxna_cred;	/* mapped credential for root/all user */
	struct sockaddr_storage	nxna_addr;	/* net address to which exported */
	struct sockaddr_storage	nxna_mask;	/* mask for net address */
	struct nfs_sec		nxna_sec;	/* security mechanism flavors */
};

struct nfs_export_args {
	uint32_t		nxa_fsid;	/* export FS ID */
	uint32_t		nxa_expid;	/* export ID */
	char			*nxa_fspath;	/* export FS path */
	char			*nxa_exppath;	/* export sub-path */
	uint32_t		nxa_flags;	/* export arg flags */
	uint32_t		nxa_netcount;	/* #entries in ex_nets array */
	struct nfs_export_net_args *nxa_nets;	/* array of net args */
};


/* nfs export arg flags */
#define NXA_DELETE		0x0001	/* delete the specified export(s) */
#define NXA_ADD			0x0002	/* add the specified export(s) */
#define NXA_REPLACE		0x0003	/* delete and add the specified export(s) */
#define NXA_DELETE_ALL		0x0004	/* delete all exports */
#define NXA_OFFLINE		0x0008	/* export is offline */
#define NXA_CHECK		0x0010	/* check if exportable */

/* export option flags */
#define NX_READONLY		0x0001	/* exported read-only */
#define NX_DEFAULTEXPORT	0x0002	/* exported to the world */
#define NX_MAPROOT		0x0004	/* map root access to anon credential */
#define NX_MAPALL		0x0008	/* map all access to anon credential */
#define NX_32BITCLIENTS		0x0020	/* restrict directory cookies to 32 bits */
#define NX_OFFLINE		0x0040	/* export is offline */

/*
 * fs.nfs sysctl(3) export stats record structures
 */
#define NFS_EXPORT_STAT_REC_VERSION 1	/* export stat record version */
#define NFS_USER_STAT_REC_VERSION 1     /* active user list record version */

/* descriptor describing following records */
struct nfs_export_stat_desc
{
	uint32_t rec_vers;		/* version of export stat records */
	uint32_t rec_count;		/* total record count */
}__attribute__((__packed__));

/* export stat record containing path and stat counters */
struct nfs_export_stat_rec {
	char     path[RPCMNT_PATHLEN + 1];
	uint64_t ops;		/* Count of NFS Requests received for this export */
	uint64_t bytes_read;	/* Count of bytes read from this export */
	uint64_t bytes_written;	/* Count of bytes written to this export */
}__attribute__((__packed__));

/* Active user list stat buffer descriptor */
struct nfs_user_stat_desc
{
	uint32_t rec_vers;	/* version of active user stat records */
	uint32_t rec_count;	/* total record count */
}__attribute__((__packed__));

/* Active user list user stat record format */
struct nfs_user_stat_user_rec {
	u_char			rec_type;
	uid_t			uid;
	struct sockaddr_storage	sock;
	uint64_t		ops;
	uint64_t		bytes_read;
	uint64_t		bytes_written;
	uint32_t		tm_start;
	uint32_t		tm_last;
}__attribute__((__packed__));

/* Active user list path record format */
struct nfs_user_stat_path_rec {
	u_char	rec_type;
	char	path[RPCMNT_PATHLEN + 1];
}__attribute__((__packed__));

/* Defines for rec_type field of
 * nfs_user_stat_rec & nfs_user_stat_rec
 * data structures
 */
#define NFS_USER_STAT_USER_REC  0
#define NFS_USER_STAT_PATH_REC  1



/*
 * XXX to allow amd to include nfs.h without nfsproto.h
 */
#ifdef NFS_NPROCS
/*
 * Stats structure
 */
struct nfsstats {
	int	attrcache_hits;
	int	attrcache_misses;
	int	lookupcache_hits;
	int	lookupcache_misses;
	int	direofcache_hits;
	int	direofcache_misses;
	int	biocache_reads;
	int	read_bios;
	int	read_physios;
	int	biocache_writes;
	int	write_bios;
	int	write_physios;
	int	biocache_readlinks;
	int	readlink_bios;
	int	biocache_readdirs;
	int	readdir_bios;
	int	rpccnt[NFS_NPROCS];
	int	rpcretries;
	int	srvrpccnt[NFS_NPROCS];
	int	srvrpc_errs;
	int	srv_errs;
	int	rpcrequests;
	int	rpctimeouts;
	int	rpcunexpected;
	int	rpcinvalid;
	int	srvcache_inproghits;
	int	srvcache_idemdonehits;
	int	srvcache_nonidemdonehits;
	int	srvcache_misses;
	int	srvvop_writes;
	int pageins;
	int pageouts;
};
#endif

/*
 * Flags for nfssvc() system call.
 */
#define	NFSSVC_NFSD	0x004
#define	NFSSVC_ADDSOCK	0x008
#define	NFSSVC_EXPORT	0x200

/*
 * Flags for nfsclnt() system call.
 */
#define NFSCLNT_LOCKDANS	0x200

/*
 * fs.nfs sysctl(3) identifiers
 */
#define NFS_NFSSTATS	1	/* struct: struct nfsstats */
#define NFS_EXPORTSTATS 3	/* gets exported directory stats */
#define NFS_USERSTATS	4	/* gets exported directory active user stats */
#define NFS_USERCOUNT	5	/* gets current count of active nfs users */

#ifndef NFS_WDELAYHASHSIZ
#define	NFS_WDELAYHASHSIZ 16	/* and with this */
#endif

#endif /* __APPLE_API_PRIVATE */

#endif
