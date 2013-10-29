/*
 * Copyright (c) 2000-2006 Apple Computer, Inc. All rights reserved.
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
 * Mach Operating System
 * Copyright (c) 1991,1990,1989,1988 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 */
/*
 *	File:	memory_object.h
 *	Author:	Michael Wayne Young
 *
 *	External memory management interface definition.
 */

#ifndef	_MACH_MEMORY_OBJECT_TYPES_H_
#define _MACH_MEMORY_OBJECT_TYPES_H_

/*
 *	User-visible types used in the external memory
 *	management interface:
 */

#include <mach/port.h>
#include <mach/message.h>
#include <mach/vm_prot.h>
#include <mach/vm_sync.h>
#include <mach/vm_types.h>
#include <mach/machine/vm_types.h>

#include <sys/cdefs.h>

#define VM_64_BIT_DATA_OBJECTS

typedef unsigned long long	memory_object_offset_t;
typedef unsigned long long	memory_object_size_t;
typedef natural_t		memory_object_cluster_size_t;
typedef natural_t *		memory_object_fault_info_t;

typedef unsigned long long 	vm_object_id_t;


/*
 * Temporary until real EMMI version gets re-implemented
 */


typedef mach_port_t	memory_object_t;
typedef mach_port_t	memory_object_control_t;


typedef memory_object_t *memory_object_array_t;
					/* A memory object ... */
					/*  Used by the kernel to retrieve */
					/*  or store data */

typedef	mach_port_t	memory_object_name_t;
					/* Used to describe the memory ... */
					/*  object in vm_regions() calls */

typedef mach_port_t	memory_object_default_t;
					/* Registered with the host ... */
					/*  for creating new internal objects */

#define MEMORY_OBJECT_NULL		((memory_object_t) 0)
#define MEMORY_OBJECT_CONTROL_NULL	((memory_object_control_t) 0)
#define MEMORY_OBJECT_NAME_NULL		((memory_object_name_t) 0)
#define MEMORY_OBJECT_DEFAULT_NULL	((memory_object_default_t) 0)


typedef	int		memory_object_copy_strategy_t;
					/* How memory manager handles copy: */
#define		MEMORY_OBJECT_COPY_NONE		0
					/* ... No special support */
#define		MEMORY_OBJECT_COPY_CALL		1
					/* ... Make call on memory manager */
#define		MEMORY_OBJECT_COPY_DELAY 	2
					/* ... Memory manager doesn't
					 *     change data externally.
					 */
#define		MEMORY_OBJECT_COPY_TEMPORARY 	3
					/* ... Memory manager doesn't
					 *     change data externally, and
					 *     doesn't need to see changes.
					 */
#define		MEMORY_OBJECT_COPY_SYMMETRIC 	4
					/* ... Memory manager doesn't
					 *     change data externally,
					 *     doesn't need to see changes,
					 *     and object will not be
					 *     multiply mapped.
					 *
					 *     XXX
					 *     Not yet safe for non-kernel use.
					 */

#define		MEMORY_OBJECT_COPY_INVALID	5
					/* ...	An invalid copy strategy,
					 *	for external objects which
					 *	have not been initialized.
					 *	Allows copy_strategy to be
					 *	examined without also
					 *	examining pager_ready and
					 *	internal.
					 */

typedef	int		memory_object_return_t;
					/* Which pages to return to manager
					   this time (lock_request) */
#define		MEMORY_OBJECT_RETURN_NONE	0
					/* ... don't return any. */
#define		MEMORY_OBJECT_RETURN_DIRTY	1
					/* ... only dirty pages. */
#define		MEMORY_OBJECT_RETURN_ALL	2
					/* ... dirty and precious pages. */
#define		MEMORY_OBJECT_RETURN_ANYTHING	3
					/* ... any resident page. */

/* 
 *	Data lock request flags
 */

