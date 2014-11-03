/*
     File:       LSInfo.h
 
     Contains:   Public interfaces for LaunchServices.framework
 
     Copyright:  (c) 2001-2012 by Apple Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/

*/

#ifndef __LSINFO__
#define __LSINFO__

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#if !TARGET_OS_IPHONE
#ifndef __CARBONCORE__
#include <CarbonCore/CarbonCore.h>
#endif
#endif

#include <Availability.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

/* ======================================================================================================== */
/* LaunchServices Type & Constants                                                                          */
/* ======================================================================================================== */

enum {
  kLSAppInTrashErr              = -10660, /* The app cannot be run when inside a Trash folder*/
  kLSExecutableIncorrectFormat  = -10661, /* No compatible executable was found*/
  kLSAttributeNotFoundErr       = -10662, /* An item attribute value could not be found with the specified name*/
  kLSAttributeNotSettableErr    = -10663, /* The attribute is not settable*/
  kLSIncompatibleApplicationVersionErr = -10664, /* The app is incompatible with the current OS*/
  kLSNoRosettaEnvironmentErr    = -10665, /* The Rosetta environment was required not available*/
  kLSUnknownErr                 = -10810, /* Unexpected internal error*/
  kLSNotAnApplicationErr        = -10811, /* Item needs to be an application, but is not*/
  kLSNotInitializedErr          = -10812, /* Not used in 10.2 and later*/
  kLSDataUnavailableErr         = -10813, /* E.g. no kind string*/
  kLSApplicationNotFoundErr     = -10814, /* E.g. no application claims the file*/
  kLSUnknownTypeErr             = -10815, /* Don't know anything about the type of the item*/
  kLSDataTooOldErr              = -10816, /* Not used in 10.3 and later*/
  kLSDataErr                    = -10817, /* Not used in 10.4 and later*/
  kLSLaunchInProgressErr        = -10818, /* E.g. launching an already launching application*/
  kLSNotRegisteredErr           = -10819, /* Not used in 10.3 and later*/
  kLSAppDoesNotClaimTypeErr     = -10820, /* One or more documents are of types (and/or one or more URLs are of schemes) not supported by the target application (sandboxed callers only)*/
  kLSAppDoesNotSupportSchemeWarning = -10821, /* Not used in 10.2 and later*/
  kLSServerCommunicationErr     = -10822, /* The server process (registration and recent items) is not available*/
  kLSCannotSetInfoErr           = -10823, /* The extension visibility on this item cannot be changed*/
  kLSNoRegistrationInfoErr      = -10824, /* The item contains no registration info*/
  kLSIncompatibleSystemVersionErr = -10825, /* The app cannot run on the current OS version*/
  kLSNoLaunchPermissionErr      = -10826, /* User doesn't have permission to launch the app (managed networks)*/
  kLSNoExecutableErr            = -10827, /* The executable is missing*/
  kLSNoClassicEnvironmentErr    = -10828, /* The Classic environment was required but is not available*/
  kLSMultipleSessionsNotSupportedErr = -10829, /* The app cannot run simultaneously in two different sessions*/
};

typedef OptionBits                      LSInitializeFlags;
enum {
  kLSInitializeDefaults         = 0x00000001
};

enum {
  kLSMinCatInfoBitmap           = (kFSCatInfoNodeFlags | kFSCatInfoParentDirID | kFSCatInfoFinderInfo | kFSCatInfoFinderXInfo) /* do not use */
};

#define kLSInvalidExtensionIndex ULONG_MAX      // Index returned from LSGetExtensionInfo when name has no extension
typedef OptionBits                      LSRequestedInfo;
enum {
  kLSRequestExtension           = 0x00000001, /* thread-safe in 10.0*/
  kLSRequestTypeCreator         = 0x00000002, /* thread-safe in 10.0*/
  kLSRequestBasicFlagsOnly      = 0x00000004, /* thread-safe in 10.2*/
  kLSRequestAppTypeFlags        = 0x00000008, /* thread-safe in 10.2*/
  kLSRequestAllFlags            = 0x00000010, /* thread-safe in 10.2*/
  kLSRequestIconAndKind         = 0x00000020, /* thread-safe in 10.2*/
  kLSRequestExtensionFlagsOnly  = 0x00000040, /* thread-safe in 10.0*/
  kLSRequestAllInfo             = (UInt32)0xFFFFFFFF /* thread-safe in 10.2*/
};

typedef OptionBits                      LSItemInfoFlags;
enum {
  kLSItemInfoIsPlainFile        = 0x00000001, /* Not a directory, volume, or symlink*/
  kLSItemInfoIsPackage          = 0x00000002, /* Packaged directory*/
  kLSItemInfoIsApplication      = 0x00000004, /* Single-file or packaged application*/
  kLSItemInfoIsContainer        = 0x00000008, /* Directory (includes packages) or volume*/
  kLSItemInfoIsAliasFile        = 0x00000010, /* Alias file (includes sym links)*/
  kLSItemInfoIsSymlink          = 0x00000020, /* UNIX sym link*/
  kLSItemInfoIsInvisible        = 0x00000040, /* Invisible by any known mechanism*/
  kLSItemInfoIsNativeApp        = 0x00000080, /* Carbon or Cocoa native app*/
  kLSItemInfoIsClassicApp       = 0x00000100, /* CFM/68K Classic app*/
  kLSItemInfoAppPrefersNative   = 0x00000200, /* Carbon app that prefers to be launched natively*/
  kLSItemInfoAppPrefersClassic  = 0x00000400, /* Carbon app that prefers to be launched in Classic*/
  kLSItemInfoAppIsScriptable    = 0x00000800, /* App can be scripted*/
  kLSItemInfoIsVolume           = 0x00001000, /* Item is a volume*/
  kLSItemInfoExtensionIsHidden  = 0x00100000 /* Item has a hidden extension*/
};

