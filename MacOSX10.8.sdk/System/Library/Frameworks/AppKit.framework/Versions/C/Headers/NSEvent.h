/*
    NSEvent.h
    Application Kit
    Copyright (c) 1994-2012, Apple Inc.
    All rights reserved.
*/

#import <AppKit/NSTouch.h>
#import <ApplicationServices/ApplicationServices.h>
#import <Foundation/NSObjCRuntime.h>
#import <Foundation/NSObject.h>
#import <Foundation/NSDate.h>
#import <Foundation/NSGeometry.h>
#import <IOKit/hidsystem/IOLLEvent.h>
#import <limits.h>

@class NSGraphicsContext, NSWindow, NSTrackingArea, NSSet;

enum {        /* various types of events */
    NSLeftMouseDown             = 1,            
    NSLeftMouseUp               = 2,
    NSRightMouseDown            = 3,
    NSRightMouseUp              = 4,
    NSMouseMoved                = 5,
    NSLeftMouseDragged          = 6,
    NSRightMouseDragged         = 7,
    NSMouseEntered              = 8,
    NSMouseExited               = 9,
    NSKeyDown                   = 10,
    NSKeyUp                     = 11,
    NSFlagsChanged              = 12,
    NSAppKitDefined             = 13,
    NSSystemDefined             = 14,
    NSApplicationDefined        = 15,
    NSPeriodic                  = 16,
    NSCursorUpdate              = 17,
    NSScrollWheel               = 22,
    NSTabletPoint               = 23,
    NSTabletProximity           = 24,
    NSOtherMouseDown            = 25,
    NSOtherMouseUp              = 26,
    NSOtherMouseDragged         = 27,
    /* The following event types are available on some hardware on 10.5.2 and later */
    NSEventTypeGesture NS_ENUM_AVAILABLE_MAC(10_5)       = 29,
    NSEventTypeMagnify NS_ENUM_AVAILABLE_MAC(10_5)       = 30,
    NSEventTypeSwipe   NS_ENUM_AVAILABLE_MAC(10_5)       = 31,
    NSEventTypeRotate  NS_ENUM_AVAILABLE_MAC(10_5)       = 18,
    NSEventTypeBeginGesture NS_ENUM_AVAILABLE_MAC(10_5)  = 19,
    NSEventTypeEndGesture NS_ENUM_AVAILABLE_MAC(10_5)    = 20,

#if __LP64__
    NSEventTypeSmartMagnify NS_ENUM_AVAILABLE_MAC(10_8) = 32,
#endif
    NSEventTypeQuickLook NS_ENUM_AVAILABLE_MAC(10_8) = 33
};
typedef NSUInteger NSEventType;

// For APIs introduced in Mac OS X 10.6 and later, this type is used with NS*Mask constants to indicate the events of interest.
typedef unsigned long long NSEventMask;

