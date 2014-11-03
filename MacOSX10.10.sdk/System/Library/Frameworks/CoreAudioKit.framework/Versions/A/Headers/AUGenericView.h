/*
     File:      AUGenericView.h
 
     Contains:  Class definition for Generic Cocoa based view for any Audio Unit
  
     Copyright: (c) 2004-2008 by Apple, Inc. All rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
*/

#import <Cocoa/Cocoa.h>
#import <CoreAudioKit/AUCustomViewPersistentData.h>

#include <AudioUnit/AudioUnit.h>

enum {
	AUViewTitleDisplayFlag			= 1 << 0,
	AUViewPropertiesDisplayFlag		= 1 << 1,
	AUViewParametersDisplayFlag		= 1 << 2
};

/*!
@class AUGenericView
@abstract  An AUGenericView object retrieves and instantiates a generic user interface view for the given audio unit
*/
@interface AUGenericView : NSView <AUCustomViewPersistentData> {
	__strong void *		_reserved[32];
}
/* @property audioUnit
@abstract Read-only property for the audio unit associated with the view
@result	  The audio unit associated with the generic view or nil on error
 */
@property (readonly) AudioUnit audioUnit;

/* @property showsExpertParameters
 @abstract Property for getting and setting whether the view is displaying expert parameters or not
 */
@property BOOL showsExpertParameters;


/*! @method initWithAudioUnit:
@abstract initializer used to create the view for a specific audio unit
@param au  The Audio Unit associated with the view
@result  Returns the newly created view object or nil on error
*/
- (AUGenericView *)initWithAudioUnit:(AudioUnit)au;
/*! @method initWithAudioUnit:displayFlags:
	@abstract initializer used to create the view for a specific audio unit with a parameter for view flags
	@param au  The Audio Unit associated with the view
	@param inFlags  The flags specifying display properties (multiple flags can be combined using the or '|' operator)
	@result  Returns the newly created view object or nil on error
*/
- (AUGenericView *)initWithAudioUnit:(AudioUnit)inAudioUnit displayFlags:(UInt32)inFlags;

@end