#define		MEMORY_OBJECT_DATA_FLUSH 	0x1
#define		MEMORY_OBJECT_DATA_NO_CHANGE	0x2
#define		MEMORY_OBJECT_DATA_PURGE	0x4
#define		MEMORY_OBJECT_COPY_SYNC		0x8
#define		MEMORY_OBJECT_DATA_SYNC		0x10
#define         MEMORY_OBJECT_IO_SYNC           0x20
#define		MEMORY_OBJECT_DATA_FLUSH_ALL	0x40

/*
 *	Types for the memory object flavor interfaces
 */

#define MEMORY_OBJECT_INFO_MAX      (1024) 
typedef int     *memory_object_info_t;      
typedef int	 memory_object_flavor_t;
typedef int      memory_object_info_data_t[MEMORY_OBJECT_INFO_MAX];


#define MEMORY_OBJECT_PERFORMANCE_INFO	11
#define MEMORY_OBJECT_ATTRIBUTE_INFO	14
#define MEMORY_OBJECT_BEHAVIOR_INFO 	15	


struct memory_object_perf_info {
	memory_object_cluster_size_t	cluster_size;
	boolean_t			may_cache;
};

struct memory_object_attr_info {
	memory_object_copy_strategy_t	copy_strategy;
	memory_object_cluster_size_t	cluster_size;
	boolean_t			may_cache_object;
	boolean_t			temporary;
};

struct memory_object_behave_info {
	memory_object_copy_strategy_t	copy_strategy;	
	boolean_t			temporary;
	boolean_t			invalidate;
	boolean_t			silent_overwrite;
	boolean_t			advisory_pageout;
};


typedef struct memory_object_behave_info *memory_object_behave_info_t;
typedef struct memory_object_behave_info memory_object_behave_info_data_t;

typedef struct memory_object_perf_info 	*memory_object_perf_info_t;
typedef struct memory_object_perf_info	memory_object_perf_info_data_t;

typedef struct memory_object_attr_info	*memory_object_attr_info_t;
typedef struct memory_object_attr_info	memory_object_attr_info_data_t;

#define MEMORY_OBJECT_BEHAVE_INFO_COUNT ((mach_msg_type_number_t)	\
                (sizeof(memory_object_behave_info_data_t)/sizeof(int)))
#define MEMORY_OBJECT_PERF_INFO_COUNT	((mach_msg_type_number_t)	\
		(sizeof(memory_object_perf_info_data_t)/sizeof(int)))
#define MEMORY_OBJECT_ATTR_INFO_COUNT	((mach_msg_type_number_t)	\
		(sizeof(memory_object_attr_info_data_t)/sizeof(int)))

#define invalid_memory_object_flavor(f)					\
	(f != MEMORY_OBJECT_ATTRIBUTE_INFO && 				\
	 f != MEMORY_OBJECT_PERFORMANCE_INFO && 			\
	 f != OLD_MEMORY_OBJECT_BEHAVIOR_INFO &&			\
	 f != MEMORY_OBJECT_BEHAVIOR_INFO &&				\
	 f != OLD_MEMORY_OBJECT_ATTRIBUTE_INFO)


/*
 * Used to support options on memory_object_release_name call
 */
#define MEMORY_OBJECT_TERMINATE_IDLE	0x1
#define MEMORY_OBJECT_RESPECT_CACHE	0x2
#define MEMORY_OBJECT_RELEASE_NO_OP	0x4


/* named entry processor mapping options */
/* enumerated */
#define MAP_MEM_NOOP		0
#define MAP_MEM_COPYBACK	1
#define MAP_MEM_IO		2
#define MAP_MEM_WTHRU		3
#define MAP_MEM_WCOMB		4	/* Write combining mode */
					/* aka store gather     */
#define MAP_MEM_INNERWBACK	5

#define GET_MAP_MEM(flags)	\
	((((unsigned int)(flags)) >> 24) & 0xFF)

#define SET_MAP_MEM(caching, flags)	\
	((flags) = ((((unsigned int)(caching)) << 24) \
			& 0xFF000000) | ((flags) & 0xFFFFFF));