typedef OptionBits                      LSRolesMask;
enum {
  kLSRolesNone                  = 0x00000001, /* no claim is made about support for this type/scheme*/
  kLSRolesViewer                = 0x00000002, /* claim to view items of this type*/
  kLSRolesEditor                = 0x00000004, /* claim to edit items of this type/scheme*/
  kLSRolesShell                 = 0x00000008, /* claim to execute items of this type*/
  kLSRolesAll                   = (UInt32)0xFFFFFFFF /* claim to do it all*/
};

#if !__LP64__
typedef UInt32                          LSKindID;
enum {
  kLSUnknownKindID              = 0
};

#endif
enum {
  kLSUnknownType                = 0,
  kLSUnknownCreator             = 0
};

struct LSItemInfoRecord {
  LSItemInfoFlags     flags;
  OSType              filetype;
  OSType              creator;
  CFStringRef         extension;              /* release when finished*/
#if !__LP64__

  CFStringRef         iconFileName;           /* not for general use*/
  LSKindID            kindID;                 /* not for general use*/
#endif

};
typedef struct LSItemInfoRecord         LSItemInfoRecord;

typedef OptionBits                      LSAcceptanceFlags;
enum {
  kLSAcceptDefault              = 0x00000001,
  kLSAcceptAllowLoginUI         = 0x00000002 /* show UI to log in if necessary*/
};


/* ======================================================================================================== */
/* LaunchServices API                                                                                       */
/* ======================================================================================================== */

/*
 *  LSInit()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    LSInit is deprecated. Do not use.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSInit(LSInitializeFlags inFlags)                             __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_3, __IPHONE_4_0, __IPHONE_4_0);



/*
 *  LSTerm()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    LSTerm is deprecated. It does nothing.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework but deprecated in 10.3
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSTerm(void)                                                  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_10_0, __MAC_10_3, __IPHONE_NA, __IPHONE_NA);



/*
 *  LSCopyItemInfoForRef()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Return information about an item.
 *  
 *  Discussion:
 *    Returns as much or as little information as requested about
 *    inItemRef.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inItemRef:
 *      The FSRef of the item about which information is requested.
 *
 *    inWhichInfo:
 *      Flags indicating which information to return
 *    
 *    outItemInfo:
 *      Information is returned in this structure. Must not be NULL
 *
 *  Deprecated:
 *    Use LSCopyItemInfoForURL or URL resource properties instead.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyItemInfoForRef(
  const FSRef *       inItemRef,
  LSRequestedInfo     inWhichInfo,
  LSItemInfoRecord *  outItemInfo)                            __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSCopyItemInfoForURL or URL resource properties instead.");



/*
 *  LSCopyItemInfoForURL()
 *  
 *  Summary:
 *    Return information about an item.
 *  
 *  Discussion:
 *    Returns as much or as little information as requested about inURL.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The CFURLRef of the item about which information is requested.
 *    
 *    inWhichInfo:
 *      Flags indicating which information to return
 *    
 *    outItemInfo:
 *      Information is returned in this structure. Must not be NULL
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyItemInfoForURL(
  CFURLRef            inURL,
  LSRequestedInfo     inWhichInfo,
  LSItemInfoRecord *  outItemInfo)                            __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);


/*
 *  LSGetExtensionInfo()
 *  
 *  Summary:
 *    Get information about the extension for a file system name.
 *  
 *  Discussion:
 *    Returns the starting index of the extension (not including the
 *    period) or kLSInvalidExtensionIndex if the input name has no
 *    extension.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inNameLen:
 *      The number of the UniChars in inNameBuffer.
 *    
 *    inNameBuffer:
 *      The buffer containing the name's Unicode characters.
 *    
 *    outExtStartIndex:
 *      On success, the starting index of the extension if there is one
 *      (not including the period). Set to kLSInvalidExtensionIndex if
 *      inNameBuffer does not contain a valid extension.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSGetExtensionInfo(
  UniCharCount    inNameLen,
  const UniChar   inNameBuffer[],
  UniCharCount *  outExtStartIndex)                           __OSX_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);



/*
 *  LSCopyDisplayNameForRef()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Get the display name for an FSRef.
 *  
 *  Discussion:
 *    Return a copy of the display name for an FSRef. Takes into
 *    consideration whether this item has a hidden extension or not.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inRef:
 *      The FSRef for which the display name is desired.
 *    
 *    outDisplayName:
 *      Pointer to the CFString into which the display name should be
 *      copied. Callers must dispose of the resulting CFString.
 *
 *  Deprecated:
 *    Use LSCopyDisplayNameForURL or the URL resource property
 *    kCFURLLocalizedNameKey or NSURLLocalizedNameKey instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyDisplayNameForRef(
  const FSRef *  inRef,
  CFStringRef *  outDisplayName)                              __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_1, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSCopyDisplayNameForURL or the URL resource property kCFURLLocalizedNameKey or NSURLLocalizedNameKey instead.");



/*
 *  LSCopyDisplayNameForURL()
 *  
 *  Summary:
 *    Get the display name for a CFURLRef.
 *  
 *  Discussion:
 *    Return a copy of the display name for a CFURLRef. Takes into
 *    consideration whether this item has a hidden extension or not.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The URL for which the display name is desired.
 *    
 *    outDisplayName:
 *      Pointer to the CFString into which the display name should be
 *      copied. Callers must dispose of the resulting CFString.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyDisplayNameForURL(
  CFURLRef       inURL,
  CFStringRef *  outDisplayName)                              __OSX_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);



/*
 *  LSSetExtensionHiddenForRef()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Sets whether the extension for an FSRef is hidden or not.
 *  
 *  Discussion:
 *    Sets the necessary file system state to indicate that the
 *    extension for inRef is hidden, as in the Finder. You can
 *    determine if an FSRef's extension is hidden using
 *    LSCopyItemInfoForRef.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inRef:
 *      The FSRef for which the extension is to be hidden or shown.
 *    
 *    inHide:
 *      True to hide inRef's extension, false to show it.
 *
 *  Deprecated:
 *    Use LSSetExtensionHiddenForURL or the URL resource property
 *    kCFURLHasHiddenExtensionKey or NSURLHasHiddenExtensionKey instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSetExtensionHiddenForRef(
  const FSRef *  inRef,
  Boolean        inHide)                                      __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_1, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSSetExtensionHiddenForURL or the URL resource property kCFURLHasHiddenExtensionKey or NSURLHasHiddenExtensionKey instead.");



/*
 *  LSSetExtensionHiddenForURL()
 *  
 *  Summary:
 *    Sets whether the extension for a CFURLRef is hidden or not.
 *  
 *  Discussion:
 *    Sets the necessary file system state to indicate that the
 *    extension for inURL is hidden, as in the Finder. You can
 *    determine if a CFURLRef's extension is hidden using
 *    LSCopyItemInfoForURL.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The CFURLRef for which the extension is to be hidden or shown.
 *    
 *    inHide:
 *      True to hide inURL's extension, false to show it.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.1 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSetExtensionHiddenForURL(
  CFURLRef   inURL,
  Boolean    inHide)                                          __OSX_AVAILABLE_STARTING(__MAC_10_1, __IPHONE_NA);



/*
 *  LSCopyKindStringForRef()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Get the kind string for an item.
 *  
 *  Discussion:
 *    Returns the kind string as used in the Finder and elsewhere for
 *    inFSRef. The CFStringRef must be released after use.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inFSRef:
 *      The item for which the kind string is requested.
 *    
 *    outKindString:
 *      A CFStringRef* to receive the copied kind string object. This
 *      CFStringRef must be released eventually.
 *
 *  Deprecated:
 *    Use LSCopyKindStringForURL or the URL resource property
 *    kCFURLLocalizedTypeDescriptionKey or NSURLLocalizedTypeDescriptionKey instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyKindStringForRef(
  const FSRef *  inFSRef,
  CFStringRef *  outKindString)                               __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSCopyKindStringForURL or the URL resource property kCFURLLocalizedTypeDescriptionKey or NSURLLocalizedTypeDescriptionKey instead.");



/*
 *  LSCopyKindStringForURL()
 *  
 *  Summary:
 *    Get the kind string for an item.
 *  
 *  Discussion:
 *    Returns the kind string as used in the Finder and elsewhere for
 *    inURL. The CFStringRef must be released after use.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The item for which the kind string is requested.
 *    
 *    outKindString:
 *      A CFStringRef* to receive the copied kind string object. This
 *      CFStringRef must be released eventually.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyKindStringForURL(
  CFURLRef       inURL,
  CFStringRef *  outKindString)                               __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  LSCopyKindStringForTypeInfo()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Return the kind string for items like the provided info
 *  
 *  Discussion:
 *    Returns the kind string as shown in the Finder for the those
 *    items whose type, creator, and/or extension match the provided
 *    information. The kind string returned will be the one that most
 *    closely describes all the information provided. The kind string
 *    is subject to the document binding preferences that have been
 *    specified by the user. For example, if a creator is specified but
 *    the user has asked for files with the given
 *    creator/type/extension combination to open in an application with
 *    a different creator, the kind string will be loaded from the
 *    user's preferred application.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inType:
 *      The OSType file type for which you want a kind string. Specify
 *      kLSUnknownType if no file type information is available.
 *    
 *    inCreator:
 *      The OSType creator for which you want a kind string. Specify
 *      kLSUnknownCreator if no creator information is available.
 *    
 *    inExtension:
 *      The extension for which you want a kind string. Specify NULL if
 *      no extension information is available.
 *    
 *    outKindString:
 *      A CFStringRef* to receive the copied kind string object. This
 *      CFStringRef must be released eventually.
 *  
 *  Deprecated:
 *    Use UTTypeCopyDescription instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyKindStringForTypeInfo(
  OSType         inType,
  OSType         inCreator,
  CFStringRef    inExtension,         /* can be NULL */
  CFStringRef *  outKindString)                               __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_2, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use UTTypeCopyDescription instead.");



