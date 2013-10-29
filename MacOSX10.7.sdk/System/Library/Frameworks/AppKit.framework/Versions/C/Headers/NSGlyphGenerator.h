/*
        NSGlyphGenerator.h
        Application Kit
        Copyright (c) 1993-2011, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSAttributedString.h>
#import <AppKit/NSFont.h> // for NSGlyph

/* NSGlyphStorage layout options */
enum {
    NSShowControlGlyphs = (1 << 0), // if set, generates displayable glyphs for control chars
    NSShowInvisibleGlyphs = (1 << 1), // if set, generates displayable glyphs for invisible chars
    NSWantsBidiLevels = (1 << 2) // if set, generates bidi levels
};

@protocol NSGlyphStorage
- (void)insertGlyphs:(const NSGlyph *)glyphs length:(NSUInteger)length forStartingGlyphAtIndex:(NSUInteger)glyphIndex characterIndex:(NSUInteger)charIndex;

// sets glyph attribute defined in NSLayoutManager.h
- (void)setIntAttribute:(NSInteger)attributeTag value:(NSInteger)val forGlyphAtIndex:(NSUInteger)glyphIndex;

- (NSAttributedString *)attributedString;
- (NSUInteger)layoutOptions;
@end

@interface NSGlyphGenerator : NSObject
- (void)generateGlyphsForGlyphStorage:(id <NSGlyphStorage>)glyphStorage desiredNumberOfCharacters:(NSUInteger)nChars glyphIndex:(NSUInteger *)glyphIndex characterIndex:(NSUInteger *)charIndex;

+ (id) sharedGlyphGenerator;
@end