/* leave room for vm_prot bits */
#define MAP_MEM_ONLY		0x010000 /* change processor caching  */
#define MAP_MEM_NAMED_CREATE	0x020000 /* create extant object      */
#define MAP_MEM_PURGABLE	0x040000 /* create a purgable VM object */
#define MAP_MEM_NAMED_REUSE	0x080000 /* reuse provided entry if identical */


/*
 *  Universal Page List data structures
 *
 *  A UPL describes a bounded set of physical pages
 *  associated with some range of an object or map
 *  and a snapshot of the attributes associated with
 *  each of those pages.
 */

struct upl_page_info {
	unsigned int	opaque[2];	/* use upl_page_xxx() accessor funcs */
};


typedef struct upl_page_info	upl_page_info_t;
typedef upl_page_info_t		*upl_page_info_array_t;
typedef upl_page_info_array_t	upl_page_list_ptr_t;

typedef uint32_t	upl_offset_t;	/* page-aligned byte offset */
typedef uint32_t	upl_size_t;	/* page-aligned byte size */

/* upl invocation flags */
/* top nibble is used by super upl */

#define UPL_FLAGS_NONE		0x00000000
#define UPL_COPYOUT_FROM	0x00000001
#define UPL_PRECIOUS		0x00000002
#define UPL_NO_SYNC		0x00000004
#define UPL_CLEAN_IN_PLACE	0x00000008
#define UPL_NOBLOCK		0x00000010
#define UPL_RET_ONLY_DIRTY	0x00000020
#define UPL_SET_INTERNAL	0x00000040
#define UPL_QUERY_OBJECT_TYPE	0x00000080
#define UPL_RET_ONLY_ABSENT	0x00000100 /* used only for COPY_FROM = FALSE */
#define UPL_FILE_IO             0x00000200
#define UPL_SET_LITE		0x00000400
#define UPL_SET_INTERRUPTIBLE	0x00000800
#define UPL_SET_IO_WIRE		0x00001000
#define UPL_FOR_PAGEOUT		0x00002000
#define UPL_WILL_BE_DUMPED      0x00004000
#define UPL_FORCE_DATA_SYNC	0x00008000
/* continued after the ticket bits... */

#define UPL_PAGE_TICKET_MASK	0x000F0000
#define UPL_PAGE_TICKET_SHIFT   16

/* ... flags resume here */
#define UPL_BLOCK_ACCESS	0x00100000
#define UPL_ENCRYPT		0x00200000
#define UPL_NOZEROFILL		0x00400000
#define UPL_WILL_MODIFY		0x00800000 /* caller will modify the pages */

#define UPL_NEED_32BIT_ADDR	0x01000000
#define UPL_UBC_MSYNC		0x02000000
#define UPL_UBC_PAGEOUT		0x04000000
#define UPL_UBC_PAGEIN		0x08000000
#define UPL_REQUEST_SET_DIRTY	0x10000000

/* UPL flags known by this kernel */
#define UPL_VALID_FLAGS		0x1FFFFFFF


/* upl abort error flags */
#define UPL_ABORT_RESTART		0x1
#define UPL_ABORT_UNAVAILABLE	0x2
#define UPL_ABORT_ERROR		0x4
#define UPL_ABORT_FREE_ON_EMPTY	0x8  /* only implemented in wrappers */
#define UPL_ABORT_DUMP_PAGES	0x10
#define UPL_ABORT_NOTIFY_EMPTY	0x20
/* deprecated: #define UPL_ABORT_ALLOW_ACCESS	0x40 */
#define UPL_ABORT_REFERENCE	0x80

/* upl pages check flags */
#define UPL_CHECK_DIRTY         0x1


/*
 *  upl pagein/pageout  flags
 *
 * 
 * when I/O is issued from this UPL it should be done synchronously
 */
#define UPL_IOSYNC	0x1

/*
 * the passed in UPL should not have either a commit or abort 
 * applied to it by the underlying layers... the site that
 * created the UPL is responsible for cleaning it up.
 */
#define UPL_NOCOMMIT	0x2

/*
 * turn off any speculative read-ahead applied at the I/O layer
 */
#define UPL_NORDAHEAD	0x4

