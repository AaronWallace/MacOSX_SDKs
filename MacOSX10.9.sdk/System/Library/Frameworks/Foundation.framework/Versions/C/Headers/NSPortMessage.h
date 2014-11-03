/*	NSPortMessage.h
	Copyright (c) 1994-2013, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSPort, NSDate, NSArray, NSMutableArray;

@interface NSPortMessage : NSObject {
    @private
    NSPort 		*localPort;
    NSPort 		*remotePort;
    NSMutableArray 	*components;
    uint32_t		msgid;
    void		*reserved2;
    void		*reserved;
}

- (id)initWithSendPort:(NSPort *)sendPort receivePort:(NSPort *)replyPort components:(NSArray *)components;

- (NSArray *)components;
- (NSPort *)receivePort;
- (NSPort *)sendPort;
- (BOOL)sendBeforeDate:(NSDate *)date;

- (uint32_t)msgid;
- (void)setMsgid:(uint32_t)msgid;

@end