enum {                    /* masks for the types of events */
    NSLeftMouseDownMask         = 1 << NSLeftMouseDown,
    NSLeftMouseUpMask           = 1 << NSLeftMouseUp,
    NSRightMouseDownMask        = 1 << NSRightMouseDown,
    NSRightMouseUpMask          = 1 << NSRightMouseUp,
    NSMouseMovedMask            = 1 << NSMouseMoved,
    NSLeftMouseDraggedMask      = 1 << NSLeftMouseDragged,
    NSRightMouseDraggedMask     = 1 << NSRightMouseDragged,
    NSMouseEnteredMask          = 1 << NSMouseEntered,
    NSMouseExitedMask           = 1 << NSMouseExited,
    NSKeyDownMask               = 1 << NSKeyDown,
    NSKeyUpMask                 = 1 << NSKeyUp,
    NSFlagsChangedMask          = 1 << NSFlagsChanged,
    NSAppKitDefinedMask         = 1 << NSAppKitDefined,
    NSSystemDefinedMask         = 1 << NSSystemDefined,
    NSApplicationDefinedMask    = 1 << NSApplicationDefined,
    NSPeriodicMask              = 1 << NSPeriodic,
    NSCursorUpdateMask          = 1 << NSCursorUpdate,
    NSScrollWheelMask           = 1 << NSScrollWheel,
    NSTabletPointMask           = 1 << NSTabletPoint,
    NSTabletProximityMask       = 1 << NSTabletProximity,
    NSOtherMouseDownMask        = 1 << NSOtherMouseDown,
    NSOtherMouseUpMask          = 1 << NSOtherMouseUp,
    NSOtherMouseDraggedMask     = 1 << NSOtherMouseDragged,
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
    /* The following event masks are available on some hardware on 10.5.2 and later */
    NSEventMaskGesture          = 1 << NSEventTypeGesture,
    NSEventMaskMagnify          = 1 << NSEventTypeMagnify,
    NSEventMaskSwipe            = 1U << NSEventTypeSwipe,
    NSEventMaskRotate           = 1 << NSEventTypeRotate,
    NSEventMaskBeginGesture     = 1 << NSEventTypeBeginGesture,
    NSEventMaskEndGesture       = 1 << NSEventTypeEndGesture,
#endif
    
#if __LP64__
    /* Note: You can only use these event masks on 64 bit. In other words, you cannot setup a local, nor global, event monitor for these event types on 32 bit. Also, you cannot search the event que for them (nextEventMatchingMask:...) on 32 bit.
     */
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_8
    NSEventMaskSmartMagnify = 1ULL << NSEventTypeSmartMagnify,
#endif
#endif
    
    NSAnyEventMask              = NSUIntegerMax
};


#if __LP64__
NS_INLINE NSUInteger NSEventMaskFromType(NSEventType type) { return (1UL << type); }
#else
NS_INLINE NSUInteger NSEventMaskFromType(NSEventType type) { return (1 << type); }
#endif

/* Device-independent bits found in event modifier flags */
enum {
    NSAlphaShiftKeyMask         = 1 << 16,
    NSShiftKeyMask              = 1 << 17,
    NSControlKeyMask            = 1 << 18,
    NSAlternateKeyMask          = 1 << 19,
    NSCommandKeyMask            = 1 << 20,
    NSNumericPadKeyMask         = 1 << 21,
    NSHelpKeyMask               = 1 << 22,
    NSFunctionKeyMask           = 1 << 23,
    NSDeviceIndependentModifierFlagsMask    = 0xffff0000UL
};

/* pointer types for NSTabletProximity events or mouse events with subtype NSTabletProximityEventSubtype*/
enum {        
    NSUnknownPointingDevice     = NX_TABLET_POINTER_UNKNOWN,
    NSPenPointingDevice         = NX_TABLET_POINTER_PEN,
    NSCursorPointingDevice      = NX_TABLET_POINTER_CURSOR,
    NSEraserPointingDevice      = NX_TABLET_POINTER_ERASER
};
typedef NSUInteger NSPointingDeviceType;

/* button masks for NSTabletPoint events or mouse events with subtype NSTabletPointEventSubtype */
enum {
    NSPenTipMask                = NX_TABLET_BUTTON_PENTIPMASK,
    NSPenLowerSideMask          = NX_TABLET_BUTTON_PENLOWERSIDEMASK,
    NSPenUpperSideMask          = NX_TABLET_BUTTON_PENUPPERSIDEMASK
};

#if MAC_OS_X_VERSION_10_7 <= MAC_OS_X_VERSION_MAX_ALLOWED
enum {
    NSEventPhaseNone        = 0, // event not associated with a phase.
    NSEventPhaseBegan       = 0x1 << 0,
    NSEventPhaseStationary  = 0x1 << 1,
    NSEventPhaseChanged     = 0x1 << 2,
    NSEventPhaseEnded       = 0x1 << 3,
    NSEventPhaseCancelled   = 0x1 << 4,
    NSEventPhaseMayBegin    = 0x1 << 5,
};
#endif
typedef NSUInteger NSEventPhase;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
enum {
    NSEventGestureAxisNone = 0,
    NSEventGestureAxisHorizontal,
    NSEventGestureAxisVertical
};
#endif
typedef NSInteger NSEventGestureAxis;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_7
enum {
    NSEventSwipeTrackingLockDirection = 0x1 << 0, // Clamp gestureAmount to 0 if the user starts to swipe in the opposite direction than they started.
    NSEventSwipeTrackingClampGestureAmount = 0x1 << 1  // Don't allow gestureAmount to go beyond +/-1.0
};
#endif
typedef NSUInteger NSEventSwipeTrackingOptions;

