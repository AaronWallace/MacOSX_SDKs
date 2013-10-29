/*	NSCoder.h
	Copyright (c) 1993-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSData;

@interface NSCoder : NSObject

- (void)encodeValueOfObjCType:(const char *)type at:(const void *)addr;
- (void)encodeDataObject:(NSData *)data;
- (void)decodeValueOfObjCType:(const char *)type at:(void *)data;
- (NSData *)decodeDataObject;
- (NSInteger)versionForClassName:(NSString *)className;

@end

@interface NSCoder (NSExtendedCoder)
    
- (void)encodeObject:(id)object;
- (void)encodeRootObject:(id)rootObject;
- (void)encodeBycopyObject:(id)anObject;
- (void)encodeByrefObject:(id)anObject;
- (void)encodeConditionalObject:(id)object;
- (void)encodeValuesOfObjCTypes:(const char *)types, ...;
- (void)encodeArrayOfObjCType:(const char *)type count:(NSUInteger)count at:(const void *)array;
- (void)encodeBytes:(const void *)byteaddr length:(NSUInteger)length;

- (id)decodeObject;
- (void)decodeValuesOfObjCTypes:(const char *)types, ...;
- (void)decodeArrayOfObjCType:(const char *)itemType count:(NSUInteger)count at:(void *)array;
- (void *)decodeBytesWithReturnedLength:(NSUInteger *)lengthp;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
- (void)encodePropertyList:(id)aPropertyList;
- (id)decodePropertyList;
#endif

- (void)setObjectZone:(NSZone *)zone;
- (NSZone *)objectZone;

- (unsigned)systemVersion;

#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (BOOL)allowsKeyedCoding;

- (void)encodeObject:(id)objv forKey:(NSString *)key;
- (void)encodeConditionalObject:(id)objv forKey:(NSString *)key;
- (void)encodeBool:(BOOL)boolv forKey:(NSString *)key;
- (void)encodeInt:(int)intv forKey:(NSString *)key;
- (void)encodeInt32:(int32_t)intv forKey:(NSString *)key;
- (void)encodeInt64:(int64_t)intv forKey:(NSString *)key;
- (void)encodeFloat:(float)realv forKey:(NSString *)key;
- (void)encodeDouble:(double)realv forKey:(NSString *)key;
- (void)encodeBytes:(const uint8_t *)bytesp length:(NSUInteger)lenv forKey:(NSString *)key;

- (BOOL)containsValueForKey:(NSString *)key;
- (id)decodeObjectForKey:(NSString *)key;
- (BOOL)decodeBoolForKey:(NSString *)key;
- (int)decodeIntForKey:(NSString *)key;
- (int32_t)decodeInt32ForKey:(NSString *)key;
- (int64_t)decodeInt64ForKey:(NSString *)key;
- (float)decodeFloatForKey:(NSString *)key;
- (double)decodeDoubleForKey:(NSString *)key;
- (const uint8_t *)decodeBytesForKey:(NSString *)key returnedLength:(NSUInteger *)lengthp;   // returned bytes immutable!
#endif

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (void)encodeInteger:(NSInteger)intv forKey:(NSString *)key;
- (NSInteger)decodeIntegerForKey:(NSString *)key;
#endif

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
FOUNDATION_EXPORT NSObject *NXReadNSObjectFromCoder(NSCoder *decoder) DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Given an NSCoder, returns an object previously written with
   NXWriteNSObject(). The returned object is autoreleased. */

@interface NSCoder (NSTypedstreamCompatibility)

- (void)encodeNXObject:(id)object DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Writes old-style object onto the coder. No sharing is done across
   separate -encodeNXObject:. Callers must have implemented an
   -encodeWithCoder:, which parallels the -write: methods, on all of
   their classes which may be touched by this operation. Object's
   -replacementObjectForCoder: compatibility method will take care
   of calling -startArchiving:. */
    
- (id)decodeNXObject DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
/* Reads an object previously written with -encodeNXObject:. No
   sharing is done across separate -decodeNXObject. Callers must
   have implemented an -initWithCoder:, which parallels the -read:
   methods, on all of their classes which may be touched by this
   operation. Object's -awakeAfterUsingCoder: compatibility method
   will take care of calling -awake and -finishUnarchiving. The
   returned object is autoreleased. */

@end
#endif

