
#pragma once

#include	<IOKit/IOKitLib.h>
#include 	<CoreFoundation/CFMachPort.h>

#include	<IOBluetooth/Bluetooth.h>

#ifdef __OBJC__
#import		<Foundation/Foundation.h>
#endif

#ifdef	__cplusplus
	extern "C" {
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!	@header		IOBluetoothUserLib.h
	@abstract	Public Interfaces for Apple's implementation of Bluetooth technology.
	@discussion	There is an accompanying header to this, "Bluetooth.h", which contains all technology-specific typedefs and information. This header relies heavily on it.
*/

//===========================================================================================================================
// Availability Macros
//===========================================================================================================================
 
#if 0
#pragma mark -
#pragma mark === Availability Macros ===
#endif


#if !defined( MAC_OS_X_VERSION_MIN_REQUIRED ) || ( MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_2 )
	#warning MAC_OS_X_VERSION_MIN_REQUIRED should be at least MAC_OS_X_VERSION_10_2 for Bluetooth support
	#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
		#undef MAC_OS_X_VERSION_MIN_REQUIRED
	#endif
	#define MAC_OS_X_VERSION_MIN_REQUIRED	MAC_OS_X_VERSION_10_2
#endif

#include <AvailabilityMacros.h>

#ifndef MAC_OS_X_VERSION_10_2_1
	#define MAC_OS_X_VERSION_10_2_1	1021
#endif

#ifndef MAC_OS_X_VERSION_10_2_2
	#define MAC_OS_X_VERSION_10_2_2	1022
#endif

#ifndef MAC_OS_X_VERSION_10_2_3
	#define MAC_OS_X_VERSION_10_2_3	1023
#endif

#ifndef MAC_OS_X_VERSION_10_2_4
	#define MAC_OS_X_VERSION_10_2_4	1024
#endif

#ifndef MAC_OS_X_VERSION_10_2_5
	#define MAC_OS_X_VERSION_10_2_5	1025
#endif

#ifndef MAC_OS_X_VERSION_10_2_6
	#define MAC_OS_X_VERSION_10_2_6	1026
#endif

#ifndef MAC_OS_X_VERSION_10_2_7
	#define MAC_OS_X_VERSION_10_2_7	1027
#endif

#define BLUETOOTH_VERSION_1_0	10000
#define BLUETOOTH_VERSION_1_0_0	BLUETOOTH_VERSION_1_0
#define BLUETOOTH_VERSION_1_0_1	10001
#define BLUETOOTH_VERSION_1_1	10100
#define BLUETOOTH_VERSION_1_1_0	BLUETOOTH_VERSION_1_1
#define BLUETOOTH_VERSION_1_2	10200
#define BLUETOOTH_VERSION_1_2_0	BLUETOOTH_VERSION_1_2
#define BLUETOOTH_VERSION_1_2_1 10201
#define BLUETOOTH_VERSION_1_3	10300
#define BLUETOOTH_VERSION_1_3_0	BLUETOOTH_VERSION_1_3
#define BLUETOOTH_VERSION_1_3_1 10301
#define BLUETOOTH_VERSION_1_6	10600
#define BLUETOOTH_VERSION_1_6_0	BLUETOOTH_VERSION_1_6
#define BLUETOOTH_VERSION_1_6_3 10603
#define BLUETOOTH_VERSION_2_0	20000
#define BLUETOOTH_VERSION_2_0_0 BLUETOOTH_VERSION_2_0
#define BLUETOOTH_VERSION_2_1	20100
#define BLUETOOTH_VERSION_2_1_0 BLUETOOTH_VERSION_2_1
#define BLUETOOTH_VERSION_2_1_1 20101

#define BLUETOOTH_VERSION_CURRENT	BLUETOOTH_VERSION_2_1_1

#ifdef BLUETOOTH_VERSION_USE_CURRENT
	#define BLUETOOTH_VERSION_MIN_REQUIRED	BLUETOOTH_VERSION_CURRENT
	#define BLUETOOTH_VERSION_MAX_ALLOWED	BLUETOOTH_VERSION_CURRENT
#else
	#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
		#if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_2_7
			#define BLUETOOTH_VERSION_MIN_REQUIRED	BLUETOOTH_VERSION_1_3_1
		#elif MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_2_5
			#define BLUETOOTH_VERSION_MIN_REQUIRED	BLUETOOTH_VERSION_1_2
		#elif MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_2_4
			#define BLUETOOTH_VERSION_MIN_REQUIRED	BLUETOOTH_VERSION_1_1
		#elif MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_2_2
			#define BLUETOOTH_VERSION_MIN_REQUIRED	BLUETOOTH_VERSION_1_0_1
		#elif MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_2
			#define BLUETOOTH_VERSION_MIN_REQUIRED	BLUETOOTH_VERSION_1_0
		#else
			#error MAC_OS_X_VERSION_MIN_REQUIRED must be >= MAC_OS_X_VERSION_10_2 for Bluetooth support
		#endif
	#endif
	
	#ifdef MAC_OS_X_VERSION_MAX_ALLOWED
		#if MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_2
			#define BLUETOOTH_VERSION_MAX_ALLOWED	BLUETOOTH_VERSION_1_0
		#elif MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_2_2
			#define BLUETOOTH_VERSION_MAX_ALLOWED	BLUETOOTH_VERSION_1_0_1
		#elif MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_2_4
			#define BLUETOOTH_VERSION_MAX_ALLOWED	BLUETOOTH_VERSION_1_1
		#elif MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_2_5
			#define BLUETOOTH_VERSION_MAX_ALLOWED	BLUETOOTH_VERSION_1_2
		#elif MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_2_7
			#define BLUETOOTH_VERSION_MAX_ALLOWED	BLUETOOTH_VERSION_1_3_1
		#elif MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_5_0
			#define BLUETOOTH_VERSION_MAX_ALLOWED	BLUETOOTH_VERSION_2_0
		#elif MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_5_4
			#define BLUETOOTH_VERSION_MAX_ALLOWED	BLUETOOTH_VERSION_2_1_1
		#else 
			#define BLUETOOTH_VERSION_MAX_ALLOWED	BLUETOOTH_VERSION_2_1_1
		#endif
	#endif
#endif


/*
 * AVAILABLE_BLUETOOTH_VERSION_1_0_1_AND_LATER
 *
 * Used on declarations introduced in Mac OS X 10.2.2 (Bluetooth version 1.0.1)
 */
 
#if BLUETOOTH_VERSION_MAX_ALLOWED < BLUETOOTH_VERSION_1_0_1
	#define AVAILABLE_BLUETOOTH_VERSION_1_0_1_AND_LATER		UNAVAILABLE_ATTRIBUTE
#elif BLUETOOTH_VERSION_MIN_REQUIRED < BLUETOOTH_VERSION_1_0_1
	#define AVAILABLE_BLUETOOTH_VERSION_1_0_1_AND_LATER		WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_BLUETOOTH_VERSION_1_0_1_AND_LATER
#endif

/*
 * AVAILABLE_BLUETOOTH_VERSION_1_1_AND_LATER
 *
 * Used on declarations introduced in Mac OS X 10.2.4 (Bluetooth version 1.1)
 */
 
#if BLUETOOTH_VERSION_MAX_ALLOWED < BLUETOOTH_VERSION_1_1
	#define AVAILABLE_BLUETOOTH_VERSION_1_1_AND_LATER		UNAVAILABLE_ATTRIBUTE
#elif BLUETOOTH_VERSION_MIN_REQUIRED < BLUETOOTH_VERSION_1_1
	#define AVAILABLE_BLUETOOTH_VERSION_1_1_AND_LATER		WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_BLUETOOTH_VERSION_1_1_AND_LATER
#endif

/*
 * AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER
 *
 * Used on declarations introduced in Mac OS X 10.2.5 (Bluetooth version 1.2)
 */
 
#if BLUETOOTH_VERSION_MAX_ALLOWED < BLUETOOTH_VERSION_1_2
	#define AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER		UNAVAILABLE_ATTRIBUTE
#elif BLUETOOTH_VERSION_MIN_REQUIRED < BLUETOOTH_VERSION_1_2
	#define AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER		WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER
#endif

/*
 * AVAILABLE_BLUETOOTH_VERSION_1_2_1_AND_LATER
 *
 * Used on declarations introduced in Bluetooth Software Update 1.2.1 (Bluetooth version 1.2.1)
 */
 
#if BLUETOOTH_VERSION_MAX_ALLOWED < BLUETOOTH_VERSION_1_2_1
	#define AVAILABLE_BLUETOOTH_VERSION_1_2_1_AND_LATER		UNAVAILABLE_ATTRIBUTE
#elif BLUETOOTH_VERSION_MIN_REQUIRED < BLUETOOTH_VERSION_1_2_1
	#define AVAILABLE_BLUETOOTH_VERSION_1_2_1_AND_LATER		WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_BLUETOOTH_VERSION_1_2_1_AND_LATER
#endif

/*
 * AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER
 *
 * Used on declarations introduced in Mac OS X 10.2.7 (Bluetooth version 1.3)
 */
 
#if BLUETOOTH_VERSION_MAX_ALLOWED < BLUETOOTH_VERSION_1_3
	#define AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER		UNAVAILABLE_ATTRIBUTE
#elif BLUETOOTH_VERSION_MIN_REQUIRED < BLUETOOTH_VERSION_1_3
	#define AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER		WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER
#endif

/*
 * AVAILABLE_BLUETOOTH_VERSION_1_3_1_AND_LATER
 *
 * Used on declarations introduced in Mac OS X 10.2.7 (Bluetooth version 1.3.1)
 */
 
#if BLUETOOTH_VERSION_MAX_ALLOWED < BLUETOOTH_VERSION_1_3_1
	#define AVAILABLE_BLUETOOTH_VERSION_1_3_1_AND_LATER		UNAVAILABLE_ATTRIBUTE
#elif BLUETOOTH_VERSION_MIN_REQUIRED < BLUETOOTH_VERSION_1_3_1
	#define AVAILABLE_BLUETOOTH_VERSION_1_3_1_AND_LATER		WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_BLUETOOTH_VERSION_1_3_1_AND_LATER
#endif

/*
 * AVAILABLE_BLUETOOTH_VERSION_1_6_AND_LATER
 *
 * Used on declarations introduced in Mac OS X 10.4.0 (Bluetooth version 1.6.0)
 */
 
#if BLUETOOTH_VERSION_MAX_ALLOWED < BLUETOOTH_VERSION_1_6
	#define AVAILABLE_BLUETOOTH_VERSION_1_6_AND_LATER		UNAVAILABLE_ATTRIBUTE
#elif BLUETOOTH_VERSION_MIN_REQUIRED < BLUETOOTH_VERSION_1_6
	#define AVAILABLE_BLUETOOTH_VERSION_1_6_AND_LATER		WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_BLUETOOTH_VERSION_1_6_AND_LATER
#endif

/*
 * AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER
 *
 * Used on declarations introduced in Mac OS X 10.4.2 (Bluetooth version 1.6.3)
 */
 
#if BLUETOOTH_VERSION_MAX_ALLOWED < BLUETOOTH_VERSION_1_6_3
	#define AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER		UNAVAILABLE_ATTRIBUTE
#elif BLUETOOTH_VERSION_MIN_REQUIRED < BLUETOOTH_VERSION_1_6_3
	#define AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER		WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER
#endif

/*
 * AVAILABLE_BLUETOOTH_VERSION_2_0_AND_LATER
 *
 * Used on declarations introduced in Mac OS X 10.5 (Bluetooth version 2.0)
 */
 
#if BLUETOOTH_VERSION_MAX_ALLOWED < BLUETOOTH_VERSION_2_0
	#define AVAILABLE_BLUETOOTH_VERSION_2_0_AND_LATER		UNAVAILABLE_ATTRIBUTE
#elif BLUETOOTH_VERSION_MIN_REQUIRED < BLUETOOTH_VERSION_2_0
	#define AVAILABLE_BLUETOOTH_VERSION_2_0_AND_LATER		WEAK_IMPORT_ATTRIBUTE
#else
	#define AVAILABLE_BLUETOOTH_VERSION_2_0_AND_LATER
#endif


//===========================================================================================================================
// only certain compilers support __attribute((deprecated))__
//===========================================================================================================================

#if defined( DEPRECATED_ATTRIBUTE ) && defined( MAC_OS_X_VERSION_10_6 )
		
    #define DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER DEPRECATED_ATTRIBUTE
	#define DEPRECATED_IN_BLUETOOTH_VERSION_2_0_AND_LATER DEPRECATED_ATTRIBUTE

#elif defined( DEPRECATED_ATTRIBUTE ) && defined( MAC_OS_X_VERSION_10_5 )
		
	#define DEPRECATED_IN_BLUETOOTH_VERSION_2_0_AND_LATER DEPRECATED_ATTRIBUTE
		
#else
		
	#define DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER
	#define DEPRECATED_IN_BLUETOOTH_VERSION_2_0_AND_LATER
		
#endif

//===========================================================================================================================
// General
//===========================================================================================================================
 
#if 0
#pragma mark -
#pragma mark === General ===
#endif


//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothGetVersion
	@abstract	Returns the versions of the bluetooth software and local hardware.
	@param		outSoftwareVersion		Bluetooth software stack version. This parameter is optional.
	@param		outHardwareVersion		HCI/Controller version information. This parameter is optional.
	@result		IOReturn				Determines if successful at getting local hardware version or not.
	@discussion	Error or not, the software version will be returned correctly.
*/

extern IOReturn	IOBluetoothGetVersion( NumVersion * outSoftwareVersion, BluetoothHCIVersionInfo * outHardwareVersion );

typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothObjectRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothDeviceRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothL2CAPChannelRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothRFCOMMChannelRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothSDPServiceRecordRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothSDPUUIDRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothSDPDataElementRef;
typedef struct OpaqueIOBluetoothObjectRef *			IOBluetoothUserNotificationRef;

typedef unsigned long								IOBluetoothObjectID;

#define kIOBluetoothObjectIDNULL	((IOBluetoothObjectID)0)

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothObjectRetain
	@abstract	Increments the ref count on the target object.
	@discussion	The Bluetooth user lib implements a reference counting scheme similar to CoreFoundation.  In general,
                any function that is named with Create returns an IOBluetoothObjectRef that must be released by
                the caller.  Unless otherwise documented, the other functions do not return an object that must
                be released.  However, if the caller wants to keep a reference to the returned object outside
                of the caller's scope, that object must be retained.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		bluetoothObject The target IOBluetoothObjectRef
	@result		Returns the IOBluetoothObjectRef passed in with one more ref count.
*/

extern IOBluetoothObjectRef IOBluetoothObjectRetain( IOBluetoothObjectRef bluetoothObject )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothObjectRelease
	@abstract	Decrements the ref count on the target object.
	@discussion	The ref counting scheme allows the IOBluetoothObjectRefs to be freed when they are no longer used.
                When the ref count reaches zero, the target object will be freed.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		bluetoothObject The target IOBluetoothObjectRef
*/

extern void IOBluetoothObjectRelease( IOBluetoothObjectRef bluetoothObject )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothGetObjectIDFromArguments
	@abstract	Returns the BluetoothObjectID passed as an argument to an auto-launched app.
	@discussion	When an application gets auto-launched by the blued process (as a result of an incoming connection
				to an appropriately configured service), it has a BluetoothObjectID passed to it on the command
				line.  To get the BluetoothObjectID, simply pass the argc and argv parameters received in main()
				to this function.  The returned BluetoothObjectID can then be used to find the appropriate
				IOBluetoothL2CAPChannel or IOBluetoothRFCOMMChannel depending on the type of service (using 
				IOBluetoothL2CAPChannelCreateFromObjectID() or IOBluetoothRFCOMMChannelCreateFromObjectID.)

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		argc The argc parameter passed to main()
	@param		argv The argv parameter passed to main()
	@result		Returns the BluetoothObjectID passed in the given arguments.  If no ID is present,
				kIOBluetoothObjectIDNULL is returned.
*/

extern IOBluetoothObjectID IOBluetoothGetObjectIDFromArguments( int argc, const char *argv[] )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @typedef IOBluetoothRemoteNameRequestCallback
    @abstract Callback function definition for a remote name request.
    @discussion This callback will be invoked when a remote name request command completes.
    @param userRefCon			(void *) This user defined parameter was provided during the original call to initiate
                                the remote name request.
    @param deviceRef			(IOBluetoothDeviceRef) The IOBluetoothDevice which the ReadRemoteName call is completing for.
    @param status				(BluetoothHCIStatus) The status of the call.  Could be success, page timeout, host timeout.
    @result None.
*/
typedef void (*IOBluetoothRemoteNameRequestCallback)			( void * userRefCon, IOBluetoothDeviceRef deviceRef, IOReturn status );

/*!
    @typedef IOBluetoothCreateConnectionCallback
    @abstract Callback function definition for a create connection call.
    @discussion This callback will be invoked when a create connection command completes.
    @param userRefCon	(void *) This user defined parameter was provided during the original call to IOBluetoothCreateConnection.
    @param deviceRef	(IOBluetoothDeviceRef) The IOBluetoothDevice which the CreateConnection call is completing for.
    @param status		(OSStatus) The status of the call.  Could be success, page timeout, host timeout, already exists, etc.
    @result None.
*/
typedef void (*IOBluetoothCreateConnectionCallback) 			( void * userRefCon, IOBluetoothDeviceRef deviceRef, IOReturn status );

/*!
    @typedef IOBluetoothSDPQueryCallback
    @abstract Callback function definition for a perform SDP query call.
    @discussion This callback will be invoked when an SDP query completes (or an error is encountered performing the query).
    @param userRefCon	(void *) This user defined parameter was provided during the original call to perform the query.
    @param deviceRef	(IOBluetoothDeviceRef) The IOBluetoothDevice on which the SDP query will be performed.
    @param status		(OSStatus) The status of the call.  Could be success, page timeout, host timeout, etc.
    @result None.
*/
typedef void (*IOBluetoothSDPQueryCallback)						( void * userRefCon, IOBluetoothDeviceRef deviceRef, IOReturn status );

//===========================================================================================================================
// Device interaction.
//===========================================================================================================================
 
#if 0
#pragma mark -
#pragma mark === Device ===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceCreateWithAddress
	@abstract	Returns the IOBluetoothDeviceRef for the given BluetoothDeviceAddress
	@discussion	Within a single application, there will be only one IOBluetoothDeviceRef for a
                given remote device address.  This function will return that shared device object.  The
                IOBluetoothDeviceRef MUST be released by the caller (by calling IOBluetoothObjectRelease()).

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

	@param		bdAddr	Pointer to a BluetoothDeviceAddress for which an IOBluetoothDeviceRef is desired
	@result		Returns the IOBluetoothDeviceRef for the given BluetoothDeviceAddress.
*/

extern IOBluetoothDeviceRef IOBluetoothDeviceCreateWithAddress(BluetoothDeviceAddress *bdAddr)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceOpenConnection
	@abstract	Create a baseband connection to the device.
	@discussion	This method can be either synchronous or asynchronous.  If a callback is specified, the
                operation is performed asynchronously and the callback called when the connection complete
                event is received.  If no callback is specified, the operation is synchronous and the 
                function will not return until the connection complete event is received.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		btDevice The target IOBluetoothDeviceRef
    @param		callback The function to be called when the connection has been established (or the
                create connection has failed).
    @param		refCon A client-supplied reference to be passed to the callback.
    @result		Returns kIOReturnSuccess if the connection was successfully created (synchronously) or if
                the create connection call was successfully sent (asynchronously).  If kIOReturnSuccess
                is not received in the asynchronous case, the callback will not be called.
*/

extern IOReturn IOBluetoothDeviceOpenConnection(IOBluetoothDeviceRef btDevice, IOBluetoothCreateConnectionCallback callback, void *refCon)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceOpenConnectionWithOptions
	@abstract	Create a baseband connection to the device.
	@discussion	This function can be either synchronous or asynchronous.  If a callback is specified, the
                operation is performed asynchronously and the callback called when the connection complete
                event is received.  If no callback is specified, the operation is synchronous and the 
                function will not return until the connection complete event is received.
				
				NOTE: This function is only available in Mac OS X 10.2.7 (Bluetooth v1.3) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		btDevice The target IOBluetoothDeviceRef
    @param		callback The function to be called when the connection has been established (or the
                create connection has failed).
    @param		refCon A client-supplied reference to be passed to the callback.
    @param		inPageTimeout A client-supplied Page timeout value to use for the create connection call.
    @param		inAuthenticationRequired A client-supplied Boolean to indicate whether we require authentication for the new connection.
    @result		Returns kIOReturnSuccess if the connection was successfully created (synchronously) or if
                the create connection call was successfully sent (asynchronously).  If kIOReturnSuccess
                is not received in the asynchronous case, the callback will not be called.
*/

extern IOReturn IOBluetoothDeviceOpenConnectionWithOptions(IOBluetoothDeviceRef btDevice, IOBluetoothCreateConnectionCallback callback, void *refCon, BluetoothHCIPageTimeout inPageTimeout, Boolean inAuthenticationRequired) AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceCloseConnection
	@abstract	Close down the baseband connection to the device.
	@discussion	This method is synchronous and will not return until the connection has been closed (or the 
                command failed).  In the future this API will be changed to allow asynchronous operation.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		btDevice The target IOBluetoothDeviceRef
    @result		Returns kIOReturnSuccess if the connection has successfully been closed.
*/

extern IOReturn IOBluetoothDeviceCloseConnection(IOBluetoothDeviceRef btDevice)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceRemoteNameRequest
	@abstract	Issues a remote name request to the target device.
	@discussion	If a callback is specified, the request is asynchronous and on completion of the REMOTE_NAME_REQUEST
                command, the callback will be called with the given refCon.
                If no target is specified, the request is made synchronously and won't return until the request is 
                complete.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		inDeviceRef The target IOBluetoothDeviceRef
    @param		inCallback The callback to call when the remote name request is complete
    @param		inUserRefCon User-supplied reference that will be passed to the callback
    @param		outDeviceName Contains the device name if the request is synchronous and completes successfully.
    @result		Returns kIOReturnSuccess if the remote name request was successfully issued (and if synchronous, if
                the request completed successfully).
*/

extern IOReturn IOBluetoothDeviceRemoteNameRequest(	IOBluetoothDeviceRef						inDeviceRef,
													IOBluetoothRemoteNameRequestCallback		inCallback,
													void *										inUserRefCon,
													BluetoothDeviceName							outDeviceName )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;	
                                                    
//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceRemoteNameRequestWithTimeout
	@abstract	Issues a remote name request to the target device.
	@discussion	If a callback is specified, the request is asynchronous and on completion of the REMOTE_NAME_REQUEST
                command, the callback will be called with the given refCon.
                If no target is specified, the request is made synchronously and won't return until the request is 
                complete.
				
				NOTE: This function is only available in Mac OS X 10.2.7 (Bluetooth v1.3) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		inDeviceRef The target IOBluetoothDeviceRef
    @param		inCallback The callback to call when the remote name request is complete
    @param		inUserRefCon User-supplied reference that will be passed to the callback
    @param		outDeviceName Contains the device name if the request is synchronous and completes successfully.
    @param		inTimeout User supplied page timeout value to use for the remote name request call.
    @result		Returns kIOReturnSuccess if the remote name request was successfully issued (and if synchronous, if
                the request completed successfully).
*/
extern IOReturn IOBluetoothDeviceRemoteNameRequestWithTimeout(	IOBluetoothDeviceRef						inDeviceRef,
																IOBluetoothRemoteNameRequestCallback		inCallback,
																void *										inUserRefCon,
																BluetoothDeviceName							outDeviceName,
																BluetoothHCIPageTimeout						inTimeout ) AVAILABLE_BLUETOOTH_VERSION_1_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;
//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDevicePerformSDPQuery
	@abstract	Performs an SDP query on the target device.
	@discussion	As a result of this call, a baseband connection will be built to the device (if not already connected).
				Then, an L2CAP channel will be opened to the SDP server on the device.  At that point, a Service
				Search Attribute request will be issued with a UUID of 0x0100 (L2CAP) and an attribute range of
				0x0000 - 0xffff specified.  This will cause the SDP server to return all attributes of all L2CAP-derived 
				services on the device.  The results essentially encompass all services on the device.
				This function is always asynchronous.  If a callback is specified, when the SDP query is complete (or
				an error is encountered), the callback will be called with the given refCon.  If no target is specified, 
				the request is still asynchronous, but no callback will be made.  That can be useful if the client has
				registered for SDP service changed notifications.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

	@param		inDeviceRef The target IOBluetoothDeviceRef
    @param		inCallback The callback to call when the SDP query is complete
    @param		inUserRefCon User-supplied reference that will be passed to the callback
    @result		Returns kIOReturnSuccess if the SDP query was successfully started.
*/

extern IOReturn IOBluetoothDevicePerformSDPQuery(	IOBluetoothDeviceRef						inDeviceRef,
                                                    IOBluetoothSDPQueryCallback					inCallback,
                                                    void *										inUserRefCon )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//===========================================================================================================================
// Device attributes
//===========================================================================================================================
 
 #if 0
#pragma mark -
#pragma mark === Device - attributes ===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetClassOfDevice
	@abstract	Gets the full class of device value for the remote device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of IOBluetoothDeviceGetLastInquiryUpdate().  If NULL is returned, then the 
                device hasn't been seen.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns the class of device for the remote device.
*/

extern BluetoothClassOfDevice IOBluetoothDeviceGetClassOfDevice(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetServiceClassMajor
	@abstract	Get the major service class of the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of IOBluetoothDeviceGetLastInquiryUpdate().  If NULL is returned, then the 
                device hasn't been seen.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns the major service class of the device.
*/

extern BluetoothServiceClassMajor IOBluetoothDeviceGetServiceClassMajor(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetDeviceClassMajor
	@abstract	Get the major device class of the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of IOBluetoothDeviceGetLastInquiryUpdate().  If NULL is returned, then the 
                device hasn't been seen.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns the major device class of the remote device.
*/

extern BluetoothDeviceClassMajor IOBluetoothDeviceGetDeviceClassMajor(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetDeviceClassMinor
	@abstract	Get the minor service class of the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of IOBluetoothDeviceGetLastInquiryUpdate().  If NULL is returned, then the 
                device hasn't been seen.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns the minor device class of the remote device.
*/

extern BluetoothDeviceClassMinor IOBluetoothDeviceGetDeviceClassMinor(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetName
	@abstract	Get the human readable name of the remote device.
	@discussion	This only returns a value if a remote name request has been performed on the target device.  If a
                successful remote name request has not been completed, NULL is returned.  To perform a remote
                name request, call IOBluetoothDeviceRemoteNameRequest().  If a remote name request has been 
                successfully completed, the function IOBluetoothDeviceGetLastNameUpdate() will return the 
                date/time of the last successful request.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns the name of the remote device name.  This value is a CFStringRef generated from the UTF-8
                format of the most recent remote name request.  The returned string does NOT need to be released
                by the caller.
*/

extern CFStringRef IOBluetoothDeviceGetName(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetNameOrAddress
	@abstract	Get the human readable name of the remote device.  If the name is not present, it will return a string
                containing the device's address.
	@discussion	If a remote name request has been successfully completed, the device name will be returned.  If not,
                a string containg the device address in the format of "XX-XX-XX-XX-XX-XX" will be returned.  Because this
                function may have to create a new string object, the resulting string must be released by the caller
                (by calling CFRelease()).

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
    @result		Returns the device's name or a string containing the device's address.  The returned string MUST be released
                by the caller by calling CFRelease().
*/

extern CFStringRef IOBluetoothDeviceGetNameOrAddress(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetLastNameUpdate
	@abstract	Get the date/time of the last successful remote name request.
    @param		device The target IOBluetoothDeviceRef
	@result		Returns the date/time of the last successful remote name request.  If no remote name request has been
                completed on the target device, NULL is returned.  The returned CFDateRef does NOT need to be released by 
                the caller.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

*/

extern CFDateRef IOBluetoothDeviceGetLastNameUpdate(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetAddress
	@abstract	Get the Bluetooth device address for the target device.
    @param		device The target IOBluetoothDeviceRef
	@result		Returns a pointer to the Bluetooth device address of the target device.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern const BluetoothDeviceAddress *IOBluetoothDeviceGetAddress(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetAddressString
	@abstract	Get a string containing the Bluetooth device address for the target device.
	@discussion	Because this function may have to create a new string object, the resulting 
				string must be released by the caller (by calling CFRelease()).
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		device The target IOBluetoothDeviceRef
	@result		Returns a pointer to a CFStringRef containing the Bluetooth device address of the target device.
				The returned string MUST be released by the caller by calling CFRelease().
*/

extern CFStringRef IOBluetoothDeviceGetAddressString(IOBluetoothDeviceRef device) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetPageScanRepetitionMode
	@abstract	Get the value of the page scan repetition mode for the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of IOBluetoothDeviceGetLastInquiryUpdate().  If NULL is returned, then the 
                device hasn't been seen.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		device The target IOBluetoothDeviceRef
	@result		Returns the page scan repetition mode value for this device.
*/

extern BluetoothPageScanRepetitionMode IOBluetoothDeviceGetPageScanRepetitionMode(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetPageScanPeriodMode
	@abstract	Get the value of the page scan period mode for the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of IOBluetoothDeviceGetLastInquiryUpdate().  If NULL is returned, then the 
                device hasn't been seen.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		device The target IOBluetoothDeviceRef
	@result		Returns page scan period mode value for the device.
*/

extern BluetoothPageScanPeriodMode IOBluetoothDeviceGetPageScanPeriodMode(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetPageScanMode
	@abstract	Get the page scan mode for the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of IOBluetoothDeviceGetLastInquiryUpdate().  If NULL is returned, then the 
                device hasn't been seen.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		device The target IOBluetoothDeviceRef
	@result		Returns the value for the page scan mode for the device.
*/

extern BluetoothPageScanMode IOBluetoothDeviceGetPageScanMode(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetClockOffset
	@abstract	Get the clock offset value of the device.
	@discussion	This value is only meaningful if the target device has been seen during an inquiry.  This can be
                by checking the result of IOBluetoothDeviceGetLastInquiryUpdate().  If NULL is returned, then the 
                device hasn't been seen.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		device The target IOBluetoothDeviceRef
	@result		Returns the clock offset value for the device.
*/

extern BluetoothClockOffset IOBluetoothDeviceGetClockOffset(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetLastInquiryUpdate
	@abstract	Get the date/time of the last time the device was returned during an inquiry.
    @param		device The target IOBluetoothDeviceRef

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
	@result		Returns the date/time of the last time the device was seen during an inquiry.
                If the device has never been seen during an inquiry, NULL is returned.  The returned CFDateRef
                does NOT need to be released by the caller.
*/

extern CFDateRef IOBluetoothDeviceGetLastInquiryUpdate(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceIsConnected
	@abstract	Indicates whether a baseband connection to the device exists.
	discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		device The target IOBluetoothDeviceRef
	@result		Returns YES if a baseband connection to the device exists.
*/

extern Boolean IOBluetoothDeviceIsConnected(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceRequestAuthentication
	@abstract	Requests that the existing baseband connection be authenticated.
	@discussion	In order to authenticate a baseband connection, a link key needs to be generated as a result of 
                the pairing process.  This call will synchronously initiate the pairing process with the target device
                and not return until the authentication process is complete.  This API will be updated to allow
                for asynchronous operation.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		device The target IOBluetoothDeviceRef
    @result		Returns kIOReturnSuccess if the connection has been successfully been authenticated.  Returns an error
                if authentication fails or no baseband connection exists.
*/

extern IOReturn IOBluetoothDeviceRequestAuthentication(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetConnectionHandle
	@abstract	Get the connection handle for the baseband connection.
	@discussion	This method only returns a valid result if a baseband connection is present
                (IOBluetoothDeviceIsConnected() returns TRUE).

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns the connection handle for the baseband connection.  If no baseband connection is present,
                kBluetoothConnectionHandleNone is returned.
*/

extern BluetoothConnectionHandle IOBluetoothDeviceGetConnectionHandle(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetLinkType
	@abstract	Get the link type for the baseband connection.
	@discussion	This method only returns a valid result if a baseband connection is present
                (IOBluetoothDeviceIsConnected() returns TRUE).

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns the link type for the baseband connection.  If no baseband connection is present,
                kBluetoothLinkTypeNone is returned.
*/

extern BluetoothLinkType IOBluetoothDeviceGetLinkType(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetEncryptionMode
	@abstract	Get the encryption mode for the baseband connection.
	@discussion	This method only returns a valid result if a baseband connection is present
                (IOBluetoothDeviceIsConnected() returns TRUE).

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns the encryption mode for the baseband connection.  If no baseband connection is present,
                kEncryptionDisabled is returned.
*/

extern BluetoothHCIEncryptionMode IOBluetoothDeviceGetEncryptionMode(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetServices
	@abstract	Gets an array of service records for the device.
	@discussion	The resulting array contains IOBluetoothSDPServiceRecordRefs.  The service records are only
                present if an SDP query has been done on the target object.  This can be determined by calling
                IOBluetoothDeviceGetLastServicesUpdate().  It will return the last date/time of the SDP query. 
                To peform an SDP query, use IOBluetoothDevicePerformSDPQuery().
                
                Instead of allowing individual clients to query for different services and service attributes,
                the system request all of the device's services and service attributes.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns an array of service records (IOBluetoothDeviceRefs) for the device if an SDP query has 
                been performed.  If no SDP query has been performed, NULL is returned.  The resulting CFArrayRef
                does NOT need to be released by the caller.
*/

extern CFArrayRef IOBluetoothDeviceGetServices(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetLastServicesUpdate
	@abstract	Get the date/time of the last SDP query.
    @param		device The target IOBluetoothDeviceRef
	@result		Returns the date/time of the last SDP query.  If an SDP query has never been performed on the
                device, NULL is returned.  The resulting CFDateRef does NOT need to be released by the caller.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern CFDateRef IOBluetoothDeviceGetLastServicesUpdate(IOBluetoothDeviceRef device)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetServiceRecordForUUID
	@abstract	Search for a service record containing the given UUID.
	@discussion	This method searches through the device's services to find a service that contains the given
                UUID.  Only the first service record will be returned.  This method only operates on services
                that have already been queried.  It will not initiate a new query.  This method should probably 
                be updated to return an array of service records if more than one contains the UUID.  

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
    @param		sdpUUID UUID value to search for.  
	@result		Returns the first service record that contains the given uuid.  If no service record is found,
                NULL is returned.  The resulting IOBluetoothSDPServiceRecordRef does NOT need to be released by
                the caller.
*/

extern IOBluetoothSDPServiceRecordRef IOBluetoothDeviceGetServiceRecordForUUID(IOBluetoothDeviceRef device, IOBluetoothSDPUUIDRef uuidRef)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothFavoriteDevices
	@abstract	Returns an array containing all of the user's favorite devices.
	@discussion	The CFArrayRef returned by this function must be released by calling CFRelease().
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
	@result		Returns a CFArray of IOBluetoothDeviceRef objects.  The resulting CFArrayRef must be released by
				the caller by calling CFRelease().
*/

extern CFArrayRef IOBluetoothFavoriteDevices() AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceIsFavorite
	@abstract	Indicates whether the target device is a favorite.
	@discussion	NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns TRUE if the device is one of the user's favorites.
*/

extern Boolean IOBluetoothDeviceIsFavorite(IOBluetoothDeviceRef device) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceAddToFavorites
	@abstract	Adds the target device to the user's list of favorite devices.
	@discussion	NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns kIOReturnSuccess if the device was successfully added to the user's list of
				favorite devices.
*/

extern IOReturn IOBluetoothDeviceAddToFavorites(IOBluetoothDeviceRef device) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceRemoveFromFavorites
	@abstract	Removes the target device from the user's list of favorite devices.
	@discussion	NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns kIOReturnSuccess if the device was successfully removed from the user's list of
				favorite devices or if the device was not in the list at all.
*/

extern IOReturn IOBluetoothDeviceRemoveFromFavorites(IOBluetoothDeviceRef device) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothRecentDevices
	@abstract	Returns an array of the most recently accessed devices.
	@discussion	The CFArrayRef returned by this function must be released by calling CFRelease().
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

	@param		numDevices	The number of recent devices to return.  If numDevices is zero, all devices accessed
							by the user will be returned.
	@result		Returns a CFArray of the most recently accessed IOBluetoothDeviceRef objects.  The resulting CFArrayRef 
				must be released by the caller by calling CFRelease().
*/

extern CFArrayRef IOBluetoothRecentDevices(unsigned long numDevices) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceGetRecentAccessDate
	@abstract	Returns a date representing the last time the user accessed the target device.
	@discussion	The CFDateRef returned by this function must be released by calling CFRelease().
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns a CFDateRef representing the last date/time that the user accessed the
				target device.  The resulting CFDateRef must be released by the caller by calling CFRelease().
*/

extern CFDateRef IOBluetoothDeviceGetRecentAccessDate(IOBluetoothDeviceRef device) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothPairedDevices
	@abstract	Returns an array of the currently paired devices.
	@discussion	The CFArrayRef returned by this function must be released by calling CFRelease().
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

	@result		Returns a CFArray of IOBluetoothDeviceRef objects.  The resulting CFArrayRef must be released by
				the caller by calling CFRelease().
*/

extern CFArrayRef IOBluetoothPairedDevices() AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceIsPaired
	@abstract	Indicates whether the target device is paired.
	@discussion	NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@result		Returns TRUE if the device is paired.
*/

extern Boolean IOBluetoothDeviceIsPaired(IOBluetoothDeviceRef device) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothSetSupervisionTimeout
	@abstract	Sets the connection supervision timeout.
	@discussion	NOTE: This method is only available in Mac OS X 10.5 (Bluetooth v2.0) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		device The target IOBluetoothDeviceRef
	@param		timeout A client-supplied link supervision timeout value to use to monitor the connection. The timeout
				value should be specified in slots, so you can use the BluetoothGetSlotsFromSeconds macro to get the proper
				value. e.g. BluetoothGetSlotsFromSeconds( 5.0 ) will give yield the proper number of slots (8000) for 5 seconds.
	@result		Returns kIOReturnSuccess if it was possible to set the connection supervision timeout.
*/

extern IOReturn IOBluetoothSetSupervisionTimeout(IOBluetoothDeviceRef device, UInt16 timeout) AVAILABLE_BLUETOOTH_VERSION_2_0_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//===========================================================================================================================
// Device searching.
//===========================================================================================================================
 
#if 0
#pragma mark -
#pragma mark === Device Searching ===
#endif

//--------------------------------------------------------------------------------------------------------------------------
// See the IOBluetoothDeviceInquiry C API further down in this file. Note that these structures and typedefs are not
// used directly in IOBluetooth.framework, but they are used by various bits of the IOBluetoothUI.framework.

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothDeviceSearchOptions
*/
typedef	UInt32	IOBluetoothDeviceSearchOptions;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@enum		IOBluetoothDeviceSearchOptionsBits
	@abstract	
*/

enum IOBluetoothDeviceSearchOptionsBits
{
	kSearchOptionsNone							= 0L,
	kSearchOptionsAlwaysStartInquiry			= (1L << 0),
	kSearchOptionsDiscardCachedResults			= (1L << 1),
};

//--------------------------------------------------------------------------------------------------------------------------
/*!	@enum		IOBluetoothDeviceSearchDeviceAttributes
	@abstract	Structure used to search for particular devices.
	@discussion Make sure you specify all fields! If you do not set deviceClassMajor for example, and the value is
				0, that is mapped to kBluetoothDeviceClassMajorMiscellaneous, which is probably not what you want. To
				search for all device types, you must pass kBluetoothDeviceClassMajorAny and its relatives. 
*/

typedef	struct	IOBluetoothDeviceSearchDeviceAttributes	IOBluetoothDeviceSearchDeviceAttributes;
struct 	IOBluetoothDeviceSearchDeviceAttributes
{
	BluetoothDeviceAddress				address;				// 00 08 22 44 AB 56, etc.
	BluetoothDeviceName					name;					// "Al Yankovic's Phone", etc.
	BluetoothServiceClassMajor			serviceClassMajor;		// Networking, Rendering, etc.
	BluetoothDeviceClassMajor			deviceClassMajor;		// Computer, Phone, Audio, etc.
	BluetoothDeviceClassMinor			deviceClassMinor;		// Desktop, cordless, headset, etc.
};

//--------------------------------------------------------------------------------------------------------------------------
/*!	@struct		IOBluetoothDeviceSearchAttributes
	@discussion You can search for general device classes and service classes, or you can search for a 
				specific device address or name. If you pass NULL as the attribute structure,
				you will get ALL devices in the vicinity found during a search. Note that passing a zeroed
				out block of attributes is NOT equivalent to passing in NULL!	
*/ 

typedef	struct	IOBluetoothDeviceSearchAttributes	IOBluetoothDeviceSearchAttributes;
struct 	IOBluetoothDeviceSearchAttributes
{
	IOBluetoothDeviceSearchOptions	options;				// Options.
	IOItemCount						maxResults;				// Maximum number of results you desire. 0 means infinite.
	IOItemCount						deviceAttributeCount;

	IOBluetoothDeviceSearchDeviceAttributes	*attributeList;	
};

//===========================================================================================================================
// Local Device Interaction
//===========================================================================================================================

#if 0
#pragma mark -
#pragma mark ===  Local Device Interaction ===
#endif

typedef void (*IOBluetoothReadNameCallback)						( void * userRefCon, OSStatus status, BluetoothDeviceName * name );
typedef void (*IOBluetoothReadAddressCallback)					( void * userRefCon, OSStatus status, BluetoothDeviceAddress * address );
typedef void (*IOBluetoothReadLocalVersionInformationCallback)	( void * userRefCon, BluetoothHCIStatus status, BluetoothHCIVersionInfo * versionInfo );
typedef void (*IOBluetoothReadLocalSupportedFeaturesCallback)	( void * userRefCon, BluetoothHCIStatus status, BluetoothHCISupportedFeatures * features );
typedef void (*IOBluetoothReadConnectionAcceptTimeoutCallback)	( void * userRefCon, BluetoothHCIStatus status, BluetoothHCIConnectionAcceptTimeout timeout );
typedef void (*IOBluetoothReadPageTimeoutCallback)				( void * userRefCon, BluetoothHCIStatus status, BluetoothHCIPageTimeout timeout );
typedef void (*IOBluetoothReadPageScanEnableCallback)			( void * userRefCon, BluetoothHCIStatus status, BluetoothHCIPageScanMode mode );
typedef void (*IOBluetoothReadAuthenticationEnableCallback)		( void * userRefCon, BluetoothHCIStatus status, BluetoothHCIAuthenticationEnable enabled );
typedef void (*IOBluetoothReadEncryptionModeCallback)			( void * userRefCon, BluetoothHCIStatus status, BluetoothHCIEncryptionMode mode );
typedef void (*IOBluetoothReadClassOfDeviceCallback)			( void * userRefCon, BluetoothHCIStatus status, BluetoothClassOfDevice classOfDevice );
typedef void (*IOBluetoothReadPageScanPeriodModeCallback)		( void * userRefCon, BluetoothHCIStatus status, BluetoothHCIPageScanPeriodMode mode );
typedef void (*IOBluetoothReadPageScanModeCallback)				( void * userRefCon, BluetoothHCIStatus status, BluetoothHCIPageScanMode mode );


//===========================================================================================================================
// Local Device Configuration
//===========================================================================================================================
 
//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceAvailable
	@abstract	Determines if a bluetooth device is available on a local machine or not.
	@result		A Boolean value. TRUE if a Bluetooth device is connected to the local machine, FALSE otherwise.
	@discussion	Determines if a bluetooth device is available on a local machine or not.
*/
extern Boolean	IOBluetoothLocalDeviceAvailable()	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceGetDiscoverable
	@abstract	Returns the discoverability state of the local device.
    @param		discoverableStatus is a pointer to boolean, it will hold the discoverabilty state.
	@result		An error code value. 0 if successful.
	@discussion	Returns the discoverability state of the local device. 
*/
extern IOReturn IOBluetoothLocalDeviceGetDiscoverable(Boolean* discoverableStatus)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceGetPowerState
	@abstract	Determines the current power state of the Bluetooth hardware.
	@discussion	If successful, it passes the current power state of the Bluetooth hardware back to the caller.
				
				NOTE: This function is only available in Mac OS X 10.2.4 (Bluetooth v1.1) or later.
	@result		An error code value. 0 if successful.
*/
extern IOReturn IOBluetoothLocalDeviceGetPowerState(BluetoothHCIPowerState* powerState) AVAILABLE_BLUETOOTH_VERSION_1_1_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadVersionInformation
	@abstract	Reads the local Bluetoot Host Controller's version information, including LMP and HCI versions, as well
				as the hardware manufacturer.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
*/

extern IOReturn IOBluetoothLocalDeviceReadVersionInformation(	BluetoothHCIVersionInfo *						outResults,
																IOBluetoothReadLocalVersionInformationCallback	inCallback,
																void *											inUserRefCon,
																void *											reserved	 )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadSupportedFeatures
	@abstract	Allows reading the local device's supported features, consisting of 8 bytes of data.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	You can use the BluetoothFeatureBits defined in Bluetooth.h to determine if a particular feature of
				interest is set in the data. These supported features are visible to other in-range devices and
				are often used to determine if a device has a feature of interest.
*/
														
extern IOReturn IOBluetoothLocalDeviceReadSupportedFeatures(	BluetoothHCISupportedFeatures *					outResults,
																IOBluetoothReadLocalSupportedFeaturesCallback	inCallback,
																void *											inUserRefCon,
																void *											reserved	 )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadAddress
	@abstract	Reads the local Bluetooth Host Controller's device address, e.g. 00-11-22-33-44-55
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	This is the same identifying address that can seen by other in-range devices, although it is usually
				hidden in preference for a "friendlier" name, obtained from IOBluetoothLocalDeviceReadName() below.
*/
															
extern IOReturn IOBluetoothLocalDeviceReadAddress(	BluetoothDeviceAddress *		outResults,
													IOBluetoothReadAddressCallback	inCallback,
													void *							inUserRefCon,
													void *							reserved	 )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadName
	@abstract	Reads the local Bluetooth Host Controller's device name.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	This is the same name that can seen by other in-range devices.
*/
											
extern IOReturn IOBluetoothLocalDeviceReadName(	BluetoothDeviceName			outResults,
												IOBluetoothReadNameCallback	inCallback,
												void *						inUserRefCon,
												void *						reserved	 )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadConnectionAcceptTimeout
	@abstract	Reads the connection accept timeout value of the Host Controller.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	See Bluetooth.h for possible values.
*/

extern IOReturn IOBluetoothLocalDeviceReadConnectionAcceptTimeout(	BluetoothHCIConnectionAcceptTimeout	*			outResults,
																	IOBluetoothReadConnectionAcceptTimeoutCallback	inCallback,
																	void *											inUserRefCon,
																	void *											reserved )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadPageTimeout
	@abstract	Reads the page timeout value of the Host Controller.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	See Bluetooth.h for possible values.
*/

extern IOReturn IOBluetoothLocalDeviceReadPageTimeout(	BluetoothHCIPageTimeout	*			outResults,
														IOBluetoothReadPageTimeoutCallback	inCallback,
														void *								inUserRefCon,
														void *								reserved )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadScanEnable
	@abstract	Reads the current scan mode of the Host Controller.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	See Bluetooth.h for possible values.
*/

extern IOReturn IOBluetoothLocalDeviceReadScanEnable(	BluetoothHCIPageScanMode	*			outResults,
														IOBluetoothReadPageScanEnableCallback	inCallback,
														void *									inUserRefCon,
														void *									reserved )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadAuthenticationEnable
	@abstract	Reads the current authentication state of the Host Controller.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	See Bluetooth.h for possible values.
*/

extern IOReturn IOBluetoothLocalDeviceReadAuthenticationEnable(	BluetoothHCIAuthenticationEnable	*		outResults,
																IOBluetoothReadAuthenticationEnableCallback	inCallback,
																void *										inUserRefCon,
																void *										reserved )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadEncryptionMode
	@abstract	Reads the current encryption mode of the Host Controller.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	See Bluetooth.h for possible values.
*/

extern IOReturn IOBluetoothLocalDeviceReadEncryptionMode(	BluetoothHCIEncryptionMode *			outResults,
															IOBluetoothReadEncryptionModeCallback	inCallback,
															void *									inUserRefCon,
															void *									reserved )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadClassOfDevice
	@abstract	Reads the current class of device of the Host Controller.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	This value is set automatically by the Bluetooth Software. It is re-written each system restart, so if
				it has been changed by an API, the value will not be persistent across restarts.
*/
									
extern IOReturn IOBluetoothLocalDeviceReadClassOfDevice(	BluetoothClassOfDevice *				outResults,
															IOBluetoothReadClassOfDeviceCallback	inCallback,
															void *									inUserRefCon,
															void *									reserved )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadPageScanPeriodMode
	@abstract	Reads the current page scan period mode of the Host Controller.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	See Bluetooth.h for possible values.
*/

extern IOReturn IOBluetoothLocalDeviceReadPageScanPeriodMode(	BluetoothHCIPageScanPeriodMode *			outResults,
																IOBluetoothReadPageScanPeriodModeCallback	inCallback,
																void *										inUserRefCon,
																void *										reserved )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothLocalDeviceReadPageScanMode
	@abstract	Reads the current page scan mode of the Host Controller.
	@param		outResults				
	@param		inCallback			
	@param		inUserRefCon	
	@param		reserved			Pass NULL here.
	@result		An error code value. 0 if successful.
	@discussion	See Bluetooth.h for possible values.
*/
																														
extern IOReturn IOBluetoothLocalDeviceReadPageScanMode(	BluetoothHCIPageScanMode *			outResults,
														IOBluetoothReadPageScanModeCallback	inCallback,
														void *								inUserRefCon,
														void *								reserved )	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

#if BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_1_1

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothIgnoreHIDDevice
	@abstract	Hints that the Mac OS X Bluetooth software should ignore a HID device that connects up.
	@param		device	A Bluetooth Device to ignore.
*/

extern	void	IOBluetoothIgnoreHIDDevice( IOBluetoothDeviceRef	device );

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRemoveIgnoredHIDDevice
	@abstract	The counterpart to the above IOBluetoothIgnoreHIDDevice() API.
	@param		device	A Bluetooth Device to "un"ignore.
*/

extern	void	IOBluetoothRemoveIgnoredHIDDevice( IOBluetoothDeviceRef	device );

#endif // BLUETOOTH_VERSION_MAX_ALLOWED >= BLUETOOTH_VERSION_2_1_1

#if 0
#pragma mark -
#pragma mark === L2CAP ===
#endif

 //===========================================================================================================================
// L2CAP channel events
//===========================================================================================================================

#if 0
#pragma mark -
#pragma mark === L2CAP channel events===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothL2CAPEvent
	@discussion	The events generated by an L2CAP channel:
        <br>
        kIOBluetoothL2CAPChannelEventTypeData:	new data.
        <br>
        kIOBluetoothL2CAPChannelEventTypeClosed: channel closed.
        <br>
        kIOBluetoothL2CAPChannelEventTypeReconfigured: channel was reconfigured (check if the MTU changed)
        <br>
        kIOBluetoothL2CAPChannelEventTypeOpenCompete: channel is open.
		<br>
		kIOBluetoothL2CAPChannelEventTypeWriteComplete: write opetation is completed
		<br>
		kIOBluetoothL2CAPChannelEventTypeQueueSpaceAvailable: the internal l2cap queue has some room
		
        See the description of IOBluetoothL2CAPDataBlock this event.
*/

typedef enum IOBluetoothL2CAPChannelEventType {
	kIOBluetoothL2CAPChannelEventTypeData					=	0x0001,
	kIOBluetoothL2CAPChannelEventTypeOpenComplete			=	0x0002,
	kIOBluetoothL2CAPChannelEventTypeClosed					=	0x0003,
	kIOBluetoothL2CAPChannelEventTypeReconfigured			=	0x0004,
	kIOBluetoothL2CAPChannelEventTypeWriteComplete			=	0x0005,
	kIOBluetoothL2CAPChannelEventTypeQueueSpaceAvailable	=	0x0006
} IOBluetoothL2CAPChannelEventType;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothL2CAPChannelDataBlock
	@discussion	Associted to the kIOBluetoothL2CAPChannelEventTypeData it carries a pointer and a size of the new incoming data.

*/

typedef struct IOBluetoothL2CAPChannelDataBlock
{
    void 	*dataPtr;
    size_t	dataSize;
} IOBluetoothL2CAPChannelDataBlock;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothL2CAPChannelEvent
	@discussion	Structure that holds an L2CAP event. Developers that wishes to pass events along are to copy the event (or
	its fields) one by one and not with memory copy methods (as bcopy or memcopy). We do not ensure the size of an event to
	be constant between releases (it is actually likely that will change).
*/

typedef struct IOBluetoothL2CAPChannelEvent {
    IOBluetoothL2CAPChannelEventType	eventType;
	// Caution:  You cannot add any more values here for binary compatibility reasons
    union
    {
			// Caution:  An element of this union cannot grow beyond 32 bytes in size for binary compatibility reasons.
            IOBluetoothL2CAPChannelDataBlock	data;
			void*								writeRefCon;
			UInt8								padding[32];
    } u;
	IOReturn							status;
	// Add new items above this comment.
} IOBluetoothL2CAPChannelEvent;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothL2CAPChannelIncomingDataListener
	@abstract	Callback for listening to L2CAP data.
	@param		l2capChannel	(IOBluetoothL2CAPChannelRef)	The L2CAP channel which received the data.
	@param		data			(void *)						A pointer to the data received.
	@param		length			(UInt16)						The length of the data received.
	@param		refCon			(void *)						The refCon provided to the framework when
                                                                you registered for data on this channel.
	@discussion	This call back will be called when data comes in on an L2CAP channel.
*/

typedef void (*IOBluetoothL2CAPChannelIncomingDataListener)(IOBluetoothL2CAPChannelRef l2capChannel, void *data, UInt16 length, void *refCon);

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothL2CAPChannelIncomingEventListener
	@abstract	Typedef for the L2CAP channel event listener.
	@param		l2capChannel	(IOBluetoothL2CAPChannelRef) L2CAP channel which received the events.
	@param		refCon		(void *) User-defined refCon provided upon registration.
	@param		event		(IOBluetoothL2CAPChannelEvent) The type of event for this notification.
	@discussion	This is the definition for the callback which will be invoked upon receiving data on a L2CAP channel.
        
        For example an event listener function:
        
        <pre>

    void l2capEventListener (IOBluetoothL2CAPChannelRef l2capChannel, void *refCon, IOBluetoothL2CAPChannelEvent *event)
    {
        switch (event->eventType)
        {
                case kIOBluetoothL2CAPNewDataEvent:
                    // In thise case:
                    // event->u.newData.dataPtr  is a pointer to the block of data received.
                    // event->u.newData.dataSize is the size of the block of data.
                break;
                
					......
					
                case kIOBluetoothL2CAPChannelTerminatedEvent:
                    // In this case:
                    // event->u.terminatedChannel is the channel that was terminated. It can be converted in an IOBluetoothL2CAPChannel
                    // object with [IOBluetoothL2CAPChannel withL2CAPChannelRef:]. (see below).
                break;
        }
    }
*/

typedef void (*IOBluetoothL2CAPChannelIncomingEventListener)(IOBluetoothL2CAPChannelRef l2capChannel, void *refCon, IOBluetoothL2CAPChannelEvent *event);

//===========================================================================================================================
// L2CAP channel creation
//===========================================================================================================================
 
#if 0
#pragma mark -
#pragma mark === Device - L2CAP channel creation ===
#endif


//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceOpenL2CAPChannel
	@abstract	Opens a new L2CAP channel to the target device.
	@discussion	This function will begin the process of opening a new L2CAP channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The L2CAP
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.  This prevents a situation where the channel succeeds
                in being configured and opened and receives data before the client is listening and
                is ready for it.
                
                Because a new IOBluetoothL2CAPChannelRef will be created for the client as a result of this
                function, the client is responsible for releasing the resulting IOBluetoothL2CAPChannelRef
                (by calling IOBluetoothObjectRelease()).

				***		DEPRECATED IN BLUETOOTH 2.0 (Mac OS X 10.5)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		btDevice 		The target IOBluetoothDeviceRef
	@param		psm				The L2CAP PSM value for the new channel.
	@param		findExisting	This value should be set to TRUE if it should look for an existing channel 
                                with the PSM.  Typically this value will be FALSE.  It should be TRUE only
                                in the case where a single channel is allowed by the spec for the given PSM.
	@param		newChannel		A pointer to an IOBluetoothL2CAPChannelRef to receive the L2CAP channel 
                                requested to be opened.  The newChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                L2CAP channel was found). 
*/

extern IOReturn IOBluetoothDeviceOpenL2CAPChannel(IOBluetoothDeviceRef btDevice, BluetoothL2CAPPSM psm, Boolean findExisting, IOBluetoothL2CAPChannelRef *newChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_0_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceSendL2CAPEchoRequest
	@abstract	Send an echo request over the L2CAP connection to a remote device.
	@discussion	The current implementation returns when the request has been sent, but does not indicate when
                a response is received.  Also, the baseband connection must be up for the echo request to be sent.
                In the future, this method will also open the connection if necessary.  The API will be updated
                to allow the client to be informed when the echo response has been received (both synchronously
                and asynchronously).

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		btDevice The target IOBluetoothDeviceRef
	@param		data	(void *) - Pointer to buffer to send.
	@param		length	(UInt16) - Length of the buffer to send
	@result		Returns kIOReturnSuccess if the echo request was able to be sent.
*/

extern IOReturn IOBluetoothDeviceSendL2CAPEchoRequest(IOBluetoothDeviceRef btDevice, void *data, UInt16 length) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceOpenL2CAPChannelAsync
	@abstract	Opens a new L2CAP channel to the target device. Returns immedialty after starting the opening process.
	@discussion	This function will begin the process of opening a new L2CAP channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The L2CAP
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.  This prevents a situation where the channel succeeds
                in being configured and opened and receives data before the client is listening and
                is ready for it.
                
                Because a new IOBluetoothL2CAPChannelRef will be created for the client as a result of this
                function, the client is responsible for releasing the resulting IOBluetoothL2CAPChannelRef
                (by calling IOBluetoothObjectRelease()).
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
 
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
 
    @param		btDevice 		The target IOBluetoothDeviceRef
	@param		newChannel		A pointer to an IOBluetoothL2CAPChannelRef to receive the L2CAP channel 
                                requested to be opened.  The newChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@param		psm				The L2CAP PSM value for the new channel.
	@param		withEventListener a IOBluetoothL2CAPChannelIncomingEventListener where to receive events
								  regarding the channel (MUST be specified).
	@param		refCon			a refcon pointer (for the callback specified above).
	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                L2CAP channel was found). 
*/

extern IOReturn IOBluetoothDeviceOpenL2CAPChannelAsync(IOBluetoothDeviceRef btDevice, IOBluetoothL2CAPChannelRef *newChannel, BluetoothL2CAPPSM psm, IOBluetoothL2CAPChannelIncomingEventListener eventListener, void *refcon) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceOpenL2CAPChannelSync
	@abstract	Opens a new L2CAP channel to the target device.  Returns only after the channel is opened.
	@discussion	This function will begin the process of opening a new L2CAP channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The L2CAP
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.  This prevents a situation where the channel succeeds
                in being configured and opened and receives data before the client is listening and
                is ready for it.
                
                Because a new IOBluetoothL2CAPChannelRef will be created for the client as a result of this
                function, the client is responsible for releasing the resulting IOBluetoothL2CAPChannelRef
                (by calling IOBluetoothObjectRelease()).
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.
 
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
 
    @param		btDevice 		The target IOBluetoothDeviceRef
	@param		newChannel		A pointer to an IOBluetoothL2CAPChannelRef to receive the L2CAP channel 
                                requested to be opened.  The newChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@param		psm				The L2CAP PSM value for the new channel.
	@param		withEventListener a IOBluetoothL2CAPChannelIncomingEventListener where to receive events
								  regarding the channel (MUST be specified).
	@param		refCon			a refcon pointer (for the callback specified above).
	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                L2CAP channel was found). 
*/

extern IOReturn IOBluetoothDeviceOpenL2CAPChannelSync(IOBluetoothDeviceRef btDevice, IOBluetoothL2CAPChannelRef *newChannel, BluetoothL2CAPPSM psm, IOBluetoothL2CAPChannelIncomingEventListener eventListener, void *refcon) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

#if 0
#pragma mark -
#pragma mark ===  L2CAP channel ===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelCreateFromObjectID
	@abstract	Returns the IOBluetoothL2CAPChannelRef with the given IOBluetoothObjectID.
    @discussion	The IOBluetoothObjectID can be used as a global reference for a given IOBluetoothL2CAPChannelRef.  It allows
				two separate applications to refer to the same IOBluetoothL2CAPChannelRef.
 
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
 
    @param		objectID	IOBluetoothObjectID of the desired IOBluetoothL2CAPChannelRef
	@result		Returns the IOBluetoothL2CAPChannelRef that matches the given IOBluetoothObjectID if one exists.  The 
				resulting IOBluetoothL2CAPChannelRef must be released by the caller by calling IOBluetoothObjectRelease.
				If no matching L2CAP channel exists, NULL is returned.
*/

extern IOBluetoothL2CAPChannelRef IOBluetoothL2CAPChannelCreateFromObjectID( IOBluetoothObjectID objectID ) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelGetObjectID
	@abstract	Returns the IOBluetoothObjectID of the given IOBluetoothL2CAPChannelRef.
    @discussion	The IOBluetoothObjectID can be used as a global reference for a given IOBluetoothL2CAPChannelRef.  It allows
				two separate applications to refer to the same IOBluetoothL2CAPChannelRef.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		l2capChannel	Target IOBluetoothL2CAPChannelRef
	@result		Returns the IOBluetoothObjectID of the given IOBluetoothl2CAPChannelRef.
*/

extern IOBluetoothObjectID IOBluetoothL2CAPChannelGetObjectID( IOBluetoothL2CAPChannelRef l2capChannel ) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelCloseChannel
	@abstract	Initiates the close process on an open L2CAP channel.
    @discussion	This method may only be called by the client that opened the channel in the first place.  In the future
                asynchronous and synchronous versions will be provided that let the client know when the close process
                has been finished.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		l2capChannel	Target L2CAP channel ref
	@result		Returns kIOReturnSuccess on success.
*/

extern IOReturn IOBluetoothL2CAPChannelCloseChannel(IOBluetoothL2CAPChannelRef l2capChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelRequestRemoteMTU
	@abstract	Initiates the process to reconfigure the L2CAP channel with a new outgoing MTU.
    @discussion	Currently, this API does not give an indication that the re-config process has completed.  In
                the future additional API will be available to provide that information both synchronously and
                asynchronously.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		l2capChannel	Target L2CAP channel ref
    @param		remoteMTU		The desired outgoing MTU. 
	@result		Returns kIOReturnSuccess if the channel re-configure process was successfully initiated.
*/

extern IOReturn IOBluetoothL2CAPChannelRequestRemoteMTU( IOBluetoothL2CAPChannelRef l2capChannel, BluetoothL2CAPMTU remoteMTU ) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelWrite
	@abstract	Writes the given data over the target L2CAP channel to the remote device.
    @discussion	The length of the data may not exceed the L2CAP channel's ougoing MTU.

				***		DEPRECATED IN BLUETOOTH 2.0 (Mac OS X 10.5)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		l2capChannel	Target L2CAP channel ref
    @param		data	Pointer to the buffer containing the data to send.
    @param		length	The length of the given data buffer.
	@result		Returns kIOReturnSuccess if the data was buffered successfully.
*/

extern IOReturn IOBluetoothL2CAPChannelWrite(IOBluetoothL2CAPChannelRef l2capChannel, void *data, UInt16 length) DEPRECATED_IN_BLUETOOTH_VERSION_2_0_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelWriteAsync
	@abstract	Writes asynchronously the given data over the target L2CAP channel to the remote device.
    @discussion	The length of the data may not exceed the L2CAP channel's ougoing MTU.
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

	@param		l2capChannel	Target L2CAP channel ref
    @param		data	Pointer to the buffer containing the data to send.
    @param		length	The length of the given data buffer.
	@param		refcon	a write identificator (is a void*, so it is up to the developer) that will be returned in the kIOBluetoothL2CAPWriteCompletedEvent.
	@result		Returns kIOReturnSuccess if the data was buffered successfully.
*/

extern IOReturn IOBluetoothL2CAPChannelWriteAsync(IOBluetoothL2CAPChannelRef l2capChannel, void *data, UInt16 length, void *refcon) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelWriteAsync
	@abstract	Writes synchronously the given data over the target L2CAP channel to the remote device.
    @discussion	The length of the data may not exceed the L2CAP channel's ougoing MTU. This method may block if previous writes have not been delivered.
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		l2capChannel	Target L2CAP channel ref
    @param		data	Pointer to the buffer containing the data to send.
    @param		length	The length of the given data buffer.
	@result		Returns kIOReturnSuccess if the data was buffered successfully.
*/

extern IOReturn IOBluetoothL2CAPChannelWriteSync(IOBluetoothL2CAPChannelRef l2capChannel, void *data, UInt16 length) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelRegisterIncomingDataListener
	@abstract	Allows a client to register a callback that gets called when new incoming data arrives.
    @discussion A newly opened L2CAP channel will not complete its configuration process until the client
                that opened it registers an incoming data listener.  This prevents that case where incoming
                data is received before the client is ready.  

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		l2capChannel	Target L2CAP channel ref
    @param		listener	Callback function that gets called when new incoming data is received.
    @param		refCon 		Client-supplied reference that gets passed to the listener function.
	@result		Returns kIOReturnSuccess if the listener is successfully registered.
*/

extern IOReturn IOBluetoothL2CAPChannelRegisterIncomingDataListener(IOBluetoothL2CAPChannelRef l2capChannel, IOBluetoothL2CAPChannelIncomingDataListener listener, void *refCon) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothL2CAPChannelRegisterIncomingEventListener
	@abstract	Registers a callback for events. 
	@discussion Registers a callback for events generated by the L2CAP channel. The form for the callback is:

				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

        @param		l2capChannel (IOBluetoothRFCOMMChannelRef) The channel reference
        @param 		listener is the callback function.
        @param 		refCon is a void*, its meaning is up to the developer. This parameter will be passed back as second parameter of
                        the callback function.
        @result An error code value. 0 if successful. 
*/

extern IOReturn	IOBluetoothL2CAPChannelRegisterIncomingEventListener(IOBluetoothL2CAPChannelRef l2capChannel, IOBluetoothL2CAPChannelIncomingEventListener listener, void *refCon) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelGetOutgoingMTU
	@abstract	Returns the current outgoing MTU for the L2CAP channel.
    @discussion	The outgoing MTU represents the maximum L2CAP packet size for packets being sent to the remote device.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		l2capChannel	Target L2CAP channel ref
	@result		Returns the current outgoing MTU for the L2CAP channel.
*/

extern BluetoothL2CAPMTU IOBluetoothL2CAPChannelGetOutgoingMTU(IOBluetoothL2CAPChannelRef l2capChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelGetIncomingMTU
	@abstract	Returns the current incoming MTU for the L2CAP channel.
    @discussion	The incoming MTU represents the maximum L2CAP packet size for packets being sent by the remote device.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		l2capChannel	Target L2CAP channel ref
	@result		Returns the current incoming MTU for the L2CAP channel.
*/

extern BluetoothL2CAPMTU IOBluetoothL2CAPChannelGetIncomingMTU(IOBluetoothL2CAPChannelRef l2capChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelGetDevice
	@abstract	Returns the IOBluetoothDevice to which the target L2CAP channel is open.
    @discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
    @param		l2capChannel	Target L2CAP channel ref
	@result		Returns the IOBluetoothDevice to which the target L2CAP channel is open.  The caller
                does NOT need to release the returned IOBluetoothDeviceRef.
*/

extern IOBluetoothDeviceRef IOBluetoothL2CAPChannelGetDevice(IOBluetoothL2CAPChannelRef l2capChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelGetPSM
	@abstract	Returns the PSM for the target L2CAP channel.
    @discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
    @param		l2capChannel	Target L2CAP channel ref
	@result		Returns the PSM for the target L2CAP channel.
*/

extern BluetoothL2CAPPSM IOBluetoothL2CAPChannelGetPSM(IOBluetoothL2CAPChannelRef l2capChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelGetLocalChannelID
	@abstract	Returns the local L2CAP channel ID for the target L2CAP channel.
    @discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
    @param		l2capChannel	Target L2CAP channel ref
	@result		Returns the local L2CAP channel ID for the target L2CAP channel.
*/

extern BluetoothL2CAPChannelID IOBluetoothL2CAPChannelGetLocalChannelID(IOBluetoothL2CAPChannelRef l2capChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelGetRemoteChannelID
	@abstract	Returns the remote L2CAP channel ID for the target L2CAP channel.
    @discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		l2capChannel	Target L2CAP channel ref
	@result		Returns the remote L2CAP channel ID for the target L2CAP channel.
*/

extern BluetoothL2CAPChannelID IOBluetoothL2CAPChannelGetRemoteChannelID(IOBluetoothL2CAPChannelRef l2capChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothL2CAPChannelIsIncoming
	@abstract	Returns TRUE if the channel is an incoming channel.
    @discussion	An incoming channel is one that was initiated by a remote device.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		l2capChannel	Target L2CAP channel ref
	@result		Returns TRUE if the channel is an incoming channel.
*/

extern Boolean IOBluetoothL2CAPChannelIsIncoming(IOBluetoothL2CAPChannelRef l2capChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//===========================================================================================================================
// RFCOMM channel user client routines
//===========================================================================================================================
 
 #if 0
#pragma mark -
#pragma mark === RFCOMM ===
#endif


 //===========================================================================================================================
// RFCOMM channel events
//===========================================================================================================================

#if 0
#pragma mark -
#pragma mark === RFCOMM channel events===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothRFCOMMEvent
	@discussion	The events generated by an RFCOMM channel:
	
        <br>
        kIOBluetoothRFCOMMChannelEventTypeData:	new data.
        <br>
        kIOBluetoothRFCOMMChannelEventTypeFlowControlChanged: flow control changed.
        <br>
        kIOBluetoothRFCOMMChannelEventTypeClosed: channel terminated.
        <br>
        kIOBluetoothRFCOMMChannelEventTypeControlSignalsChanged: signals (like DTR, CTR) changed. (not yet supported)
        <br>
		kIOBluetoothRFCOMMChannelEventTypeWriteComplete:	write operation completed
		<br>
		kIOBluetoothRFCOMMChannelEventTypeQueueSpaceAvailable: more room in the RFCOMM channel output queue
		
		Obsolete Event types:
		
        <br>
        kIOBluetoothRFCOMMNewDataEvent:	new data.
        <br>
        kIOBluetoothRFCOMMFlowControlChangedEvent: flow control changed.
        <br>
        kIOBluetoothRFCOMMChannelTerminatedEvent: channel terminated.
        <br>
        kIOBluetoothRFCOMMControlSignalsChangedEvent: signals (like DTR, CTR) changed. (not yet supported)
        <br>
        
        See the description of kIOBluetoothRFCOMMChannelEventTypeDataType and  kIOBluetoothRFCOMMChannelEventTypeFlowControlChangedType for more
        information on these events.
*/


typedef enum IOBluetoothRFCOMMChannelEventType {
	// New event types added in 1.2 (Mac OS X 10.2.5)
	kIOBluetoothRFCOMMChannelEventTypeData									=	0x0000,
	kIOBluetoothRFCOMMChannelEventTypeFlowControlChanged					=	0x0001,
	kIOBluetoothRFCOMMChannelEventTypeClosed								=	0x0002,
	kIOBluetoothRFCOMMChannelEventTypeOpenComplete							=	0x0003,
	kIOBluetoothRFCOMMChannelEventTypeControlSignalsChanged					=	0x0004,
	kIOBluetoothRFCOMMChannelEventTypeWriteComplete						=	0x0005,
	kIOBluetoothRFCOMMChannelEventTypeQueueSpaceAvailable					=	0x0006,
	
	// Obsolete Event names:
	kIOBluetoothRFCOMMNewDataEvent				=	0x0000,
	kIOBluetoothRFCOMMFlowControlChangedEvent	=	0x0001,
	kIOBluetoothRFCOMMChannelTerminatedEvent	=	0x0002
} IOBluetoothRFCOMMChannelEventType;

// This is to keep build build. Please use the new type, this is going to be deprecated
typedef IOBluetoothRFCOMMChannelEventType IOBluetoothRFCOMMEvent;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothRFCOMMDataBlock
	@discussion	Associted to the kIOBluetoothRFCOMMNewDataEvent it carries a pointer and a size of the new incoming data.

*/

typedef struct IOBluetoothRFCOMMDataBlock
{
    void 	*dataPtr;
    size_t	dataSize;
} IOBluetoothRFCOMMDataBlock;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothRFCOMMFlowControlStatus
	@discussion	Related to the kIOBluetoothRFCOMMFlowControlChangedEvent it carries the status of the flow control.
                        For the first release of the APIs this event is generated only when flow control switches from OFF
                        to ON. Future releases will support the switch from ON to OFF as well.
*/

typedef enum IOBluetoothRFCOMMFlowControlStatus {
    kIOBluetoothRFCOMMChannelFlowControlStatusIsOff		=	0x0000,
    kIOBluetoothRFCOMMChannelFlowControlStatusIsOn		=	0x0001
} IOBluetoothRFCOMMFlowControlStatus;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothRFCOMMChannelEvent
	@discussion	Structure that holds an RFCOMM event.
*/

typedef struct IOBluetoothRFCOMMChannelEvent {
	// Caution:  You cannot add any more values here for binary compatibility reasons
    IOBluetoothRFCOMMChannelEventType	eventType;
    union
    {
			// Caution:  An element of this union cannot grow beyond 32 bytes in size for binary compatibility reasons.
            IOBluetoothRFCOMMDataBlock				data;
            IOBluetoothRFCOMMFlowControlStatus		flowStatus;
            IOBluetoothRFCOMMChannelRef				terminatedChannel;
			void*									writeRefCon;
			
			UInt8								padding[32];

			// Old name, is going to be deprecated, use data instead
			IOBluetoothRFCOMMDataBlock				newData;
    } u;
	IOReturn							status;
	// Add new items above this comment.
} IOBluetoothRFCOMMChannelEvent;


//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothRFCOMMChannelIncomingDataListener
	@abstract	Typedef for the RFCOMM channel data listener.
	@param		rfcommChannel	(IOBluetoothRFCOMMChannelRef)	RFCOMM channel which received the data.
	@param		data			(void *)						Pointer to the data received.
	@param		length			(UInt16)						Length of the data received.
	@param		refCon			(void *)						User-defined refCon provided upon registration.
	@discussion	This is the definition for the callback which will be invoked upon receiving data on a RFCOMM channel. This is a
        semplified version of IOBluetoothRFCOMMChannelIncomingEventListener. See IOBluetoothRFCOMMChannelIncomingEventListener for more
        information on the rfcommChannel parameter.
*/

typedef void (*IOBluetoothRFCOMMChannelIncomingDataListener)(IOBluetoothRFCOMMChannelRef rfcommChannel, void *data, UInt16 length, void *refCon);

//--------------------------------------------------------------------------------------------------------------------------
/*!	@typedef	IOBluetoothRFCOMMChannelIncomingEventListener
	@abstract	Typedef for the RFCOMM channel event listener.
	@param		rfcommChannel	(IOBluetoothRFCOMMChannelRef)		RFCOMM channel which received the events.
	@param		refCon		(void *)				User-defined refCon provided upon registration.
	@param		event		(IOBluetoothRFCOMMChannelEvent)		The type of event for this notification.
	@discussion	This is the definition for the callback which will be invoked upon receiving data on a RFCOMM channel.
        
        For example an event listener function:
        
        <pre>

    void rfcommEventListener (IOBluetoothRFCOMMChannelRef rfcommChannel, void *refCon, IOBluetoothRFCOMMChannelEvent *event)
    {
        switch (event->eventType)
        {
                case kIOBluetoothRFCOMMNewDataEvent:
                    // In thise case:
                    // event->u.newData.dataPtr  is a pointer to the block of data received.
                    // event->u.newData.dataSize is the size of the block of data.
                break;
                
                case kIOBluetoothRFCOMMFlowControlChangedEvent:
                    // In thise case:
                    // event->u.flowStatus       is the status of flow control (see IOBluetoothRFCOMMFlowControlStatus for current restrictions)
                break;
                
                case kIOBluetoothRFCOMMChannelTerminatedEvent:
                    // In this case:
                    // event->u.terminatedChannel is the channel that was terminated. It can be converted in an IOBluetoothRFCOMMChannel
                    // object with [IOBluetoothRFCOMMChannel withRFCOMMChannelRef:]. (see below).
                break;
        }
    }

        </pre>
        
        rfcommChannel is the channel that generated the event and it is the channel where the callback was generated. 
        rfcommChannel is a  IOBluetoothRFCOMMChannelRef reference, it can be converted in an Objective C IOBluetoothRFCOMMChannel
        object with:
        
        <pre>
        
    IOBluetoothRFCOMMChannel *myOBJCChannel = [IOBluetoothRFCOMMChannel withRFCOMMChannelRef:rfcommChannel];
        
        </pre>
*/

typedef void (*IOBluetoothRFCOMMChannelIncomingEventListener)(IOBluetoothRFCOMMChannelRef rfcommChannel, void *refCon, IOBluetoothRFCOMMChannelEvent *event);

//===========================================================================================================================
// RFCOMM channel creation
//===========================================================================================================================
 
 #if 0
#pragma mark -
#pragma mark === Device - RFCOMM channel creation===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceOpenRFCOMMChannel
	@abstract	Opens a new RFCOMM channel to the target device.
	@discussion	This function will begin the process of opening a new RFCOMM channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The RFCOMM
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.
                                
                Because a new IOBluetoothRFCOMMChannelRef will be created for the client as a result of this
                function, the client is responsible for releasing the resulting IOBluetoothRFCOMMChannelRef
                (by calling IOBluetoothObjectRelease()).

				***		DEPRECATED IN BLUETOOTH 2.0 (Mac OS X 10.5)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		btDevice The target IOBluetoothDeviceRef
	@param		channelID		The RFCOMM channel ID for the new channel.
	@param		rfcommChannel	A pointer to an IOBluetoothRFCOMMChannelRef to receive the RFCOMM channel 
                                requested to be opened.  The rfcommChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@result		Returns kIOReturnSuccess if the open process was successfully started (or if an existing
                RFCOMM channel was found). 
*/

extern IOReturn IOBluetoothDeviceOpenRFCOMMChannel(IOBluetoothDeviceRef btDevice, BluetoothRFCOMMChannelID channelID, IOBluetoothRFCOMMChannelRef *rfcommChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_0_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceOpenRFCOMMChannelAsync
	@abstract	Opens a new RFCOMM channel to the target device. Returns immedialty after starting the opening process.
	@discussion	This function will begin the process of opening a new RFCOMM channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The RFCOMM
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.
                                
                Because a new IOBluetoothRFCOMMChannelRef will be created for the client as a result of this
                function, the client is responsible for releasing the resulting IOBluetoothRFCOMMChannelRef
                (by calling IOBluetoothObjectRelease()).
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		btDevice The target IOBluetoothDeviceRef
	@param		rfcommChannel	A pointer to an IOBluetoothRFCOMMChannelRef to receive the RFCOMM channel 
                                requested to be opened.  The rfcommChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@param		channelID		The RFCOMM channel ID for the new channel.
	@param		withEventListener a IOBluetoothRFCOMMChannelIncomingEventListener where to receive events
								  regarding the channel (MUST be specified).
	@param		refCon			a refcon pointer (for the callback specified above).
	@result		Returns kIOReturnSuccess if the open process was successfully started .
*/

IOReturn IOBluetoothDeviceOpenRFCOMMChannelAsync(IOBluetoothDeviceRef btDevice, IOBluetoothRFCOMMChannelRef *newChannel, BluetoothRFCOMMChannelID channelID, IOBluetoothRFCOMMChannelIncomingEventListener eventListener, void *refcon) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceOpenRFCOMMChannelSync
	@abstract	Opens a new RFCOMM channel to the target device. Does not return until the channel is open or failed to open.
	@discussion	This function will begin the process of opening a new RFCOMM channel to the target device.  
                The baseband connection to the device will be opened if it is not open already.  The RFCOMM
                channel open process will not complete until the client has registered an incoming data 
                listener on the new channel.
                                
                Because a new IOBluetoothRFCOMMChannelRef will be created for the client as a result of this
                function, the client is responsible for releasing the resulting IOBluetoothRFCOMMChannelRef
                (by calling IOBluetoothObjectRelease()).
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		btDevice The target IOBluetoothDeviceRef
	@param		rfcommChannel	A pointer to an IOBluetoothRFCOMMChannelRef to receive the RFCOMM channel 
                                requested to be opened.  The rfcommChannel pointer will only be set if 
                                kIOReturnSuccess is returned.
	@param		channelID		The RFCOMM channel ID for the new channel.
	@param		withEventListener a IOBluetoothRFCOMMChannelIncomingEventListener where to receive events
								  regarding the channel (MUST be specified).
	@param		refCon			a refcon pointer (for the callback specified above).
	@result		Returns kIOReturnSuccess if the open process was successfully started .
*/

IOReturn IOBluetoothDeviceOpenRFCOMMChannelSync(IOBluetoothDeviceRef btDevice, IOBluetoothRFCOMMChannelRef *newChannel, BluetoothRFCOMMChannelID channelID, IOBluetoothRFCOMMChannelIncomingEventListener eventListener, void *refcon) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;


#if 0
#pragma mark -
#pragma mark === RFCOMM Channel ===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothRFCOMMChannelCreateFromObjectID
	@abstract	Returns the IOBluetoothRFCOMMChannelRef with the given IOBluetoothObjectID.
    @discussion	The IOBluetoothObjectID can be used as a global reference for a given IOBluetoothRFCOMMChannelRef.  It allows
				two separate applications to refer to the same IOBluetoothRFCOMMChannelRef.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		objectID	IOBluetoothObjectID of the desired IOBluetoothRFCOMMChannelRef
	@result		Returns the IOBluetoothRFCOMMChannelRef that matches the given IOBluetoothObjectID if one exists.  The 
				resulting IOBluetoothRFCOMMChannelRef must be released by the caller by calling IOBluetoothObjectRelease.
				If no matching RFCOMM channel exists, NULL is returned.
*/

extern IOBluetoothRFCOMMChannelRef IOBluetoothRFCOMMChannelCreateFromObjectID( IOBluetoothObjectID objectID ) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothRFCOMMChannelGetObjectID
	@abstract	Returns the IOBluetoothObjectID of the given IOBluetoothRFCOMMChannelRef.
    @discussion	The IOBluetoothObjectID can be used as a global reference for a given IOBluetoothRFCOMMChannelRef.  It allows
				two separate applications to refer to the same IOBluetoothRFCOMMChannelRef.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		rfcommChannel	Target IOBluetoothRFCOMMChannelRef
	@result		Returns the IOBluetoothObjectID of the given IOBluetoothRFCOMMChannelRef.
*/

extern IOBluetoothObjectID IOBluetoothRFCOMMChannelGetObjectID( IOBluetoothRFCOMMChannelRef rfcommChannel ) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelCloseChannel
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@result		An error code value. 0 if successful.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn	IOBluetoothRFCOMMChannelCloseChannel(IOBluetoothRFCOMMChannelRef rfcommChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelIsOpen
	@abstract	
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@result		true if the channel is open false if the channel is not open.
	@discussion	note that "not open" means closed, opening and closing

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern Boolean IOBluetoothRFCOMMChannelIsOpen(IOBluetoothRFCOMMChannelRef rfcommChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelGetMTU
	@abstract	
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@result		Channel MTU size.
	@discussion Returns the length of the largest chunk of data that this channel can carry. If the
				caller wishes to use the write:length:sleep: api the length of the data can not be bigger than
				the channel MTU (maximum transfer unit).	

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern BluetoothRFCOMMMTU IOBluetoothRFCOMMChannelGetMTU( IOBluetoothRFCOMMChannelRef rfcommChannel ) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//-------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelIsTransmissionPaused
	@abstract	
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@result		true if the action of sending data will block the current thread, false otherwise.
	@discussion Returns true if the remote device flow control is stopping out transmission. This is
                useful because we do not buffer data, we stop the transmitting actor. With this method
                the transmitter can check if sending data is going to be successful or is going to block. 

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern Boolean IOBluetoothRFCOMMChannelIsTransmissionPaused( IOBluetoothRFCOMMChannelRef rfcommChannel ) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER; 

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelGetChannelID
	@abstract	Returns the RFCOMM channel number for a given IOBluetoothRFCOMMChannelRef.
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@result		the RFCOMM channel number for this channel.
	@discussion	Returns the RFCOMM channel number for a given IOBluetoothRFCOMMChannelRef.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern BluetoothRFCOMMChannelID IOBluetoothRFCOMMChannelGetChannelID( IOBluetoothRFCOMMChannelRef rfcommChannel ) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelWrite
	@abstract	Write data to a RFCOMM channel synchronusly.
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@param 		data is a pointer to the data buffer to be sent.
	@param 		length the length of the buffer to be sent (in bytes).
	@param 		sleepFlag is a boolean if set to TRUE the call will wait until it is possible to send data.
				If set to FALSE and it is not possible to send data the method will return immediately with an error
	@result		An error code value. 0 if successful.
	@discussion Sends data through the channel. The number of bytes to be sent must not exceed the channel MTU. 
				If the return value is an error condition none of the data was sent.

				***		DEPRECATED IN BLUETOOTH 2.0 (Mac OS X 10.5)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn	IOBluetoothRFCOMMChannelWrite(IOBluetoothRFCOMMChannelRef rfcommChannel, void *data, UInt16 length, Boolean sleepFlag) DEPRECATED_IN_BLUETOOTH_VERSION_2_0_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelWriteAsync
	@abstract	Write data to a RFCOMM channel asynchronously.
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@param 		data is a pointer to the data buffer to be sent.
	@param 		length the length of the buffer to be sent (in bytes).
	@param		refcon a NON NULL value that will be contained in the return event (once the data is sent).
	@result		An error code value. 0 if successful.
	@discussion	Sends data through the channel. The number of bytes to be sent must not exceed the channel MTU. 
				If the return value is an error condition none of the data was sent.
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn	IOBluetoothRFCOMMChannelWriteAsync(IOBluetoothRFCOMMChannelRef rfcommChannel, void *data, UInt16 length, void *refcon) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelWriteSync
	@abstract	Write data to a RFCOMM channel synchronously.
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@param 		data is a pointer to the data buffer to be sent.
	@param 		length the length of the buffer to be sent (in bytes).
	@param		refcon a NON NULL value that will be contained in the return event (once the data is sent).
	@result		An error code value. 0 if successful.
	@discussion	Sends data through the channel. The number of bytes to be sent must not exceed the channel MTU. 
				If the return value is an error condition none of the data was sent.
				
				NOTE: This function is only available in Mac OS X 10.2.5 (Bluetooth v1.2) or later.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn	IOBluetoothRFCOMMChannelWriteSync(IOBluetoothRFCOMMChannelRef rfcommChannel, void *data, UInt16 length) AVAILABLE_BLUETOOTH_VERSION_1_2_AND_LATER DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelWriteSimple
	@abstract	
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@param		data a pointer to the data buffer to be sent.
	@param		length the length of the buffer to be sent (in bytes).
	@param		sleepFlag a boolean if set to true the call will wait until it is possible to send all the data.
	@param		a UInt32 pointer in which the caller received the nuber of bytes sent.
				If set to FALSE and it is not possible to send part of the data the method will return immediately.
	@result		An error code value. 0 if successful.
	@discussion	Sends data through the channel. The number of bytes to be sent is arbitrary. The caller
				does not have to worry about the MTU. 

				***		DEPRECATED IN BLUETOOTH 2.0 (Mac OS X 10.5)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn IOBluetoothRFCOMMChannelWriteSimple(IOBluetoothRFCOMMChannelRef rfcommChannel, void *data, UInt16 length, Boolean sleepFlag, UInt32 *numBytesSent) DEPRECATED_IN_BLUETOOTH_VERSION_2_0_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMSetSerialParameters
	@abstract	
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@param		speed				
	@param		nBits				
	@param		parity	
	@param		bitStop			
	@result		An error code value. 0 if successful.	
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn IOBluetoothRFCOMMSetSerialParameters(IOBluetoothRFCOMMChannelRef rfcommChannel, UInt32 speed, UInt8 nBits, BluetoothRFCOMMParityType parity, UInt8 bitStop) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelGetDevice
	@abstract	
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@result		A reference to the device where this RFCOMM channel was open. 0 if unsuccessful.  The caller does NOT
				need to release the returned IOBluetoothDeviceRef.
	@discussion	

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOBluetoothDeviceRef IOBluetoothRFCOMMChannelGetDevice(IOBluetoothRFCOMMChannelRef rfcommChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;


//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMSendRemoteLineStatus
	@abstract	
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@param 		lineStatus the error type. The error code can be NoError, OverrunError, ParityError or FramingError.							
	@result		An error code value. 0 if successful.	
	@discussion	

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn IOBluetoothRFCOMMSendRemoteLineStatus( IOBluetoothRFCOMMChannelRef rfcommChannel , BluetoothRFCOMMLineStatus lineStatus) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelRegisterIncomingDataListener
	@abstract	
	@discussion Registers a callback for the incoming data. The form for the callback is:
	
				<br>void function(IOBluetoothRFCOMMChannelRef rfcommChannel, void *data, UInt16 length, void *refCon)<br>
	
				where rfcommChannel is the refernce to the channel that received data, data is a buffer with the received data, length is the buffer length
				(in bytes) and refCon is a user defined void* (maybe the reference to the object to call back ?).

				***		DEPRECATED IN BLUETOOTH 2.0 (Mac OS X 10.5)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@param 		listener is the callback function.
	@param 		refCon is a void*, its meaning is up to the developer. This parameter will be passed back as last parameter of
				the callback function.
	@result		An error code value. 0 if successful. 	
*/

extern IOReturn	IOBluetoothRFCOMMChannelRegisterIncomingDataListener(IOBluetoothRFCOMMChannelRef rfcommChannel, IOBluetoothRFCOMMChannelIncomingDataListener listener, void *refCon) DEPRECATED_IN_BLUETOOTH_VERSION_2_0_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelRegisterIncomingEventListener
	@abstract	Registers a callback for events. 
	@discussion	Registers a callback for events generated by the RFCOMM channel. The form for the callback is:
	
				<br>void function(IOBluetoothRFCOMMChannelRef rfcommChannel, void *refCon, IOBluetoothRFCOMMChannelEvent *event)<br>
				
				where rfcommChannel is the refernce to the channel that generated the event, refCon is a user defined void* (maybe the reference to the object to
				call back ?) and event is the generated event. There are three types of events available:

				<br>
				kIOBluetoothRFCOMMNewDataEvent when new data is received.<br>
				kIOBluetoothRFCOMMFlowControlChangedEvent change of flow control.<br>
				kIOBluetoothRFCOMMChannelTerminatedEvent when the rfcomm channel is no more valid.<br>
				<br>
				
				Note that the kIOBluetoothRFCOMMNewDataEvent provides the same functionality
				of the data listener callback. This means that if the developer has both an event callback and a datalistener callback both
				functions will be called when new data arrives. It is up to the developer to properly filter the events (or better to use only
				one callback). For a better descriptions of the events and the event structure see IOBluetoothUserLib.h.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference
	@param 		listener is the callback function.
	@param 		refCon is a void*, its meaning is up to the developer. This parameter will be passed back as second parameter of
				the callback function.
	@result		An error code value. 0 if successful. 
*/


extern IOReturn	IOBluetoothRFCOMMChannelRegisterIncomingEventListener(IOBluetoothRFCOMMChannelRef rfcommChannel, IOBluetoothRFCOMMChannelIncomingEventListener listener, void *refCon) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRFCOMMChannelIsIncoming
	@abstract 	Returns the direction of the channel.  An incoming channel is one that was opened by the remote
				device.
	@param		rfcommChannel (IOBluetoothRFCOMMChannelRef) The channel reference				
	@result 	Returns TRUE if the channel was opened by the remote device, FALSE if the channel was opened by this object.
	@discussion
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

*/

extern Boolean IOBluetoothRFCOMMChannelIsIncoming(IOBluetoothRFCOMMChannelRef rfcommChannel) DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

#if 0
#pragma mark -
#pragma mark === SDP ===
#endif

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothAddServiceDict
	@abstract	Adds a service to the local SDP server.
    @discussion	Each entry in the dictionary representing the service contains the individual attributes.  Each
                attribute in the dict is keyed by a string that must begin with a hex number representing the
                attribute ID.  The key string may contain additional characters if desired as long as they 
                follow a space after the ID hex string.  The attribute value must follow the dictionary format 
                described by IOBluetoothSDPDataElement.  This dictionary format allows a service dict to be
                created as a plist file and then loaded into the system rather than built up in code.  See the
                example code for an example of how can be done.
                
                If the service record handle, L2CAP PSM or RFCOMM channel ID specified in the dictionary are in
                use, an alternate one will be assigned.
                
                In addition to attributes that represent the service itself, additional attributes may be specified
				that control the local behavior of the service.  To specify these local attributes, an additional
				property titled "LocalAttributes" may be added to the root of the service dict.  The value of this 
				property must be a dictionary that contains the individual local attributes.
				
				Currently, only two local attributes are supported: "Persistent" and "TargetApplication".
				
				The "Persistent" local attribute must be either a boolean or number representing whether the service
				should be persistent.  A persistent service will be saved off and restored any time the Bluetooth
				hardware is present.  It will persist through reboots and can only be removed by calling 
				IOBluetoothRemoveServiceWithRecordHandle().  This attribute is optional.  By default, if no 
				"Persistent" local property is present,	the service will only exist temporarily.  It will 
				be removed either when IOBluetoothRemoveServiceWithRecordHandle() is called or when the client 
				application exits.
				
				The "TargetApplication" local attribute is used to specify an application to be launched when a 
				remote device attempts to connect to the service (by opening either an L2CAP or RFCOMM channel of
				the type specified in the service).  This value must be a string representing the absolute path to
				the target executable (not just the .app wrapper - i.e. 
				/System/Library/CoreServices/OBEXAgent.app/Contents/MacOS/OBEXAgent).  This attribute is optional.
				If no "TargetApplication" local attribute is specified, no special action will take place when an
				incoming connection to the service is created.  It is up to the client to be monitoring for the
				connection and to do the right thing when one appears.
				
				The "LocalAttributes" property is optional.  If it is not specified, by default the created service
				is transient and will be removed when the client exits.
                
                Additional local attributes to further control incoming services will be added in the future.
                
	@param		serviceDict	A dictionary containing the attributes for the new service
	@param		outServiceRecord A pointer to the newly created IOBluetoothSDPServiceRecordRef.  The assigned RFCOMM
				channel ID can be retrieved from the service record (as can other assigned parameters.)  This value 
				only gets set if kIOReturnSuccess is returned.  The caller is responsible for releasing the 
				IOBluetoothSDPServiceRecordRef by calling IOBluetoothObjectRelease() when done.
	@result		Returns kIOReturnSuccess if successful.
*/

extern IOReturn IOBluetoothAddServiceDict(CFDictionaryRef serviceDict, IOBluetoothSDPServiceRecordRef *outServiceRecord);

//--------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothRemoveServiceWithRecordHandle
	@abstract	Removes the given service from the local SDP server.
	@discussion	The service record handle passed to this function must match the handle in the service record returned by 
                IOBluetoothAddServiceDict.
	@param		serviceRecordHandle The handle of the service to be removed.
	@result		Returns kIOReturnSuccess if successful.
*/

extern IOReturn IOBluetoothRemoveServiceWithRecordHandle( BluetoothSDPServiceRecordHandle serviceRecordHandle );


#if 0
#pragma mark -
#pragma mark === IOBluetoothSDPUUID ===
#endif

/*!
    @function	IOBluetoothSDPUUIDCreateWithBytes
    @abstract	Creates a new IOBluetoothSDPUUIDRef  with the given bytes of the given length.
    @discussion If the length is invalid for a UUID, NULL is returned.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		bytes An array of bytes representing the UUID.
    @param		length The length of the array of bytes.
    @result		Returns the new IOBluetoothSDPUUIDRef or NULL on failure.  The caller MUST release the returned
				IOBluetoothSDPUUIDRef by calling IOBluetoothObjectRelease().
*/

extern IOBluetoothSDPUUIDRef IOBluetoothSDPUUIDCreateWithBytes(const void *bytes, UInt8 length)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPUUIDCreateWithData
    @abstract	Creates a new IOBluetoothSDPUUIDRef from the given CFDataRef.
    @discussion	If the length of the CFDataRef is invalid for a UUID, NULL is returned.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		data The CFDataRef containing the UUID bytes.
    @result		Returns the new IOBluetoothSDPUUIDRef or NULL on failure.  The caller MUST release the returned
				IOBluetoothSDPUUIDRef by calling IOBluetoothObjectRelease().
*/

extern IOBluetoothSDPUUIDRef IOBluetoothSDPUUIDCreateWithData(CFDataRef data)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPUUIDCreateUUID16
    @abstract	Creates a new 16-bit IOBluetoothSDPUUIDRef with the given UUID16
    @param		uuid16 A scalar representing a 16-bit UUID
    @result		Returns the new IOBluetoothSDPUUIDRef or NULL on failure.  The caller MUST release the returned
				IOBluetoothSDPUUIDRef by calling IOBluetoothObjectRelease().
    @discussion
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOBluetoothSDPUUIDRef IOBluetoothSDPUUIDCreateUUID16(BluetoothSDPUUID16 uuid16)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPUUIDCreateUUID32
    @abstract	Creates a new 32-bit IOBluetoothSDPUUIDRef with the given UUID32
    @param		uuid32 A scalar representing a 32-bit UUID
    @result		Returns the new IOBluetoothSDPUUIDRef or NULL on failure.  The caller MUST release the returned
				IOBluetoothSDPUUIDRef by calling IOBluetoothObjectRelease().
    @discussion
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOBluetoothSDPUUIDRef IOBluetoothSDPUUIDCreateUUID32(BluetoothSDPUUID32 uuid32)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPUUIDGetBytes
    @abstract	Returns a pointer to the array of UUID bytes.
    @param		uuid The target IOBluetoothSDPUUIDRef
    @result		Returns a pointer to the array of UUID bytes.
    @discussion
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern const void *IOBluetoothSDPUUIDGetBytes(IOBluetoothSDPUUIDRef uuid)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPUUIDGetLength
    @abstract	Returns the length (in bytes) of the UUID.
    @param		uuid The target IOBluetoothSDPUUIDRef
    @result		Returns the length (in bytes) of the UUID.
    @discussion
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern UInt8 IOBluetoothSDPUUIDGetLength(IOBluetoothSDPUUIDRef uuid)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPUUIDGetUUIDWithLength
    @abstract	Returns an IOBluetoothSDPUUIDRef matching the target UUID, but with the given number of bytes.
    @discussion If the target IOBluetoothSDPUUIDRef is the same length as newLength, it returns the
                IOBluetoothSDPUUIDRef itself.  If newLength is greater it creates a new IOBluetoothSDPUUIDRef 
                with the correct value for the given length.  If newLength is smaller, it will attempt to create 
                a new IOBluetoothSDPUUIDRef that is smaller if the data matches the Bluetooth UUID base.  This 
                downconversion is currently unimplemented.
                
                Because this function creates a new IOBluetoothSDPUUIDRef to be returned, the caller is
                responsible for calling IOBluetoothObjectRelease() on the returned IOBluetoothSDPUUIDRef.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		uuid The target IOBluetoothSDPUUIDRef
    @param		newLength The desired length for the UUID. 
    @result		Returns an IOBluetoothSDPUUIDRef with the same data as the target but with the given length if it
				is possible to do so.  Otherwise, NULL is returned.
*/

extern IOBluetoothSDPUUIDRef IOBluetoothSDPUUIDGetUUIDWithLength(IOBluetoothSDPUUIDRef uuid, UInt8 newLength)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPUUIDIsEqualToUUID
    @abstract	Compares the two IOBluetoothSDPUUIDRefs.
    @discussion This function will compare the two UUID values independent of their length.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		uuid1 The first IOBluetoothSDPUUIDRef to be compared.
    @param		uuid2 The second IOBluetoothSDPUUIDRef to be compared.
    @result		Returns TRUE if the UUID values of each IOBluetoothSDPUUIDRef are equal.  This includes the case 
				where the sizes are different but the data itself is the same when the Bluetooth UUID base is applied.
*/

extern Boolean IOBluetoothSDPUUIDIsEqualToUUID(IOBluetoothSDPUUIDRef uuid1, IOBluetoothSDPUUIDRef uuid2)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

#if 0
#pragma mark -
#pragma mark === IOBluetoothSDPDataElement ===
#endif

/*!
    @function	IOBluetoothSDPDataElementGetTypeDescriptor
    @abstract	Returns the SDP spec defined data element type descriptor for the target data element.
    @param		dataElement The target IOBluetoothSDPDataElementRef.
    @result		Returns the type descriptor for the target data element.
    @discussion
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern BluetoothSDPDataElementTypeDescriptor IOBluetoothSDPDataElementGetTypeDescriptor(IOBluetoothSDPDataElementRef dataElement)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function IOBluetoothSDPDataElementGetSizeDescriptor
    @abstract Returns the SDP spec defined data element size descriptor for the target data element.
    @param	dataElement The target IOBluetoothSDPDataElementRef.
    @result Returns the size descriptor for the target data element.
    @discussion
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern BluetoothSDPDataElementSizeDescriptor IOBluetoothSDPDataElementGetSizeDescriptor(IOBluetoothSDPDataElementRef dataElement)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPDataElementGetSize
    @abstract	Returns the size in bytes of the target data element.
    @discussion The size is valid whether the data element has a fixed or variable size descriptor.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		dataElement The target IOBluetoothSDPDataElementRef.
    @result		Returns the size in bytes of the target data element.
*/

extern UInt32 IOBluetoothSDPDataElementGetSize(IOBluetoothSDPDataElementRef dataElement)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPDataElementGetNumberValue
    @abstract	If the data element is represented by a number, it returns the value as an CFNumberRef.
    @discussion The data types represented by a number are 1 (unsigned int), 2 (signed int) and 5 (boolean) 
                except for 128-bit versions of 1 and 2.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
    @param		dataElement The target IOBluetoothSDPDataElementRef.
	
    @result		Returns an CFNumberRef representation of the data element if it is a numeric type.  The caller is
				NOT responsible for releasing the returned CFNumberRef.
*/

extern CFNumberRef IOBluetoothSDPDataElementGetNumberValue(IOBluetoothSDPDataElementRef dataElement)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPDataElementGetDataValue
    @abstract	If the data element is represented by a data object, it returns the value as an CFDataRef.
    @discussion The data types represented by a data object are 128-bit versions of 1 (unsigned int) and 
                2 (signed int).

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
    @param		dataElement The target IOBluetoothSDPDataElementRef.
	
    @result		Returns an CFDataRef representation of the data element if it is a 128-bit number.  The caller is
				NOT responsible for releasing the returned IOBluetoothSDPDataElementRef.
*/

extern CFDataRef IOBluetoothSDPDataElementGetDataValue(IOBluetoothSDPDataElementRef dataElement)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPDataElementGetStringValue
    @abstract	If the data element is represented by a string object, it returns the value as a CFStringRef.
    @discussion The data types represented by a string object are 4 (text string) and 8 (URL).
    @param		dataElement The target IOBluetoothSDPDataElementRef.
    @result		Returns a CFStringRef representation of the data element if it is a text or URL type.  The caller is
				NOT responsible for releasing the returned CFStringRef.
*/

extern CFStringRef IOBluetoothSDPDataElementGetStringValue(IOBluetoothSDPDataElementRef dataElement)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPDataElementGetArrayValue
    @abstract	If the data element is represented by an array object, it returns the value as a CFArrayRef.
    @discussion The data types represented by an array object are 6 (data element sequence) and 7 (data
                element alternative).

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		dataElement The target IOBluetoothSDPDataElementRef.
    @result		Returns a CFArrayRef representation of the data element if it is a sequence type.  The caller is
				NOT responsible for releasing the returned CFArrayRef.
*/

extern CFArrayRef IOBluetoothSDPDataElementGetArrayValue(IOBluetoothSDPDataElementRef dataElement)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPDataElementGetUUIDValue
    @abstract	If the data element is a UUID (type 3), it returns the value as an IOBluetoothSDPUUIDRef.
    @param		dataElement The target IOBluetoothSDPDataElementRef.
    @result		Returns an IOBluetoothSDPUUIDRef representation of the data element if it is a UUID.  The caller is
				NOT responsible for releasing the returned IOBluetoothSDPUUIDRef.
    @discussion
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOBluetoothSDPUUIDRef IOBluetoothSDPDataElementGetUUIDValue(IOBluetoothSDPDataElementRef dataElement)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPDataElementContainsDataElement
    @abstract	Checks to see if the target data element is the same as the dataElement parameter or if it contains
                the dataElement parameter (if its a sequence type).
    @discussion If the target data element is not a sequence type, this method simply compares the two data elements.  If
                it is a sequence type, it will search through the sequence (and sub-sequences) for the dataElement
                parameter.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
   @param		dataElement The target IOBluetoothSDPDataElementRef.
    @param		subDataElement The data element to compare with (and search for). 
    @result		Returns TRUE if the target either matches the given data element or if it contains the given data element.
*/

extern Boolean IOBluetoothSDPDataElementContainsDataElement(IOBluetoothSDPDataElementRef dataElement, IOBluetoothSDPDataElementRef subDataElement)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPDataElementIsEqualToDataElement
    @abstract	Compares the target data element with the given object.
    @discussion This method will compare a data element with either another data element or a data element value.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		dataElement The target IOBluetoothSDPDataElementRef.
    @param		dataElement2 The IOBluetoothSDPDataElementRef to compare the target to.
    @result		Returns TRUE if the target data element is the same as the given object or if it's value matches the
				given object.
*/

extern Boolean IOBluetoothSDPDataElementIsEqualToDataElement(IOBluetoothSDPDataElementRef dataElement, IOBluetoothSDPDataElementRef dataElement2)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

#if 0
#pragma mark -
#pragma mark === IOBluetoothSDPServiceRecord ===
#endif

/*!
    @function	IOBluetoothSDPServiceRecordGetDevice
    @abstract	Returns the IOBluetoothDeviceRef that the target service belongs to.
    @discussion If the service is a local service (i.e. one the current host is vending out), then NULL is returned.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		serviceRecord The target IOBluetoothSDPServiceRecordRef
    @result		Returns the IOBluetoothDeviceRef that the target service belongs to.  If the service is one the local host
				is vending, then NULL is returned.
*/

extern IOBluetoothDeviceRef IOBluetoothSDPServiceRecordGetDevice(IOBluetoothSDPServiceRecordRef serviceRecord)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPServiceRecordGetAttributes
    @abstract	Returns a CFDictionaryRef containing the attributes for the service.
    @discussion The attribute dictionary is keyed off of the attribute id represented as a CFNumberRef.  The values
                in the CFDictionaryRef are IOBluetoothSDPDataElementRefs representing the data element for the
                given attribute.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		serviceRecord The target IOBluetoothSDPServiceRecordRef
    @result		Returns a CFDictionaryRef containing the attributes for the target service.
*/

extern CFDictionaryRef IOBluetoothSDPServiceRecordGetAttributes(IOBluetoothSDPServiceRecordRef serviceRecord)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPServiceRecordGetAttributeDataElement
    @abstract	Returns the data element for the given attribute ID in the target service.
    @param		serviceRecord The target IOBluetoothSDPServiceRecordRef
    @param		attributeID The attribute ID of the desired attribute.	 
    @result		Returns the data element for the given attribute ID in the target service.  If the service does not
				contain an attribute with the given ID, then NULL is returned.
    @discussion
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOBluetoothSDPDataElementRef IOBluetoothSDPServiceRecordGetAttributeDataElement(IOBluetoothSDPServiceRecordRef serviceRecord, BluetoothSDPServiceAttributeID attributeID)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPServiceRecordGetServiceName
    @abstract	Returns the name of the service.
    @param		serviceRecord The target IOBluetoothSDPServiceRecordRef
    @discussion This is currently implemented to simply return the attribute with an id of 0x0100.  In
                the future, it will be extended to allow name localization based on the user's chosen
                language or other languages.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @result		Returns the name of the target service.
*/

extern CFStringRef IOBluetoothSDPServiceRecordGetServiceName(IOBluetoothSDPServiceRecordRef serviceRecord)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPServiceRecordGetRFCOMMChannelID
    @abstract	Allows the discovery of the RFCOMM channel ID assigned to the service.
    @discussion This function will search through the ProtoclDescriptorList attribute to find an entry
                with the RFCOMM UUID (UUID16: 0x0003).  If one is found, it gets the second element of
                the data element sequence and sets the rfcommChannelID pointer to it.  The channel ID
                only gets set when kIOReturnSuccess is returned.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		serviceRecord The target IOBluetoothSDPServiceRecordRef
    @param		rfcommChannelID A pointer to the location that will get the found RFCOMM channel ID.
    @result		Returns kIOReturnSuccess if the channel ID is found.
*/

extern IOReturn IOBluetoothSDPServiceRecordGetRFCOMMChannelID(IOBluetoothSDPServiceRecordRef serviceRecord, BluetoothRFCOMMChannelID *channelID)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPServiceRecordGetL2CAPPSM
    @abstract	Allows the discovery of the L2CAP PSM assigned to the service.
    @discussion This function will search through the ProtoclDescriptorList attribute to find an entry
                with the L2CAP UUID (UUID16: 0x0100).  If one is found, it gets the second element of
                the data element sequence and sets the outPSM pointer to it.  The PSM value
                only gets set when kIOReturnSuccess is returned.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
				
    @param		serviceRecord The target IOBluetoothSDPServiceRecordRef
    @param		outPSM A pointer to the location that will get the found L2CAP PSM.
    @result		Returns kIOReturnSuccess if the PSM is found.
*/

extern IOReturn IOBluetoothSDPServiceRecordGetL2CAPPSM(IOBluetoothSDPServiceRecordRef serviceRecord, BluetoothL2CAPPSM *psm)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPServiceRecordGetServiceRecordHandle
    @abstract	Allows the discovery of the service record handle assigned to the service.
    @discussion This method will search through the attributes to find the one representing the 
                service record handle.  If one is found the outServiceRecordHandle param is set
                with the value.  The outServiceRecordHandle value only gets set when kIOReturnSuccess 
                is returned.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		serviceRecord The target IOBluetoothSDPServiceRecordRef
    @param		outServiceRecordHandle A pointer to the location that will get the found service record handle.
    @result		Returns kIOReturnSuccess if the service record handle is found.
*/

extern IOReturn IOBluetoothSDPServiceRecordGetServiceRecordHandle(IOBluetoothSDPServiceRecordRef serviceRecord, BluetoothSDPServiceRecordHandle *serviceRecordHandle)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

/*!
    @function	IOBluetoothSDPServiceRecordHasServiceFromArray
    @abstract	Returns TRUE if any one of the UUIDs in the given array is found in the target service.
    @discussion The given array should contain IOBluetoothSDPUUIDRefs.  It is currently implemented
                such that it returns TRUE if any of the UUIDs are found.  However in the future, it is likely
                that this will change to more closely match the functionality in the SDP spec so that it only
                returns TRUE if all of the given UUIDs are present.  That way, both AND and OR comparisons
                can be implemented.  Please make a note of this potential change.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.

    @param		serviceRecord The target IOBluetoothSDPServiceRecordRef
    @param		array An NSArray of IOBluetoothSDPUUIDRefs to search for in the target service.	 
    @result		Returns TRUE if any of the given UUIDs are present in the service.
*/

extern Boolean IOBluetoothSDPServiceRecordHasServiceFromArray(IOBluetoothSDPServiceRecordRef serviceRecord, CFArrayRef array)	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;


#if 0
#pragma mark -
#pragma mark === Notifications ===
#endif

typedef enum IOBluetoothUserNotificationChannelDirection
{
    kIOBluetoothUserNotificationChannelDirectionAny						= 0,
    kIOBluetoothUserNotificationChannelDirectionIncoming				= 1,
    kIOBluetoothUserNotificationChannelDirectionOutgoing				= 2,
} IOBluetoothUserNotificationChannelDirection;

/*!
    @typedef IOBluetoothUserNotificationCallback
    @abstract Callback function definition for user notifications.
    @discussion This callback will be invoked when the notification for which it was registered is sent.
    @param userRefCon	(void *) This user defined parameter was provided during the original call to register
						the notification.
    @param inRef		(IOBluetoothUserNotificationRef) The notification responsible for sending the notification.
    @param status		(IOBluetoothObjectRef) The object that originated the notification.
    @result None.
*/

typedef void (*IOBluetoothUserNotificationCallback)( 	void * userRefCon,
                                                        IOBluetoothUserNotificationRef inRef,
                                                        IOBluetoothObjectRef objectRef );

/*!
    @function IOBluetoothUserNotificationUnregister
    @abstract Unregisters the target notification.
    @discussion This function will unregister the notification.  Once the notification has been unregistered,
				it will no longer call the callback.  Additionally, once this function has been called the
				target IOBluetoothUserNotificationRef is no longer valid.
    @param	notificationRef The target IOBluetoothUserNotificationRef to be unregistered
    @result None.
*/

void IOBluetoothUserNotificationUnregister( IOBluetoothUserNotificationRef notificationRef );

/*!
    @function	IOBluetoothRegisterForDeviceConnectNotifications
	@abstract	Allows a client to register for device connect notifications for any connection.
	@discussion	The given callback will be called whenever any device connection is made.
	@param		callback	The callback to be called when a new connection is made
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding device connect notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRegisterForDeviceConnectNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                    void * inRefCon );

/*!
    @function	IOBluetoothDeviceRegisterForDisconnectNotification
	@abstract	Allows a client to register for device disconnect notification.
	@discussion	The given callback will be called when the target device's connection is closed..
	@param		callback	The callback to be called when the target's connection is destroyed
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding device disconnect notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothDeviceRegisterForDisconnectNotification(	IOBluetoothDeviceRef inDevice,
                                                                                    IOBluetoothUserNotificationCallback callback,
                                                                                    void * inRefCon );

/*!
    @function	IOBluetoothRegisterForL2CAPChannelOpenNotifications
	@abstract	Allows a client to register for L2CAP channel open notifications for any L2CAP channel.
	@discussion	The given callback will be called whenever any L2CAP channel is opened.
	@param		callback	The callback to be called when a new L2CAP channel is opened.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding L2CAP channel notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRegisterForL2CAPChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                    void *inRefCon );

/*!
    @function	IOBluetoothRegisterForFilteredL2CAPChannelOpenNotifications
	@abstract	Allows a client to register for L2CAP channel open notifications for certain types of
				L2CAP channels.
	@discussion	The given callback will be called whenever any L2CAP channel is opened.
	@param		callback	The callback to be called when a new L2CAP channel is opened.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@param		psm			PSM to match a new L2CAP channel.  If the PSM doesn't matter, 0 may be passed in.
	@param		inDirection	The desired direction of the L2CAP channel - kIOBluetoothUserNotificationChannelDirectionAny
				if the direction doesn't matter.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding L2CAP channel notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRegisterForFilteredL2CAPChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                            void * inRefCon,
                                                                                            BluetoothL2CAPPSM inPSM,
                                                                                            IOBluetoothUserNotificationChannelDirection inDirection );

/*!
    @function	IOBluetoothL2CAPChannelRegisterForChannelCloseNotification
	@abstract	Allows a client to register for a channel close notification.
    @discussion	The given callback will be called when the L2CAP channel is closed.
	@param		channel		The target L2CAP channel
	@param		callback	Callback to be called when the L2CAP channel is closed.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding L2CAP channel close notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothL2CAPChannelRegisterForChannelCloseNotification(	IOBluetoothL2CAPChannelRef channel,
                                                                                            IOBluetoothUserNotificationCallback callback,
                                                                                            void *inRefCon );

/*!
    @function	IOBluetoothRegisterForRFCOMMChannelOpenNotifications
	@abstract	Allows a client to register for RFCOMM channel open notifications for any RFCOMM channel.
	@discussion	The given callback will be called whenever any RFCOMM channel is opened.
	@param		callback	The callback to be called when a new RFCOMM channel is opened.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding RFCOMM channel notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRegisterForRFCOMMChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                        void * inRefCon );

/*!
    @function	IOBluetoothRegisterForFilteredRFCOMMChannelOpenNotifications
	@abstract	Allows a client to register for RFCOMM channel open notifications for certain types of
				RFCOMM channels.
	@discussion	The given callback will be called whenever any RFCOMM channel is opened.
	@param		callback	The callback to be called when a new RFCOMM channel is opened.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@param		channeLID	RFCOMM channel ID to match a new RFCOMM channel.  If the channel ID doesn't matter, 0 may be passed in.
	@param		inDirection	The desired direction of the RFCOMM channel - kIOBluetoothUserNotificationChannelDirectionAny
				if the direction doesn't matter.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding RFCOMM channel notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRegisterForFilteredRFCOMMChannelOpenNotifications(	IOBluetoothUserNotificationCallback callback,
                                                                                                void * inRefCon,
                                                                                                BluetoothRFCOMMChannelID channelID,
                                                                                                IOBluetoothUserNotificationChannelDirection inDirection );

/*!
    @function	IOBluetoothRFCOMMChannelRegisterForChannelCloseNotification
	@abstract	Allows a client to register for a channel close notification.
    @discussion	The given callback will be called when the RFCOMM channel is closed.
	@param		channel		The target RFCOMM channel
	@param		callback	Callback to be called when the RFCOMM channel is closed.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns an IOBluetoothUserNotificationRef representing the outstanding RFCOMM channel close notification.
				To unregister the notification, call IOBluetoothUserNotificationUnregister() with the returned
				IOBluetoothUserNotificationRef.  If an error is encountered creating the notification, NULL is returned.  
				The returned IOBluetoothUserNotificationRef will be valid for as long as the notification is registered.
				It is not necessary to retain the result.  Once the notification is unregistered, it will no longer
				be valid.
*/

IOBluetoothUserNotificationRef IOBluetoothRFCOMMChannelRegisterForChannelCloseNotification(	IOBluetoothRFCOMMChannelRef inChannel,
                                                                                            IOBluetoothUserNotificationCallback callback,
                                                                                            void * inRefCon );

#if 0
#pragma mark -
#pragma mark === Device Inquiry ===
#endif

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @typedef	IOBluetoothDeviceInquiryRef
	@abstract	An opaque object, representing an Inquiry that can be used to get all devices in range of this computer.	
	@discussion See individual functions for information on usage. Of note: this API is non-functional in OS versions prior
				to 10.4.3, even though (most) of the API was introduced in 10.4. We strongly recommend using the Objective C
				API if possible.
*/

typedef struct OpaqueIOBluetoothDeviceInquiryRef *			IOBluetoothDeviceInquiryRef;

/*!
    @typedef	IOBluetoothDeviceInquiryStartedCallback
    @abstract	Callback function definition for inquiry messages.
    @discussion	This callback will be invoked when the message for which it was registered is sent.
    @param		inquiryRef		(IOBluetoothDeviceInquiryRef) The inquiry object ref responsible for sending the callback.
    @param		userRefCon		(void *) This user defined parameter was provided during the original call to register the callback.
    @result		None.
*/

typedef void (*IOBluetoothDeviceInquiryStartedCallback)( 	void * 							userRefCon,
															IOBluetoothDeviceInquiryRef		inquiryRef	);

/*!
    @typedef	IOBluetoothDeviceInquiryDeviceFoundCallback
    @abstract	Callback function definition for inquiry messages.
    @discussion	This callback will be invoked when the message for which it was registered is sent.
    @param		inquiryRef		(IOBluetoothDeviceInquiryRef) The inquiry object ref responsible for sending the callback.
    @param		userRefCon		(void *) This user defined parameter was provided during the original call to register the callback.
    @result		None.
*/

typedef void (*IOBluetoothDeviceInquiryDeviceFoundCallback)( 	void * 						userRefCon,
																IOBluetoothDeviceInquiryRef	inquiryRef,
																IOBluetoothDeviceRef 		deviceRef );

/*!
    @typedef	IOBluetoothDeviceInquiryUpdatingNamesStartedCallback
    @abstract	Callback function definition for inquiry messages.
    @discussion	This callback will be invoked when the message for which it was registered is sent.
    @param		inquiryRef			(IOBluetoothDeviceInquiryRef) The inquiry object ref responsible for sending the callback.
    @param		userRefCon			(void *) This user defined parameter was provided during the original call to register the callback.
    @param		devicesRemaining	Number of devices remaining to be updated.
    @result		None.
*/

typedef void (*IOBluetoothDeviceInquiryUpdatingNamesStartedCallback)(	void * 						userRefCon,
																		IOBluetoothDeviceInquiryRef	inquiryRef,
																		uint32_t					devicesRemaining );

/*!
    @typedef	IOBluetoothDeviceInquiryDeviceNameUpdatedCallback
    @abstract	Callback function definition for inquiry messages.
    @discussion	This callback will be invoked when the message for which it was registered is sent.
    @param		inquiryRef			(IOBluetoothDeviceInquiryRef) The inquiry object ref responsible for sending the callback.
    @param		userRefCon			(void *) This user defined parameter was provided during the original call to register the callback.
    @param		deviceRemaining		Number of devices remaining to be updated.
    @result		None.
*/

typedef void (*IOBluetoothDeviceInquiryDeviceNameUpdatedCallback)( 	void * 						userRefCon,
																	IOBluetoothDeviceInquiryRef	inquiryRef,
																	IOBluetoothDeviceRef 		deviceRef,
																	uint32_t					devicesRemaining );
	
/*!
    @typedef	IOBluetoothDeviceInquiryCompleteCallback
    @abstract	Callback function definition for inquiry messages.
    @discussion	This callback will be invoked when the message for which it was registered is sent.
    @param		inquiryRef	(IOBluetoothDeviceInquiryRef) The inquiry object ref responsible for sending the callback.
    @param		userRefCon	(void *) This user defined parameter was provided during the original call to register the callback.
    @param		error		(IOReturn) kIOReturnSuccess if inquiry completed without event. Otherwise, an error code.
    @param		aborted		1 if user called -stop on the inquiry.
    @result		None.
*/

typedef void (*IOBluetoothDeviceInquiryCompleteCallback)( 	void * 						userRefCon,
															IOBluetoothDeviceInquiryRef	inquiryRef,
															IOReturn					error,
															Boolean						aborted );

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquiryCreateWithCallbackRefCon
	@abstract	Returns a new inquiry object.
	@param		inUserRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns whether the inquiry was successfully created.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOBluetoothDeviceInquiryRef IOBluetoothDeviceInquiryCreateWithCallbackRefCon( void *		inUserRefCon )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquiryDelete
	@abstract	Frees the IOBluetoothDeviceInquiryRef. You do not need to do anything further with the inquiry after this.
	@param		inRefCon	Client-supplied refCon to be passed to the callback.
	@result		Returns whether the inquiry was successfully deleted.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn		IOBluetoothDeviceInquiryDelete( IOBluetoothDeviceInquiryRef inquiryRef )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquiryStart
	@abstract	Starts the inquiry using the IOBluetoothDeviceInquiryRef.
	@result		Returns whether the inquiry was started with or without error.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn		IOBluetoothDeviceInquiryStart( IOBluetoothDeviceInquiryRef inInquiryRef )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquiryStop
	@abstract	Stops the inquiry using the IOBluetoothDeviceInquiryRef.
	@result		Returns whether the inquiry was stopped with or without error.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern	IOReturn	IOBluetoothDeviceInquiryStop( IOBluetoothDeviceInquiryRef inInquiryRef )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquirySetStartedCallback
	@abstract	Set the function callback that is invoked when the inquiry is started.
	@param		callback	Function ptr that conforms to IOBluetoothDeviceInquiryStartedCallback.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn 	IOBluetoothDeviceInquirySetStartedCallback(	IOBluetoothDeviceInquiryRef				inInquiryRef,
																IOBluetoothDeviceInquiryStartedCallback	callback )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquirySetDeviceFoundCallback
	@abstract	Set the function callback that is invoked when the inquiry finds a new device.
	@param		callback	Function ptr that conforms to IOBluetoothDeviceInquiryDeviceFoundCallback.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn 	IOBluetoothDeviceInquirySetDeviceFoundCallback(	IOBluetoothDeviceInquiryRef				inInquiryRef,
																	IOBluetoothDeviceInquiryDeviceFoundCallback	callback )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquirySetUpdatingNamesStartedCallback
	@abstract	Set the function callback that is invoked when the inquiry begins to update device names (using remote name requests).
	@param		callback	Function ptr that conforms to IOBluetoothDeviceInquiryUpdatingNamesStartedCallback.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn 	IOBluetoothDeviceInquirySetUpdatingNamesStartedCallback(	IOBluetoothDeviceInquiryRef								inInquiryRef,
																				IOBluetoothDeviceInquiryUpdatingNamesStartedCallback	callback )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquirySetDeviceNameUpdatedCallback
	@abstract	Set the function callback that is invoked when the inquiry updates a device name.
	@param		callback	Function ptr that conforms to IOBluetoothDeviceInquiryDeviceNameUpdatedCallback.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn 	IOBluetoothDeviceInquirySetDeviceNameUpdatedCallback(	IOBluetoothDeviceInquiryRef								inInquiryRef,
																			IOBluetoothDeviceInquiryDeviceNameUpdatedCallback		callback )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquirySetCompleteCallback
	@abstract	Set the function callback that is invoked when the inquiry is complete.
	@param		callback	Function ptr that conforms to IOBluetoothDeviceInquiryCompleteCallback.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn 	IOBluetoothDeviceInquirySetCompleteCallback(	IOBluetoothDeviceInquiryRef					inInquiryRef,
																	IOBluetoothDeviceInquiryCompleteCallback	callback )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquirySetUserRefCon
	@abstract	Set the user reference constant that is provided to the callbacks when they are called.
	@param		void *	A ptr to an object.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn 	IOBluetoothDeviceInquirySetUserRefCon(	IOBluetoothDeviceInquiryRef	inInquiryRef,
															void * 						inUserRefCon )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquiryGetUserRefCon
	@abstract	Get the user reference constant.
	@result		void *	A ptr to an object that was previously supplied with IOBluetoothDeviceInquirySetUserRefCon.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern void  *	IOBluetoothDeviceInquiryGetUserRefCon(	IOBluetoothDeviceInquiryRef	inInquiryRef )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquirySetInquiryLength
	@abstract   Set the length of the inquiry that is performed each time -start is used on an inquiry object. 
	@param		inSeconds		Number of seconds the inquiry will search for in-range devices before refreshing device names, if specified.
	@result		Number of seconds the search will be performed.
	@discussion A default of 10 seconds is used, unless a different value is specifed using this method.  Note that if you
				have called -start again too quickly, your inquiry may actually take much longer than what length you
				specify, as inquiries are throttled in the system.
				
				Also note that this length value is only the amount of time the hardware spends "discovering" devices. The
				total inquiry might take longer, however, if it is also updating device names.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn 	IOBluetoothDeviceInquirySetInquiryLength(	IOBluetoothDeviceInquiryRef	inInquiryRef,
																int8_t						inSeconds )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquiryGetInquiryLength
	@abstract   Returns the number of seconds the search will be performed.
	@result		Number of seconds the search will be performed.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern uint8_t IOBluetoothDeviceInquiryGetInquiryLength( 	IOBluetoothDeviceInquiryRef	inInquiryRef )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquirySetUpdateNewDeviceNames
	@abstract   Sets whether or not the inquiry object will retrieve the names of devices found during the search.
	@param		inUpdateNames		Pass TRUE if names are to be updated, otherwise pass FALSE.
	@discussion The default value for the inquiry object is TRUE, unless this method is used to change it.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern IOReturn 	IOBluetoothDeviceInquirySetUpdateNewDeviceNames( 	IOBluetoothDeviceInquiryRef	inInquiryRef,
																		Boolean						inUpdateNames )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!
    @function	IOBluetoothDeviceInquirySetUpdateNewDeviceNames
	@abstract	Returns whether or the inquiry object will perform remote name requests on found devices. 
	@result		TRUE if the inquiry will get device name for found objects, FALSE if not.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern Boolean 	IOBluetoothDeviceInquiryGetUpdateNewDeviceNames( 	IOBluetoothDeviceInquiryRef	inInquiryRef )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothDeviceInquiryGetFoundDevices
	@abstract   Returns found IOBluetoothDeviceRef objects as an array.
	@result		Returns an CFArrayRef of IOBluetoothDeviceRef objects.
	@discussion Will not return nil. If there are no devices found, returns an array with length of 0.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern	CFArrayRef	IOBluetoothDeviceInquiryGetFoundDevices( 	IOBluetoothDeviceInquiryRef	inInquiryRef )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothDeviceInquiryClearFoundDevices
	@abstract   Removes all found devices from the inquiry object.
	@discussion	
				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern	IOReturn	IOBluetoothDeviceInquiryClearFoundDevices( 	IOBluetoothDeviceInquiryRef	inInquiryRef )	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;

//---------------------------------------------------------------------------------------------------------------------------
/*!	@function	IOBluetoothDeviceInquirySetSearchCriteria
	@abstract   Use this method to set the criteria for the device search.
	@param		inServiceClassMajor		Set the major service class for found devices. Set to kBluetoothServiceClassMajorAny for all devices. See BluetoothAssignedNumbers.h for possible values.
	@param		inMajorDeviceClass		Set the major device class for found devices. Set to kBluetoothDeviceClassMajorAny for all devices. See BluetoothAssignedNumbers.h for possible values.
	@param		inMinorDeviceClass		Set the minor device class for found devices. Set to kBluetoothDeviceClassMinorAny for all devices. See BluetoothAssignedNumbers.h for possible values.
	@discussion The default inquiry object qill search for all types of devices. If you wish to find only keyboards, for example, you might use this method like this:
	
				IOBluetoothDeviceInquirySetSearchCriteria(	myInquiryObjectRef,
														kBluetoothServiceClassMajorAny
														kBluetoothDeviceClassMajorPeripheral
														kBluetoothDeviceClassMinorPeripheral1Keyboard );
										
				However, we recommend only using this if you are certain of the device class you are looking for, as some
				devices may report a different/unexpected device class, and the search may miss the device you are interested in.

				***		DEPRECATED IN BLUETOOTH 2.2 (Mac OS X 10.6)
				***		You should transition your code to Objective-C equivalents.
				***		This API may be removed any time in the future.
*/

extern	IOReturn	IOBluetoothDeviceInquirySetSearchCriteria(	IOBluetoothDeviceInquiryRef		inInquiryRef,
																BluetoothServiceClassMajor		inServiceClassMajor,
																BluetoothDeviceClassMajor		inMajorDeviceClass,
																BluetoothDeviceClassMinor		inMinorDeviceClass	)	AVAILABLE_BLUETOOTH_VERSION_1_6_3_AND_LATER	DEPRECATED_IN_BLUETOOTH_VERSION_2_2_AND_LATER;


#if 0
#pragma mark -
#pragma mark === SCO Audio ===
#endif

/*!
    @function	IOBluetoothAddSCOAudioDevice
    @abstract   Creates a persistent audio driver that will route audio data to/from the specified device.
    @discussion Teh Bluetooth device must be paired before it can be added.
				The Bluetooth hardware must also support SCO connections for devices to be added.
 
				When a client attempts to use the audio driver, it will automatically open the baseband connection
				and the SCO connection if necessary.  Once they are open, it will route audio data to/from the
				audio system.  The audio driver will continue to exist (even through reboots) until IOBluetoothRemoveAudioDevice
				is called.

				Currently, the only recognized entry in the configDict is "IOAudioControls".  That entry will be an NSArray of 
				NSDictionary objects where each dictionary represents a single audio control.  Following is a description of the mandatory
				and optional entries in each control dictionary.

				Mandatory entries:

					kIOAudioControlTypeKey			= Four-char-code representing the control type (see IOAudioTypes.h)
														Possible values:
															kIOAudioControlTypeLevel
															kIOAudioControlTypeToggle
															kIOAudioControlTypeSelector
					kIOAudioControlSubTypeKey		= Four-char-code representing the control subtype.  The value is dependent on the control type.
													  Following are common subtypes for each control type:
														kIOAudioControlTypeLevel:
															kIOAudioLevelControlSubTypeVolume
														kIOAudioControlTypeToggle:
															kIOAudioToggleControlSubTypeMute
														kIOAudioControlTypeSelector:
															kIOAudioSelectorControlSubTypeOutput
															kIOAudioSelectorControlSubTypeInput
					kIOAudioControlUsageKey			= Four-char-code representing the usage of the control (i.e. what part of the I/O chain the control 
													  affects - input, output, pass-thru, ...) (see IOAudioTypes.h)
														Possible values:
															kIOAudioControlUsageOutput
															kIOAudioControlUsageInput
															kIOAudioControlUsagePassThru
					kIOAudioControlChannelIDKey		= channel ID for the channel(s) the control acts on (see IOAudioControl.h and IOAudioTypes.h for more info)
					kIOAudioControlChannelNameKey	= name for the channel (see IOAudioControl.h and IOAudioDefines.h for more info)
					kIOAudioControlValueKey			= Initial value of the control - as an NSNumber

				Optional entries:
					kIOAudioControlIDKey			= Optional developer-defined ID field used to uniquely identify each control.

				Level control-specific entries (see IOAudioDefines.h)
					kIOAudioLevelControlMinValueKey	= Min value for the range for the level control
					kIOAudioLevelControlMaxValueKey	= Max value for the range for the level control
					kIOAudioLevelControlMinDBKey	= Min value in db for the range for the level control.  Value is a fixed-point 16.16 number
													  represented as an integer in an NSNumber.
					kIOAudioLevelControlMaxDBKey	= Max value in db for the range for the level control.  Value is a fixed-point 16.16 number
													  represented as an integer in an NSNumber.
				
				For a more detailed description of these attributes and how IOAudioControls work, see the headerdoc for IOAudioControl, IOAudioLevelControl,
				IOAudioToggleControl and IOAudioSelectorControl in the Kernel.framework.
	@param		device	A paired Bluetooth audio device
	@param		configDict	Configuration dictionary containing a description of the audio controls to be attached to the driver.  Passing NULL will result in default controls
	@result		Returns kIOReturnSuccess if the audio driver was successfully created, error if hardware does not support SCO or device is not paired.
*/
extern IOReturn IOBluetoothAddSCOAudioDevice( IOBluetoothDeviceRef device, CFDictionaryRef configDict )	AVAILABLE_BLUETOOTH_VERSION_1_6_AND_LATER;

/*!
    @function	IOBluetoothRemoveSCOAudioDevice
    @abstract   Removes a persistent audio driver for a device that had already been added using IOBluetoothAddAudioDevice().
	@param		device	Bluetooth audio device to remove
	@result		Returns kIOReturnSuccess if the audio driver was successfully removed.
*/
extern IOReturn IOBluetoothRemoveSCOAudioDevice( IOBluetoothDeviceRef device )	AVAILABLE_BLUETOOTH_VERSION_1_6_AND_LATER;


#ifdef	__cplusplus
	}
#endif