@interface NSEvent : NSObject <NSCopying, NSCoding> {
    /*All instance variables are private*/
    NSEventType _type;
    NSPoint _location;
    unsigned int _modifierFlags;
    id _WSTimestamp;
    NSTimeInterval _timestamp;
    NSInteger _windowNumber;
    NSWindow *_window;
    NSGraphicsContext* _context;
    union {
        struct {
            int eventNumber;
            int clickCount;
            float pressure;
#if __LP64__
            CGFloat deltaX;
            CGFloat deltaY;
            int subtype;
            short buttonNumber;
            short reserved1;
            int reserved2[3];
#endif
        } mouse;
        struct {
            NSString *keys;
            NSString *unmodKeys;
            unsigned short keyCode;
            BOOL isARepeat;
#if __LP64__
            int eventFlags;
            int reserved[5];
#endif
        } key;
        struct {
            int eventNumber;
            NSInteger trackingNumber;
            void *userData;
#if __LP64__
            int reserved[6];
#endif
        } tracking;
        struct {
            CGFloat deltaX;
            CGFloat deltaY;
            CGFloat deltaZ; 
#if __LP64__
            short subtype;
            short reserved1;
            int reserved2[6];
#endif
        } scrollWheel;
        struct {
            CGFloat deltaX;
            CGFloat deltaY;
            CGFloat deltaZ; 
#if __LP64__
            int reserved[7];
#endif
        } axisGesture;
        struct {
            short subtype;
            BOOL gestureEnded;
            BOOL reserved;
            int value;
            float percentage;
#if __LP64__
            int reserved2[7];
#endif
        } miscGesture;
        struct {
            int subtype;
            NSInteger data1;
            NSInteger data2;
#if __LP64__
            int reserved[6];
#endif
        } misc;
#if __LP64__
        int tabletPointData[14];
        int tabletProximityData[14];
#endif
    } _data;
    void *_eventRef;
#if __LP64__
    void *reserved1;
    void *reserved2;
#endif
}


/* these messages are valid for all events */
- (NSEventType)type;
- (NSUInteger)modifierFlags;
- (NSTimeInterval)timestamp;
- (NSWindow *)window;
- (NSInteger)windowNumber;
- (NSGraphicsContext*)context;

/* these messages are valid for all mouse down/up/drag events */
- (NSInteger)clickCount;
- (NSInteger)buttonNumber;    // for NSOtherMouse events, but will return valid constants for NSLeftMouse and NSRightMouse
/* these messages are valid for all mouse down/up/drag and enter/exit events */
- (NSInteger)eventNumber;

/* -pressure is valid for all mouse down/up/drag events, and is also valid for NSTabletPoint events on 10.4 or later */
- (float)pressure;
/* -locationInWindow is valid for all mouse-related events */
- (NSPoint)locationInWindow;

/* these messages are valid for scroll wheel events and mouse move/drag events.  As of 10.5.2, deltaX and deltaY are also valid for swipe events.  A non-0 deltaX will represent a horizontal swipe, -1 for swipe right and 1 for swipe left.  A non-0 deltaY will represent a vertical swipe, -1 for swipe down and 1 for swipe up. As of 10.7, the preferred methods for scroll wheel events are scrollingDeltaX and scrollingDeltaY defined below.
*/
- (CGFloat)deltaX;    
- (CGFloat)deltaY;    
- (CGFloat)deltaZ;    // 0 for most scroll wheel and mouse events

