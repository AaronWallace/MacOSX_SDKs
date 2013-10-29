/*
        NSQuickDrawView.h
        Application Kit
        Copyright (c) 1999-2009, Apple Inc.
        All rights reserved.
*/

/* QuickDraw is deprecated for 32-bit apps, and doesn't exist in 64-bit. */

#if !__LP64__
#import <AppKit/NSView.h>

@interface NSQuickDrawView : NSView
{
@private
    void*  _qdPort;
    void*  _savePort;
    BOOL   _synchToView;
}

- (void*) qdPort DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

@end
#endif /* !__LP64__ */
