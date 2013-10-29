/*	NSMapTable.h
	Copyright (c) 1994-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSPointerFunctions.h>
#import <Foundation/NSString.h>
#import <Foundation/NSEnumerator.h>

@class NSArray, NSDictionary, NSMapTable;

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED

/****************	Class	****************/

/* An NSMapTable is modeled after a dictionary, although, because of its options, is not a dictionary because it will behave differently.  The major option is to have keys and/or values held "weakly" in a manner that entries are removed when one of the objects is collected under garbage collection.  Under non-GC conditions, the entries must be removed by the programmer explicitly.  In addition to being held weakly, keys or values may be copied on input or may use pointer identity for equality and hashing.
   An NSMapTable can also be configured to operate on arbitrary pointers and not just objects.  We recommend the C function API for "void *" access.  To configure for pointer use, consult and choose the appropriate NSPointerFunctionsOptions or configure or use  NSPointerFunctions objects directly for initialization.
*/

enum {
    NSMapTableStrongMemory             = 0, // NSPointerFunctionsStrongMemory
    NSMapTableZeroingWeakMemory        = NSPointerFunctionsZeroingWeakMemory,
    NSMapTableCopyIn                   = NSPointerFunctionsCopyIn,
    NSMapTableObjectPointerPersonality = NSPointerFunctionsObjectPointerPersonality
};

typedef NSUInteger NSMapTableOptions;

@interface NSMapTable : NSObject <NSCopying, NSCoding, NSFastEnumeration>

- (id)initWithKeyOptions:(NSPointerFunctionsOptions)keyOptions valueOptions:(NSPointerFunctionsOptions)valueOptions capacity:(NSUInteger)initialCapacity;
- (id)initWithKeyPointerFunctions:(NSPointerFunctions *)keyFunctions valuePointerFunctions:(NSPointerFunctions *)valueFunctions capacity:(NSUInteger)initialCapacity;

+ (id)mapTableWithKeyOptions:(NSPointerFunctionsOptions)keyOptions valueOptions:(NSPointerFunctionsOptions)valueOptions;

+ (id)mapTableWithStrongToStrongObjects;
+ (id)mapTableWithWeakToStrongObjects;
+ (id)mapTableWithStrongToWeakObjects;
+ (id)mapTableWithWeakToWeakObjects;

/* return an NSPointerFunctions object reflecting the functions in use.  This is a new autoreleased object that can be subsequently modified and/or used directly in the creation of other pointer "collections". */
- (NSPointerFunctions *)keyPointerFunctions;
- (NSPointerFunctions *)valuePointerFunctions;

- (id)objectForKey:(id)aKey;

- (void)removeObjectForKey:(id)aKey;
- (void)setObject:(id)anObject forKey:(id)aKey;   // add/replace value (CFDictionarySetValue, NSMapInsert)

- (NSUInteger)count;

- (NSEnumerator *)keyEnumerator;
- (NSEnumerator *)objectEnumerator;

- (void)removeAllObjects;

- (NSDictionary *)dictionaryRepresentation;  // create a dictionary of contents
@end

#endif



/****************	void * Map table operations	****************/

typedef struct {NSUInteger _pi; NSUInteger _si; void *_bs;} NSMapEnumerator;



FOUNDATION_EXPORT void NSFreeMapTable(NSMapTable *table);
FOUNDATION_EXPORT void NSResetMapTable(NSMapTable *table);
FOUNDATION_EXPORT BOOL NSCompareMapTables(NSMapTable *table1, NSMapTable *table2);
FOUNDATION_EXPORT NSMapTable *NSCopyMapTableWithZone(NSMapTable *table, NSZone *zone);
FOUNDATION_EXPORT BOOL NSMapMember(NSMapTable *table, const void *key, void **originalKey, void **value);
FOUNDATION_EXPORT void *NSMapGet(NSMapTable *table, const void *key);
FOUNDATION_EXPORT void NSMapInsert(NSMapTable *table, const void *key, const void *value);
FOUNDATION_EXPORT void NSMapInsertKnownAbsent(NSMapTable *table, const void *key, const void *value);
FOUNDATION_EXPORT void *NSMapInsertIfAbsent(NSMapTable *table, const void *key, const void *value);
FOUNDATION_EXPORT void NSMapRemove(NSMapTable *table, const void *key);
FOUNDATION_EXPORT NSMapEnumerator NSEnumerateMapTable(NSMapTable *table);
FOUNDATION_EXPORT BOOL NSNextMapEnumeratorPair(NSMapEnumerator *enumerator, void **key, void **value);
FOUNDATION_EXPORT void NSEndMapTableEnumeration(NSMapEnumerator *enumerator);
FOUNDATION_EXPORT NSUInteger NSCountMapTable(NSMapTable *table);
FOUNDATION_EXPORT NSString *NSStringFromMapTable(NSMapTable *table);
FOUNDATION_EXPORT NSArray *NSAllMapTableKeys(NSMapTable *table);
FOUNDATION_EXPORT NSArray *NSAllMapTableValues(NSMapTable *table);


/****************     Legacy     ***************************************/

typedef struct {
    NSUInteger	(*hash)(NSMapTable *table, const void *);
    BOOL	(*isEqual)(NSMapTable *table, const void *, const void *);
    void	(*retain)(NSMapTable *table, const void *);
    void	(*release)(NSMapTable *table, void *);
    NSString 	*(*describe)(NSMapTable *table, const void *);
    const void	*notAKeyMarker;
} NSMapTableKeyCallBacks;
    
#define NSNotAnIntMapKey	((const void *)NSIntegerMin)
#define NSNotAnIntegerMapKey	((const void *)NSIntegerMin)
#define NSNotAPointerMapKey	((const void *)UINTPTR_MAX)

typedef struct {
    void	(*retain)(NSMapTable *table, const void *);
    void	(*release)(NSMapTable *table, void *);
    NSString 	*(*describe)(NSMapTable *table, const void *);
} NSMapTableValueCallBacks;

FOUNDATION_EXPORT NSMapTable *NSCreateMapTableWithZone(NSMapTableKeyCallBacks keyCallBacks, NSMapTableValueCallBacks valueCallBacks, NSUInteger capacity, NSZone *zone);
FOUNDATION_EXPORT NSMapTable *NSCreateMapTable(NSMapTableKeyCallBacks keyCallBacks, NSMapTableValueCallBacks valueCallBacks, NSUInteger capacity);


/****************	Common map table key callbacks	****************/

FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSIntegerMapKeyCallBacks AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonOwnedPointerMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonOwnedPointerOrNullMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSNonRetainedObjectMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSObjectMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSOwnedPointerMapKeyCallBacks;
FOUNDATION_EXPORT const NSMapTableKeyCallBacks NSIntMapKeyCallBacks DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

/****************	Common map table value callbacks	****************/

FOUNDATION_EXPORT const NSMapTableValueCallBacks NSIntegerMapValueCallBacks AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSNonOwnedPointerMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSObjectMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSNonRetainedObjectMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSOwnedPointerMapValueCallBacks;
FOUNDATION_EXPORT const NSMapTableValueCallBacks NSIntMapValueCallBacks DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