/* This message is valid for NSScrollWheel events. A generic scroll wheel issues rather coarse scroll deltas. Some Apple mice and trackpads provide much more precise delta. This method determines the resolution of the scrollDeltaX and scrollDeltaY values.
*/
- (BOOL)hasPreciseScrollingDeltas NS_AVAILABLE_MAC(10_7);

/* The following two message are the preferred API for accessing NSScrollWheel deltas. When -hasPreciseScrollDeltas reutrns NO, multiply the returned value by line or row height. When -hasPreciseScrollDeltas returns YES, scroll by the returned value (in points). 
*/
- (CGFloat)scrollingDeltaX NS_AVAILABLE_MAC(10_7);
- (CGFloat)scrollingDeltaY NS_AVAILABLE_MAC(10_7);

/* This message is valid for NSScrollWheel events. With the Magic Mouse and some trackpads, the user can flick thier finger resulting in a stream of scroll events that dissipate over time. The location of these scroll wheel events changes as the user moves the cursor. AppKit latches these scroll wheel events to the view that is under the cursor when the flick occurs. A custom view can use this method to recognize these momentum scroll events and further route the event to the appropriate sub component.
*/
- (NSEventPhase)momentumPhase NS_AVAILABLE_MAC(10_7);

/* valid for NSEventScrollWheel events. The user may choose to change the scrolling behavior such that it feels like they are moving the content instead of the scroll bar. To accomplish this, deltaX/Y and scrollingDeltaX/Y are automatically inverted for NSEventScrollWheel events according to the user's preferences. However, for some uses, the behavior should not respect the user preference. This method allows you to determine when the event has been inverted and compensate by multiplying -1 if needed. 
*/
- (BOOL)isDirectionInvertedFromDevice NS_AVAILABLE_MAC(10_7);

/* these messages are valid for keyup and keydown events */
- (NSString *)characters;
- (NSString *)charactersIgnoringModifiers;
  /* the chars that would have been generated, regardless of modifier keys (except shift) */
- (BOOL)isARepeat;
/* this message is valid for keyup, keydown and flagschanged events */
- (unsigned short)keyCode;        /* device-independent key number */

/* these messages are valid for enter and exit events */
- (NSInteger)trackingNumber;
- (void *)userData NS_RETURNS_INNER_POINTER;
/* -trackingArea returns the NSTrackingArea that generated this event.  It is possible for there to be no trackingArea associated with the event in some cases where the event corresponds to a trackingRect installed with -[NSView addTrackingRect:owner:userData:assumeInside:], in which case nil is returned. */
- (NSTrackingArea *)trackingArea NS_AVAILABLE_MAC(10_5); 

/* this message is valid for kit, system, and app-defined events */
/* this message is also valid for mouse events on 10.4 or later */
- (short)subtype;

/* these messages are valid for kit, system, and app-defined events */
- (NSInteger)data1;
- (NSInteger)data2;


/* -eventRef and +eventWithEventRef:  are valid for all events */
/* -eventRef returns an EventRef corresponding to the NSEvent.  The EventRef is retained by the NSEvent, so will be valid as long as the NSEvent is valid, and will be released when the NSEvent is freed.  You can use RetainEvent to extend the lifetime of the EventRef, with a corresponding ReleaseEvent when you are done with it.  If there is no EventRef corresponding to the NSEvent, -eventRef will return NULL.
*/
- (const void * /* EventRef */)eventRef NS_RETURNS_INNER_POINTER NS_AVAILABLE_MAC(10_5);
/* +eventWithEventRef: returns an autoreleased NSEvent corresponding to the EventRef.  The EventRef is retained by the NSEvent and will be released when the NSEvent is freed.  If there is no NSEvent corresponding to the EventRef, +eventWithEventRef will return nil.
*/
+ (NSEvent *)eventWithEventRef:(const void * /* EventRef */)eventRef NS_AVAILABLE_MAC(10_5);

