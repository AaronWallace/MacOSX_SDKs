/*	
	NSGlyphInfo.h
	Copyright (c) 2002-2012, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSString.h>
#import <AppKit/NSFont.h>

enum {
    NSIdentityMappingCharacterCollection = 0, // Identity mapping (CID == NSGlyph)
    NSAdobeCNS1CharacterCollection = 1, // Adobe-CNS1
    NSAdobeGB1CharacterCollection = 2, // Adobe-GB1
    NSAdobeJapan1CharacterCollection = 3, // Adobe-Japan1
    NSAdobeJapan2CharacterCollection = 4, // Adobe-Japan2
    NSAdobeKorea1CharacterCollection = 5, // Adobe-Korea1
};
typedef NSUInteger NSCharacterCollection;

@interface NSGlyphInfo : NSObject <NSCopying, NSCoding> {
    NSString *_baseString;
}

// Returns an NSGlyphInfo object for the glyph name such as "copyright."
+ (NSGlyphInfo *)glyphInfoWithGlyphName:(NSString *)glyphName forFont:(NSFont *)font baseString:(NSString *)theString;

// Returns an NSGlyphInfo object for the NSGlyph glyph
+ (NSGlyphInfo *)glyphInfoWithGlyph:(NSGlyph)glyph forFont:(NSFont *)font baseString:(NSString *)theString;

// Returns an NSGlyphInfo object for the CID/RO
+ (NSGlyphInfo *)glyphInfoWithCharacterIdentifier:(NSUInteger)cid collection:(NSCharacterCollection)characterCollection baseString:(NSString *)theString;

// Returns the glyph name.  If the receiver is instantiated without glyph name, returns nil
- (NSString *)glyphName;

// Returns CID
- (NSUInteger)characterIdentifier;

// Returns RO (character collection).  Returns NSIdentityMappingCharacterCollection if instantiated with NSGlyph or glyph name
- (NSCharacterCollection)characterCollection;
@end