/*
 *  LSCopyKindStringForMIMEType()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Get the kind string for the specified MIME type.
 *  
 *  Discussion:
 *    Returns the localized kind string describing the specified MIME
 *    type.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inMIMEType:
 *      The string specifying the MIME type.
 *    
 *    outKindString:
 *      A CFStringRef* to receive the copied kind string object. This
 *      CFStringRef must be released eventually.
 *  
 *  Deprecated:
 *    Use UTTypeCopyDescription instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyKindStringForMIMEType(
  CFStringRef    inMIMEType,
  CFStringRef *  outKindString)                               __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_2, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use UTTypeCopyDescription instead.");


/*
 *  LSGetApplicationForItem()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Return the application used to open an item.
 *  
 *  Discussion:
 *    Consults the binding tables to return the application that would
 *    be used to open inItemRef if it were double-clicked in the
 *    Finder. This application will be the user-specified override if
 *    appropriate or the default otherwise. If no application is known
 *    to LaunchServices suitable for opening this item,
 *    kLSApplicationNotFoundErr will be returned.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inItemRef:
 *      The FSRef of the item for which the application is requested.
 *    
 *    inRoleMask:
 *      Whether to return the editor or viewer for inItemRef. If you
 *      don't care which, use kLSRolesAll.
 *    
 *    outAppRef:
 *      Filled in with the FSRef of the application if not NULL.
 *    
 *    outAppURL:
 *      Filled in with the CFURLRef of the application if not NULL.
 *      THIS FUNCTION, DESPITE ITS NAME, RETAINS THE URL REFERENCE ON
 *      BEHALF OF THE CALLER. THE CALLER MUST EVENTUALLY RELEASE THE
 *      RETURNED URL REFERENCE.
 *
 *  Deprecated:
 *    Use LSCopyDefaultApplicationURLForURL instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSGetApplicationForItem(
  const FSRef *  inItemRef,
  LSRolesMask    inRoleMask,
  FSRef *        outAppRef,        /* can be NULL */
  CFURLRef *     outAppURL)        /* can be NULL */          __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSCopyDefaultApplicationURLForURL instead.");


	
