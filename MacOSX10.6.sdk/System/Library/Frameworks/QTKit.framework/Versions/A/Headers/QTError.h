/*
	File:		QTError.h
 
	Copyright:	(c)2007-2010 by Apple Inc., all rights reserved.
 
*/

#import <Foundation/Foundation.h>
#import <QTKit/QTKitDefines.h>

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2

QTKIT_EXTERN NSString * const QTKitErrorDomain							AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;

QTKIT_EXTERN NSString * const QTErrorCaptureInputKey					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;
QTKIT_EXTERN NSString * const QTErrorCaptureOutputKey					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;
QTKIT_EXTERN NSString * const QTErrorDeviceKey							AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;
QTKIT_EXTERN NSString * const QTErrorExcludingDeviceKey					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;
QTKIT_EXTERN NSString * const QTErrorTimeKey							AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER;  // NSValue interpreted as QTTime
QTKIT_EXTERN NSString * const QTErrorFileSizeKey						AVAILABLE_QTKIT_VERSION_7_6_3_AND_LATER;  // NSNumber interpreted as file size in bytes
QTKIT_EXTERN NSString * const QTErrorRecordingSuccesfullyFinishedKey	AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;

enum {
	QTErrorUnknown                                      = -1,
	QTErrorIncompatibleInput                            = 1002,
	QTErrorIncompatibleOutput                           = 1003,
	QTErrorInvalidInputsOrOutputs                       = 1100,
	QTErrorDeviceAlreadyUsedbyAnotherSession            = 1101,
	QTErrorNoDataCaptured                               = 1200,
	QTErrorSessionConfigurationChanged                  = 1201,
	QTErrorDiskFull                                     = 1202,
	QTErrorDeviceWasDisconnected                        = 1203,
	QTErrorMediaChanged                                 = 1204,
	QTErrorMaximumDurationReached                       = 1205,
	QTErrorMaximumFileSizeReached                       = 1206,
	QTErrorMediaDiscontinuity                           = 1207,
#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3
    QTErrorMaximumNumberOfSamplesForFileFormatReached   = 1208,
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_6_3 */
	QTErrorDeviceNotConnected                           = 1300,
	QTErrorDeviceInUseByAnotherApplication              = 1301,
	QTErrorDeviceExcludedByAnotherDevice                = 1302,
};

#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */
