/*
        NSMenuItem.h
        Application Kit
        Copyright (c) 1996-2011, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <AppKit/NSView.h>

@class NSMenu;
@class NSImage, NSAttributedString, NSView;

@interface NSMenuItem : NSObject <NSCopying, NSCoding, NSValidatedUserInterfaceItem>
{
    /*All instance variables are private*/
    @private
    NSMenu *_menu;
    NSString *_title;
    NSString *_keyEquivalent;
#if __LP64__
    NSString *_uiid;
    id _repObject;
    NSMenu *_submenu;
    id _extraData;
    id _target;
    SEL _action;
    NSInteger _tag;
    unsigned char _keyEquivalentModifierMask;
#else
    NSUInteger _keyEquivalentModifierMask;
    NSInteger _userKEGenerationCount;
    NSInteger _state;
    NSImage *_image;
    NSMenu *_submenu;
    NSString *_uiid;
    id _repObject;
    id _target;
    SEL _action;
    NSInteger _tag;
    id _extraData;    
#endif
    struct __miFlags {
        unsigned int keGenerationCount:8;
        unsigned int disabled:1;
        unsigned int isSeparator:1;
        unsigned int hidden:1;
        unsigned int alternate:1;
        unsigned int moreAlternate:1;
        unsigned int singleAlternate:1;
        unsigned int indent:4;
        unsigned int keShareMode:3;
        unsigned int state:2;
        unsigned int RESERVED1:2;
        unsigned int limitedView:1;
        unsigned int nextItemIsAlternate:1;
        unsigned int blockKE:1;
        unsigned int ignoredForAccessibility:1;
        unsigned int hiddenActiveKE:1;
        unsigned int noRepeatKEs:1;
        unsigned int RESERVED2:1;
    } _miFlags;
}

+ (void)setUsesUserKeyEquivalents:(BOOL)flag;
+ (BOOL)usesUserKeyEquivalents;

+ (NSMenuItem *)separatorItem;

- (id)initWithTitle:(NSString *)aString action:(SEL)aSelector keyEquivalent:(NSString *)charCode;

- (void)setMenu:(NSMenu *)menu;
- (NSMenu *)menu;
    // Never call the set method directly it is there only for subclassers.


- (BOOL)hasSubmenu;
- (void)setSubmenu:(NSMenu *)submenu;
- (NSMenu *)submenu;

/* Returns the NSMenuItem whose submenu contains the receiver, or nil if the receiver does not have a parent item.
*/
- (NSMenuItem *)parentItem NS_AVAILABLE_MAC(10_6);

- (void)setTitle:(NSString *)aString;
- (NSString *)title;
- (void)setAttributedTitle:(NSAttributedString*)string;
- (NSAttributedString*)attributedTitle;

- (BOOL)isSeparatorItem;

- (void)setKeyEquivalent:(NSString *)aKeyEquivalent;
- (NSString *)keyEquivalent;
- (void)setKeyEquivalentModifierMask:(NSUInteger)mask;
- (NSUInteger)keyEquivalentModifierMask;

- (NSString *)userKeyEquivalent;

- (void)setTitleWithMnemonic:(NSString *)stringWithAmpersand;

- (void)setImage:(NSImage *)menuImage;
- (NSImage *)image;

- (void)setState:(NSInteger)state;
- (NSInteger)state;
- (void)setOnStateImage:(NSImage *)image;  // checkmark by default
- (NSImage *)onStateImage;
- (void)setOffStateImage:(NSImage *)image;  // none by default
- (NSImage *)offStateImage;
- (void)setMixedStateImage:(NSImage *)image;  // horizontal line by default?
- (NSImage *)mixedStateImage;

- (void)setEnabled:(BOOL)flag;
- (BOOL)isEnabled;


- (void)setAlternate:(BOOL)isAlternate;
- (BOOL)isAlternate;

- (void)setIndentationLevel:(NSInteger)indentationLevel;
- (NSInteger)indentationLevel;

- (void)setTarget:(id)anObject;
- (id)target;
- (void)setAction:(SEL)aSelector;
- (SEL)action;

- (void)setTag:(NSInteger)anInt;
- (NSInteger)tag;

- (void)setRepresentedObject:(id)anObject;
- (id)representedObject;

/* Set (and get) the view for a menu item.  By default, a menu item has a nil view.
A menu item with a view does not draw its title, state, font, or other standard drawing attributes, and assigns drawing responsibility entirely to the view.  Keyboard equivalents and type-select continue to use the key equivalent and title as normal.
A menu item with a view sizes itself according to the view's frame, and the width of the other menu items.  The menu item will always be at least as wide as its view, but it may be wider.  If you want your view to auto-expand to fill the menu item, then make sure that its autoresizing mask has NSViewWidthSizable set; in that case, the view's width at the time setView: is called will be treated as the minimum width for the view.  A menu will resize itself as its containing views change frame size.  Changes to the view's frame during tracking are reflected immediately in the menu.
A view in a menu item will receive mouse and keyboard events normally.  During non-sticky menu tracking (manipulating menus with the mouse button held down), a view in a menu item will receive mouseDragged: events.
Animation is possible via the usual mechanism (set a timer to call setNeedsDisplay: or display), but because menu tracking occurs in the NSEventTrackingRunLoopMode, you must add the timer to the run loop in that mode.
When the menu is opened, the view is added to a window; when the menu is closed the view is removed from the window.  Override viewDidMoveToWindow in your view for a convenient place to start/stop animations, reset tracking rects, etc., but do not attempt to move or otherwise modify the window.
When a menu item is copied via NSCopying, any attached view is copied via archiving/unarchiving.  Menu item views are not supported in the Dock menu. */
- (void)setView:(NSView *)view NS_AVAILABLE_MAC(10_5);
- (NSView *)view NS_AVAILABLE_MAC(10_5);

/* Indicates whether the menu item should be drawn highlighted or not. */
- (BOOL)isHighlighted NS_AVAILABLE_MAC(10_5);

/* Set (and get) the visibility of a menu item.  Hidden menu items (or items with a hidden superitem) do not appear in a menu and do not participate in command key matching.  isHiddenOrHasHiddenAncestor returns YES if the item is hidden or any of its superitems are hidden. */
- (void)setHidden:(BOOL)hidden NS_AVAILABLE_MAC(10_5);
- (BOOL)isHidden NS_AVAILABLE_MAC(10_5);
- (BOOL)isHiddenOrHasHiddenAncestor NS_AVAILABLE_MAC(10_5);


- (void) setToolTip:(NSString*)toolTip;
- (NSString*)toolTip;

@end

@interface NSView (NSViewEnclosingMenuItem)
/* Returns the menu item containing the receiver or any of its superviews in the view hierarchy, or nil if the receiver's view hierarchy is not in a menu item. */
- (NSMenuItem *)enclosingMenuItem NS_AVAILABLE_MAC(10_5);
@end

// The NSMenuItem protocol is deprecated.  Use the NSMenuItem class in your code.
#if defined(__GNUC__) && (__GNUC__ >= 4) && (__GNUC_MINOR__ >= 2)
NS_DEPRECATED_MAC(10_0, 10_6)
#endif
@protocol NSMenuItem;

/* The following methods are deprecated.  They have never done anything useful in Mac OS X. */
@interface NSMenuItem (NSDeprecated)

- (void)setMnemonicLocation:(NSUInteger)location NS_DEPRECATED_MAC(10_0, 10_6);
- (NSUInteger)mnemonicLocation NS_DEPRECATED_MAC(10_0, 10_6);
- (NSString *)mnemonic NS_DEPRECATED_MAC(10_0, 10_6);

@end
