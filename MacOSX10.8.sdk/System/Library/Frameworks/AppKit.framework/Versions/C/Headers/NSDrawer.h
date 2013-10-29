/*
        NSDrawer.h
        Application Kit
        Copyright (c) 1999-2012, Apple Inc.
        All rights reserved.
*/

#import <CoreFoundation/CFDate.h>
#import <CoreFoundation/CFRunLoop.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSResponder.h>
#import <AppKit/NSWindow.h>

@class NSArray;
@class NSLock;
@class NSView;
@class NSWindow;
@class NSNotification;
@protocol NSDrawerDelegate;

enum {
    NSDrawerClosedState			= 0,
    NSDrawerOpeningState 		= 1,
    NSDrawerOpenState 			= 2,
    NSDrawerClosingState 		= 3
};
typedef NSUInteger NSDrawerState;

@interface NSDrawer : NSResponder
{
    /*All instance variables are private*/
    NSDrawerState 	_drawerState;
    NSDrawerState	_drawerNextState;
    NSRectEdge 		_drawerEdge;
    NSRectEdge 		_drawerNextEdge;
    NSRectEdge 		_drawerPreferredEdge;
    float 		_drawerPercent;
    float 		_drawerPercentSaved;
    CGFloat		_drawerLeadingOffset;
    CGFloat		_drawerTrailingOffset;
    NSLock 		*_drawerLock;
    NSWindow		*_drawerWindow;
    NSWindow 		*_drawerParentWindow;
    NSWindow		*_drawerNextParentWindow;
    NSString		*_drawerSaveName;
    CFAbsoluteTime 	_drawerStartTime;
    CFTimeInterval 	_drawerTotalTime;
    CFRunLoopRef 	_drawerLoop;
    __strong CFRunLoopTimerRef 	_drawerTimer;
    id 			_drawerDelegate;
    unsigned int	_drawerFlags;
    __strong CFRunLoopObserverRef _drawerObserver;
}

- (id)initWithContentSize:(NSSize)contentSize preferredEdge:(NSRectEdge)edge;

- (void)setParentWindow:(NSWindow *)parent;
- (NSWindow *)parentWindow;
- (void)setContentView:(NSView *)aView;
- (NSView *)contentView;
- (void)setPreferredEdge:(NSRectEdge)edge;
- (NSRectEdge)preferredEdge;
- (void)setDelegate:(id <NSDrawerDelegate>)anObject;
- (id <NSDrawerDelegate>)delegate;

- (void)open;
- (void)openOnEdge:(NSRectEdge)edge;
- (void)close;

- (void)open:(id)sender;
- (void)close:(id)sender;
- (void)toggle:(id)sender;

- (NSInteger)state;
- (NSRectEdge)edge;

- (void)setContentSize:(NSSize)size;
- (NSSize)contentSize;
- (void)setMinContentSize:(NSSize)size;
- (NSSize)minContentSize;
- (void)setMaxContentSize:(NSSize)size;
- (NSSize)maxContentSize;

- (void)setLeadingOffset:(CGFloat)offset;
- (CGFloat)leadingOffset;
- (void)setTrailingOffset:(CGFloat)offset;
- (CGFloat)trailingOffset;

@end

@interface NSWindow(Drawers)

- (NSArray *)drawers;

@end

@protocol NSDrawerDelegate <NSObject>
@optional
- (BOOL)drawerShouldOpen:(NSDrawer *)sender;
- (BOOL)drawerShouldClose:(NSDrawer *)sender;
- (NSSize)drawerWillResizeContents:(NSDrawer *)sender toSize:(NSSize)contentSize;

/* Notifications */
- (void)drawerWillOpen:(NSNotification *)notification;
- (void)drawerDidOpen:(NSNotification *)notification;
- (void)drawerWillClose:(NSNotification *)notification;
- (void)drawerDidClose:(NSNotification *)notification;

@end

/* Notifications */
APPKIT_EXTERN NSString *NSDrawerWillOpenNotification;
APPKIT_EXTERN NSString *NSDrawerDidOpenNotification;
APPKIT_EXTERN NSString *NSDrawerWillCloseNotification;
APPKIT_EXTERN NSString *NSDrawerDidCloseNotification;

/* Note that the size of a drawer is determined partly by its content, partly by
the size of its parent window.  The size in the direction of the drawer's motion
is determined by the drawer's content size, and may be manually changed by the
user within the limits determined by the min and max content sizes (programmatic
changes are not so limited.)  The size in the transverse direction is determined
by the size of the parent window, combined with the drawer's leading and trailing
offsets.  For finer control over the size of the drawer in the transverse direction,
listen for the parent window's NSWindowDidResizeNotification and then reset the
leading and/or trailing offsets accordingly.  The one overriding restriction is
that a drawer can never be larger than its parent, and the sizes of both drawer
and parent are constrained by this. */
