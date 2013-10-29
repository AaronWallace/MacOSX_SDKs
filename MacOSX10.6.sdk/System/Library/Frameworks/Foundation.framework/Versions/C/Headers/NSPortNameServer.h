/*	NSPortNameServer.h
	Copyright (c) 1993-2009, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSString, NSPort;

@interface NSPortNameServer : NSObject

+ (NSPortNameServer *)systemDefaultPortNameServer;

- (NSPort *)portForName:(NSString *)name;
- (NSPort *)portForName:(NSString *)name host:(NSString *)host;

- (BOOL)registerPort:(NSPort *)port name:(NSString *)name;

- (BOOL)removePortForName:(NSString *)name;

@end

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_IPHONE_SIMULATOR

@interface NSMachBootstrapServer : NSPortNameServer
	// This port name server actually takes and
	// returns instances of NSMachPort

+ (id)sharedInstance;

- (NSPort *)portForName:(NSString *)name;
- (NSPort *)portForName:(NSString *)name host:(NSString *)host;
	// the bootstrap server is a local-only server;
	// host parameter must be emptry string or nil

- (BOOL)registerPort:(NSPort *)port name:(NSString *)name;

// removePortForName: functionality is not supported in
// the bootstrap server; if you want to cancel a service,
// you have to destroy the port (invalidate the NSMachPort
// given to registerPort:name:).

- (NSPort *)servicePortWithName:(NSString *)name AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

@end

#endif

@interface NSMessagePortNameServer : NSPortNameServer
	// This port name server actually takes and
	// returns instances of NSMessagePort

+ (id)sharedInstance;

- (NSPort *)portForName:(NSString *)name;
- (NSPort *)portForName:(NSString *)name host:(NSString *)host;
	// this name server is a local-only server;
	// host parameter must be emptry string or nil

// removePortForName: functionality is not supported in
// this name server; if you want to cancel a service,
// you have to destroy the port (invalidate the
// NSMessagePort given to registerPort:name:).

@end

@interface NSSocketPortNameServer : NSPortNameServer
	// This port name server actually takes and
	// returns instances of NSSocketPort

+ (id)sharedInstance;

- (NSPort *)portForName:(NSString *)name;
- (NSPort *)portForName:(NSString *)name host:(NSString *)host;
    // this name server supports remote lookup
- (BOOL)registerPort:(NSPort *)port name:(NSString *)name;

- (BOOL)removePortForName:(NSString *)name;
     // removePortForName: is supported, and should be used

// the following may be used in the future, but for now nameServerPortNumber arguments are ignored
- (NSPort *)portForName:(NSString *)name host:(NSString *)host nameServerPortNumber:(uint16_t)portNumber;
- (BOOL)registerPort:(NSPort *)port name:(NSString *)name nameServerPortNumber:(uint16_t)portNumber;
- (void)setDefaultNameServerPortNumber:(uint16_t)portNumber;
- (uint16_t)defaultNameServerPortNumber;

@end


