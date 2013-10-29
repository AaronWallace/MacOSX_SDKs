/*
	NSGraphics.h
	Application Kit
	Copyright (c) 1994-2012, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSGeometry.h> 
#import <AppKit/AppKitDefines.h>

@class NSColor, NSView;

/*=== CONSTANTS ===*/
/* operation types for composite operators */
/* Constants moved from dpsOpenStep.h */
enum {
    NSCompositeClear		= 0,
    NSCompositeCopy		= 1,
    NSCompositeSourceOver	= 2,
    NSCompositeSourceIn		= 3,
    NSCompositeSourceOut	= 4,
    NSCompositeSourceAtop	= 5,
    NSCompositeDestinationOver	= 6,
    NSCompositeDestinationIn	= 7,
    NSCompositeDestinationOut	= 8,
    NSCompositeDestinationAtop	= 9,
    NSCompositeXOR		= 10,
    NSCompositePlusDarker	= 11,
    NSCompositeHighlight	= 12,
    NSCompositePlusLighter	= 13
};
typedef NSUInteger NSCompositingOperation;

/* types of window backing store */
enum {
    NSBackingStoreRetained	 = 0,
    NSBackingStoreNonretained	 = 1,
    NSBackingStoreBuffered	 = 2
};
typedef NSUInteger NSBackingStoreType;

/* ways to order windows */
enum {
    NSWindowAbove		 =  1,
    NSWindowBelow		 = -1,
    NSWindowOut			 =  0
};
typedef NSInteger NSWindowOrderingMode;

/* order in which to draw focus ring - above or below graphic or just draw ring */
enum {
    NSFocusRingOnly	 = 0,
    NSFocusRingBelow	 = 1,
    NSFocusRingAbove	 = 2
};
typedef NSUInteger NSFocusRingPlacement;

/* used by NSView and NSCell to configure if and how the control should draw its focus ring */ 
enum {
    NSFocusRingTypeDefault = 0,
    NSFocusRingTypeNone = 1,
    NSFocusRingTypeExterior = 2
};
typedef NSUInteger NSFocusRingType;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
enum {
    NSColorRenderingIntentDefault, //  = kCGRenderingIntentDefault,
    NSColorRenderingIntentAbsoluteColorimetric, //  = kCGRenderingIntentAbsoluteColorimetric,
    NSColorRenderingIntentRelativeColorimetric, //  = kCGRenderingIntentRelativeColorimetric,
    NSColorRenderingIntentPerceptual, // = kCGRenderingIntentPerceptual,
    NSColorRenderingIntentSaturation // = kCGRenderingIntentSaturation
};
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5 */
typedef NSInteger NSColorRenderingIntent;  // values interchangeable with CGColorRenderingIntent values


/* Predefined colorspace names.
*/
APPKIT_EXTERN NSString *NSCalibratedWhiteColorSpace;	/* 1.0 == white */
APPKIT_EXTERN NSString *NSCalibratedRGBColorSpace;
APPKIT_EXTERN NSString *NSDeviceWhiteColorSpace;	/* 1.0 == white */
APPKIT_EXTERN NSString *NSDeviceRGBColorSpace;
APPKIT_EXTERN NSString *NSDeviceCMYKColorSpace;
APPKIT_EXTERN NSString *NSNamedColorSpace;		/* Used for "catalog" colors */
APPKIT_EXTERN NSString *NSPatternColorSpace;
APPKIT_EXTERN NSString *NSCustomColorSpace;		/* Used to indicate a custom gstate in images */

/* Prefer colorspaces where 1.0 means white.
 */
APPKIT_EXTERN NSString *NSCalibratedBlackColorSpace     /* 1.0 == black */ NS_DEPRECATED_MAC(10_0, 10_6);	
APPKIT_EXTERN NSString *NSDeviceBlackColorSpace 	/* 1.0 == black */ NS_DEPRECATED_MAC(10_0, 10_6);