/*
 *  LSGetApplicationForInfo()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Return the application used to open items with particular data.
 *  
 *  Discussion:
 *    Consults the binding tables to return the application that would
 *    be used to open items with type, creator, and/or extension as
 *    provided if they were double-clicked in the Finder. This
 *    application will be the default for items like this if one has
 *    been set. If no application is known to LaunchServices suitable
 *    for opening such items, kLSApplicationNotFoundErr will be
 *    returned. Not all three input parameters can be NULL at the same
 *    time nor can both output parameters be NULL at the same time.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inType:
 *      The file type to consider. Can be kLSUnknownType.
 *    
 *    inCreator:
 *      The file creator to consider. Can be kLSUnknownCreator.
 *    
 *    inExtension:
 *      The file name extension to consider. Can be NULL.
 *    
 *    inRoleMask:
 *      Whether to return the editor or viewer for inItemRef. If you
 *      don't care which, use kLSRolesAll.
 *    
 *    outAppRef:
 *      Filled in with the FSRef of the application if not NULL.
 *    
 *    outAppURL:
 *      Filled in with the CFURLRef of the application if not NULL.
 *      THIS FUNCTION, DESPITE ITS NAME, RETAINS THE URL REFERENCE ON
 *      BEHALF OF THE CALLER. THE CALLER MUST EVENTUALLY RELEASE THE
 *      RETURNED URL REFERENCE.
 *
 *  Deprecated:
 *    Use LSCopyDefaultApplicationURLForContentType instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSGetApplicationForInfo(
  OSType        inType,
  OSType        inCreator,
  CFStringRef   inExtension,       /* can be NULL */
  LSRolesMask   inRoleMask,
  FSRef *       outAppRef,         /* can be NULL */
  CFURLRef *    outAppURL)         /* can be NULL */          __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSCopyDefaultApplicationURLForContentType instead.");



/*
 *  LSCopyApplicationForMIMEType()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Return the application used to handle data with the specified
 *    MIME type.
 *  
 *  Discussion:
 *    The returned application URL will be the user's preferred handler
 *    for the MIME type if one has been set. If no user preferred
 *    application has been set, Launch Services will select a default
 *    handler for the MIME type. If no application is known to handle
 *    the MIME type, kLSApplicationNotFoundErr will be returned.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inMIMEType:
 *      The string specifying the MIME type.
 *    
 *    inRoleMask:
 *      A role mask that the chosen application must satisfy. Use
 *      kLSRolesAll if the role is not important.
 *    
 *    outAppURL:
 *      Receives the copied CFURLRef, which must be released by the
 *      caller.
 *
 *  Deprecated:
 *    Use LSCopyDefaultApplicationURLForContentType instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyApplicationForMIMEType(
  CFStringRef   inMIMEType,
  LSRolesMask   inRoleMask,
  CFURLRef *    outAppURL)                                    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_2, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSCopyDefaultApplicationURLForContentType instead.");



/*
 *  LSGetApplicationForURL()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Return the application used to open an item.
 *  
 *  Discussion:
 *    Consults the binding tables to return the application that would
 *    be used to open inURL if it were double-clicked in the Finder.
 *    This application will be the user-specified override if
 *    appropriate or the default otherwise. If no application is known
 *    to LaunchServices suitable for opening this item,
 *    kLSApplicationNotFoundErr will be returned.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The CFURLRef of the item for which the application is requested.
 *    
 *    inRoleMask:
 *      Whether to return the editor or viewer for inItemRef. If you
 *      don't care which, use kLSRolesAll.
 *    
 *    outAppRef:
 *      Filled in with the FSRef of the application if not NULL.
 *    
 *    outAppURL:
 *      Filled in with the CFURLRef of the application if not NULL.
 *      THIS FUNCTION, DESPITE ITS NAME, RETAINS THE URL REFERENCE ON
 *      BEHALF OF THE CALLER. THE CALLER MUST EVENTUALLY RELEASE THE
 *      RETURNED URL REFERENCE.
 *
 *  Deprecated:
 *    Use LSCopyDefaultApplicationURLForURL instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSGetApplicationForURL(
  CFURLRef      inURL,
  LSRolesMask   inRoleMask,
  FSRef *       outAppRef,        /* can be NULL */
  CFURLRef *    outAppURL)        /* can be NULL */           __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSCopyDefaultApplicationURLForURL instead.");



/*
 *  LSFindApplicationForInfo()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Locate a specific application.
 *  
 *  Discussion:
 *    Returns the application with the corresponding input information.
 *    The registry of applications is consulted first in order of
 *    bundleID, then creator, then name. All comparisons are case
 *    insensitive and 'ties' are decided first by version, then by
 *    native vs. Classic.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inCreator:
 *      The file creator to consider. Can be kLSUnknownCreator.
 *    
 *    inBundleID:
 *      The bundle ID to consider. Can be NULL.
 *    
 *    inName:
 *      The name to consider. Can be NULL. Must include any extensions
 *      that are part of the file system name, e.g. '.app'.
 *    
 *    outAppRef:
 *      Filled in with the FSRef of the application if not NULL.
 *    
 *    outAppURL:
 *      Filled in with the CFURLRef of the application if not NULL.
 *      THIS FUNCTION, DESPITE ITS NAME, RETAINS THE URL REFERENCE ON
 *      BEHALF OF THE CALLER. THE CALLER MUST EVENTUALLY RELEASE THE
 *      RETURNED URL REFERENCE.
 *
 *  Deprecated:
 *    Use LSCopyApplicationURLsForBundleIdentifier instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSFindApplicationForInfo(
  OSType        inCreator,
  CFStringRef   inBundleID,       /* can be NULL */
  CFStringRef   inName,           /* can be NULL */
  FSRef *       outAppRef,        /* can be NULL */
  CFURLRef *    outAppURL)        /* can be NULL */           __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSCopyApplicationURLsForBundleIdentifier instead.");


	
