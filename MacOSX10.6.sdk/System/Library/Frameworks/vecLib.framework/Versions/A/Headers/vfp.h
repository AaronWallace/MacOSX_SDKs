/*
     File:       vecLib/vfp.h
 
     Contains:   MathLib style functions for vectors
 
     Version:    vecLib-268.0
 
     Copyright:  � 1999-2010 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VFP__
#define __VFP__

#include <stdint.h>
/*
#ifndef __VECLIBTYPES__
#include <vecLib/vecLibTypes.h>
#endif

*/
#include "vecLibTypes.h"

#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ppc__) || defined(__ppc64__) || defined(__i386__) || defined(__x86_64__)
#if defined _AltiVecPIMLanguageExtensionsAreEnabled || defined __SSE__
/*
�������������������������������������������������������������������������������
                                                                                
    A collection of numerical functions designed to facilitate a wide         
    range of numerical programming for the Altivec Programming model.       
                                                                                
�������������������������������������������������������������������������������
*/

/*
������������������������[ Computational Functions]�����������������������������
                                                                                
    vdivf        C = A � B                                                          
    vsqrtf       B = �A                                                         
    vrsqrtf      B = 1/�A                                                       
                                                                                
�������������������������������������������������������������������������������
*/
/*
 *  vceilf() -- vector ceilf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vceilf( vFloat A )                                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 *  vfloorf()  -- vector floorf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vfloorf( vFloat A )                                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 *  vintf()  -- vector truncf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vintf( vFloat A )                                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/*
 *  vnintf()  -- vector rintf()   (round-to-nearest-even rounding mode)
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vnintf( vFloat A )                                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  vrecf() -- vector reciprocal  1.0f / v
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vrecf( vFloat A )                                            AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  vdivf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vdivf(vFloat A, vFloat B)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vsqrtf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vsqrtf(vFloat X)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vrsqrtf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vrsqrtf(vFloat X)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
��������������������������[ Exponential Functions]�����������������������������
                                                                                
    vexpf       B = Exp(A)                                                      
    vexpm1f     ExpM1(x) = Exp(x) - 1.  But, for small enough arguments,        
                ExpM1(x) is expected to be more accurate than Exp(x) - 1.       
    vlogf       B = Log(A)                                                      
    vlog10f     B = Log10(A)                                                      
    vlog1pf     Log1P = Log(1 + x). But, for small enough arguments,            
                Log1P is expected to be more accurate than Log(1 + x).          
    vlogbf      Extracts the exponent of its argument, as a signed integral     
                value. A subnormal argument is treated as though it were first  
                normalized. Thus:                                               
                1   <=   x * 2^(-logb(x))   <   2                           
    vscalbf     Computes x * 2^n efficently.  This is not normally done by      
                computing 2^n explicitly.                                       
                                                                                
�������������������������������������������������������������������������������
*/
/*
 *  vexpf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vexpf(vFloat X)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vexpm1f()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vexpm1f(vFloat X)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vlogf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vlogf(vFloat X)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  vlogf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vlog10f(vFloat X)                              AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  vlog1pf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vlog1pf(vFloat X)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vlogbf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vlogbf(vFloat X)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vscalbf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vscalbf(vFloat X, vSInt32 n)                                  AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
���������������������������[ Auxiliary Functions]������������������������������
                                                                                
    vfabf           Absolute value is part of the programming model, however    
                    completeness it is included in the library.                 
    vcopysignf      Produces a value with the magnitude of its first argument   
                    and sign of its second argument.  NOTE: the order of the    
                    arguments matches the recommendation of the IEEE 754        
                    floating point standard,  which is opposite from the SANE   
                    copysign function.                                          
    vnextafterf     Computes the next representable value after 'x' in the      
                    direction of 'y'.  if x == y, then y is returned.           
                                                                                
�������������������������������������������������������������������������������
*/
/*
 *  vfabf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vfabf(vFloat v)                                AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vcopysignf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vcopysignf(vFloat arg2, vFloat arg1)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vnextafterf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vnextafterf(vFloat x, vFloat y)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
�����������������������������[ Inquiry Functions]������������������������������
                                                                                
    vclassifyf      Returns one of the FP_� values.                             
    vsignbitf       Non-zero if and only if the sign of the argument x is       
                    negative.  This includes, NaNs, infinities and zeros.       
                                                                                
�������������������������������������������������������������������������������
*/
/*
 *  vclassifyf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32  vclassifyf(vFloat arg)                        AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vsignbitf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32  vsignbitf(vFloat arg)                         AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
�������������������������[ Transcendental Functions]����������������������������
                                                                                
    vsinf           B = Sin(A). 
    vcosf           B = Cos(A).                                                 
    vtanf           B = Tan(A).                                                 
                                                                                
�������������������������������������������������������������������������������
*/
/*
 *  vsinf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vsinf(vFloat arg)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;

/*
 *  vsincosf()   -- simultaneous calculation of sine and cosine of input. (Cheaper than doing these separately.)
 *                  sine_result must be a valid pointer and must be at least 16 byte aligned.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in Accelerate.framework
 */
