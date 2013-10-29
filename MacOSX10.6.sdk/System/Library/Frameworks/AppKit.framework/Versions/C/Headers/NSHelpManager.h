/*
	NSHelpManager.h
	Application Kit
	Copyright (c) 1995-2009, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSMapTable.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSBundle.h>
#import <AppKit/AppKitDefines.h>
#import <AppKit/NSApplication.h>

@class NSAttributedString, NSWindow;

@interface NSHelpManager : NSObject
{
    /*All instance variables are private*/
    NSMapTable		*_helpMapTable;
    NSMapTable		*_keyMapTable;
    NSMapTable		*_bundleMapTable;
    NSWindow		*_helpWindow;
    NSWindow		*_shadowWindow;
    NSWindow		*_evtWindow;
    NSBundle		*_helpBundle;
}

+ (NSHelpManager *)sharedHelpManager;
+ (void)setContextHelpModeActive:(BOOL)active;
+ (BOOL)isContextHelpModeActive;

- (void)setContextHelp:(NSAttributedString *)attrString forObject:(id)object;
- (void)removeContextHelpForObject:(id)object;
- (NSAttributedString *)contextHelpForObject:(id)object;

- (BOOL)showContextHelpForObject:(id)object locationHint:(NSPoint)pt;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
- (void)openHelpAnchor:(NSString *)anchor inBook:(NSString *)book;
- (void)findString:(NSString *)query inBook:(NSString *)book;
#endif

/* Register one or more help books in the given bundle.  The main bundle is automatically registered by -openHelpAnchor:inBook: and -findString:inBook:.  You can use -registerBooksInBundle: to register help books in a plugin bundle, for example.  The Info.plist in the bundle should contain a help book directory path, which specifies one or more folders containing help books.  Returns NO if the bundle doesn't contain any help books or if registration fails.  Returns YES on successful registration. */
- (BOOL)registerBooksInBundle:(NSBundle *)bundle AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

//
// Notifications for the activation/deactivation of the context help mode
//

APPKIT_EXTERN NSString *NSContextHelpModeDidActivateNotification;
APPKIT_EXTERN NSString *NSContextHelpModeDidDeactivateNotification;

//
//  Conveniences for accessing Help.plist
//

@interface NSBundle(NSBundleHelpExtension)
- (NSAttributedString *)contextHelpForKey:(NSString *)key;	/* return nil if not found */
@end

//
//  Convenience methods on NSApplication
//

@interface NSApplication(NSApplicationHelpExtension)
- (void)activateContextHelpMode:(id)sender;
  // Target method cover for [NSHelpManager setContextHelpModeActive:YES];
- (void)showHelp:(id)sender;
@end
