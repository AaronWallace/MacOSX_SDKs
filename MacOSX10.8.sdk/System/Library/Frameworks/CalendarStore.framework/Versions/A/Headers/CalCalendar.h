//	
//	CalCalendar.h
//	Calendar Store Framework
//	
//  Copyright 2006 Apple Computer, Inc. All rights reserved.
//	
//	This class can be used to get attributes of a calendar, but cannot be used to get the list of events or tasks in a calendar. 
//	Instead use CalCalendarStore's eventsFromPredicate: and tasksFromPredicate: methods.
//
//  The Calendar Store framework is deprecated.  Please use the Event Kit framework instead.

@class NSColor;

extern NSString * const CalCalendarTypeBirthday NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalCalendarTypeCalDAV NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalCalendarTypeLocal NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalCalendarTypeSubscription NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalCalendarTypeIMAP NS_DEPRECATED_MAC(10_5, 10_8);
extern NSString * const CalCalendarTypeExchange  NS_DEPRECATED_MAC(10_6, 10_8);

@interface CalCalendar : NSObject <NSCopying>
{
    @private
    id _objectID;
	id _group;
    void *_reserved;
	NSColor *_color;
	NSString *_notes;
	NSString *_title;
	NSString *_type;
	NSString *_uid;
	BOOL _isEditable;
}

//  All calendars created with this API will be of type CalCalendarTypeLocal
+ (id)calendar NS_DEPRECATED_MAC(10_5, 10_8);

@property(copy) NSColor *color NS_DEPRECATED_MAC(10_5, 10_8);
@property(copy) NSString *notes NS_DEPRECATED_MAC(10_5, 10_8);
@property(copy) NSString *title NS_DEPRECATED_MAC(10_5, 10_8);
@property(readonly) NSString *type NS_DEPRECATED_MAC(10_5, 10_8);
@property(readonly) NSString *uid NS_DEPRECATED_MAC(10_5, 10_8);
@property(readonly) BOOL isEditable NS_DEPRECATED_MAC(10_5, 10_8);

@end