/*
 * pageout request is targeting a real file
 * as opposed to a swap file.
 */

#define UPL_VNODE_PAGER	0x8
/*
 * this pageout is being originated as part of an explicit
 * memory synchronization operation... no speculative clustering
 * should be applied, only the range specified should be pushed.
 */
#define UPL_MSYNC		0x10

/*
 *
 */
#define UPL_PAGING_ENCRYPTED	0x20

/*
 * this pageout is being originated as part of an explicit
 * memory synchronization operation that is checking for I/O
 * errors and taking it's own action... if an error occurs,
 * just abort the pages back into the cache unchanged
 */
#define UPL_KEEPCACHED		0x40

/*
 * this pageout originated from within cluster_io to deal
 * with a dirty page that hasn't yet been seen by the FS
 * that backs it... tag it so that the FS can take the
 * appropriate action w/r to its locking model since the
 * pageout will reenter the FS for the same file currently
 * being handled in this context.
 */
#define UPL_NESTED_PAGEOUT	0x80

/*
 * we've detected a sequential access pattern and
 * we are speculatively and aggressively pulling
 * pages in... do not count these as real PAGEINs
 * w/r to our hard throttle maintenance
 */
#define UPL_IOSTREAMING		0x100




/* upl commit flags */
#define UPL_COMMIT_FREE_ON_EMPTY	0x1 /* only implemented in wrappers */
#define UPL_COMMIT_CLEAR_DIRTY		0x2
#define UPL_COMMIT_SET_DIRTY		0x4
#define UPL_COMMIT_INACTIVATE		0x8
#define UPL_COMMIT_NOTIFY_EMPTY		0x10
/* deprecated: #define UPL_COMMIT_ALLOW_ACCESS		0x20 */
#define UPL_COMMIT_CS_VALIDATED		0x40
#define UPL_COMMIT_CLEAR_PRECIOUS	0x80
#define UPL_COMMIT_SPECULATE		0x100
#define UPL_COMMIT_FREE_ABSENT		0x200

#define UPL_COMMIT_KERNEL_ONLY_FLAGS	(UPL_COMMIT_CS_VALIDATED | UPL_COMMIT_FREE_ABSENT)

/* flags for return of state from vm_map_get_upl,  vm_upl address space */
/* based call */
#define UPL_DEV_MEMORY			0x1
#define UPL_PHYS_CONTIG			0x2


/* 
 * Flags for the UPL page ops routine.  This routine is not exported
 * out of the kernel at the moment and so the defs live here.
 */
#define UPL_POP_DIRTY		0x1
#define UPL_POP_PAGEOUT		0x2
#define UPL_POP_PRECIOUS		0x4
#define UPL_POP_ABSENT		0x8
#define UPL_POP_BUSY			0x10

#define UPL_POP_PHYSICAL	0x10000000
#define UPL_POP_DUMP		0x20000000
#define UPL_POP_SET		0x40000000
#define UPL_POP_CLR		0x80000000

/* 
 * Flags for the UPL range op routine.  This routine is not exported 
 * out of the kernel at the moemet and so the defs live here.
 */
/*
 * UPL_ROP_ABSENT: Returns the extent of the range presented which
 * is absent, starting with the start address presented    
 */
#define UPL_ROP_ABSENT		0x01
/*
 * UPL_ROP_PRESENT: Returns the extent of the range presented which
 * is present (i.e. resident), starting with the start address presented
 */
#define UPL_ROP_PRESENT		0x02
/*
 * UPL_ROP_DUMP: Dump the pages which are found in the target object
 * for the target range.
 */
#define UPL_ROP_DUMP			0x04


__BEGIN_DECLS

extern boolean_t	upl_page_present(upl_page_info_t *upl, int index);
extern boolean_t	upl_dirty_page(upl_page_info_t *upl, int index);
extern boolean_t	upl_valid_page(upl_page_info_t *upl, int index);
extern void		upl_deallocate(upl_t upl);

__END_DECLS


#endif	/* _MACH_MEMORY_OBJECT_TYPES_H_ */
