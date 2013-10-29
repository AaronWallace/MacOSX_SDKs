/*
	NSDocumentController.h
	Application Kit
	Copyright (c) 1997-2009, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSNibDeclarations.h>
#import <AppKit/NSUserInterfaceValidation.h>
#import <Foundation/NSDate.h>

@class NSArray, NSDocument, NSError, NSMenuItem, NSMutableDictionary, NSOpenPanel, NSURL, NSWindow;

@interface NSDocumentController : NSObject<NSCoding, NSUserInterfaceValidations> {
    @private
    id _documents;
    id _moreVars;
    NSArray *_cachedTypeDescriptions;
    NSMutableDictionary *_recents;
    int _recentsLimit;
}

#pragma mark *** The Shared Document Controller ***

/* Return the application's shared document controller. This method will create an instance of NSDocumentController if there is no shared document controller yet. Because the first instance of NSDocumentController to be allocate and initialized during application launch is used as the shared document controller, you have two options for installing an instance of a custom subclass of NSDocumentController as the shared document controller:
    1) Instantiate your NSDocumentController subclass in the application's main nib, or
    2) Allocate and initialize an instance of your subclass in your application delegate's applicationWillFinishLaunching: method.
*/
+ (id)sharedDocumentController;

/* The designated initializer. The first instance of NSDocumentController to be allocate and initialized during application launch is used as the shared document controller.
*/
- (id)init;

#pragma mark *** Currently Open Documents ***

/* Return an array of all open documents.
*/
- (NSArray *)documents;

/* Return the active document, or nil if there is no active document. The "active" document is the one corresponding to the key window, or the one corresponding to the main window if the key window has no document.
*/
- (id)currentDocument;

/* Return the path of the directory containing the active document's file or file package, if there is an active document and it has a file or file package. Return nil otherwise. The default implementation of -URLsFromRunningOpenPanel invokes this to find the current directory to set in the open panel before presenting it.
*/
- (NSString *)currentDirectory;

/* Given a URL, return the open document whose file or file package is located by the URL, or nil if there is no such open document. The default implementation of this method queries each open document to find one whose URL matches, and returns the first one whose URL does match.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self documentForFileName:[url path]] if -documentForFileName: is overridden and the URL uses the "file:" scheme.  
*/
- (id)documentForURL:(NSURL *)absoluteURL AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Given a window, return the document corresponding to the window, nil if no document corrresponds to the window.
*/
- (id)documentForWindow:(NSWindow *)window;

/* Add or remove a document from the list of open documents. You can override these methods if your application needs to customize what is done when documents are opened and closed. -addDocument is invoked by the default implementations of all NSDocumentController methods whose names start with "open." Your application can invoke -addDocument: manually if it creates a document using something other than one of NSDocument's "open" methods. -removeDocument is invoked by the default implementation of -[NSDocument close].
*/
- (void)addDocument:(NSDocument *)document;
- (void)removeDocument:(NSDocument *)document;

#pragma mark *** Document Creation ***

/* The action of the File menu's New item in a document-based application. The default implementation of this method invokes -openUntitledDocumentAndDisplay:error: and, if nil is returned, presents the error in an application-modal panel.
*/
- (IBAction)newDocument:(id)sender;

/* Create a new untitled document, present its user interface if displayDocument is YES, and return the document if successful. If not successful, return nil after setting *outError to an NSError that encapsulates the reason why a new untitled document could not be created. The default implementation of this method invokes [self defaultType] to determine the type of new document to create, invokes -makeUntitledDocumentOfType:error: to create it, then invokes -addDocument: to record its opening. If displayDocument is YES, it then sends the new document -makeWindowControllers and -showWindows messages.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self openUntitledDocumentOfType:[self defaultType] display:displayDocument] if -openUntitledDocumentOfType:display: is overridden.
*/
- (id)openUntitledDocumentAndDisplay:(BOOL)displayDocument error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Instantiate a new untitled document of the specified type and return it if successful. If not successful, return nil after setting *outError to an NSError that encapsulates the reason why a new untitled document could not be instantiated. The default implementation of this method invokes -documentClassForType: to find out the class of document to instantiate, allocates a document object, and initializes it by sending it an -initWithType:error: message.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self makeUntitledDocumentOfType:typeName] if -makeUntitledDocumentOfType: is overridden.
*/
- (id)makeUntitledDocumentOfType:(NSString *)typeName error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#pragma mark *** Document Opening ***