/* -CGEvent returns an autoreleased CGEventRef corresponding to the NSEvent.  If there is no CGEventRef corresponding to the NSEvent, -CGEvent will return NULL.
*/
- (CGEventRef)CGEvent NS_AVAILABLE_MAC(10_5);

/* +eventWithCGEvent: returns an autoreleased NSEvent corresponding to the CGEventRef.  The CGEventRef is retained by the NSEvent and will be released when the NSEvent is freed.  If there is no NSEvent corresponding to the CGEventRef, +eventWithEventRef will return nil.
*/
+ (NSEvent *)eventWithCGEvent:(CGEventRef)cgEvent NS_AVAILABLE_MAC(10_5);

/* Enable or disable coalescing of mouse movement events, including mouse moved, mouse dragged, and tablet events.  Coalescing is enabled by default.
*/
+ (void)setMouseCoalescingEnabled:(BOOL)flag NS_AVAILABLE_MAC(10_5);
+ (BOOL)isMouseCoalescingEnabled NS_AVAILABLE_MAC(10_5);


/* This message is valid for events of type NSEventTypeMagnify, on 10.5.2 or later */
- (CGFloat)magnification NS_AVAILABLE_MAC(10_5);       // change in magnification.   This value should be added to the current scaling of an item to get the new scale factor.

/* this message is valid for mouse events with subtype NSTabletPointEventSubtype or NSTabletProximityEventSubtype, and for NSTabletPoint and NSTabletProximity events */
- (NSUInteger)deviceID;

/* this message is valid for valid for mouse events with subtype NSTabletPointEventSubtype, and for NSTabletPoint events.  On 10.5.2 or later, it is also valid for NSEventTypeRotate events. */
- (float)rotation;       // In degrees.  For NSTabletPoint, this is rotation of the pen.  For NSEventTypeRotate, it is rotation on the track pad.

/* these messages are valid for mouse events with subtype NSTabletPointEventSubtype, and for NSTabletPoint events */
/* absolute x coordinate in tablet space at full tablet resolution */
- (NSInteger)absoluteX; 
/* absolute y coordinate in tablet space at full tablet resolution */
- (NSInteger)absoluteY;               
/* absolute z coordinate in tablet space at full tablet resolution */
- (NSInteger)absoluteZ;     
/* mask indicating which buttons are pressed.*/
- (NSUInteger)buttonMask;  
/* range is -1 to 1 for both axes */
- (NSPoint)tilt;     
/* tangential pressure on the device; range is -1 to 1 */
- (float)tangentialPressure;  
/* NSArray of 3 vendor defined shorts */
- (id)vendorDefined;    

/* these messages are valid for mouse events with subtype NSTabletProximityEventSubtype, and  for NSTabletProximity events */
/* vendor defined, typically USB vendor ID */
- (NSUInteger)vendorID;
/* vendor defined tablet ID */
- (NSUInteger)tabletID;
/* index of the device on the tablet.  Usually 0, except for tablets that support multiple concurrent devices */
- (NSUInteger)pointingDeviceID;
/* system assigned unique tablet ID */
- (NSUInteger)systemTabletID;
/* vendor defined pointing device type */
- (NSUInteger)vendorPointingDeviceType; 
/* vendor defined serial number of pointing device */
- (NSUInteger)pointingDeviceSerialNumber; 
/* vendor defined unique ID */
- (unsigned long long)uniqueID;    
/* mask representing capabilities of device */
- (NSUInteger)capabilityMask;    
/* mask representing capabilities of device */
- (NSPointingDeviceType)pointingDeviceType;
/* YES - entering; NO - leaving */
- (BOOL)isEnteringProximity;    


- (NSSet *)touchesMatchingPhase:(NSTouchPhase)phase inView:(NSView*)view NS_AVAILABLE_MAC(10_6);

