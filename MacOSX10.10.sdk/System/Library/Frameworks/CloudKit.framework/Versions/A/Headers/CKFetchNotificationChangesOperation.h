//
//  CKFetchNotificationChangesOperation.h
//  CloudKit
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <CloudKit/CKDatabaseOperation.h>

@class CKNotification, CKServerChangeToken;

NS_CLASS_AVAILABLE(10_10, 8_0)
@interface CKFetchNotificationChangesOperation : CKOperation

/* This operation will fetch all notification changes.
   If a change anchor from a previous CKFetchNotificationChangesOperation is passed in, only the notifications that have changed
    since that anchor will be fetched.
   If this is your first fetch, pass nil for the change anchor.
   Change anchors are opaque tokens and clients should not infer any behavior based on their content. */
- (instancetype)initWithPreviousServerChangeToken:(CKServerChangeToken *)previousServerChangeToken;

@property (nonatomic, copy) CKServerChangeToken *previousServerChangeToken;

@property (nonatomic, assign) NSUInteger resultsLimit;

/* Will be set before fetchNotificationChangesCompletionBlock is called. If moreComing is true then the server wasn't able to return all the changes in this response.
 Another CKFetchNotificationChangesOperation operation should be run with the updated serverChangeToken token from this operation. */
@property (nonatomic, readonly) BOOL moreComing;

@property (nonatomic, copy) void (^notificationChangedBlock)(CKNotification *notification);

/* Clients are responsible for saving the change token at the end of the operation and passing it in to the next call to CKFetchNotificationChangesOperation.
   Note that a fetch can fail partway. If that happens, an updated change token may be returned in the completion
    block so that already fetched notifications don't need to be re-downloaded on a subsequent operation. */
@property (nonatomic, copy) void (^fetchNotificationChangesCompletionBlock)(CKServerChangeToken *serverChangeToken, NSError *operationError);

@end