/*
 *  LSCopyDefaultApplicationURLForURL()
 *  
 *  Summary:
 *    Return the application used to open an item.
 *  
 *  Discussion:
 *    Consults the binding tables to return the application that would
 *    be used to open inURL if it were double-clicked in the
 *    Finder. This application will be the user-specified override if
 *    appropriate or the default otherwise.
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The URL of the item for which the application is requested.
 *
 *    inRoleMask:
 *      Whether to return the editor or viewer for inURL. If you
 *      don't care which, use kLSRolesAll.
 *    
 *    outError:
 *      On failure, set to a CFError describing the problem. If you are
 *      not interested in this information, pass NULL. The caller is
 *      responsible for releasing this object.
 *
 *  Result:
 *    If an acceptable application is found, its URL is returned.
 *    If the URL is a file:// URL, the application bound to the specified
 *    file or directory's type is returned. If the URL's scheme is something
 *    else, its default scheme handler is returned. If no application could
 *    be found, NULL is returned and outError (if not NULL) is populated.
 *    with kLSApplicationNotFoundErr.
 *    The caller is responsible for releasing this URL.
 */
extern CFURLRef
LSCopyDefaultApplicationURLForURL(
  CFURLRef      inURL,
  LSRolesMask   inRoleMask,
  CFErrorRef *  outError)                                     __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_NA);
	
	
	
/*
 *  LSCopyDefaultApplicationURLForContentType()
 *  
 *  Summary:
 *    Return the application used to open a content type (UTI).
 *  
 *  Discussion:
 *    Consults the binding tables to return the application that would
 *    be used to open a file of type inContentType if it were double-clicked
 *    in the Finder. This application will be the user-specified override if
 *    appropriate or the default otherwise.
 *  
 *  Parameters:
 *    
 *    inContentType:
 *      The Uniform Type Identifier (UTI) of the item for which the
 *      application is requested.
 *
 *    inRoleMask:
 *      Whether to return the editor or viewer for inContentType. If you
 *      don't care which, use kLSRolesAll.
 *    
 *    outError:
 *      On failure, set to a CFError describing the problem. If you are
 *      not interested in this information, pass NULL. The caller is
 *      responsible for releasing this object.
 *
 *  Result:
 *    If an acceptable application is found, its URL is returned.
 *    If no application could be found, NULL is returned and
 *    outError (if not NULL) is populated with kLSApplicationNotFoundErr.
 *    The caller is responsible for releasing this URL.
 */
extern CFURLRef
LSCopyDefaultApplicationURLForContentType(
  CFStringRef   inContentType,
  LSRolesMask   inRoleMask,
  CFErrorRef *  outError)                                     __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_NA);
	
	
	
/*
 *  LSCopyApplicationURLsForBundleIdentifier()
 *  
 *  Summary:
 *    Given a bundle identifier (such as com.apple.finder), find
 *    all URLs to the corresponding application.
 *  
 *  Discussion:
 *    Returns zero or more URLs to applications that have the specified
 *    bundle identifier.
 *  
 *  Parameters:
 *    
 *    inBundleIdentifier:
 *      The bundle identifier of interest, such as "com.apple.finder". Must
 *      not be NULL.
 *    
 *    outError:
 *      On failure, set to a CFError describing the problem. If you are
 *      not interested in this information, pass NULL. The caller is
 *      responsible for releasing this object.
 *    
 *  Result:
 *    If any applications with the specified bundle identifier are found,
 *    their URLs are returned in a CFArray. If no application could be found,
 *    NULL is returned and outError (if not NULL) is populated with kLSApplicationNotFoundErr.
 *    The order of elements in the array is undefined.
 *    The caller is responsible for releasing this array.
 *
 */
extern CFArrayRef
LSCopyApplicationURLsForBundleIdentifier(
  CFStringRef   inBundleIdentifier,
  CFErrorRef *  outError)                                     __OSX_AVAILABLE_STARTING(__MAC_10_10, __IPHONE_NA);
	
	
	
