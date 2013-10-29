/*	NSStream.h
        Copyright (c) 2003-2011, Apple Inc. All rights reserved
*/

#import <Foundation/NSObject.h>

@class NSData, NSDictionary, NSError, NSHost, NSInputStream, NSOutputStream, NSRunLoop, NSString, NSURL;
@protocol NSStreamDelegate;

enum {
    NSStreamStatusNotOpen = 0,
    NSStreamStatusOpening = 1,
    NSStreamStatusOpen = 2,
    NSStreamStatusReading = 3,
    NSStreamStatusWriting = 4,
    NSStreamStatusAtEnd = 5,
    NSStreamStatusClosed = 6,
    NSStreamStatusError = 7
};
typedef NSUInteger NSStreamStatus;

enum {
    NSStreamEventNone = 0,
    NSStreamEventOpenCompleted = 1UL << 0,
    NSStreamEventHasBytesAvailable = 1UL << 1,
    NSStreamEventHasSpaceAvailable = 1UL << 2,
    NSStreamEventErrorOccurred = 1UL << 3,
    NSStreamEventEndEncountered = 1UL << 4
};
typedef NSUInteger NSStreamEvent;

// NSStream is an abstract class encapsulating the common API to NSInputStream and NSOutputStream.
// Subclassers of NSInputStream and NSOutputStream must also implement these methods.
@interface NSStream : NSObject
- (void)open;
- (void)close;

- (id <NSStreamDelegate>)delegate;
- (void)setDelegate:(id <NSStreamDelegate>)delegate;
    // By default, a stream is its own delegate, and subclassers of NSInputStream and NSOutputStream must maintain this contract. [someStream setDelegate:nil] must restore this behavior. As usual, delegates are not retained.

- (id)propertyForKey:(NSString *)key;
- (BOOL)setProperty:(id)property forKey:(NSString *)key;

- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;
- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode;

- (NSStreamStatus)streamStatus;
- (NSError *)streamError;
@end

// NSInputStream is an abstract class representing the base functionality of a read stream.
// Subclassers are required to implement these methods.
@interface NSInputStream : NSStream
- (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)len;
    // reads up to length bytes into the supplied buffer, which must be at least of size len. Returns the actual number of bytes read.

- (BOOL)getBuffer:(uint8_t **)buffer length:(NSUInteger *)len;
    // returns in O(1) a pointer to the buffer in 'buffer' and by reference in 'len' how many bytes are available. This buffer is only valid until the next stream operation. Subclassers may return NO for this if it is not appropriate for the stream type. This may return NO if the buffer is not available.

- (BOOL)hasBytesAvailable;
    // returns YES if the stream has bytes available or if it impossible to tell without actually doing the read.
@end

// NSOutputStream is an abstract class representing the base functionality of a write stream.
// Subclassers are required to implement these methods.
@interface NSOutputStream : NSStream
- (NSInteger)write:(const uint8_t *)buffer maxLength:(NSUInteger)len;
    // writes the bytes from the specified buffer to the stream up to len bytes. Returns the number of bytes actually written.

- (BOOL)hasSpaceAvailable;
    // returns YES if the stream can be written to or if it is impossible to tell without actually doing the write.
@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE))
@interface NSStream (NSSocketStreamCreationExtensions)
+ (void)getStreamsToHost:(NSHost *)host port:(NSInteger)port inputStream:(NSInputStream **)inputStream outputStream:(NSOutputStream **)outputStream;
@end
#endif

// The NSInputStreamExtensions category contains additional initializers and convenience routines for dealing with NSInputStreams.
@interface NSInputStream (NSInputStreamExtensions)
- (id)initWithData:(NSData *)data;
- (id)initWithFileAtPath:(NSString *)path;
- (id)initWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);

+ (id)inputStreamWithData:(NSData *)data;
+ (id)inputStreamWithFileAtPath:(NSString *)path;
+ (id)inputStreamWithURL:(NSURL *)url NS_AVAILABLE(10_6, 4_0);
@end