extern vFloat  vsincosf( vFloat arg, vFloat *sine_result)     AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;


/*
 *  vcosf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vcosf(vFloat arg)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vtanf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vtanf(vFloat arg)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
�������������������������[ Trigonometric Functions]����������������������������
                                                                                
    vasinf      result is in [-pi/2,pi/2].                                      
    vacosf      result is in [0,pi].                                            
    vatanf      result is in [-pi/2,pi/2].                                      
    vatan2f     Computes the arc tangent of y/x in [-pi,pi] using the sign of   
                both arguments to determine the quadrant of the computed value. 
                                                                                
�������������������������������������������������������������������������������
*/
/*
 *  vasinf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vasinf(vFloat arg)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vacosf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vacosf(vFloat arg)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vatanf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vatanf(vFloat arg)                             AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vatan2f()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vatan2f(vFloat arg1, vFloat arg2)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
��������������������������[ Hyperbolic Functions]������������������������������
                                                                                
    vsinhf      Sine Hyperbolic.                                                
    vcoshf      Cosine Hyperbolic.                                              
    vtanhf      Tangent Hyperbolic.                                             
    vasinhf     Arcsine Hyperbolic.
    vacoshf     Arccosine Hyperbolic.
    vatanhf     Atctangent Hyperbolic.
                                                                                
�������������������������������������������������������������������������������
*/
/*
 *  vsinhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vsinhf(vFloat X)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vcoshf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vcoshf(vFloat X)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vtanhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vtanhf(vFloat X)                               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vasinhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vasinhf(vFloat X)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vacoshf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vacoshf(vFloat X)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vatanhf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vatanhf(vFloat X)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
���������������������������[ Remainder Functions]������������������������������
                                                                                
    vfmodf          B = X mod Y.                                                
    vremainderf     IEEE 754 floating point standard for remainder.             
    vremquof        SANE remainder.  It stores into 'quotient' the 7 low-order  
                    bits of the integer quotient x/y, such that:                
                    -127 <= quotient <= 127.                                
                                                                                
�������������������������������������������������������������������������������
*/
/*
 *  vfmodf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vfmodf(vFloat X, vFloat Y)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vremainderf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vremainderf(vFloat X, vFloat Y)                              AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vremquof()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vremquof(vFloat X, vFloat Y, vUInt32 *QUO)                            AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;




/*
������������������������������[ Power Functions]������������������������������
                                                                                
    vipowf          Returns x raised to the integer power of y.                 
    vpowf           Returns x raised to the power of y.  Result is more         
                    accurate than using exp(log(x)*y).                          
                                                                                
�������������������������������������������������������������������������������
*/
/*
 *  vipowf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vipowf(vFloat X, vSInt32 Y)                                   AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


/*
 *  vpowf()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vFloat  vpowf(vFloat X, vFloat Y)                                    AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;



/*
�������������������������������������������������������������������������������
    Useful                                                                      
�������������������������������������������������������������������������������
*/
/*
 *  vtablelookup()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32  vtablelookup(vSInt32 Index_Vect, uint32_t *Table)               AVAILABLE_MAC_OS_X_VERSION_10_0_AND_LATER;


#endif	// defined _AltiVecPIMLanguageExtensionsAreEnabled || defined __SSE__

#endif  /* defined(__ppc__) || defined(__ppc64__) || defined(__i386__) || defined(__x86_64__) */


#ifdef __cplusplus
}
#endif

#endif /* __VFP__ */

