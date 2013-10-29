/*
        NSAffineTransform.h
        Application Kit
        Copyright (c) 1997-2012, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSAffineTransform.h>

@class NSBezierPath;

@interface NSAffineTransform (NSAppKitAdditons)
// Transform a path
- (NSBezierPath *)transformBezierPath:(NSBezierPath *)aPath;

// Setting a transform in NSGraphicsContext
- (void)set;
- (void)concat;
@end
