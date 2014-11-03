/*	NSArchiver.h
	Copyright (c) 1994-2014, Apple Inc. All rights reserved.
*/

#import <Foundation/NSCoder.h>

@class NSString, NSData, NSMutableData, NSMutableDictionary, NSMutableArray;

/************		Archiving: Writing	****************/

@interface NSArchiver : NSCoder {
@private
    void		* __strong mdata;
    void		*pointerTable;
    void		*stringTable;
    void		*ids;
    void		*map;
    void		*replacementTable;
    void		*reserved;
}

- (instancetype)initForWritingWithMutableData:(NSMutableData *)mdata NS_DESIGNATED_INITIALIZER;
    
@property (readonly, retain) NSMutableData *archiverData;

- (void)encodeRootObject:(id)rootObject;
- (void)encodeConditionalObject:(id)object;

+ (NSData *)archivedDataWithRootObject:(id)rootObject;

+ (BOOL)archiveRootObject:(id)rootObject toFile:(NSString *)path;

- (void)encodeClassName:(NSString *)trueName intoClassName:(NSString *)inArchiveName;
- (NSString *)classNameEncodedForTrueClassName:(NSString *)trueName;

- (void)replaceObject:(id)object withObject:(id)newObject;

@end

/************		Archiving: Reading		****************/

@interface NSUnarchiver : NSCoder {
@private
    void *		datax;
    NSUInteger		cursor;
    NSZone		*objectZone;
    NSUInteger		systemVersion;
    signed char		streamerVersion;
    char		swap;
    char		unused1;
    char		unused2;
    void		*pointerTable;
    void		*stringTable;
    id			classVersions;
    NSInteger			lastLabel;
    void		*map;
    void		*allUnarchivedObjects;
    id			reserved;
}

- (instancetype)initForReadingWithData:(NSData *)data NS_DESIGNATED_INITIALIZER;

- (void)setObjectZone:(NSZone *)zone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;
- (NSZone *)objectZone NS_AUTOMATED_REFCOUNT_UNAVAILABLE;

@property (getter=isAtEnd, readonly) BOOL atEnd;

@property (readonly) unsigned int systemVersion;

+ (id)unarchiveObjectWithData:(NSData *)data;
+ (id)unarchiveObjectWithFile:(NSString *)path;

+ (void)decodeClassName:(NSString *)inArchiveName asClassName:(NSString *)trueName;

- (void)decodeClassName:(NSString *)inArchiveName asClassName:(NSString *)trueName;

+ (NSString *)classNameDecodedForArchiveClassName:(NSString *)inArchiveName;
- (NSString *)classNameDecodedForArchiveClassName:(NSString *)inArchiveName;

- (void)replaceObject:(id)object withObject:(id)newObject;

@end

/************		Exceptions		****************/

FOUNDATION_EXPORT NSString * const NSInconsistentArchiveException;

/************		Object call back		****************/

@interface NSObject (NSArchiverCallback)

@property (readonly) Class classForArchiver;
- (id)replacementObjectForArchiver:(NSArchiver *)archiver;

@end