/* The phase of a gesture scroll event. A gesture phrase are all the events that begin with a NSEventPhaseBegan and end with either a NSEventPhaseEnded or NSEventPhaseCancelled. All the gesture events are sent to the view under the cursor when the NSEventPhaseBegan occurred.  A gesture scroll event starts with a NSEventPhaseBegan phase and ends with a NSPhaseEnded. Legacy scroll wheel events (say from a Mighty Mouse) and momentum scroll wheel events have a phase of NSEventPhaseNone.
    Valid for NSScrollWheel
*/
- (NSEventPhase)phase NS_AVAILABLE_MAC(10_7);

/* Returns the user's preference about using gesture scrolls as a way to track fluid swipes. This value is determined by the Mouse / Trackpad preference panel for the current user. Generally, NSScrollView will check this for you. However, if your app is not using an NSScrollView, or your NSResponder can receive scrollWheel messages without first being sent to an NSScrollView, then you should check this preference before calling -trackSwipeEventWithOptions:dampenAmountThresholdMin:max:usingHandler:
*/
+ (BOOL)isSwipeTrackingFromScrollEventsEnabled NS_AVAILABLE_MAC(10_7);

/* This method allows easy tracking and UI feedback of scroll events as fluid swipes. Fluid swipes are tracked not only to the end of the physical gesture phase by the user, but also to the completion of any UI animation that should be performed. Using this method allows your implementation to maintain a consistent fluid feel with other applications. Any gesture amount outside of the supplied minimum and maximum dampen amount is pre-dampened for you to provide an elastic feel.

   The trackingHandler has the following parameters:
       gestureAmount: the amount of gesture that you should display in the UI. This may be a fractional amount. Note: Upon completion, the gesture amount will animate to one of the following values: -1, 0, 1.
       phase: the phase of the physical gesture as performed by the user. When the phase is either NSPhaseEnded, or NSPhaseCancelled, the use has physically ended the gesture successfully or not, respectively. Your handler will continue to be called with updated progress values to complete the fluid swipe animation with a phase of NSPhaseNone.
       isComplete: Signifies the swipe and animation are complete and you should tear down any temporary animation objects. The trackingHandler is released and will not be called further.
      *stop: A pointer to a BOOL allowing you to cancel further use of this trackingHandler by setting its value to YES. The trackingHandler is released appropriately.

   Note: This method returns immediately and tracking is performed asynchronously.

   Valid for Scroll events with a phase of NSEventPhaseBegan or NSEventPhaseChanged
*/
- (void)trackSwipeEventWithOptions:(NSEventSwipeTrackingOptions)options dampenAmountThresholdMin:(CGFloat)minDampenThreshold max:(CGFloat)maxDampenThreshold usingHandler:(void (^)(CGFloat gestureAmount, NSEventPhase phase, BOOL isComplete, BOOL *stop))trackingHandler NS_AVAILABLE_MAC(10_7);

/* used for initial delay and periodic behavior in tracking loops */
+ (void)startPeriodicEventsAfterDelay:(NSTimeInterval)delay withPeriod:(NSTimeInterval)period;
+ (void)stopPeriodicEvents;

/* apps will rarely create these objects */
+ (NSEvent *)mouseEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSUInteger)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(NSGraphicsContext*)context eventNumber:(NSInteger)eNum clickCount:(NSInteger)cNum pressure:(float)pressure;
+ (NSEvent *)keyEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSUInteger)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(NSGraphicsContext*)context characters:(NSString *)keys charactersIgnoringModifiers:(NSString *)ukeys isARepeat:(BOOL)flag keyCode:(unsigned short)code;
+ (NSEvent *)enterExitEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSUInteger)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(NSGraphicsContext*)context eventNumber:(NSInteger)eNum trackingNumber:(NSInteger)tNum userData:(void *)data;
+ (NSEvent *)otherEventWithType:(NSEventType)type location:(NSPoint)location modifierFlags:(NSUInteger)flags timestamp:(NSTimeInterval)time windowNumber:(NSInteger)wNum context:(NSGraphicsContext*)context subtype:(short)subtype data1:(NSInteger)d1 data2:(NSInteger)d2;

// global mouse coordinates
+ (NSPoint)mouseLocation;

