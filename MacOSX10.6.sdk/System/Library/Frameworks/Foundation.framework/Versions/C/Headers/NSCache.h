/*      NSCache.h
        Copyright (c) 2008-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED

@class NSString;

@interface NSCache : NSObject {
@private
    id _delegate;
    void *_private[5];
    void *_reserved;
}

- (void)setName:(NSString *)n;
- (NSString *)name;

- (void)setDelegate:(id)d;
- (id)delegate;

- (id)objectForKey:(id)key;
- (void)setObject:(id)obj forKey:(id)key; // 0 cost
- (void)setObject:(id)obj forKey:(id)key cost:(NSUInteger)g;
- (void)removeObjectForKey:(id)key;

- (void)removeAllObjects;

- (void)setTotalCostLimit:(NSUInteger)lim;
- (NSUInteger)totalCostLimit;	// limits are imprecise/not strict

- (void)setCountLimit:(NSUInteger)lim;
- (NSUInteger)countLimit;	// limits are imprecise/not strict

- (BOOL)evictsObjectsWithDiscardedContent;
- (void)setEvictsObjectsWithDiscardedContent:(BOOL)b;

@end

@protocol NSCacheDelegate
@optional
- (void)cache:(NSCache *)cache willEvictObject:(id)obj;
@end

#endif

