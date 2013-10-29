/*
     File:       vecLib/vBasicOps.h
 
     Contains:   Basic Algebraic Operations for AltiVec
 
     Version:    vecLib-325.4
 
     Copyright:  � 1999-2011 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __VBASICOPS__
#define __VBASICOPS__

#include <stdint.h>
/*
#ifndef __VECLIBTYPES__
#include <vecLib/vecLibTypes.h>
#endif

*/
#include "vecLibTypes.h"

#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ppc__) || defined(__ppc64__) || defined(__i386__) || defined(__x86_64__)
#if defined _AltiVecPIMLanguageExtensionsAreEnabled || defined __SSE2__
/*                                                                                  
  This section is a collection of algebraic functions that uses the AltiVec       
  instruction set, and is designed to facilitate vector processing in             
  mathematical programming. Following table indicates which functions are covered
  by AltiVec instruction set and which ones are performed by vBasicOps library:

Legend:
    H/W   = Hardware
    LIB  = vBasicOps Library
    NRel  = Next Release of vBasicOps Library
    N/A   = Not Applicable

+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
| Data Type/    | U8  | S8  | U16 | S16 | U32 | S32 | U64 | S64 | U128 | S128 |
| Function      |     |     |     |     |     |     |     |     |      |      |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Add        | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  |  LIB |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    AddS       | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Sub        | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    SubS       | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|  Mul(Half)    | LIB | LIB | LIB | LIB | LIB | LIB | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|Mul Even (Full)| H/W | H/W | H/W | H/W | LIB | LIB | LIB | LIB |  N/A |  N/A |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|Mul Odd  (Full)| H/W | H/W | H/W | H/W | LIB | LIB | LIB | LIB |  N/A |  N/A |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Divide     | LIB | LIB | LIB | LIB | LIB | LIB | LIB |NRel | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Shift      | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+
|    Rotate     | H/W | H/W | H/W | H/W | H/W | H/W | LIB | LIB | LIB  | LIB  |
+---------------+-----+-----+-----+-----+-----+-----+-----+-----+------+------+



Following is a short description of functions in this section:
                                                                         
      Add:      It takes two vectors of data elements and adds each element         
                of the second vector to the corresponding element of the first      
                vector and puts the result in the associated data element of the    
                destination register.

      Subtract: It takes two vectors of data elements and subtracts each element    
                of the second vector from the corresponding element of the first    
                vector and puts the result in the associated data element of the    
                destination register.

      Multiply: It takes two vectors of data elements and multiplies each element   
                of the first vector by the corresponding element of the second      
                vector and puts the result in the associated data element of the    
                destination register. 

      Divide:   It takes two vectors of data elements and divides each element      
                of the first vector by the corresponding element of the second      
                vector and puts the result in the associated data element of the    
                destination register. A pointer is passed to the function to get   
                the remainder.

      Shift:    It takes a vector of two 64-bit data elements or one 128-bit
                data element and shifts it to right or left, in a logical or 
                algebraic manner, using a shift factor that is passed as an
                arguement to the function.

      Rotate:   It takes a vector of two 64-bit data elements or one 128-bit
                data element and rotates it to right or left, using a shift 
               factor that is passed as an arguement to the function.


   Following abbreviations are used in the names of functions in this section:   
                                                                                 
      v            Vector                                                        
      U            Unsigned                                                      
      S            Signed                                                        
      8            8-bit                                                         
      16           16-bit                                                        
      32           32-bit                                                        
      64           64-bit                                                        
      128          128-bit                                                       
      Add          Addition                                                      
      AddS         Addition with Saturation                                      
      Sub          Subtraction                                                   
      SubS         Subtraction with Saturation                                   
      Mul          Multiplication                                                
      Divide       Division                                                      
      Half         Half (multiplication, width of result is the same as width of 
                      operands)                                                  
      Full         Full (multiplication, width of result is twice width of each  
                      operand)                                                   
      Even         Multiplication is performed on EVEN data elements of vector   
                      (Please note that Big endian is used. So the left-most     
                      data element is labled as element 0)                       
      Odd          Multiplication is performed on ODD  data elements of vector.  
      A            Algebraic      
      LL           Logical Left     
      LR           Logical Right     
      Shift        Shift by one factor     
      Shift2       Shift by two factors( only apply to 64 bit operation )     
      Rotate       Rotate by one factor     
      Rotate2      Rotate by two factors( only apply to 64 bit operation )     
                                                                                 
*/


