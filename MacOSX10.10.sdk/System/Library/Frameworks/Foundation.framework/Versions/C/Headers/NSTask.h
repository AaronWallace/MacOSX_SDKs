/*	NSTask.h
	Copyright (c) 1996-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSArray, NSDictionary;

typedef NS_ENUM(NSInteger, NSTaskTerminationReason) {
    NSTaskTerminationReasonExit = 1,
    NSTaskTerminationReasonUncaughtSignal = 2
} NS_ENUM_AVAILABLE(10_6, NA);

@interface NSTask : NSObject

// Create an NSTask which can be run at a later time
// An NSTask can only be run once. Subsequent attempts to
// run an NSTask will raise.
// Upon task death a notification will be sent
//   { Name = NSTaskDidTerminateNotification; object = task; }
//

- (instancetype)init NS_DESIGNATED_INITIALIZER;

// these methods can only be set before a launch
@property (copy) NSString *launchPath;
@property (copy) NSArray *arguments;
@property (copy) NSDictionary *environment; // if not set, use current
@property (copy) NSString *currentDirectoryPath; // if not set, use current

// standard I/O channels; could be either an NSFileHandle or an NSPipe
@property (retain) id standardInput;
@property (retain) id standardOutput;
@property (retain) id standardError;

// actions
- (void)launch;

- (void)interrupt; // Not always possible. Sends SIGINT.
- (void)terminate; // Not always possible. Sends SIGTERM.

- (BOOL)suspend;
- (BOOL)resume;

// status
@property (readonly) int processIdentifier;
@property (readonly, getter=isRunning) BOOL running;

@property (readonly) int terminationStatus;
@property (readonly) NSTaskTerminationReason terminationReason NS_AVAILABLE(10_6, NA);

/*
A block to be invoked when the process underlying the NSTask terminates.  Setting the block to nil is valid, and stops the previous block from being invoked, as long as it hasn't started in any way.  The NSTask is passed as the argument to the block so the block does not have to capture, and thus retain, it.  The block is copied when set.  Only one termination handler block can be set at any time.  The execution context in which the block is invoked is undefined.  If the NSTask has already finished, the block is executed immediately/soon (not necessarily on the current thread).  If a terminationHandler is set on an NSTask, the NSTaskDidTerminateNotification notification is not posted for that task.  Also note that -waitUntilExit won't wait until the terminationHandler has been fully executed.  You cannot use this property in a concrete subclass of NSTask which hasn't been updated to include an implementation of the storage and use of it.  
*/
@property (copy) void (^terminationHandler)(NSTask *) NS_AVAILABLE(10_7, NA);

@property NSQualityOfService qualityOfService NS_AVAILABLE(10_10, 8_0); // read-only after the task is launched

@end

@interface NSTask (NSTaskConveniences)

+ (NSTask *)launchedTaskWithLaunchPath:(NSString *)path arguments:(NSArray *)arguments;
	// convenience; create and launch

- (void)waitUntilExit;
	// poll the runLoop in defaultMode until task completes

@end

FOUNDATION_EXPORT NSString * const NSTaskDidTerminateNotification;