/*
 *  LSCopyApplicationURLsForURL()
 *  
 *  Discussion:
 *    Returns an array of URLs to applications that offer the requested
 *    role(s) for the input item.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The CFURLRef of the item for which all suitable applications
 *      are desired. If the URL is a file URL, it is treated as a
 *      document, and applications are selected based on the document's
 *      type information. Otherwise, applications are selected based on
 *      the URL's scheme.
 *    
 *    inRoleMask:
 *      The role(s) which must intersect with the role provided by an
 *      application for the specified item in order for the application
 *      to be included in the result. Pass kLSRolesAll if any role is
 *      acceptable.
 *  
 *  Result:
 *    An array of CFURLRefs, one for each application which can open
 *    inURL with at least one of the roles in inRoleMask, or NULL if no
 *    applications can open the item. When an array is returned, you
 *    must eventually release it.
 *
 *    The order of the resulting array is undefined. If you need the
 *    default application for the specified URL, use LSCopyDefaultApplicationURLForURL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern CFArrayRef 
LSCopyApplicationURLsForURL(
  CFURLRef      inURL,
  LSRolesMask   inRoleMask)                                   __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_NA);

	
	
/*
 *  LSCanRefAcceptItem()   *** DEPRECATED ***
 *  
 *  Summary:
 *    Determine whether an item can accept another item.
 *  
 *  Discussion:
 *    Returns in outAcceptsItem whether inTargetRef can accept
 *    inItemFSRef as in a drag and drop operation. If inRoleMask is
 *    other than kLSRolesAll then make sure inTargetRef claims to
 *    fulfill the requested role.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inItemFSRef:
 *      FSRef of the item about which acceptance is requested.
 *    
 *    inTargetRef:
 *      FSRef of the potential target.
 *    
 *    inRoleMask:
 *      The role(s) the target must claim in order to consider
 *      acceptance.
 *    
 *    inFlags:
 *      Use kLSAcceptDefault.
 *    
 *    outAcceptsItem:
 *      Filled in with result. Must not be NULL.
 *
 *  Deprecated:
 *    Use LSCanURLAcceptURL instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCanRefAcceptItem(
  const FSRef *       inItemFSRef,
  const FSRef *       inTargetRef,
  LSRolesMask         inRoleMask,
  LSAcceptanceFlags   inFlags,
  Boolean *           outAcceptsItem)                         __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_0, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSCanURLAcceptURL instead.");



/*
 *  LSCanURLAcceptURL()
 *  
 *  Summary:
 *    Determine whether an item can accept another item.
 *  
 *  Discussion:
 *    Returns in outAcceptsItem whether inTargetURL can accept
 *    inItemURL as in a drag and drop operation. If inRoleMask is other
 *    than kLSRolesAll then make sure inTargetRef claims to fulfill the
 *    requested role.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.2
 *  
 *  Parameters:
 *    
 *    inItemURL:
 *      CFURLRef of the item about which acceptance is requested.
 *    
 *    inTargetURL:
 *      CFURLRef of the potential target.
 *    
 *    inRoleMask:
 *      The role(s) the target must claim in order to consider
 *      acceptance.
 *    
 *    inFlags:
 *      Use kLSAcceptDefault.
 *    
 *    outAcceptsItem:
 *      Filled in with result. Must not be NULL.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.0 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCanURLAcceptURL(
  CFURLRef            inItemURL,
  CFURLRef            inTargetURL,
  LSRolesMask         inRoleMask,
  LSAcceptanceFlags   inFlags,
  Boolean *           outAcceptsItem)                         __OSX_AVAILABLE_STARTING(__MAC_10_0, __IPHONE_NA);



/*
 *  LSRegisterURL()
 *  
 *  Discussion:
 *    If the specified URL refers to an application or other bundle
 *    claiming to handle documents or URLs, add the bundle's document
 *    and URL claims to the Launch Services database.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inURL:
 *      The CFURLRef of the item (a directory or file) to be registered.
 *    
 *    inUpdate:
 *      When false, LSRegisterURL does not register the item if it has
 *      already been registered and the current modification date of
 *      the item has not changed from when it was last registered. When
 *      true, the item's registered info is updated, even if the
 *      modification has not changed.
 *  
 *  Result:
 *    An OSStatus value: noErr - Success kLSNoRegistrationInfoErr - The
 *    item does not contain info requiring registration kLSDataErr -
 *    The item's property list info is malformed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSRegisterURL(
  CFURLRef   inURL,
  Boolean    inUpdate)                                        __OSX_AVAILABLE_STARTING(__MAC_10_3, __IPHONE_4_0);


/*
 *  LSRegisterFSRef()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    If the specified FSRef refers to an application or other bundle
 *    claiming to handle documents or URLs, add the bundle's document
 *    and URL claims to the Launch Services database.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.3
 *  
 *  Parameters:
 *    
 *    inRef:
 *      The FSRef of the item to be registered.
 *    
 *    inUpdate:
 *      When false, LSRegisterFSRef does not register the item if it
 *      has already been registered and the current modification date
 *      of the item has not changed from when it was last registered.
 *      When true, the item's registered info is updated, even if the
 *      modification has not changed.
 *  
 *  Result:
 *    An OSStatus value: noErr - Success kLSNoRegistrationInfoErr - The
 *    item does not contain info requiring registration kLSDataErr -
 *    The item's property list info is malformed.
 *
 *  Deprecated:
 *    Use LSRegisterURL instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.3 and later in CoreServices.framework
 *    CarbonLib:        not available in CarbonLib 1.x
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSRegisterFSRef(
  const FSRef *  inRef,
  Boolean        inUpdate)                                    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_3, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use LSRegisterURL instead.");



/* ================================================================================== */
/*   API for retrieving item attributes                                               */
/* ================================================================================== */
/* 
 *  Attributes Names
 *
 *  kLSItemContentType
 *
 *    The item's content type identifier (a uniform type identifier string)
 *    Value type CFStringRef
 *
 *
 *  kLSItemFileType
 *
 *    The item's file type (OSType)
 *    Value type CFStringRef
 *
 *
 *  kLSItemFileCreator
 *
 *    The item's file creator (OSType)
 *    Value type CFStringRef 
 *
 *
 *  kLSItemExtension
 *
 *    The item's filename extension
 *    Value type CFStringRef 
 *
 *
 *  kLSItemDisplayName
 *
 *    The item's name as displayed to the user
 *    (The display name reflects localization and
 *    extension hiding which may be in effect)
 *    Value type CFStringRef 
 *
 *
 *  kLSItemDisplayKind
 *
 *    The localized kind string describing this item's type
 *    Value type CFStringRef 
 *
 *
 *  kLSItemRoleHandlerDisplayName
 *
 *    The display name of the application set to handle (open) this item
 *    (subject to the role mask)
 *    value type CFStringRef 
 *
 *
 *  kLSItemIsInvisible
 *
 *    True if the item is normally hidden from users
 *    Value type CFBooleanRef 
 *
 *
 *  kLSItemExtensionIsHidden
 *
 *    True if the item's extension is set to be hidden
 *    Value type CFBooleanRef 
 *
 *
 *  kLSItemQuarantineProperties (can be set)
 *
 *    A dictionary of quarantine properties. See LSQuarantine.h for
 *    quarantine property definitions. This attribute is not
 *    present if the item is not quarantined.
 *    Value type CFDictionaryRef. May be NULL.
 */
