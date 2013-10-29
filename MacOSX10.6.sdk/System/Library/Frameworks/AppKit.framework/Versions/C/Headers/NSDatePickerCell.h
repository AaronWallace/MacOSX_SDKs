/*
	NSDatePickerCell.h
	Application Kit
	Copyright (c) 2004-2009, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSDate.h>
#import <AppKit/NSActionCell.h>

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

enum {
    NSTextFieldAndStepperDatePickerStyle    = 0,
    NSClockAndCalendarDatePickerStyle       = 1,
    NSTextFieldDatePickerStyle              = 2
};
typedef NSUInteger NSDatePickerStyle;

enum {
    NSSingleDateMode = 0,
    NSRangeDateMode = 1
};
typedef NSUInteger NSDatePickerMode;

typedef NSUInteger NSDatePickerElementFlags;
enum {
    /* Time Elements */
    NSHourMinuteDatePickerElementFlag       = 0x000c,
    NSHourMinuteSecondDatePickerElementFlag = 0x000e,
    NSTimeZoneDatePickerElementFlag	    = 0x0010,

    /* Date Elements */
    NSYearMonthDatePickerElementFlag	    = 0x00c0,
    NSYearMonthDayDatePickerElementFlag	    = 0x00e0,
    NSEraDatePickerElementFlag		    = 0x0100,
};

@class NSCalendar, NSLocale, NSTimeZone;
@protocol NSDatePickerCellDelegate;

@interface NSDatePickerCell : NSActionCell
{
@private
    NSTimeInterval _timeInterval;
    NSDate *_minDate;
    NSDate *_maxDate;
    struct __dateCellFlags {
        unsigned int elements:16;
        unsigned int controlStyle:3;
        unsigned int controlMode:2;
        unsigned int trackingHand:2;
        unsigned int reserved2:4;
        unsigned int drawsBackground:1;
        unsigned int digitsEntered:2;
        unsigned int forcesLeadingZeroes:1;
        unsigned int wrapsDateComponentArithmetic:1;
    } _dcFlags;
    id _delegate;
    NSCalendar *_calendar;
    NSLocale *_locale;
    NSTimeZone *_timeZone;
    NSColor *_backgroundColor;
    NSColor *_textColor;
    int _indexOfSelectedSubfield;
    int _reserved0;
    id _reserved1;
    id _reserved2;
    id _reserved3;
    id _reserved4;
}

#pragma mark *** Appearance Control ***

- (NSDatePickerStyle)datePickerStyle;
- (void)setDatePickerStyle:(NSDatePickerStyle)newStyle;

- (BOOL)drawsBackground;
- (void)setDrawsBackground:(BOOL)flag;

- (NSColor *)backgroundColor;
- (void)setBackgroundColor:(NSColor *)color;

- (NSColor *)textColor;
- (void)setTextColor:(NSColor *)color;

#pragma mark *** Range Mode Control ***

- (NSDatePickerMode)datePickerMode;
- (void)setDatePickerMode:(NSDatePickerMode)newMode;

#pragma mark *** Date Presentation Control ***

- (NSDatePickerElementFlags)datePickerElements;
- (void)setDatePickerElements:(NSDatePickerElementFlags)elementFlags;

- (NSCalendar *)calendar;
- (void)setCalendar:(NSCalendar *)newCalendar;

- (NSLocale *)locale;
- (void)setLocale:(NSLocale *)newLocale;

- (NSTimeZone *)timeZone;
- (void)setTimeZone:(NSTimeZone *)newTimeZone;

#pragma mark *** Object Value Access ***

- (NSDate *)dateValue;
- (void)setDateValue:(NSDate *)newStartDate;

- (NSTimeInterval)timeInterval;
- (void)setTimeInterval:(NSTimeInterval)newTimeInterval;

#pragma mark *** Constraints on Displayable/Selectable Range ***

- (NSDate *)minDate;
- (void)setMinDate:(NSDate *)date;

- (NSDate *)maxDate;
- (void)setMaxDate:(NSDate *)date;

#pragma mark *** Delegate ***

- (id <NSDatePickerCellDelegate>)delegate;
- (void)setDelegate:(id <NSDatePickerCellDelegate>)anObject;

@end

@protocol NSDatePickerCellDelegate <NSObject>
@optional
- (void)datePickerCell:(NSDatePickerCell *)aDatePickerCell validateProposedDateValue:(NSDate **)proposedDateValue timeInterval:(NSTimeInterval *)proposedTimeInterval;
@end

#endif