/* The action of the File menu's Open... item in a document-based application. The default implementation of this method invokes -URLsFromRunningOpenPanel, unless -fileNamesFromRunningOpenPanel is overridden, in which case that method is invoked instead for backward binary compatibility with Mac OS 10.3 and earlier. If something other than nil is returned, it invokes -openDocumentWithContentsOfURL:display:error: for each URL and, if nil is returned for any of them, presents the error in an application-modal panel and stops trying to open documents.
*/
- (IBAction)openDocument:(id)sender;

/* Present an application-modal open panel to the user and, if the user selects one or more files and indicates that they are to be opened, return an array of those files' URLs. Return nil otherwise. The default implementation of this method invokes -runModalOpenPanel:forTypes: after it has set up an open panel.
*/
- (NSArray *)URLsFromRunningOpenPanel;

/* Present the application-modal open panel to the user, specifying a list of UTIs (in Mac OS 10.5), file name extensions, and encoded HFS file types for openable files. Return NSOKButton or NSCancelButton depending on how the user dismisses the panel.
*/
- (NSInteger)runModalOpenPanel:(NSOpenPanel *)openPanel forTypes:(NSArray *)types;

/* Open a document located by a URL, present its user interface if displayDocuments is YES, and return the document if successful. If not  successful, return nil after setting *outError to an NSError that encapsulates the reason why the document could not be opened. The default implementation of this method checks to see if the document is already open according to -documentForURL:, and if it is not open determines the type of the document, invokes -makeDocumentWithContentsOfURL:ofType:error: to instantiate it, then invokes -addDocument: to record its opening, and sends the document -makeWindowControllers and -showWindows messages if displayDocument is YES. If the document is already open it is just sent a -showWindows message if displayDocument is YES.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self openDocumentWithContentsOfFile:[absoluteURL path] display:displayDocuments], if -openDocumentWithContentsOfFile:display: is overridden and the URL uses the "file:" scheme.
*/
- (id)openDocumentWithContentsOfURL:(NSURL *)absoluteURL display:(BOOL)displayDocument error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Instantiate a document located by a URL, of a specified type, and return it if successful. If not successful, return nil after setting *outError to an NSError that encapsulates the reason why the document could not be instantiated. The default implementation of this method invokes -documentClassForType: to find out the class of document to instantiate, allocates a document object, and initializes it by sending it an -initWithContentsOfURL:ofType:error: message.

For backward binary compatibility with Mac OS 10.3 and earlier, the default implementation of this method instead invokes [self makeDocumentWithContentsOfFile:[absoluteURL path] ofType:typeName] if -makeDocumentWithContentsOfFile:ofType: is overridden and the URL uses the "file:" scheme.
*/
- (id)makeDocumentWithContentsOfURL:(NSURL *)absoluteURL ofType:(NSString *)typeName error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#pragma mark *** Document Reopening ***

/* Reopen a document located by a URL by reading the contents for the document from another URL, present its user interface, and return YES if successful. If not  successful, return NO after setting *outError to an NSError that encapsulates the reason why the document could not be reopened. The default implementation of this method determines the type of document being reopened, sends a -makeDocumentForURL:withContentsOfURL:ofType:error: to instantiate it, then invokes -addDocument: to record its opening. It then sends the document -makeWindowControllers and -showWindows messages.
*/
- (BOOL)reopenDocumentForURL:(NSURL *)absoluteDocumentURL withContentsOfURL:(NSURL *)absoluteDocumentContentsURL error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Instantiate a document located by a URL, of a specified type, but by reading the contents for the document from another URL, and return it if successful. If not successful, return nil after setting *outError to an NSError that encapsulates the reason why the document could not be instantiated. The default implementation of this method invokes -documentClassForType: to find out the class of document to instantiate, allocates a document object, and initializes it by sending it an -initForURL:withContentsOfURL:ofType:error: message.
*/
- (id)makeDocumentForURL:(NSURL *)absoluteDocumentURL withContentsOfURL:(NSURL *)absoluteDocumentContentsURL ofType:(NSString *)typeName error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#pragma mark *** Document Autosaving ***