/*
 *  kLSItemContentType   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use the URL resource property kCFURLTypeIdentifierKey or NSURLTypeIdentifierKey instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSItemContentType                          __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_4_0, __IPHONE_8_0, "Use the URL resource property kCFURLTypeIdentifierKey or NSURLTypeIdentifierKey instead.");
/*
 *  kLSItemFileType   *** DEPRECATED ***
 *
 *  Deprecated:
 *    Use the URL resource property kCFURLTypeIdentifierKey or NSURLTypeIdentifierKey to get the file's UTI instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSItemFileType                             __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_4_0, __IPHONE_8_0, "Use the URL resource property kCFURLTypeIdentifierKey or NSURLTypeIdentifierKey to get the file's UTI instead.");
/*
 *  kLSItemFileCreator   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use the URL resource property kCFURLTypeIdentifierKey or NSURLTypeIdentifierKey to get the file's UTI instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSItemFileCreator                          __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_4_0, __IPHONE_8_0, "Use the URL resource property kCFURLTypeIdentifierKey or NSURLTypeIdentifierKey to get the file's UTI instead.");
/*
 *  kLSItemExtension   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use CFURLCopyPathExtension or -[NSURL pathExtension] instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSItemExtension                            __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_4_0, __IPHONE_8_0, "Use CFURLCopyPathExtension or -[NSURL pathExtension] instead.");
/*
 *  kLSItemDisplayName   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use LSCopyDisplayNameForURL or the URL resource property
 *    kCFURLLocalizedNameKey or NSURLLocalizedNameKey instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSItemDisplayName                          __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_4_0, __IPHONE_8_0, "Use LSCopyDisplayNameForURL or the URL resource property kCFURLLocalizedNameKey or NSURLLocalizedNameKey instead.");
/*
 *  kLSItemDisplayKind   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use LSCopyKindStringForURL or the URL resource property
 *    kCFURLLocalizedTypeDescriptionKey or NSURLLocalizedTypeDescriptionKey instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSItemDisplayKind                          __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_4_0, __IPHONE_8_0, "Use LSCopyKindStringForURL or the URL resource property kCFURLLocalizedTypeDescriptionKey or NSURLLocalizedTypeDescriptionKey instead.");
/*
 *  kLSItemRoleHandlerDisplayName   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Instead, resolve the desired role handler for the file, then use the URL resource
 *    property kCFURLLocalizedNameKey or NSURLLocalizedNameKey on the role handler's URL.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSItemRoleHandlerDisplayName               __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_4_0, __IPHONE_8_0, "Instead, resolve the desired role handler for the file, then use the URL resource property kCFURLLocalizedNameKey or NSURLLocalizedNameKey on the role handler's URL.");
/*
 *  kLSItemIsInvisible   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use the URL resource property kCFURLIsHiddenKey or NSURLIsHiddenKey instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSItemIsInvisible                          __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_4_0, __IPHONE_8_0, "Use the URL resource property kCFURLIsHiddenKey or NSURLIsHiddenKey instead.");
/*
 *  kLSItemExtensionIsHidden   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use LSSetExtensionHiddenForURL or the URL resource property
 *    kCFURLHasHiddenExtensionKey or NSURLHasHiddenExtensionKey instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSItemExtensionIsHidden                    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_4_0, __IPHONE_8_0, "Use LSSetExtensionHiddenForURL or the URL resource property kCFURLHasHiddenExtensionKey or NSURLHasHiddenExtensionKey instead.");
/*
 *  kLSItemQuarantineProperties   *** DEPRECATED ***
 *  
 *  Deprecated:
 *    Use the URL resource property kCFURLQuarantinePropertiesKey or NSURLQuarantinePropertiesKey instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kLSItemQuarantineProperties                 __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_5, __MAC_10_10, __IPHONE_4_0, __IPHONE_8_0, "Use the URL resource property kCFURLQuarantinePropertiesKey or NSURLQuarantinePropertiesKey instead.");

/*
 *  LSCopyItemAttribute()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Assigns the value of the specified item's attribute (or NULL, if
 *    the item has no such attribute or an error occurs) to *outValue.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The FSRef of the item
 *    
 *    inRoles:
 *      The role(s), at least one of which must be provided by the
 *      application selected when computing attributes related to
 *      document binding (such as kLSItemRoleHandlerDisplayName). Pass
 *      kLSRolesAll if any role is acceptable.
 *    
 *    inAttributeName:
 *      The name of the attribute to copy
 *    
 *    outValue:
 *      Receives the attribute value
 *  
 *  Result:
 *    an OSStatus value. Returns kLSAttributeNotFoundErr if the item
 *    does not have the requested attribute.
 *
 *  Deprecated:
 *    Use CFURLCopyResourcePropertyForKey or -[NSURL getResourceValue:forKey:error:] instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyItemAttribute(
  const FSRef *  inItem,
  LSRolesMask    inRoles,
  CFStringRef    inAttributeName,
  CFTypeRef *    outValue)                                    __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use CFURLCopyResourcePropertyForKey or -[NSURL getResourceValue:forKey:error:] instead.");



/*
 *  LSCopyItemAttributes()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Creates a dictionary containing the specified attribute values
 *    and assigns it to *outValues. The output dictionary keys are the
 *    attribute names. The CFTypeID of each value in the dictionary
 *    varies by attribute. See each attribute name constant for a
 *    description of its value type. An attribute key will be absent
 *    from the values dictionary if the item has no such attribute.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The FSRef of the item
 *    
 *    inRoles:
 *      The role(s), at least one of which must be provided by the
 *      application selected when computing attributes related to
 *      document binding (such as kLSItemRoleHandlerDisplayName). Pass
 *      kLSRolesAll if any role is acceptable.
 *    
 *    inAttributeNames:
 *      The array of attribute names
 *    
 *    outValues:
 *      Receives the dictionary of attribure name-value pairs
 *  
 *  Result:
 *    an OSStatus value.
 *
 *  Deprecated:
 *    Use CFURLCopyResourcePropertiesForKeys or -[NSURL resourceValuesForKeys:error:] instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSCopyItemAttributes(
  const FSRef *      inItem,
  LSRolesMask        inRoles,
  CFArrayRef         inAttributeNames,
  CFDictionaryRef *  outValues)                               __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_4, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use CFURLCopyResourcePropertiesForKeys or -[NSURL resourceValuesForKeys:error:] instead.");



/*
 *  LSSetItemAttribute()   *** DEPRECATED ***
 *  
 *  Discussion:
 *    Sets the value of a settable item's attribute. Currently, only
 *    the kLSItemQuarantineProperties attribute may be set.
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.5
 *  
 *  Parameters:
 *    
 *    inItem:
 *      The FSRef of the item
 *    
 *    inRoles:
 *      Reserved for future use. To ensure compatibility, pass
 *      kLSRolesAll for this argument.
 *    
 *    inAttributeName:
 *      The name of the attribute to set
 *    
 *    inValue:
 *      The new value of the attribute. If NULL, removes the attribute
 *      from the item.
 *  
 *  Result:
 *    an OSStatus value. Returns kLSAttributeNotSettableErr if the
 *    attribute is read-only.
 *
 *  Deprecated:
 *    Use CFURLSetResourcePropertyForKey or -[NSURL setResourceValue:forKey:error:] instead.
 *
 *  Availability:
 *    Mac OS X:         in version 10.5 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSetItemAttribute(
  const FSRef *  inItem,
  LSRolesMask    inRoles,
  CFStringRef    inAttributeName,
  CFTypeRef      inValue)               /* can be NULL */     __OSX_AVAILABLE_BUT_DEPRECATED_MSG(__MAC_10_5, __MAC_10_10, __IPHONE_NA, __IPHONE_NA, "Use CFURLSetResourcePropertyForKey or -[NSURL setResourceValue:forKey:error:] instead.");



