/*	NSData.h
	Copyright (c) 1994-2011, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSString, NSURL, NSError;


/****************	Read/Write Options	****************/

enum {
    NSDataReadingMappedIfSafe =   1UL << 0,	// Hint to map the file in if possible and safe
    NSDataReadingUncached = 1UL << 1,	// Hint to get the file not to be cached in the kernel
#if MAC_OS_X_VERSION_10_7 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_5_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    NSDataReadingMappedAlways = 1UL << 3,	// Hint to map the file in if possible. This takes precedence over NSDataReadingMappedIfSafe if both are given.
#endif
};
typedef NSUInteger NSDataReadingOptions;

enum {	                          
    NSDataWritingAtomic = 1UL << 0,	// Hint to use auxiliary file when saving; equivalent to atomically:YES
    
#if __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    NSDataWritingFileProtectionNone                                 = 0x10000000,
    NSDataWritingFileProtectionComplete                             = 0x20000000,
#if __IPHONE_5_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
    NSDataWritingFileProtectionCompleteUnlessOpen                   = 0x30000000,
    NSDataWritingFileProtectionCompleteUntilFirstUserAuthentication = 0x40000000,
#endif
    NSDataWritingFileProtectionMask                                 = 0xf0000000
#endif
};
typedef NSUInteger NSDataWritingOptions;


enum {	// Options with old names for NSData reading methods. Please stop using these old names.
    NSDataReadingMapped = NSDataReadingMappedIfSafe,	// Deprecated name for NSDataReadingMappedIfSafe
    NSMappedRead = NSDataReadingMapped,			// Deprecated name for NSDataReadingMapped
    NSUncachedRead = NSDataReadingUncached		// Deprecated name for NSDataReadingUncached
};

enum {	// Options with old names for NSData writing methods. Please stop using these old names.
    NSAtomicWrite = NSDataWritingAtomic	    // Deprecated name for NSDataWritingAtomic
};

/****************	Data Search Options	****************/
#if MAC_OS_X_VERSION_10_6 <= MAC_OS_X_VERSION_MAX_ALLOWED || __IPHONE_4_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED
enum {
    NSDataSearchBackwards = 1UL << 0,
    NSDataSearchAnchored = 1UL << 1
};
#endif
typedef NSUInteger NSDataSearchOptions;

/****************	Immutable Data		****************/

@interface NSData : NSObject <NSCopying, NSMutableCopying, NSCoding>

- (NSUInteger)length;
- (const void *)bytes;

@end

@interface NSData (NSExtendedData)

- (NSString *)description;
- (void)getBytes:(void *)buffer length:(NSUInteger)length;
- (void)getBytes:(void *)buffer range:(NSRange)range;
- (BOOL)isEqualToData:(NSData *)other;
- (NSData *)subdataWithRange:(NSRange)range;
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)useAuxiliaryFile;
- (BOOL)writeToURL:(NSURL *)url atomically:(BOOL)atomically; // the atomically flag is ignored if the url is not of a type the supports atomic writes
- (BOOL)writeToFile:(NSString *)path options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)errorPtr;
- (BOOL)writeToURL:(NSURL *)url options:(NSDataWritingOptions)writeOptionsMask error:(NSError **)errorPtr;
- (NSRange)rangeOfData:(NSData *)dataToFind options:(NSDataSearchOptions)mask range:(NSRange)searchRange NS_AVAILABLE(10_6, 4_0);

@end

@interface NSData (NSDataCreation)

+ (id)data;
+ (id)dataWithBytes:(const void *)bytes length:(NSUInteger)length;
+ (id)dataWithBytesNoCopy:(void *)bytes length:(NSUInteger)length;
+ (id)dataWithBytesNoCopy:(void *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)b;
+ (id)dataWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
+ (id)dataWithContentsOfURL:(NSURL *)url options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
+ (id)dataWithContentsOfFile:(NSString *)path;
+ (id)dataWithContentsOfURL:(NSURL *)url;
- (id)initWithBytes:(const void *)bytes length:(NSUInteger)length;
- (id)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length;
- (id)initWithBytesNoCopy:(void *)bytes length:(NSUInteger)length freeWhenDone:(BOOL)b;
- (id)initWithContentsOfFile:(NSString *)path options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
- (id)initWithContentsOfURL:(NSURL *)url options:(NSDataReadingOptions)readOptionsMask error:(NSError **)errorPtr;
- (id)initWithContentsOfFile:(NSString *)path;
- (id)initWithContentsOfURL:(NSURL *)url;
- (id)initWithData:(NSData *)data;
+ (id)dataWithData:(NSData *)data;

@end

@interface NSData (NSDeprecated)

/* This method is unsafe because it could potentially cause buffer overruns. You should use -getBytes:length: or -getBytes:range: instead.
*/
- (void)getBytes:(void *)buffer;

/* These methods are deprecated. You should use +dataWithContentsOfURL:options:error: or -initWithContentsOfURL:options:error: with NSDataReadingMappedIfSafe or NSDataReadingMappedAlways instead.
*/
+ (id)dataWithContentsOfMappedFile:(NSString *)path;
- (id)initWithContentsOfMappedFile:(NSString *)path;

@end

/****************	Mutable Data		****************/

@interface NSMutableData : NSData

- (void *)mutableBytes;
- (void)setLength:(NSUInteger)length;

@end

@interface NSMutableData (NSExtendedMutableData)

- (void)appendBytes:(const void *)bytes length:(NSUInteger)length;
- (void)appendData:(NSData *)other;
- (void)increaseLengthBy:(NSUInteger)extraLength;
- (void)replaceBytesInRange:(NSRange)range withBytes:(const void *)bytes;
- (void)resetBytesInRange:(NSRange)range;
- (void)setData:(NSData *)data;
- (void)replaceBytesInRange:(NSRange)range withBytes:(const void *)replacementBytes length:(NSUInteger)replacementLength;

@end

@interface NSMutableData (NSMutableDataCreation)

+ (id)dataWithCapacity:(NSUInteger)aNumItems;
+ (id)dataWithLength:(NSUInteger)length;
- (id)initWithCapacity:(NSUInteger)capacity;
- (id)initWithLength:(NSUInteger)length;

@end

/****************	    Purgeable Data	****************/

NS_CLASS_AVAILABLE(10_6, 4_0)
@interface NSPurgeableData : NSMutableData <NSDiscardableContent> {
@private
    NSUInteger _length;
    int32_t _accessCount;
    uint8_t _private[32];
    void *_reserved;
}

@end