// The NSOutputStreamExtensions category contains additional initializers and convenience routines for dealing with NSOutputStreams.
@interface NSOutputStream (NSOutputStreamExtensions)
- (id)initToMemory;
- (id)initToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity;
- (id)initToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;
- (id)initWithURL:(NSURL *)url append:(BOOL)shouldAppend NS_AVAILABLE(10_6, 4_0);

+ (id)outputStreamToMemory;
+ (id)outputStreamToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity;
+ (id)outputStreamToFileAtPath:(NSString *)path append:(BOOL)shouldAppend;
+ (id)outputStreamWithURL:(NSURL *)url append:(BOOL)shouldAppend NS_AVAILABLE(10_6, 4_0);
@end

@protocol NSStreamDelegate <NSObject>
@optional
- (void)stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode;
@end

// NSString constants for the propertyForKey/setProperty:forKey: API
// String constants for the setting of the socket security level.
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelKey		NS_AVAILABLE(10_3, 2_0);	// use this as the key for setting one of the following values for the security level of the target stream.

FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelNone		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelSSLv2		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelSSLv3		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelTLSv1		NS_AVAILABLE(10_3, 2_0);
FOUNDATION_EXPORT NSString * const NSStreamSocketSecurityLevelNegotiatedSSL	NS_AVAILABLE(10_3, 2_0);

FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyConfigurationKey		NS_AVAILABLE(10_3, 2_0);	// Value is an NSDictionary containing the key/value pairs below. The dictionary returned from SystemConfiguration for SOCKS proxies will work without alteration.

FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyHostKey			NS_AVAILABLE(10_3, 2_0);
    // Value is an NSString
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyPortKey			NS_AVAILABLE(10_3, 2_0);
    // Value is an NSNumber
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyVersionKey		NS_AVAILABLE(10_3, 2_0);
    // Value is one of NSStreamSOCKSProxyVersion4 or NSStreamSOCKSProxyVersion5
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyUserKey			NS_AVAILABLE(10_3, 2_0);
    // Value is an NSString
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyPasswordKey		NS_AVAILABLE(10_3, 2_0);
    // Value is an NSString

FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyVersion4			NS_AVAILABLE(10_3, 2_0);
    // Value for NSStreamSOCKProxyVersionKey
FOUNDATION_EXPORT NSString * const NSStreamSOCKSProxyVersion5			NS_AVAILABLE(10_3, 2_0);
    // Value for NSStreamSOCKProxyVersionKey

FOUNDATION_EXPORT NSString * const NSStreamDataWrittenToMemoryStreamKey	NS_AVAILABLE(10_3, 2_0);
    // Key for obtaining the data written to a memory stream.

FOUNDATION_EXPORT NSString * const NSStreamFileCurrentOffsetKey		NS_AVAILABLE(10_3, 2_0);
    // Value is an NSNumber representing the current absolute offset of the stream.

// NSString constants for error domains.
FOUNDATION_EXPORT NSString * const NSStreamSocketSSLErrorDomain			NS_AVAILABLE(10_3, 2_0);
    // SSL errors are to be interpreted via <Security/SecureTransport.h>
FOUNDATION_EXPORT NSString * const NSStreamSOCKSErrorDomain			NS_AVAILABLE(10_3, 2_0);

// Property key to specify the type of service for the stream.  This
// allows the system to properly handle the request with respect to
// routing, suspension behavior and other networking related attributes
// appropriate for the given service type.  The service types supported
// are documented below.
FOUNDATION_EXPORT NSString * const NSStreamNetworkServiceType		    NS_AVAILABLE(10_7, 4_0);
// Supported network service types:
FOUNDATION_EXPORT NSString * const NSStreamNetworkServiceTypeVoIP	    NS_AVAILABLE(10_7, 4_0);
FOUNDATION_EXPORT NSString * const NSStreamNetworkServiceTypeVideo	    NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSStreamNetworkServiceTypeBackground	    NS_AVAILABLE(10_7, 5_0);
FOUNDATION_EXPORT NSString * const NSStreamNetworkServiceTypeVoice	    NS_AVAILABLE(10_7, 5_0);

