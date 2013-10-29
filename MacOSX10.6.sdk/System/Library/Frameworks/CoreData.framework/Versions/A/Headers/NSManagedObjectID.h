/*
    NSManagedObjectID.h
    Core Data
    Copyright (c) 2004-2009 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#if MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_5
#ifndef NSPersistentStore
#define NSPersistentStore NSObject
#endif
#endif

@class NSPersistentStore;
@class NSEntityDescription;
@class NSURL;

// Managed object IDs are opaque identifiers for managed objects.
@interface NSManagedObjectID : NSObject <NSCopying> {
}

- (NSEntityDescription *)entity;    // entity for the object identified by an ID
- (NSPersistentStore *)persistentStore;    // persistent store that fetched the object identified by an ID

- (BOOL)isTemporaryID;    // indicates whether or not this ID will be replaced later, such as after a save operation (temporary IDs are assigned to newly inserted objects and replaced with permanent IDs when an object is written to a persistent store); most IDs return NO

- (NSURL *)URIRepresentation;    // URI which provides an archivable reference to the object which this ID refers

@end

#endif