/* NSWindowDepth defines the values used in setting window depth limits. "0" indicates default depth. Window depths should not be made persistent as they will not be the same across systems. Use the functions NSBitsPerSampleFromDepth(), NSColorSpaceFromDepth(), NSBitsPerPixelFromDepth(), and NSPlanarFromDepth() to extract info from an NSWindowDepth 

On Mac OS X 10.5 and earlier, use NSBestDepth() to compute window depths. NSBestDepth() will try to accomodate all the parameters (match or better); if there are multiple matches, it gives the closest, with matching colorSpace first, then bps, then planar, then bpp. bpp is "bits per pixel"; 0 indicates default (same as the number of bits per plane, either bps or bps * NSNumberOfColorComponents()); other values maybe used as hints to provide backing stores of different configuration; for instance, 8 bit color. exactMatch is optional and indicates whether all the parameters matched exactly.

On Mac OS X 10.6 and later, you can pass one of the explicit bit depths below to -[NSWindow setDepthLimit:].  NSWindowDepthTwentyfourBitRGB is the default.
*/
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
enum {
    NSWindowDepthTwentyfourBitRGB = 0x208,
    NSWindowDepthSixtyfourBitRGB = 0x210,
    NSWindowDepthOnehundredtwentyeightBitRGB = 0x220
};
#endif

typedef int NSWindowDepth;

APPKIT_EXTERN NSWindowDepth NSBestDepth (NSString *colorSpace, NSInteger bps, NSInteger bpp, BOOL planar, BOOL *exactMatch);
APPKIT_EXTERN BOOL NSPlanarFromDepth (NSWindowDepth depth);
APPKIT_EXTERN NSString *NSColorSpaceFromDepth (NSWindowDepth depth);
APPKIT_EXTERN NSInteger NSBitsPerSampleFromDepth(NSWindowDepth depth);
APPKIT_EXTERN NSInteger NSBitsPerPixelFromDepth(NSWindowDepth depth);
APPKIT_EXTERN NSInteger NSNumberOfColorComponents(NSString *colorSpaceName);
APPKIT_EXTERN const NSWindowDepth *NSAvailableWindowDepths (void); /* 0 terminated */


/* Standard gray values for the 2-bit deep grayscale colorspace.
*/
APPKIT_EXTERN const CGFloat NSWhite;
APPKIT_EXTERN const CGFloat NSLightGray;
APPKIT_EXTERN const CGFloat NSDarkGray;
APPKIT_EXTERN const CGFloat NSBlack;


/* Keys for deviceDescription dictionaries.
*/
APPKIT_EXTERN NSString *NSDeviceResolution;		/* NSValue containing NSSize, basically dpi */
APPKIT_EXTERN NSString *NSDeviceColorSpaceName;	/* NSString */
APPKIT_EXTERN NSString *NSDeviceBitsPerSample;		/* NSValue containing int */
APPKIT_EXTERN NSString *NSDeviceIsScreen;		/* "YES" or not there */
APPKIT_EXTERN NSString *NSDeviceIsPrinter;		/* "YES" or not there */
APPKIT_EXTERN NSString *NSDeviceSize;			/* NSValue containing NSSize */