/* modifier keys currently down.  This returns the state of devices combined with synthesized events at the moment, independent of which events have been delivered via the event stream. */
+ (NSUInteger)modifierFlags NS_AVAILABLE_MAC(10_6);

/* mouse buttons currently down.  Returns indices of the mouse buttons currently down.  1 << 0 corresponds to leftMouse, 1 << 1 to rightMouse, and 1 << n, n >= 2 to other mouse buttons.  This returns the state of devices combined with synthesized events at the moment, independent of which events have been delivered via the event stream, so this method is not suitable for tracking. */
+ (NSUInteger)pressedMouseButtons NS_AVAILABLE_MAC(10_6);

/* the time in which a second click must occur in order to be considered a doubleClick.  This is a system value so overrides will have no effect. */
+ (NSTimeInterval)doubleClickInterval   NS_AVAILABLE_MAC(10_6);
/* the time for which a key must be held down in order to generate the first key repeat event.  This is a system value so overrides will have no effect. */
+ (NSTimeInterval)keyRepeatDelay        NS_AVAILABLE_MAC(10_6);
/* the time between subsequent key repeat events.  This is a system value so overrides will have no effect. */
+ (NSTimeInterval)keyRepeatInterval     NS_AVAILABLE_MAC(10_6);

/*
   API for monitoring events in other processes, or in your own process. For either +addGlobal or +addLocal, pass an event mask specifying which events you wish to monitor, and a block that will be called with the event to monitor.

   Use +addGlobal to install an event monitor that receives copies of events posted to other applications. Events are delivered asynchronously to your app and you can only observe the event; you cannot modify or otherwise prevent the event from being delivered to its original target application. Key-related events may only be monitored if accessibility is enabled or if your application is trusted for accessibility access (see AXIsProcessTrusted in AXUIElement.h). Note that your handler will not be called for events that are sent to your own application.

   Use +addLocal to install an event monitor that receives events before they are dispatched by -[NSApplication sendEvent:]. In this case, your block should either return a valid NSEvent (which may be the same as the incoming NSEvent, or may be a newly created NSEvent) to cause the event to be dispatched, or it may return nil to stop dispatching of the event. Note that your handler will not be called for events that are consumed by nested event-tracking loops such as control tracking, menu tracking, or window dragging; only events that are dispatched through -[NSApplication sendEvent:] will be passed to your handler.

   In either case, the return value of the API is a retained NSObject. You typically do not need to retain and release the event monitor yourself, since the implementation will retain it while needed.
   
   To remove the event monitor, under both garbage collection and non-GC, pass the return value from the +add API to +removeMonitor.
*/
#if NS_BLOCKS_AVAILABLE
+ (id)addGlobalMonitorForEventsMatchingMask:(NSEventMask)mask handler:(void (^)(NSEvent*))block NS_AVAILABLE_MAC(10_6);
+ (id)addLocalMonitorForEventsMatchingMask:(NSEventMask)mask handler:(NSEvent* (^)(NSEvent*))block NS_AVAILABLE_MAC(10_6);
+ (void)removeMonitor:(id)eventMonitor NS_AVAILABLE_MAC(10_6);
#endif

@end


