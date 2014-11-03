/*
        NSParagraphStyle.h
        Copyright (c) 1994-2013, Apple Inc.  All rights reserved.

	NSParagraphStyle and NSMutableParagraphStyle hold paragraph style information
	NSTextTab holds information about a single tab stop
*/

#import <Foundation/NSObject.h>
#import <AppKit/NSText.h>

enum {
    NSLeftTabStopType = 0,
    NSRightTabStopType,
    NSCenterTabStopType,
    NSDecimalTabStopType
};
typedef NSUInteger NSTextTabType;

enum {		/* What to do with long lines */
    NSLineBreakByWordWrapping = 0,     	/* Wrap at word boundaries, default */
    NSLineBreakByCharWrapping,		/* Wrap at character boundaries */
    NSLineBreakByClipping,		/* Simply clip */
    NSLineBreakByTruncatingHead,	/* Truncate at head of line: "...wxyz" */
    NSLineBreakByTruncatingTail,	/* Truncate at tail of line: "abcd..." */
    NSLineBreakByTruncatingMiddle	/* Truncate middle of line:  "ab...yz" */
};
typedef NSUInteger NSLineBreakMode;

/* An attribute for NSTextTab options.  The value is NSCharacterSet.  The character set is used to determine the tab column terminating character.  The tab itself and newline characters are implied even if non-existent in the character set.
*/
APPKIT_EXTERN NSString *NSTabColumnTerminatorsAttributeName;

NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSTextTab : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    struct {
	NSTextAlignment alignment:4;
        unsigned int refCount:24;
        unsigned int unused:4;
#if __LP64__
        unsigned int :32;
#endif
    } _flags;
    CGFloat _location;
    id _reserved;
}

/* Initializes a text tab with the text alignment, location, and options.  The text alignment is used to determine the position of text inside the tab column.  These are the mapping from/to NSTextTabType.

To NSTextTabType:
NSLeftTextAlignment -> NSLeftTabStopType
NSRightTextAlignment -> NSRightTabStopType
NSCenterTextAlignment -> NSCenterTabStopType
NSJustifiedTextAlignment -> NSLeftTabStopType
NSNaturalTextAlignment -> NSLeftTabStopType or NSRightTabStopType depending on the user setting
NSRightTextAlignment w/ terminator -> NSDecimalTabStopType

From NSTextTabType:
NSLeftTabStopType -> NSLeftTextAlignment
NSRightTabStopType -> NSRightTextAlignment
NSCenterTabStopType -> NSCenterTextAlignment
NSDecimalTabStopType -> NSRightTextAlignment with the decimal character for the user setting
*/
- (id)initWithTextAlignment:(NSTextAlignment)alignment location:(CGFloat)loc options:(NSDictionary *)options;

- (NSTextAlignment)alignment;
- (NSDictionary *)options;
- (id)initWithType:(NSTextTabType)type location:(CGFloat)loc;
- (CGFloat)location;
- (NSTextTabType)tabStopType;
@end

NS_AUTOMATED_REFCOUNT_WEAK_UNAVAILABLE
@interface NSParagraphStyle : NSObject <NSCopying, NSMutableCopying, NSCoding> {
    /*All instance variables are private*/
    CGFloat _lineSpacing;
    CGFloat _paragraphSpacing;
    CGFloat _headIndent;
    CGFloat _tailIndent;
    CGFloat _firstLineHeadIndent;
    CGFloat _minimumLineHeight;
    CGFloat _maximumLineHeight;
    NSArray *_tabStops;
    struct {
	NSTextAlignment alignment:4;
        NSLineBreakMode lineBreakMode:4;
        unsigned int tabStopsIsMutable:1;
        unsigned int isNaturalDirection:1;
        unsigned int rightToLeftDirection:1;
        unsigned int fixedMultiple:2;
        unsigned int refCount:19;
#if __LP64__
        unsigned int :32;
#endif
    } _flags;
    CGFloat _defaultTabInterval;
    id _extraData;
}

+ (NSParagraphStyle *)defaultParagraphStyle;

+ (NSWritingDirection)defaultWritingDirectionForLanguage:(NSString *)languageName;  // languageName is in ISO lang region format