/* The time interval in seconds for periodic autosaving. A value of 0 indicates that periodic autosaving should not be done at all. NSDocumentController will use this number as the amount of time to wait between detecting that a document has unautosaved changes and sending the document an -autosaveDocumentWithDelegate:didAutosaveSelector:contextInfo: message. The default value is 0. You can change it to enable periodic autosaving.
*/
- (void)setAutosavingDelay:(NSTimeInterval)autosavingDelay AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSTimeInterval)autosavingDelay AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#pragma mark *** Document Saving ***

/* The action of the File menu's Save All item in a document-based application. The default implementation of this method sends each modified document a -saveDocumentWithDelegate:didSaveSelector:contextInfo: message.
*/
- (IBAction)saveAllDocuments:(id)sender;

#pragma mark *** Document Closing ***

/* Return YES if any open document is modified, NO otherwise. This method is invoked at application quitting time, to determine whether -reviewUnsavedDocumentsWithAlertTitle:cancellable:delegate:didReviewAllSelector:contextInfo: should be invoked.
*/
- (BOOL)hasEditedDocuments;

/* If there is more than one modified document, present an application-modal alert panel telling the user that there are unsaved documents and giving the option of canceling, not saving the documents, or saving the documents. If the user indicates that saving should be done, or if there was only one modified document in the first place, invoke -closeAllDocumentsWithDelegate:didCloseAllSelector:didReviewAll:contextInfo: to attempt to close all modified documents, doing whatever saving is necessary to not lose data. Finally, send the message selected by didReviewAllSelector to the delegate, with the contextInfo as the last argument. The default implementation of this method ignores the passed-in title string (which is passed in only as the result of a historical quirk). The method selected by didReviewAllSelector must have the same signature as:

    - (void)documentController:(NSDocumentController *)documentController didReviewAll:(BOOL)didReviewAll contextInfo:(void *)contextInfo;
*/
- (void)reviewUnsavedDocumentsWithAlertTitle:(NSString *)title cancellable:(BOOL)cancellable delegate:(id)delegate didReviewAllSelector:(SEL)didReviewAllSelector contextInfo:(void *)contextInfo;

/* For each open, modified, document present a document-modal alert panel asking whether the document should be saved and giving the option of canceling, not saving the document, or saving the document. Stop presenting alert panels if the user indicates cancellation in any one of them. The default implementation of this merely sends each open document -canCloseDocumentWithDelegate:shouldCloseSelector:contextInfo: and -close messages until one of them cannot be closed. The method selected by didCloseAllSelector must have the same signature as:

    - (void)documentController:(NSDocumentController *)documentController didCloseAll:(BOOL)didCloseAll contextInfo:(void *)contextInfo;
*/
- (void)closeAllDocumentsWithDelegate:(id)delegate didCloseAllSelector:(SEL)didCloseAllSelector contextInfo:(void *)contextInfo;

#pragma mark *** Error Presentation ***

/* Methods that are declared by NSResponder and also implemented by NSDocumentController, even though for historical reasons NSDocumentController is not a subclass of NSResponder. NSDocumentController's default implementations are equivalent to NSResponder's while treating the application object as the "next responder" and forwarding error presentation messages to it.

NSDocument has overrides of -presentError:modalForWindow:delegate:didPresentSelector:contextInfo: and -presentError: that treat the shared document controller as the "next responder" and forward these messages it.

The default implementations of several NSDocumentController methods invoke -presentError:.

You can customize the presentation of errors for all kinds of documents by overriding -willPresentError:. Your override should follow the advice given for overriding of -[NSResponder willPresentError:].
*/
- (void)presentError:(NSError *)error modalForWindow:(NSWindow *)window delegate:(id)delegate didPresentSelector:(SEL)didPresentSelector contextInfo:(void *)contextInfo AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (BOOL)presentError:(NSError *)error AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSError *)willPresentError:(NSError *)error AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#pragma mark *** The Open Recent Menu ***

/* Return the maximum number of items that may be presented in the standard Open Recent menu. A value of 0 indicates that NSDocumentController will not attempt to add an Open Recent menu to your application's File menu, though NSDocumentController will not attempt to remove any Open Recent menu item if there is one already there. The default implementation returns a value that is subject to change and may or may not be derived from a setting made by the user in a System Preferences panel.
*/
- (NSUInteger)maximumRecentDocumentCount AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* The action of the Open Recent menu's Clear Menu item.
*/
- (IBAction)clearRecentDocuments:(id)sender;

