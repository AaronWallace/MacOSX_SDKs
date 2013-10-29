/*	CFData.h
	Copyright (c) 1998-2009, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFDATA__)
#define __COREFOUNDATION_CFDATA__ 1

#include <CoreFoundation/CFBase.h>

CF_EXTERN_C_BEGIN
    
typedef const struct __CFData * CFDataRef;
typedef struct __CFData * CFMutableDataRef;

CF_EXPORT
CFTypeID CFDataGetTypeID(void);

CF_EXPORT
CFDataRef CFDataCreate(CFAllocatorRef allocator, const UInt8 *bytes, CFIndex length);

CF_EXPORT
CFDataRef CFDataCreateWithBytesNoCopy(CFAllocatorRef allocator, const UInt8 *bytes, CFIndex length, CFAllocatorRef bytesDeallocator);
    /* Pass kCFAllocatorNull as bytesDeallocator to assure the bytes aren't freed */

CF_EXPORT
CFDataRef CFDataCreateCopy(CFAllocatorRef allocator, CFDataRef theData);

CF_EXPORT
CFMutableDataRef CFDataCreateMutable(CFAllocatorRef allocator, CFIndex capacity);

CF_EXPORT
CFMutableDataRef CFDataCreateMutableCopy(CFAllocatorRef allocator, CFIndex capacity, CFDataRef theData);

CF_EXPORT
CFIndex CFDataGetLength(CFDataRef theData);

CF_EXPORT
const UInt8 *CFDataGetBytePtr(CFDataRef theData);

CF_EXPORT
UInt8 *CFDataGetMutableBytePtr(CFMutableDataRef theData);

CF_EXPORT
void CFDataGetBytes(CFDataRef theData, CFRange range, UInt8 *buffer); 

CF_EXPORT
void CFDataSetLength(CFMutableDataRef theData, CFIndex length);

CF_EXPORT
void CFDataIncreaseLength(CFMutableDataRef theData, CFIndex extraLength);

CF_EXPORT
void CFDataAppendBytes(CFMutableDataRef theData, const UInt8 *bytes, CFIndex length);

CF_EXPORT
void CFDataReplaceBytes(CFMutableDataRef theData, CFRange range, const UInt8 *newBytes, CFIndex newLength);

CF_EXPORT
void CFDataDeleteBytes(CFMutableDataRef theData, CFRange range);

#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    kCFDataSearchBackwards = 1UL << 0,
    kCFDataSearchAnchored = 1UL << 1
};
#endif
typedef CFOptionFlags CFDataSearchFlags;

CF_EXPORT
CFRange CFDataFind(CFDataRef theData, CFDataRef dataToFind, CFRange searchRange, CFDataSearchFlags compareOptions) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFDATA__ */