/* Unicodes we reserve for function keys on the keyboard,  OpenStep reserves the range 0xF700-0xF8FF for this purpose.  The availability of various keys will be system dependent. */
enum {
    NSUpArrowFunctionKey        = 0xF700,
    NSDownArrowFunctionKey      = 0xF701,
    NSLeftArrowFunctionKey      = 0xF702,
    NSRightArrowFunctionKey     = 0xF703,
    NSF1FunctionKey             = 0xF704,
    NSF2FunctionKey             = 0xF705,
    NSF3FunctionKey             = 0xF706,
    NSF4FunctionKey             = 0xF707,
    NSF5FunctionKey             = 0xF708,
    NSF6FunctionKey             = 0xF709,
    NSF7FunctionKey             = 0xF70A,
    NSF8FunctionKey             = 0xF70B,
    NSF9FunctionKey             = 0xF70C,
    NSF10FunctionKey            = 0xF70D,
    NSF11FunctionKey            = 0xF70E,
    NSF12FunctionKey            = 0xF70F,
    NSF13FunctionKey            = 0xF710,
    NSF14FunctionKey            = 0xF711,
    NSF15FunctionKey            = 0xF712,
    NSF16FunctionKey            = 0xF713,
    NSF17FunctionKey            = 0xF714,
    NSF18FunctionKey            = 0xF715,
    NSF19FunctionKey            = 0xF716,
    NSF20FunctionKey            = 0xF717,
    NSF21FunctionKey            = 0xF718,
    NSF22FunctionKey            = 0xF719,
    NSF23FunctionKey            = 0xF71A,
    NSF24FunctionKey            = 0xF71B,
    NSF25FunctionKey            = 0xF71C,
    NSF26FunctionKey            = 0xF71D,
    NSF27FunctionKey            = 0xF71E,
    NSF28FunctionKey            = 0xF71F,
    NSF29FunctionKey            = 0xF720,
    NSF30FunctionKey            = 0xF721,
    NSF31FunctionKey            = 0xF722,
    NSF32FunctionKey            = 0xF723,
    NSF33FunctionKey            = 0xF724,
    NSF34FunctionKey            = 0xF725,
    NSF35FunctionKey            = 0xF726,
    NSInsertFunctionKey         = 0xF727,
    NSDeleteFunctionKey         = 0xF728,
    NSHomeFunctionKey           = 0xF729,
    NSBeginFunctionKey          = 0xF72A,
    NSEndFunctionKey            = 0xF72B,
    NSPageUpFunctionKey         = 0xF72C,
    NSPageDownFunctionKey       = 0xF72D,
    NSPrintScreenFunctionKey    = 0xF72E,
    NSScrollLockFunctionKey     = 0xF72F,
    NSPauseFunctionKey          = 0xF730,
    NSSysReqFunctionKey         = 0xF731,
    NSBreakFunctionKey          = 0xF732,
    NSResetFunctionKey          = 0xF733,
    NSStopFunctionKey           = 0xF734,
    NSMenuFunctionKey           = 0xF735,
    NSUserFunctionKey           = 0xF736,
    NSSystemFunctionKey         = 0xF737,
    NSPrintFunctionKey          = 0xF738,
    NSClearLineFunctionKey      = 0xF739,
    NSClearDisplayFunctionKey   = 0xF73A,
    NSInsertLineFunctionKey     = 0xF73B,
    NSDeleteLineFunctionKey     = 0xF73C,
    NSInsertCharFunctionKey     = 0xF73D,
    NSDeleteCharFunctionKey     = 0xF73E,
    NSPrevFunctionKey           = 0xF73F,
    NSNextFunctionKey           = 0xF740,
    NSSelectFunctionKey         = 0xF741,
    NSExecuteFunctionKey        = 0xF742,
    NSUndoFunctionKey           = 0xF743,
    NSRedoFunctionKey           = 0xF744,
    NSFindFunctionKey           = 0xF745,
    NSHelpFunctionKey           = 0xF746,
    NSModeSwitchFunctionKey     = 0xF747
};


enum {        /* event subtypes for NSAppKitDefined events */
    NSWindowExposedEventType            = 0,
    NSApplicationActivatedEventType     = 1,
    NSApplicationDeactivatedEventType   = 2,
    NSWindowMovedEventType              = 4,
    NSScreenChangedEventType            = 8,
    NSAWTEventType                      = 16
};

enum {        /* event subtypes for NSSystemDefined events */
    NSPowerOffEventType             = 1
};


enum {        /* event subtypes for mouse events */
    NSMouseEventSubtype             = NX_SUBTYPE_DEFAULT,
    NSTabletPointEventSubtype       = NX_SUBTYPE_TABLET_POINT,
    NSTabletProximityEventSubtype   = NX_SUBTYPE_TABLET_PROXIMITY,
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
    NSTouchEventSubtype             = NX_SUBTYPE_MOUSE_TOUCH
#endif
};

