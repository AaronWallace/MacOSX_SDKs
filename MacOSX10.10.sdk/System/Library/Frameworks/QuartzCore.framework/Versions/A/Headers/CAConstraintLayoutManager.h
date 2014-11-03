/* CoreAnimation - CAConstraintLayoutManager.h

   Copyright (c) 2006-2014, Apple Inc.
   All rights reserved. */

#import <QuartzCore/CALayer.h>

/* The constraint-based layout manager add a `constraints' layer
 * property, an array of CAConstraint objects. Each object describes
 * one geometry relationship between two layers. Layout is then
 * performed by fetching the constraints of each sublayer and solving
 * the resulting system of constraints for the frame of each sublayer
 * starting from the bounds of the containing layer.
 *
 * The relationships between layers are linear equations of the form:
 *
 *  u = m v + c
 *
 * where 'u' and 'v' are scalar values representing geometry attributes
 * of the two layers (e.g. leftmost x position), and 'm' and 'c' are
 * constants.
 *
 * Sibling layers are referenced by name, using the `name' property of
 * each layer. The special name "superlayer" should be used to refer to
 * the layer's superlayer. */

typedef NS_ENUM (int, CAConstraintAttribute)
{
  kCAConstraintMinX,
  kCAConstraintMidX,
  kCAConstraintMaxX,
  kCAConstraintWidth,
  kCAConstraintMinY,
  kCAConstraintMidY,
  kCAConstraintMaxY,
  kCAConstraintHeight,
};

@class CAConstraint;

/** The additions to CALayer for constraint layout. **/

@interface CALayer (CAConstraintLayoutManager)

/* The layer's array of CAConstraint objects. */

@property(copy) NSArray *constraints;

/* Append 'c' to the receiver's array of constraint objects. */

- (void)addConstraint:(CAConstraint *)c;

@end

/** The constraint-based layout manager. **/

@interface CAConstraintLayoutManager : NSObject

/* Returns a new layout manager object. */

+ (id)layoutManager;

@end

/** The class representing a single layout constraint. **/

@interface CAConstraint : NSObject <NSCoding>
{
@private
  NSString *_srcId;
  CAConstraintAttribute _srcAttr :16;
  CAConstraintAttribute _attr :16;
  CGFloat _scale, _offset;
};

/* Create a new constraint object with the specified parameters. In the
 * general case the new constraint will have the form:
 * 
 *	layer.attr = m * srcLayer.srcAttr + c
 *
 * 'm' defaults to one when undefined; 'c' defaults to zero. */

+ (id)constraintWithAttribute:(CAConstraintAttribute)attr
    relativeTo:(NSString *)srcId attribute:(CAConstraintAttribute)srcAttr
    scale:(CGFloat)m offset:(CGFloat)c;
+ (id)constraintWithAttribute:(CAConstraintAttribute)attr
    relativeTo:(NSString *)srcId attribute:(CAConstraintAttribute)srcAttr
    offset:(CGFloat)c;
+ (id)constraintWithAttribute:(CAConstraintAttribute)attr
    relativeTo:(NSString *)srcId attribute:(CAConstraintAttribute)srcAttr;

/* Designated initializer. */

- (id)initWithAttribute:(CAConstraintAttribute)attr
    relativeTo:(NSString *)srcId attribute:(CAConstraintAttribute)srcAttr
    scale:(CGFloat)m offset:(CGFloat)c;

/* Accessors. */

@property(readonly) CAConstraintAttribute attribute;
@property(readonly) NSString *sourceName;
@property(readonly) CAConstraintAttribute sourceAttribute;
@property(readonly) CGFloat scale, offset;

@end
