//
//  SKLabelNode.h
//  SpriteKit
//
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <SpriteKit/SKSpriteNode.h>
#import <SpriteKit/SpriteKitBase.h>

typedef NS_ENUM(NSInteger, SKLabelVerticalAlignmentMode) {
    SKLabelVerticalAlignmentModeBaseline    = 0,
    SKLabelVerticalAlignmentModeCenter      = 1,
    SKLabelVerticalAlignmentModeTop         = 2,
    SKLabelVerticalAlignmentModeBottom      = 3,
} NS_ENUM_AVAILABLE(10_9, 7_0);

typedef NS_ENUM(NSInteger, SKLabelHorizontalAlignmentMode) {
    SKLabelHorizontalAlignmentModeCenter    = 0,
    SKLabelHorizontalAlignmentModeLeft      = 1,
    SKLabelHorizontalAlignmentModeRight     = 2,
} NS_ENUM_AVAILABLE(10_9, 7_0);

/**
 A node that displays a text label with a given font.
 */
SK_EXPORT @interface SKLabelNode : SKNode

+ (instancetype)labelNodeWithFontNamed:(NSString *)fontName;

- (instancetype)initWithFontNamed:(NSString *)fontName;

@property (SK_NONATOMIC_IOSONLY) SKLabelVerticalAlignmentMode verticalAlignmentMode;
@property (SK_NONATOMIC_IOSONLY) SKLabelHorizontalAlignmentMode horizontalAlignmentMode;

@property (SK_NONATOMIC_IOSONLY, copy) NSString *fontName;
@property (SK_NONATOMIC_IOSONLY, copy) NSString *text;
@property (SK_NONATOMIC_IOSONLY) CGFloat fontSize;

/**
 Base color that the text is rendered with (if supported by the font)
 */
@property (SK_NONATOMIC_IOSONLY, retain) SKColor *fontColor;

/**
 Controls the blending between the rendered text and a color. The valid interval of values is from 0.0 up to and including 1.0. A value above or below that interval is clamped to the minimum (0.0) if below or the maximum (1.0) if above.
 */
@property (SK_NONATOMIC_IOSONLY) CGFloat colorBlendFactor;

/**
 Color to be blended with the text based on the colorBlendFactor
 */
@property (SK_NONATOMIC_IOSONLY, retain) SKColor *color;

/**
 Sets the blend mode to use when composing the sprite with the final framebuffer.
 @see SKNode.SKBlendMode
 */
@property (SK_NONATOMIC_IOSONLY) SKBlendMode blendMode;

@end
