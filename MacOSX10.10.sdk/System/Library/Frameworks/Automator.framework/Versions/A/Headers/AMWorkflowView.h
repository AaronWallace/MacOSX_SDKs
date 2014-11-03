/*	
    AMWorkflowView.h
    Copyright (C) 2005-2006, 2014 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Cocoa/Cocoa.h>
#import <Automator/AMAttributesForAnalyzer.h>

@class AMWorkflow;
@class AMWorkflowController;

@interface AMWorkflowView : NSView {
@private
	AMWorkflowController *_workflowController;
	NSMutableArray *_actionViewControllers;
	NSArray *_draggedActionViews;
	NSString *_messageString;
	id _unused;
	id _variablesEditorController;
	AM_UNUSED_FOR_ANALYZER id _showWhenRunController;
	struct __AMWorkflowViewFlags {
		BOOL ignoreSubviewFrameChanges:1;
		BOOL editingEnabled:1;
        NSUInteger reserved:30;
    } _flags;
	NSUInteger _draggingIndex;
	NSRect _selectionRect;
	
	id _future[4];
}

@property (getter=isEditable) BOOL editable;

@property (strong) AMWorkflowController *workflowController;

@end

