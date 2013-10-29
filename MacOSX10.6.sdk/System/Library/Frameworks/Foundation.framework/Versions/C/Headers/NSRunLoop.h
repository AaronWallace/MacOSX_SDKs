/*	NSRunLoop.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <CoreFoundation/CFRunLoop.h>

@class NSTimer, NSPort, NSArray;

FOUNDATION_EXPORT NSString * const NSDefaultRunLoopMode;
FOUNDATION_EXPORT NSString * const NSRunLoopCommonModes AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@interface NSRunLoop : NSObject {
@private
    id          _rl;
    id          _dperf;
    id          _perft;
    id          _info;
    id		_ports;
    void	*_reserved[6];
}

+ (NSRunLoop *)currentRunLoop;
+ (NSRunLoop *)mainRunLoop AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

- (NSString *)currentMode;
- (CFRunLoopRef)getCFRunLoop;

- (void)addTimer:(NSTimer *)timer forMode:(NSString *)mode;

- (void)addPort:(NSPort *)aPort forMode:(NSString *)mode;
- (void)removePort:(NSPort *)aPort forMode:(NSString *)mode;

- (NSDate *)limitDateForMode:(NSString *)mode;
- (void)acceptInputForMode:(NSString *)mode beforeDate:(NSDate *)limitDate;

@end

@interface NSRunLoop (NSRunLoopConveniences)

- (void)run; 
- (void)runUntilDate:(NSDate *)limitDate;
- (BOOL)runMode:(NSString *)mode beforeDate:(NSDate *)limitDate;

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
- (void)configureAsServer DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
#endif

@end

/**************** 	Delayed perform	 ******************/

@interface NSObject (NSDelayedPerforming)

- (void)performSelector:(SEL)aSelector withObject:(id)anArgument afterDelay:(NSTimeInterval)delay inModes:(NSArray *)modes;
- (void)performSelector:(SEL)aSelector withObject:(id)anArgument afterDelay:(NSTimeInterval)delay;
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget selector:(SEL)aSelector object:(id)anArgument;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
+ (void)cancelPreviousPerformRequestsWithTarget:(id)aTarget;
#endif

@end

@interface NSRunLoop (NSOrderedPerform)

- (void)performSelector:(SEL)aSelector target:(id)target argument:(id)arg order:(NSUInteger)order modes:(NSArray *)modes;
- (void)cancelPerformSelector:(SEL)aSelector target:(id)target argument:(id)arg;
#if MAC_OS_X_VERSION_10_2 <= MAC_OS_X_VERSION_MAX_ALLOWED
- (void)cancelPerformSelectorsWithTarget:(id)target;
#endif

@end

