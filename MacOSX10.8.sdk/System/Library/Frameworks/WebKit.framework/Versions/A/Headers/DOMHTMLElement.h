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

#import <WebKit/DOMElement.h>

#if WEBKIT_VERSION_MAX_ALLOWED >= WEBKIT_VERSION_1_3

@class DOMHTMLCollection;
@class NSString;

@interface DOMHTMLElement : DOMElement
@property(copy) NSString *idName;
@property(copy) NSString *title;
@property(copy) NSString *lang;
@property(copy) NSString *dir;
@property(copy) NSString *className;
@property int tabIndex;
@property(copy) NSString *accessKey AVAILABLE_AFTER_WEBKIT_VERSION_5_1;
@property(copy) NSString *innerHTML;
@property(copy) NSString *innerText;
@property(copy) NSString *outerHTML;
@property(copy) NSString *outerText;
@property(readonly, retain) DOMHTMLCollection *children;
@property(copy) NSString *contentEditable;
@property(readonly) BOOL isContentEditable;
@property(readonly, copy) NSString *titleDisplayString AVAILABLE_WEBKIT_VERSION_3_0_AND_LATER;

- (void)click AVAILABLE_AFTER_WEBKIT_VERSION_5_1;
@end

#endif
