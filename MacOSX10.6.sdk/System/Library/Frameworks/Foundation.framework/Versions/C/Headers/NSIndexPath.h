/*  NSIndexPath.h
    Copyright (c) 2003-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

#if MAC_OS_X_VERSION_10_4 <= MAC_OS_X_VERSION_MAX_ALLOWED

@interface NSIndexPath : NSObject <NSCopying, NSCoding> {
	@private
	NSUInteger *_indexes;
	NSUInteger _hash;
	NSUInteger _length;
        void *_reserved;
}

+ (id)indexPathWithIndex:(NSUInteger)index;
+ (id)indexPathWithIndexes:(NSUInteger *)indexes length:(NSUInteger)length;   

- (id)initWithIndex:(NSUInteger)index;
- (id)initWithIndexes:(NSUInteger *)indexes length:(NSUInteger)length;    // designated initializer

- (NSIndexPath *)indexPathByAddingIndex:(NSUInteger)index;
- (NSIndexPath *)indexPathByRemovingLastIndex;

- (NSUInteger)indexAtPosition:(NSUInteger)position;
- (NSUInteger)length;

- (void)getIndexes:(NSUInteger *)indexes;

	// comparison support
- (NSComparisonResult)compare:(NSIndexPath *)otherObject; // sorting an array of indexPaths using this comparison results in an array representing nodes in depth-first traversal order

@end

#endif