/*
 *  vU8Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt8 
vU8Divide(
  vUInt8    vN,
  vUInt8    vD,
  vUInt8 *  vRemainder) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS8Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt8 
vS8Divide(
  vSInt8    vN,
  vSInt8    vD,
  vSInt8 *  vRemainder) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU16Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt16 
vU16Divide(
  vUInt16    vN,
  vUInt16    vD,
  vUInt16 *  vRemainder) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS16Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt16 
vS16Divide(
  vSInt16    vN,
  vSInt16    vD,
  vSInt16 *  vRemainder) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU32Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU32Divide(
  vUInt32    vN,
  vUInt32    vD,
  vUInt32 *  vRemainder) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS32Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS32Divide(
  vSInt32    vN,
  vSInt32    vD,
  vSInt32 *  vRemainder) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU64Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64Divide(
  vUInt32    vN,
  vUInt32    vD,
  vUInt32 *  vRemainder) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64Divide(
  vSInt32    vN,
  vSInt32    vD,
  vSInt32 *  vRemainder) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128Divide(
  vUInt32    vN,
  vUInt32    vD,
  vUInt32 *  vRemainder) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128Divide()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128Divide(
  vSInt32    vN,
  vSInt32    vD,
  vSInt32 *  vRemainder) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  vU8HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt8 
vU8HalfMultiply(
  vUInt8   vA,
  vUInt8   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS8HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt8 
vS8HalfMultiply(
  vSInt8   vA,
  vSInt8   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU16HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt16 
vU16HalfMultiply(
  vUInt16   vA,
  vUInt16   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS16HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt16 
vS16HalfMultiply(
  vSInt16   vA,
  vSInt16   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU32HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU32HalfMultiply(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS32HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS32HalfMultiply(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU32FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU32FullMulEven(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU32FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU32FullMulOdd(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS32FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS32FullMulEven(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS32FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS32FullMulOdd(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU64FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64FullMulEven(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU64FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64FullMulOdd(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU64HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64HalfMultiply(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64HalfMultiply(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64FullMulEven()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64FullMulEven(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64FullMulOdd()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64FullMulOdd(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128HalfMultiply(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128HalfMultiply()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128HalfMultiply(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  vU64Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64Sub(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU64SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64SubS(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128Sub(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128SubS(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64Sub(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128Sub()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128Sub(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64SubS(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128SubS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128SubS(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  vU64Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64Add(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU64AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU64AddS(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128Add(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vU128AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vU128AddS(
  vUInt32   vA,
  vUInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64Add(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS64AddS(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128Add()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128Add(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS128AddS()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vSInt32 
vS128AddS(
  vSInt32   vA,
  vSInt32   vB) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  vU64Neg()
 */  
extern vUInt32 
vU64Neg (
  vUInt32   vA) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vS64Neg()
 */  
extern vSInt32 
vS64Neg (
  vSInt32   vA) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vU1284Neg()
 */  
extern vUInt32 
vU128Neg (
  vUInt32   vA) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vS1284Neg()
 */  
extern vSInt32 
vS128Neg (
  vSInt32   vA) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);



/*
 *  vLL64Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vLL64Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vA64Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vA64Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vLR64Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vLR64Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vLL64Shift2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vLL64Shift2(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vA64Shift2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vA64Shift2(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vLR64Shift2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vLR64Shift2(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vLL128Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vLL128Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vLR128Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vLR128Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_5, __IPHONE_NA);


/*
 *  vA128Shift()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vA128Shift(
  vUInt32   vA,
  vUInt8    vShiftFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  vL64Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vL64Rotate(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vR64Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vR64Rotate(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vL64Rotate2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vL64Rotate2(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vR64Rotate2()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vR64Rotate2(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vL128Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vL128Rotate(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  vR128Rotate()
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in vecLib.framework
 *    CarbonLib:        not in Carbon, but vecLib is compatible with CarbonLib
 *    Non-Carbon CFM:   in vecLib 1.0 and later
 */
extern vUInt32 
vR128Rotate(
  vUInt32   vA,
  vUInt8    vRotateFactor) __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


#endif	// defined _AltiVecPIMLanguageExtensionsAreEnabled || defined __SSE2__

#endif  /* defined(__ppc__) || defined(__ppc64__) || defined(__i386__) || defined(__x86_64__) */


#ifdef __cplusplus
}
#endif

#endif /* __VBASICOPS__ */

