/*	NSFileHandle.h
	Copyright (c) 1995-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSRange.h>

@class NSString, NSData, NSError;

@interface NSFileHandle : NSObject

- (NSData *)availableData;

- (NSData *)readDataToEndOfFile;
- (NSData *)readDataOfLength:(NSUInteger)length;

- (void)writeData:(NSData *)data;

- (unsigned long long)offsetInFile;
- (unsigned long long)seekToEndOfFile;
- (void)seekToFileOffset:(unsigned long long)offset;

- (void)truncateFileAtOffset:(unsigned long long)offset;
- (void)synchronizeFile;
- (void)closeFile;

@end

@interface NSFileHandle (NSFileHandleCreation)

+ (id)fileHandleWithStandardInput;
+ (id)fileHandleWithStandardOutput;
+ (id)fileHandleWithStandardError;
+ (id)fileHandleWithNullDevice;

+ (id)fileHandleForReadingAtPath:(NSString *)path;
+ (id)fileHandleForWritingAtPath:(NSString *)path;
+ (id)fileHandleForUpdatingAtPath:(NSString *)path;

+ (id)fileHandleForReadingFromURL:(NSURL *)url error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (id)fileHandleForWritingToURL:(NSURL *)url error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
+ (id)fileHandleForUpdatingURL:(NSURL *)url error:(NSError **)error AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

FOUNDATION_EXPORT NSString * const NSFileHandleOperationException;

FOUNDATION_EXPORT NSString * const NSFileHandleReadCompletionNotification;
FOUNDATION_EXPORT NSString * const NSFileHandleReadToEndOfFileCompletionNotification;
FOUNDATION_EXPORT NSString * const NSFileHandleConnectionAcceptedNotification;
FOUNDATION_EXPORT NSString * const NSFileHandleDataAvailableNotification;

FOUNDATION_EXPORT NSString * const NSFileHandleNotificationDataItem;
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationFileHandleItem;
FOUNDATION_EXPORT NSString * const NSFileHandleNotificationMonitorModes;

@interface NSFileHandle (NSFileHandleAsynchronousAccess)

- (void)readInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)readInBackgroundAndNotify;

- (void)readToEndOfFileInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)readToEndOfFileInBackgroundAndNotify;

- (void)acceptConnectionInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)acceptConnectionInBackgroundAndNotify;

- (void)waitForDataInBackgroundAndNotifyForModes:(NSArray *)modes;
- (void)waitForDataInBackgroundAndNotify;

@end

@interface NSFileHandle (NSFileHandlePlatformSpecific)

- (id)initWithFileDescriptor:(int)fd closeOnDealloc:(BOOL)closeopt;
- (id)initWithFileDescriptor:(int)fd;
- (int)fileDescriptor;

@end

@interface NSPipe : NSObject

- (NSFileHandle *)fileHandleForReading;
- (NSFileHandle *)fileHandleForWriting;

- (id)init;
+ (id)pipe;

@end

