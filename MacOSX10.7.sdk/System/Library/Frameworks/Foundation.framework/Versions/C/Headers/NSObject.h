/*	NSObject.h
	Copyright (c) 1994-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSZone.h>

@class NSInvocation, NSMethodSignature, NSCoder, NSString, NSEnumerator;
@class Protocol;

/***************	Basic protocols		***************/

@protocol NSObject

- (BOOL)isEqual:(id)object;
- (NSUInteger)hash;

- (Class)superclass;
- (Class)class;
- (id)self;
- (NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

- (id)performSelector:(SEL)aSelector;
- (id)performSelector:(SEL)aSelector withObject:(id)object;
- (id)performSelector:(SEL)aSelector withObject:(id)object1 withObject:(id)object2;

- (BOOL)isProxy;

- (BOOL)isKindOfClass:(Class)aClass;
- (BOOL)isMemberOfClass:(Class)aClass;
- (BOOL)conformsToProtocol:(Protocol *)aProtocol;

- (BOOL)respondsToSelector:(SEL)aSelector;

- (id)retain NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
- (oneway void)release NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
- (id)autorelease NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
- (NSUInteger)retainCount NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

- (NSString *)description;

@end

@protocol NSCopying

- (id)copyWithZone:(NSZone *)zone;

@end

@protocol NSMutableCopying

- (id)mutableCopyWithZone:(NSZone *)zone;

@end

@protocol NSCoding

- (void)encodeWithCoder:(NSCoder *)aCoder;
- (id)initWithCoder:(NSCoder *)aDecoder;

@end

/***********	Base class		***********/

@interface NSObject <NSObject> {
    Class	isa;
}

+ (void)load;

+ (void)initialize;
- (id)init;

+ (id)new;
+ (id)allocWithZone:(NSZone *)zone;
+ (id)alloc;
- (void)dealloc;

- (void)finalize;

- (id)copy;
- (id)mutableCopy;

+ (id)copyWithZone:(NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
+ (id)mutableCopyWithZone:(NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

+ (Class)superclass;
+ (Class)class;
+ (BOOL)instancesRespondToSelector:(SEL)aSelector;
+ (BOOL)conformsToProtocol:(Protocol *)protocol;
- (IMP)methodForSelector:(SEL)aSelector;
+ (IMP)instanceMethodForSelector:(SEL)aSelector;
- (void)doesNotRecognizeSelector:(SEL)aSelector;

- (id)forwardingTargetForSelector:(SEL)aSelector;
- (void)forwardInvocation:(NSInvocation *)anInvocation;
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector;

+ (NSMethodSignature *)instanceMethodSignatureForSelector:(SEL)aSelector;

- (BOOL)allowsWeakReference NS_UNAVAILABLE;
- (BOOL)retainWeakReference NS_UNAVAILABLE;

+ (NSString *)description;

+ (BOOL)isSubclassOfClass:(Class)aClass;

+ (BOOL)resolveClassMethod:(SEL)sel NS_AVAILABLE(10_5, 2_0);
+ (BOOL)resolveInstanceMethod:(SEL)sel NS_AVAILABLE(10_5, 2_0);

@end

@interface NSObject (NSCoderMethods)

+ (NSInteger)version;
+ (void)setVersion:(NSInteger)aVersion;
- (Class)classForCoder;
- (id)replacementObjectForCoder:(NSCoder *)aCoder;
- (id)awakeAfterUsingCoder:(NSCoder *)aDecoder;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSObject (NSDeprecatedMethods)

+ (void)poseAsClass:(Class)aClass NS_DEPRECATED(10_0, 10_5, 2_0, 2_0)
#if __OBJC2__
UNAVAILABLE_ATTRIBUTE
#endif
;

@end
#endif


/***********	Discardable Content		***********/

@protocol NSDiscardableContent
#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
@required
- (BOOL)beginContentAccess;
- (void)endContentAccess;
- (void)discardContentIfPossible;
- (BOOL)isContentDiscarded;
#endif
@end

@interface NSObject (NSDiscardableContentProxy)
- (id)autoContentAccessingProxy NS_AVAILABLE(10_6, 4_0);
@end


/***********	Object Allocation / Deallocation		*******/
    
FOUNDATION_EXPORT id NSAllocateObject(Class aClass, NSUInteger extraBytes, NSZone *zone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT void NSDeallocateObject(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT id NSCopyObject(id object, NSUInteger extraBytes, NSZone *zone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT BOOL NSShouldRetainWithZone(id anObject, NSZone *requestedZone) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT void NSIncrementExtraRefCount(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT BOOL NSDecrementExtraRefCountWasZero(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

FOUNDATION_EXPORT NSUInteger NSExtraRefCount(id object) NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

#if __has_feature(objc_arc)

// After using a CFBridgingRetain on an NSObject, the caller must take responsibility for calling CFRelease at an appropriate time.
NS_INLINE CF_RETURNS_RETAINED CFTypeRef CFBridgingRetain(id X) {
    return (__bridge_retained CFTypeRef)X;
}

NS_INLINE id CFBridgingRelease(CFTypeRef CF_CONSUMED X) {
    return (__bridge_transfer id)X;
}

#else

// This function is intended for use while converting to ARC mode only.
NS_INLINE CF_RETURNS_RETAINED CFTypeRef CFBridgingRetain(id X) {
    return X ? CFRetain((CFTypeRef)X) : NULL;
}

// This function is intended for use while converting to ARC mode only.
NS_INLINE id CFBridgingRelease(CFTypeRef CF_CONSUMED X) {
    return [(id)CFMakeCollectable(X) autorelease];
}

#endif
