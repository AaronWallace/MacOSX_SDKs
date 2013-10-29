/*
	NSTextFieldCell.h
	Application Kit
	Copyright (c) 1994-2009, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSActionCell.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
enum {
    NSTextFieldSquareBezel  = 0,
    NSTextFieldRoundedBezel = 1
};
typedef NSUInteger NSTextFieldBezelStyle;
#endif

@class NSColor;

@interface NSTextFieldCell : NSActionCell  {
    /*All instance variables are private*/
    NSColor *_backgroundColor;
    NSColor *_textColor;
    struct __tfFlags {
	unsigned int drawsBackground:1;
	unsigned int bezelStyle:3;
	unsigned int thcSortDirection:2;
	unsigned int thcSortPriority:4;
	unsigned int mini:1;
	unsigned int textColorIgnoresNormalDisableFlag:1;
	unsigned int textColorDisableFlag:1;
        unsigned int thcForceHighlightForSort:1;
	unsigned int invalidTextColor:1;
        unsigned int notificationForMarkedText:1;
	unsigned int reservedTextFieldCell:16;
    } _tfFlags;
}

- (void)setBackgroundColor:(NSColor *)color;
- (NSColor *)backgroundColor;
- (void)setDrawsBackground:(BOOL)flag;
- (BOOL)drawsBackground;
- (void)setTextColor:(NSColor *)color;
- (NSColor *)textColor;
- (NSText *)setUpFieldEditorAttributes:(NSText *)textObj;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_2
- (void)setBezelStyle:(NSTextFieldBezelStyle)style;
- (NSTextFieldBezelStyle)bezelStyle;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)setPlaceholderString:(NSString*)string;
- (NSString*)placeholderString;
- (void)setPlaceholderAttributedString:(NSAttributedString*)string;
- (NSAttributedString*)placeholderAttributedString;
#endif

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
- (void)setWantsNotificationForMarkedText:(BOOL)flag;

/* Returns an array of locale identifiers representing keyboard input sources allowed to be enabled when the receiver has the keyboard focus.
 */
- (NSArray *)allowedInputSourceLocales;
- (void)setAllowedInputSourceLocales:(NSArray *)localeIdentifiers;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */

@end

