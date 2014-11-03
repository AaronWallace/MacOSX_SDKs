/*
     File:       vecLib/vecLib.h
 
     Contains:   Master include for vecLib framework
 
     Version:    vecLib-423.32
 
     Copyright:  2000-2013 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VECLIB__
#define __VECLIB__


#if !defined __ACCELERATE__
	#if !defined __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED || __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED >= 1040
		#error "<vecLib/vecLib.h> is deprecated.  Please #include <Accelerate/Accelerate.h> and link to Accelerate.framework."
	#endif
#endif

#ifndef __VECLIBTYPES__
#include <vecLib/vecLibTypes.h>
#endif

#ifndef __VBASICOPS__
#include <vecLib/vBasicOps.h>
#endif

#ifndef __VBIGNUM__
#include <vecLib/vBigNum.h>
#endif

#ifndef __VECTOROPS__
#include <vecLib/vectorOps.h>
#endif

#ifndef __VFP__
#include <vecLib/vfp.h>
#endif

#ifndef __VDSP__
#include <vecLib/vDSP.h>
#endif

#if defined __ppc__ || defined __i386__
#ifndef __VDSP_TRANSLATE__
#include <vecLib/vDSP_translate.h>
#endif
#endif

#ifndef CBLAS_H	
#include <vecLib/cblas.h>
#endif

#ifndef __CLAPACK_H
#include <vecLib/clapack.h>
#endif	

#ifndef __VFORCE_H
#include <vecLib/vForce.h>
#endif


#endif /* __VECLIB__ */
