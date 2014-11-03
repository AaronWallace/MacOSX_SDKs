/*
 * Copyright (C) 2004, 2005, 2006, 2007, 2008, 2009 Apple Inc. All rights reserved.
 * Copyright (C) 2006 Samuel Weinig <sam.weinig@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#import <WebKit/DOMEvent.h>

#if WEBKIT_VERSION_MAX_ALLOWED >= WEBKIT_VERSION_1_3

@class DOMAbstractView;
@class NSString;

@interface DOMUIEvent : DOMEvent
@property(readonly, retain) DOMAbstractView *view;
@property(readonly) int detail;
@property(readonly) int keyCode AVAILABLE_WEBKIT_VERSION_3_0_AND_LATER;
@property(readonly) int charCode AVAILABLE_WEBKIT_VERSION_3_0_AND_LATER;
@property(readonly) int layerX AVAILABLE_WEBKIT_VERSION_3_0_AND_LATER_BUT_DEPRECATED;
@property(readonly) int layerY AVAILABLE_WEBKIT_VERSION_3_0_AND_LATER_BUT_DEPRECATED;
@property(readonly) int pageX AVAILABLE_WEBKIT_VERSION_3_0_AND_LATER;
@property(readonly) int pageY AVAILABLE_WEBKIT_VERSION_3_0_AND_LATER;
@property(readonly) int which AVAILABLE_WEBKIT_VERSION_3_0_AND_LATER;

- (void)initUIEvent:(NSString *)type canBubble:(BOOL)canBubble cancelable:(BOOL)cancelable view:(DOMAbstractView *)view detail:(int)detail AVAILABLE_WEBKIT_VERSION_3_0_AND_LATER;
@end

@interface DOMUIEvent (DOMUIEventDeprecated)
- (void)initUIEvent:(NSString *)type :(BOOL)canBubble :(BOOL)cancelable :(DOMAbstractView *)view :(int)detail AVAILABLE_WEBKIT_VERSION_1_3_AND_LATER_BUT_DEPRECATED_IN_WEBKIT_VERSION_3_0;
@end

#endif