/* ================================================================================== */
/*   API for accessing content and URL handler preferences                            */
/* ================================================================================== */

/*
 *  LSCopyDefaultRoleHandlerForContentType
 *  
 *  Returns the application bundle identifier of the default handler 
 *  for the specified content type (UTI), in the specified role(s).
 *  For any role, specify kLSRolesAll. Returns NULL if no handler
 *  is available.
 */
/*
 *  LSCopyDefaultRoleHandlerForContentType()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
LSCopyDefaultRoleHandlerForContentType(
  CFStringRef   inContentType,
  LSRolesMask   inRole)                                       __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);



/*
 *  LSCopyAllRoleHandlersForContentType
 *  
 *  Returns an array of application bundle identifiers for
 *  applications capable of handling the specified content type 
 *  (UTI) with the specified role(s). Application content handling 
 *  capabilities are determined according to the kCFBundleDocumentTypes 
 *  listed in an application's Info.plist). For any role, specify kLSRolesAll. 
 *  Returns NULL if no handlers are available.
 */
/*
 *  LSCopyAllRoleHandlersForContentType()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFArrayRef 
LSCopyAllRoleHandlersForContentType(
  CFStringRef   inContentType,
  LSRolesMask   inRole)                                       __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_NA);



/*
 *  LSSetDefaultRoleHandlerForContentType
 *  
 *  Sets the user's preferred handler for the specified content
 *  type (UTI) in the specified role(s). For all roles, specify
 *  kLSRolesAll. The handler is specified as an application
 *  bundle identifier.
 */
/*
 *  LSSetDefaultRoleHandlerForContentType()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSetDefaultRoleHandlerForContentType(
  CFStringRef   inContentType,
  LSRolesMask   inRole,
  CFStringRef   inHandlerBundleID)                            __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);



/*
 *  LSHandlerOptions
 *
 *  Options controlling how content handlers are selected.
 *
 *    kLSHandlerOptionsDefault - by default, Launch Services will
 *        use a content item's creator (when available) to select a handler
 *    kLSHandlerOptionsIgnoreCreator - Launch Services will ignore content item 
 *        creator information when selecting a role handler for the specified 
 *        content type
 */
typedef OptionBits                      LSHandlerOptions;
enum {
  kLSHandlerOptionsDefault      = 0,
  kLSHandlerOptionsIgnoreCreator = 1
};


/*
 *  LSGetHandlerOptionsForContentType
 *  
 *  Get the handler options for the specified content type (UTI).
 */
/*
 *  LSGetHandlerOptionsForContentType()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern LSHandlerOptions 
LSGetHandlerOptionsForContentType(CFStringRef inContentType)  __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);



/*
 *  LSSetHandlerOptionsForContentType
 *  
 *  Set the handler options for the specified content type (UTI).
 */
/*
 *  LSSetHandlerOptionsForContentType()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSetHandlerOptionsForContentType(
  CFStringRef        inContentType,
  LSHandlerOptions   inOptions)                               __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);



/*
 *  LSCopyDefaultHandlerForURLScheme
 *  
 *  Returns the bundle identifier of the default handler for
 *  the specified URL scheme. Returns NULL if no handler
 *  is available.
 */
/*
 *  LSCopyDefaultHandlerForURLScheme()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
LSCopyDefaultHandlerForURLScheme(CFStringRef inURLScheme)     __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);



/*
 *  LSCopyAllHandlersForURLScheme
 *  
 *  Returns an array of application bundle identifiers for
 *  applications capable of handling the specified URL scheme. 
 *  URL handling capability is determined according to the 
 *  kCFBundleURLTypes listed in an application's Info.plist).
 *  Returns NULL if no handlers are available.
 */
/*
 *  LSCopyAllHandlersForURLScheme()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern CFArrayRef 
LSCopyAllHandlersForURLScheme(CFStringRef inURLScheme)        __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);



/*
 *  LSSetDefaultHandlerForURLScheme
 *  
 *  Sets the user's preferred handler for the specified URL
 *  scheme. The handler is specified as an application
 *  bundle identifier.
 */
/*
 *  LSSetDefaultHandlerForURLScheme()
 *  
 *  Mac OS X threading:
 *    Thread safe since version 10.4
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in CoreServices.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
LSSetDefaultHandlerForURLScheme(
  CFStringRef   inURLScheme,
  CFStringRef   inHandlerBundleID)                            __OSX_AVAILABLE_STARTING(__MAC_10_4, __IPHONE_4_0);



#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif /* __LSINFO__ */

