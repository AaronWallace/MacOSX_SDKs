/*
	NSPanel.h
	Application Kit
	Copyright (c) 1994-2013, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSWindow.h>

/*
 These functions are deprecated in 10.9 and will be formally deprecated in the following release
 NSAlert should be used instead
 * In the following three functions, msg may be a printf-like message with
 * the arguments tacked onto the end.  Thus, to get a '%' in your message,
 * you must use '%%'
 */
APPKIT_EXTERN NSInteger NSRunAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6);
APPKIT_EXTERN NSInteger NSRunInformationalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6);
APPKIT_EXTERN NSInteger NSRunCriticalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6);

/*
** The NSRunAlertPanelRelativeToWindow variants are deprecated.  
** Please use the corresponding NSBeginAlertSheet() function instead.
*/
APPKIT_EXTERN NSInteger NSRunAlertPanelRelativeToWindow(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...) NS_DEPRECATED_MAC(10_0, 10_0);
APPKIT_EXTERN NSInteger NSRunInformationalAlertPanelRelativeToWindow(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...) NS_DEPRECATED_MAC(10_0, 10_0);
APPKIT_EXTERN NSInteger NSRunCriticalAlertPanelRelativeToWindow(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, ...) NS_DEPRECATED_MAC(10_0, 10_0);

/*
 These functions are deprecated in 10.9 and will be formally deprecated in the following release
 NSAlert should be used instead.
**  Present a sheet alert on the given window.  When the modal session is ended, but before the sheet is dismissed,
** the didEndSelector will be invoked in the modalDelegate.  After the sheet
** is dismissed, the didDismissSelector will be invoked. Typically, you will want to implement the didEndSelector but you may
** pass NULL for the didDismissSelector.
** The methods should have the following signatures:
** - (void)sheetDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
** - (void)sheetDidDismiss:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
**
*/
APPKIT_EXTERN void NSBeginAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msgFormat, ...) NS_FORMAT_FUNCTION(10,11);
APPKIT_EXTERN void NSBeginInformationalAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msgFormat, ...)NS_FORMAT_FUNCTION(10,11);
APPKIT_EXTERN void NSBeginCriticalAlertSheet(NSString *title, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, NSWindow *docWindow, id modalDelegate, SEL didEndSelector, SEL didDismissSelector, void *contextInfo, NSString *msgFormat, ...) NS_FORMAT_FUNCTION(10,11);
APPKIT_EXTERN id NSGetAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6);
APPKIT_EXTERN id NSGetInformationalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6);
APPKIT_EXTERN id NSGetCriticalAlertPanel(NSString *title, NSString *msgFormat, NSString *defaultButton, NSString *alternateButton, NSString *otherButton, ...) NS_FORMAT_FUNCTION(2,6);
APPKIT_EXTERN void NSReleaseAlertPanel(id panel);



/*
 These constants are deprecated in 10.9 and will be formally deprecated in the following release 
 These constants are used by deprecated NSRunAlertPanel() and NSGetAlertPanel()functions.
 Modern NSAlert API uses NSAlertFirstButtonReturn, etc.
 */
enum {
    NSAlertDefaultReturn		= 1,
    NSAlertAlternateReturn		= 0,
    NSAlertOtherReturn			= -1,
    NSAlertErrorReturn			= -2
};
enum {
    NSOKButton				= 1, // NSModalResponseOK should be used instead (in NSWindow)
    NSCancelButton			= 0  // NSModalResponseCancel should be used instead (in NSWindow)
};



// Panel specific styleMask
enum {
    NSUtilityWindowMask			= 1 << 4,
    NSDocModalWindowMask 		= 1 << 6
};

enum {
    NSNonactivatingPanelMask		= 1 << 7	// specify a panel that does not activate owning application
};

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
enum {
    NSHUDWindowMask                 = 1 << 13           // specify a heads up display panel
};
#endif

@interface NSPanel : NSWindow
{
/*All instance variables are private*/
}

- (BOOL)isFloatingPanel;
- (void)setFloatingPanel:(BOOL)flag;
- (BOOL)becomesKeyOnlyIfNeeded;
- (void)setBecomesKeyOnlyIfNeeded:(BOOL)flag;
- (BOOL)worksWhenModal;
- (void)setWorksWhenModal:(BOOL)flag;

@end