- (CGFloat)lineSpacing;		/* "Leading": distance between the bottom of one line fragment and top of next (applied between lines in the same container). Can't be negative. This value is included in the line fragment heights in layout manager. */
- (CGFloat)paragraphSpacing; 	/* Distance between the bottom of this paragraph and top of next (or the beginning of its paragraphSpacingBefore, if any). */
- (NSTextAlignment)alignment;

/* The following values are relative to the appropriate margin (depending on the paragraph direction) */
   
- (CGFloat)headIndent;		/* Distance from margin to front edge of paragraph */
- (CGFloat)tailIndent;		/* Distance from margin to back edge of paragraph; if negative or 0, from other margin */
- (CGFloat)firstLineHeadIndent;	/* Distance from margin to edge appropriate for text direction */
- (NSArray *)tabStops;		/* Distance from margin to tab stops */

- (CGFloat)minimumLineHeight;	/* Line height is the distance from bottom of descenders to top of ascenders; basically the line fragment height. Does not include lineSpacing (which is added after this computation). */
- (CGFloat)maximumLineHeight;	/* 0 implies no maximum. */ 

- (NSLineBreakMode)lineBreakMode;

- (NSWritingDirection)baseWritingDirection;

- (CGFloat)lineHeightMultiple;	/* Natural line height is multiplied by this factor (if positive) before being constrained by minimum and maximum line height. */
- (CGFloat)paragraphSpacingBefore;/* Distance between the bottom of the previous paragraph (or the end of its paragraphSpacing, if any) and the top of this paragraph. */
- (CGFloat)defaultTabInterval;	/* Tabs after the last specified in tabStops are placed at integral multiples of this distance (if positive). */ 

- (NSArray *)textBlocks;    /* Array to specify the text blocks containing the paragraph, nested from outermost to innermost. */
- (NSArray *)textLists;     /* Array to specify the text lists containing the paragraph, nested from outermost to innermost. */

/* Specifies the threshold for hyphenation.  Valid values lie between 0.0 and 1.0 inclusive.  Hyphenation will be attempted when the ratio of the text width as broken without hyphenation to the width of the line fragment is less than the hyphenation factor.  When this takes on its default value of 0.0, the layout manager's hyphenation factor is used instead.  When both are 0.0, hyphenation is disabled.
*/
- (float)hyphenationFactor;

/* Specifies the threshold for using tightening as an alternative to truncation.  When the line break mode specifies truncation, the text system will attempt to tighten inter-character spacing as an alternative to truncation, provided that the ratio of the text width to the line fragment width does not exceed 1.0 + tighteningFactorForTruncation.  Otherwise the text will be truncated at a location determined by the line break mode.  The default value is 0.05.
*/
- (float)tighteningFactorForTruncation;

/* Specifies whether the paragraph is to be treated as a header for purposes of HTML generation.  Should be set to 0 (the default value) if the paragraph is not a header, or from 1 through 6 if the paragraph is to be treated as a header. */
- (NSInteger)headerLevel;

@end

@interface NSMutableParagraphStyle : NSParagraphStyle

- (void)setLineSpacing:(CGFloat)aFloat;
- (void)setParagraphSpacing:(CGFloat)aFloat;
- (void)setAlignment:(NSTextAlignment)alignment;
- (void)setFirstLineHeadIndent:(CGFloat)aFloat;
- (void)setHeadIndent:(CGFloat)aFloat;
- (void)setTailIndent:(CGFloat)aFloat;
- (void)setLineBreakMode:(NSLineBreakMode)mode;
- (void)setMinimumLineHeight:(CGFloat)aFloat;
- (void)setMaximumLineHeight:(CGFloat)aFloat;
- (void)addTabStop:(NSTextTab *)anObject;
- (void)removeTabStop:(NSTextTab *)anObject;
- (void)setTabStops:(NSArray *)array;
- (void)setParagraphStyle:(NSParagraphStyle *)obj;
- (void)setBaseWritingDirection:(NSWritingDirection)writingDirection;
- (void)setLineHeightMultiple:(CGFloat)aFloat;
- (void)setParagraphSpacingBefore:(CGFloat)aFloat;
- (void)setDefaultTabInterval:(CGFloat)aFloat;
- (void)setTextBlocks:(NSArray *)array;
- (void)setTextLists:(NSArray *)array;
- (void)setHyphenationFactor:(float)aFactor;
- (void)setTighteningFactorForTruncation:(float)aFactor;
- (void)setHeaderLevel:(NSInteger)level;
@end