/* Add an item corresponding to a document to the Open Recent menu, or replace an existing item for the same document.
*/
- (void)noteNewRecentDocument:(NSDocument *)document;

/* Add an item corresponding to the data located by a URL to the Open Recent menu, or replace an existing item with the same URL. You can use this even in non-NSDocument-based applications.
*/
- (void)noteNewRecentDocumentURL:(NSURL *)absoluteURL;

/* Return an array of URLs for the entries currently appearing in the Open Recent menu.
*/
- (NSArray *)recentDocumentURLs;

#pragma mark *** Document Types ***

/* Return the name of the document type that should be used when creating new documents. The default implementation of this method returns the first Editor type declared in the application's Info.plist, or returns nil if no Editor type is declared. You can override it to customize the type of document that is created when, for instance, the user chooses New in the File menu.
*/
- (NSString *)defaultType AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Given a URL, return the name of the document type that should be used when opening the document at that location, if successful. If not successful, return nil after setting *outError to an NSError that encapsulates the reason why the document's type could not be determined, or the fact that the document's type is just unrecognized. The default implementation of this method merely returns the URL's NSURLTypeIdentifierKey resource value. You can override this to customize type determination for documents being opened.

For backward binary compatibility with Mac OS 10.4 and earlier, the default implementation of this method actually first does the same thing that it did in Mac OS 10.4 (invoke -typeFromFileExtension:, possibly twice, passing an HFS file type string for the second invocation) if there are any CFBundleDocumentTypes Info.plist entries that don't have LSItemContentTypes subentries, and only gets the URL's NSURLTypeIdentifierKey resource value if that does not succeed.
*/
- (NSString *)typeForContentsOfURL:(NSURL *)inAbsoluteURL error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Return the names of NSDocument subclasses supported by this application. The default implementation of this method returns information derived from the application's Info.plist. You can override it to return the names of document classes that are dynamically loaded from plugins.
*/
- (NSArray *)documentClassNames AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/* Given a document type name, return the subclass of NSDocument that should be instantiated when opening a document of that type, or nil for failure.
*/
- (Class)documentClassForType:(NSString *)typeName;

/* Given a document type name, return a string describing the document type that is fit to present to the user, or nil for failure.
*/
- (NSString *)displayNameForType:(NSString *)typeName;

#pragma mark *** Menu Item Validation ***

/* Conformance to the NSUserInterfaceValidations protocol. NSDocumentController's implementation of this method conditionally enables menu items for all of the action methods listed in this header file, as well as the private action method for Open Recent menu items.
*/
- (BOOL)validateUserInterfaceItem:(id <NSValidatedUserInterfaceItem>)anItem;

@end

@interface NSDocumentController(NSDeprecated)

#pragma mark *** Backward Compatibility

/* Methods that were deprecated in Mac OS 10.5, and don't work well in applications whose document types are declared with UTIs. In general, if each of the application's CFBundleDocumentTypes Info.plist entries has a valid LSItemContentTypes subentry, and the application doesn't invoke deprecated methods like -fileNamesFromRunningOpenPanel, then these methods will never be invoked from within Cocoa.
*/
- (NSArray *)fileExtensionsFromType:(NSString *)typeName DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSString *)typeFromFileExtension:(NSString *)fileNameExtensionOrHFSFileType DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Methods that were deprecated in Mac OS 10.4. See the comments above for information about when your overrides of them are still invoked, for backward binary compatibility.
*/
- (id)documentForFileName:(NSString *)fileName DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (NSArray *)fileNamesFromRunningOpenPanel DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (id)makeDocumentWithContentsOfFile:(NSString *)fileName ofType:(NSString *)type DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (id)makeDocumentWithContentsOfURL:(NSURL *)url ofType:(NSString *)type DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (id)makeUntitledDocumentOfType:(NSString *)type DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (id)openDocumentWithContentsOfFile:(NSString *)fileName display:(BOOL)display DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (id)openDocumentWithContentsOfURL:(NSURL *)url display:(BOOL)display DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (id)openUntitledDocumentOfType:(NSString*)type display:(BOOL)display DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (void)setShouldCreateUI:(BOOL)flag DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;
- (BOOL)shouldCreateUI DEPRECATED_IN_MAC_OS_X_VERSION_10_4_AND_LATER;

@end