/* Graphics functions
*/
APPKIT_EXTERN void NSRectFill(NSRect aRect);
APPKIT_EXTERN void NSRectFillList(const NSRect *rects, NSInteger count);
APPKIT_EXTERN void NSRectFillListWithGrays(const NSRect *rects, const CGFloat *grays, NSInteger num);
APPKIT_EXTERN void NSRectFillListWithColors(const NSRect *rects, NSColor * const *colors, NSInteger num);
APPKIT_EXTERN void NSRectFillUsingOperation(NSRect aRect, NSCompositingOperation op);
APPKIT_EXTERN void NSRectFillListUsingOperation(const NSRect *rects, NSInteger count, NSCompositingOperation op);
APPKIT_EXTERN void NSRectFillListWithColorsUsingOperation(const NSRect *rects, NSColor * const *colors, NSInteger num, NSCompositingOperation op);
APPKIT_EXTERN void NSFrameRect(NSRect aRect);
APPKIT_EXTERN void NSFrameRectWithWidth(NSRect aRect, CGFloat frameWidth);
APPKIT_EXTERN void NSFrameRectWithWidthUsingOperation(NSRect aRect, CGFloat frameWidth, NSCompositingOperation op);
APPKIT_EXTERN void NSRectClip(NSRect aRect);
APPKIT_EXTERN void NSRectClipList(const NSRect *rects, NSInteger count);
APPKIT_EXTERN NSRect NSDrawTiledRects(NSRect boundsRect, NSRect clipRect, const NSRectEdge *sides, const CGFloat *grays, NSInteger count);
APPKIT_EXTERN void NSDrawGrayBezel(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawGroove(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawWhiteBezel(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawButton(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSEraseRect(NSRect aRect);
APPKIT_EXTERN NSColor *NSReadPixel(NSPoint passedPoint);
APPKIT_EXTERN void NSDrawBitmap(NSRect rect, NSInteger width, NSInteger height, NSInteger bps, NSInteger spp, NSInteger bpp, NSInteger bpr, BOOL isPlanar, BOOL hasAlpha, NSString *colorSpaceName, const unsigned char *const data[5]);
APPKIT_EXTERN void NSCopyBits(NSInteger srcGState, NSRect srcRect, NSPoint destPoint);
APPKIT_EXTERN void NSHighlightRect(NSRect aRect);
APPKIT_EXTERN void NSBeep(void);

/* gets performance stats about window server memory usage */
APPKIT_EXTERN NSInteger NSGetWindowServerMemory(NSInteger context, NSInteger *virtualMemory, NSInteger *windowBackingMemory, NSString **windowDumpString);

APPKIT_EXTERN NSRect NSDrawColorTiledRects(NSRect boundsRect, NSRect clipRect, const NSRectEdge *sides, NSColor **colors, NSInteger count);
APPKIT_EXTERN void NSDrawDarkBezel(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDrawLightBezel(NSRect aRect, NSRect clipRect);
APPKIT_EXTERN void NSDottedFrameRect(NSRect aRect);

APPKIT_EXTERN void NSDrawWindowBackground(NSRect aRect);
APPKIT_EXTERN void NSSetFocusRingStyle(NSFocusRingPlacement placement);

/* Disable and reenable screen updates.  
** NSDisableScreenUpdates prevents drawing for all windows belonging to the calling  
** process from being flushed to the screen.  This function permits operations on 
** multiple windows to appear atomic to the user, and is particularly useful for parent
** and child windows.  Note that this function should be used with care for short 
** operations only as the system will only allow updates to be disabled for a short 
** time (currently one second) before automatically reenabling updates.
** NSEnableScreenUpdates reenables drawing that was previously disabled by 
** NSDisableScreenUpdates.  Multiple calls stack.
*/
APPKIT_EXTERN void NSDisableScreenUpdates(void);
APPKIT_EXTERN void NSEnableScreenUpdates(void);


/* Runs one of the standard system animation effects (display and sound).
** 'centerLocation' represents the center, in screen coordinates, to show the effect.
** 'size' specifies how big the effect should be.  Use NSZeroSize to get the default size.
** 'animationDelegate' is optionally, an object that wants to know when the effect has completed.
** 'didEndSelector' will be invoked in the animationDelegate when the animation has completed.
**  
** The didEndSelector should have the following signature:
** 	- (void)animationEffectDidEnd:(void *)contextInfo;
*/

enum {
	// The default effect used to indicate removal of an item from a collection, 
	// such as toolbar (indicates removal, without destroying the underlying data).
	NSAnimationEffectDisappearingItemDefault = 0,

	// An effect showing a puff of smoke.
	NSAnimationEffectPoof = 10
};
typedef NSUInteger NSAnimationEffect;

APPKIT_EXTERN void NSShowAnimationEffect(NSAnimationEffect animationEffect, NSPoint centerLocation, NSSize size, id animationDelegate, SEL didEndSelector, void *contextInfo);


/* NSCountWindows, NSWindowList, NSCountWindowsForContext, and NSWindowListForContext are deprecated on Mac OS 10.6 and later.  Use +[NSWindow windowNumbersWithOptions:] instead */
APPKIT_EXTERN void NSCountWindows(NSInteger *count);
APPKIT_EXTERN void NSWindowList(NSInteger size, NSInteger list[]);
APPKIT_EXTERN void NSCountWindowsForContext(NSInteger context, NSInteger *count);
APPKIT_EXTERN void NSWindowListForContext(NSInteger context, NSInteger size, NSInteger list[]);

