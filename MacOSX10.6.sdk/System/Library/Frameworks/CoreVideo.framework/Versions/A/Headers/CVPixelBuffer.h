/*
 *  CVPixelBuffer.h
 *  CoreVideo
 *
 *  Copyright (c) 2004 Apple Computer, Inc. All rights reserved.
 *
 */
 
  /*! @header CVPixelBuffer.h
	@copyright 2004 Apple Computer, Inc. All rights reserved.
	@availability Mac OS X 10.4 or later
    @discussion CVPixelBuffers are CVImageBuffers that hold the pixels in main memory
		   
*/

#if !defined(__COREVIDEO_CVPIXELBUFFER_H__)
#define __COREVIDEO_CVPIXELBUFFER_H__ 1

#include <TargetConditionals.h>

#include <CoreVideo/CVImageBuffer.h>
#include <CoreFoundation/CFArray.h>

#if COREVIDEO_SUPPORTS_IOSURFACE
#include <IOSurface/IOSurface.h>
#endif // COREVIDEO_SUPPORTS_IOSURFACE

#if defined(__cplusplus)
extern "C" {
#endif

/*
CoreVideo pixel format type constants.
CoreVideo does not provide support for all of these formats; this list just defines their names.
*/
enum {
  kCVPixelFormatType_1Monochrome    = 0x00000001, /* 1 bit indexed */
  kCVPixelFormatType_2Indexed       = 0x00000002, /* 2 bit indexed */
  kCVPixelFormatType_4Indexed       = 0x00000004, /* 4 bit indexed */
  kCVPixelFormatType_8Indexed       = 0x00000008, /* 8 bit indexed */
  kCVPixelFormatType_1IndexedGray_WhiteIsZero = 0x00000021, /* 1 bit indexed gray, white is zero */
  kCVPixelFormatType_2IndexedGray_WhiteIsZero = 0x00000022, /* 2 bit indexed gray, white is zero */
  kCVPixelFormatType_4IndexedGray_WhiteIsZero = 0x00000024, /* 4 bit indexed gray, white is zero */
  kCVPixelFormatType_8IndexedGray_WhiteIsZero = 0x00000028, /* 8 bit indexed gray, white is zero */
  kCVPixelFormatType_16BE555        = 0x00000010, /* 16 bit BE RGB 555 */
  kCVPixelFormatType_16LE555        = 'L555',     /* 16 bit LE RGB 555 */
  kCVPixelFormatType_16LE5551       = '5551',     /* 16 bit LE RGB 5551 */
  kCVPixelFormatType_16BE565        = 'B565',     /* 16 bit BE RGB 565 */
  kCVPixelFormatType_16LE565        = 'L565',     /* 16 bit LE RGB 565 */
  kCVPixelFormatType_24RGB          = 0x00000018, /* 24 bit RGB */
  kCVPixelFormatType_24BGR          = '24BG',     /* 24 bit BGR */
  kCVPixelFormatType_32ARGB         = 0x00000020, /* 32 bit ARGB */
  kCVPixelFormatType_32BGRA         = 'BGRA',     /* 32 bit BGRA */
  kCVPixelFormatType_32ABGR         = 'ABGR',     /* 32 bit ABGR */
  kCVPixelFormatType_32RGBA         = 'RGBA',     /* 32 bit RGBA */
  kCVPixelFormatType_64ARGB         = 'b64a',     /* 64 bit ARGB, 16-bit big-endian samples */
  kCVPixelFormatType_48RGB          = 'b48r',     /* 48 bit RGB, 16-bit big-endian samples */
  kCVPixelFormatType_32AlphaGray    = 'b32a',     /* 32 bit AlphaGray, 16-bit big-endian samples, black is zero */
  kCVPixelFormatType_16Gray         = 'b16g',     /* 16 bit Grayscale, 16-bit big-endian samples, black is zero */
  kCVPixelFormatType_422YpCbCr8     = '2vuy',     /* Component Y'CbCr 8-bit 4:2:2, ordered Cb Y'0 Cr Y'1 */
  kCVPixelFormatType_4444YpCbCrA8   = 'v408',     /* Component Y'CbCrA 8-bit 4:4:4:4, ordered Cb Y' Cr A */
  kCVPixelFormatType_4444YpCbCrA8R  = 'r408',     /* Component Y'CbCrA 8-bit 4:4:4:4, rendering format. full range alpha, zero biased YUV, ordered A Y' Cb Cr */
  kCVPixelFormatType_444YpCbCr8     = 'v308',     /* Component Y'CbCr 8-bit 4:4:4 */
  kCVPixelFormatType_422YpCbCr16    = 'v216',     /* Component Y'CbCr 10,12,14,16-bit 4:2:2 */
  kCVPixelFormatType_422YpCbCr10    = 'v210',     /* Component Y'CbCr 10-bit 4:2:2 */
  kCVPixelFormatType_444YpCbCr10    = 'v410',     /* Component Y'CbCr 10-bit 4:4:4 */
  kCVPixelFormatType_420YpCbCr8Planar = 'y420',   /* Planar Component Y'CbCr 8-bit 4:2:0.  baseAddr points to a big-endian CVPlanarPixelBufferInfo_YCbCrPlanar struct */
  kCVPixelFormatType_422YpCbCr_4A_8BiPlanar = 'a2vy', /* First plane: Video-range Component Y'CbCr 8-bit 4:2:2, ordered Cb Y'0 Cr Y'1; second plane: alpha 8-bit 0-255 */
};

	
/*!
	@enum Pixel Buffer Locking Flags
	@discussion Flags to pass to CVPixelBufferLockBaseAddress() / CVPixelBufferUnlockBaseAddress()
	@constant kCVPixelBufferLock_ReadOnly
		If you are not going to modify the data while you hold the lock, you should set this flag
		to avoid potentially invalidating any existing caches of the buffer contents.  This flag
		should be passed both to the lock and unlock functions.  Non-symmetrical usage of this
		flag will result in undefined behavior.
*/
enum CVPixelBufferLockFlags {
	kCVPixelBufferLock_ReadOnly = 0x00000001,
};

/*
Planar pixel buffers have the following descriptor at their base address.  
Clients should generally use CVPixelBufferGetBaseAddressOfPlane, 
CVPixelBufferGetBytesPerRowOfPlane, etc. instead of accessing it directly.
*/
struct CVPlanarComponentInfo {
  int32_t             offset;    /* offset from main base address to base address of this plane, big-endian */
  uint32_t            rowBytes;  /* bytes per row of this plane, big-endian */
};
typedef struct CVPlanarComponentInfo      CVPlanarComponentInfo;
struct CVPlanarPixelBufferInfo {
  CVPlanarComponentInfo  componentInfo[1];
};
typedef struct CVPlanarPixelBufferInfo         CVPlanarPixelBufferInfo;
struct CVPlanarPixelBufferInfo_YCbCrPlanar {
  CVPlanarComponentInfo  componentInfoY;
  CVPlanarComponentInfo  componentInfoCb;
  CVPlanarComponentInfo  componentInfoCr;
};
typedef struct CVPlanarPixelBufferInfo_YCbCrPlanar   CVPlanarPixelBufferInfo_YCbCrPlanar;

#pragma mark BufferAttributeKeys
CV_EXPORT const CFStringRef kCVPixelBufferPixelFormatTypeKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		    // A single CFNumber or a CFArray of CFNumbers (OSTypes)
CV_EXPORT const CFStringRef kCVPixelBufferMemoryAllocatorKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		    // CFAllocatorRef
CV_EXPORT const CFStringRef kCVPixelBufferWidthKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;			    // CFNumber
CV_EXPORT const CFStringRef kCVPixelBufferHeightKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;			    // CFNumber
CV_EXPORT const CFStringRef kCVPixelBufferExtendedPixelsLeftKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	    // CFNumber
CV_EXPORT const CFStringRef kCVPixelBufferExtendedPixelsTopKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;		    // CFNumber
CV_EXPORT const CFStringRef kCVPixelBufferExtendedPixelsRightKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	    // CFNumber
CV_EXPORT const CFStringRef kCVPixelBufferExtendedPixelsBottomKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	    // CFNumber
CV_EXPORT const CFStringRef kCVPixelBufferBytesPerRowAlignmentKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	    // CFNumber
CV_EXPORT const CFStringRef kCVPixelBufferCGBitmapContextCompatibilityKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;  // CFBoolean
CV_EXPORT const CFStringRef kCVPixelBufferCGImageCompatibilityKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	    // CFBoolean
CV_EXPORT const CFStringRef kCVPixelBufferOpenGLCompatibilityKey AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;	    // CFBoolean
CV_EXPORT const CFStringRef kCVPixelBufferPlaneAlignmentKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;		    // CFNumber
CV_EXPORT const CFStringRef kCVPixelBufferIOSurfacePropertiesKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;     // CFDictionary; presence requests buffer allocation via IOSurface
// Ensures that CGLTexImageIOSurface2D() will succeed in creating a valid texture object from the CVPixelBuffer's IOSurface.
CV_EXPORT const CFStringRef kCVPixelBufferIOSurfaceOpenGLTextureCompatibilityKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;	// CFBoolean
// Ensures that CGLTexImageIOSurface2D() will succeed in creating a valid texture object from the CVPixelBuffer's IOSurface AND that the resulting texture may be used as a color buffer attachment to a OpenGL frame buffer object.
CV_EXPORT const CFStringRef kCVPixelBufferIOSurfaceOpenGLFBOCompatibilityKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;	// CFBoolean
// Ensures that the CVPixelBuffer's IOSurfaceRef can be displayed in an CoreAnimation CALayer.
CV_EXPORT const CFStringRef kCVPixelBufferIOSurfaceCoreAnimationCompatibilityKey AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;	// CFBoolean


/*!
    @typedef	CVPixelBufferRef
    @abstract   Based on the image buffer type. The pixel buffer implements the memory storage for an image buffer.

*/
typedef CVImageBufferRef CVPixelBufferRef;

CV_EXPORT CFTypeID CVPixelBufferGetTypeID(void) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferRetain
    @abstract   Retains a CVPixelBuffer object
    @discussion Equivalent to CFRetain, but NULL safe
    @param      buffer A CVPixelBuffer object that you want to retain.
    @result     A CVPixelBuffer object that is the same as the passed in buffer.
*/
CV_EXPORT CVPixelBufferRef CVPixelBufferRetain( CVPixelBufferRef texture ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferRelease
    @abstract   Releases a CVPixelBuffer object
    @discussion Equivalent to CFRelease, but NULL safe
    @param      buffer A CVPixelBuffer object that you want to release.
*/
CV_EXPORT void CVPixelBufferRelease( CVPixelBufferRef texture ) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferCreateResolvedAttributesDictionary
    @abstract   Takes a CFArray of CFDictionary objects describing various pixel buffer attributes and tries to resolve them into a
                single dictionary.
    @discussion This is useful when you need to resolve multiple requirements between different potential clients of a buffer.
    @param      attributes CFArray of CFDictionaries containing kCVPixelBuffer key/value pairs.
    @param      resolvedDictionaryOut The resulting dictionary will be placed here.
    @result     Return value that may be useful in discovering why resolution failed.
*/
CV_EXPORT CVReturn CVPixelBufferCreateResolvedAttributesDictionary(CFAllocatorRef allocator, CFArrayRef attributes, CFDictionaryRef *resolvedDictionaryOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*!
    @function   CVPixelBufferCreate
    @abstract   Call to create a single PixelBuffer for a given size and pixelFormatType.
    @discussion Creates a single PixelBuffer for a given size and pixelFormatType. It allocates the necessary memory based on the pixel dimensions, pixelFormatType and extended pixels described in the pixelBufferAttributes. Not all parameters of the pixelBufferAttributes will be used here.
    @param      width   Width of the PixelBuffer in pixels.
    @param      height  Height of the PixelBuffer in pixels.
    @param	pixelFormatType		Pixel format indentified by its respective OSType.
    @param	pixelBufferAttributes      A dictionary with additional attributes for a a pixel buffer. This parameter is optional. See PixelBufferAttributes for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result	returns kCVReturnSuccess on success.
*/    
CV_EXPORT CVReturn CVPixelBufferCreate(CFAllocatorRef allocator,
                                      size_t width,
                                      size_t height,
                                      OSType pixelFormatType,
                                      CFDictionaryRef pixelBufferAttributes,
                                      CVPixelBufferRef *pixelBufferOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

typedef void (*CVPixelBufferReleaseBytesCallback)( void *releaseRefCon, const void *baseAddress );

/*!
    @function   CVPixelBufferCreateWithBytes
    @abstract   Call to create a single PixelBuffer for a given size and pixelFormatType based on a passed in piece of memory.
    @discussion Creates a single PixelBuffer for a given size and pixelFormatType. Not all parameters of the pixelBufferAttributes will be used here. It requires a release callback function that will be called, when the PixelBuffer gets destroyed so that the owner of the pixels can free the memory.
    @param      width   Width of the PixelBuffer in pixels
    @param      height  Height of the PixelBuffer in pixels
    @param      pixelFormatType		Pixel format indentified by its respective OSType.
    @param      baseAddress		Address of the memory storing the pixels.
    @param      bytesPerRow		Row bytes of the pixel storage memory.
    @param      releaseCallback         CVPixelBufferReleaseBytePointerCallback function that gets called when the PixelBuffer gets destroyed.
    @param      releaseRefCon           User data identifying the PixelBuffer for the release callback.
    @param      pixelBufferAttributes      A dictionary with additional attributes for a a pixel buffer. This parameter is optional. See PixelBufferAttributes for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result	returns kCVReturnSuccess on success.
*/
CV_EXPORT CVReturn CVPixelBufferCreateWithBytes(CFAllocatorRef allocator,
					       size_t width,
					       size_t height,
					       OSType pixelFormatType,
					       void *baseAddress,
					       size_t bytesPerRow,
					       CVPixelBufferReleaseBytesCallback releaseCallback,
					       void *releaseRefCon,
					       CFDictionaryRef pixelBufferAttributes,
				               CVPixelBufferRef *pixelBufferOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

typedef void (*CVPixelBufferReleasePlanarBytesCallback)( void *releaseRefCon, const void *dataPtr, size_t dataSize, size_t numberOfPlanes, const void *planeAddresses[] );

/*!
    @function   CVPixelBufferCreateWithPlanarBytes
    @abstract   Call to create a single PixelBuffer in planar format for a given size and pixelFormatType based on a passed in piece of memory.
    @discussion Creates a single PixelBuffer for a given size and pixelFormatType. Not all parameters of the pixelBufferAttributes will be used here. It requires a release callback function that will be called, when the PixelBuffer gets destroyed so that the owner of the pixels can free the memory.
    @param      width			Width of the PixelBuffer in pixels
    @param      height			Height of the PixelBuffer in pixels
    @param      pixelFormatType		Pixel format indentified by its respective OSType.
    @param	dataPtr			Pass a pointer to a plane descriptor block, or NULL.
    @param	dataSize		pass size if planes are contiguous, NULL if not.
    @param	numberOfPlanes		Number of planes.
    @param	planeBaseAddress	Array of base addresses for the planes.
    @param	planeWidth		Array of plane widths.
    @param	planeHeight		Array of plane heights.
    @param	planeBytesPerRow	Array of plane bytesPerRow values.
    @param	releaseCallback		CVPixelBufferReleaseBytePointerCallback function that gets called when the PixelBuffer gets destroyed.
    @param	releaseRefCon		User data identifying the PixelBuffer for the release callback.
    @param	pixelBufferAttributes      A dictionary with additional attributes for a a pixel buffer. This parameter is optional. See PixelBufferAttributes for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result	returns kCVReturnSuccess on success.
*/
CV_EXPORT CVReturn CVPixelBufferCreateWithPlanarBytes(CFAllocatorRef allocator,
							 size_t width,
							 size_t height,
							 OSType pixelFormatType,
							 void *dataPtr, // pass a pointer to a plane descriptor block, or NULL
							 size_t dataSize, // pass size if planes are contiguous, NULL if not
							 size_t numberOfPlanes,
							 void *planeBaseAddress[],
							 size_t planeWidth[],
							 size_t planeHeight[],
							 size_t planeBytesPerRow[],
							 CVPixelBufferReleasePlanarBytesCallback releaseCallback,
							 void *releaseRefCon,
							 CFDictionaryRef pixelBufferAttributes,
							 CVPixelBufferRef *pixelBufferOut) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*!
	@function   CVPixelBufferLockBaseAddress
	@abstract   Description Locks the BaseAddress of the PixelBuffer to ensure that the memory is accessible.
	@param      pixelBuffer Target PixelBuffer.
	@param      lockFlags See CVPixelBufferLockFlags.
	@result     kCVReturnSuccess if the lock succeeded, or error code on failure
*/
CV_EXPORT CVReturn CVPixelBufferLockBaseAddress(CVPixelBufferRef pixelBuffer, CVOptionFlags lockFlags) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
	@function   CVPixelBufferUnlockBaseAddress
	@abstract   Description Unlocks the BaseAddress of the PixelBuffer.
	@param      pixelBuffer Target PixelBuffer.
	@param      unlockFlags See CVPixelBufferLockFlags.
	@result     kCVReturnSuccess if the unlock succeeded, or error code on failure
*/
CV_EXPORT CVReturn CVPixelBufferUnlockBaseAddress(CVPixelBufferRef pixelBuffer, CVOptionFlags unlockFlags) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetWidth
    @abstract   Returns the width of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Width in pixels.
*/
CV_EXPORT size_t CVPixelBufferGetWidth(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetHeight
    @abstract   Returns the height of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Height in pixels.
*/
CV_EXPORT size_t CVPixelBufferGetHeight(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetPixelFormatType
    @abstract   Returns the PixelFormatType of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     OSType identifying the pixel format by its type.
*/
CV_EXPORT OSType CVPixelBufferGetPixelFormatType(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetBaseAddress
    @abstract   Returns the base address of the PixelBuffer.
    @discussion Retrieving the base address for a PixelBuffer requires that the buffer base address be locked
                via a successful call to CVPixelBufferLockBaseAddress.
    @param      pixelBuffer Target PixelBuffer.
    @result     Base address of the pixels.
		For chunky buffers, this will return a pointer to the pixel at 0,0 in the buffer
		For planar buffers this will return a pointer to a PlanarComponentInfo struct (defined in QuickTime).
*/
CV_EXPORT void *CVPixelBufferGetBaseAddress(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetBytesPerRow
    @abstract   Returns the rowBytes of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Bytes per row of the image data.   For planar buffers this will return a rowBytes value such that bytesPerRow * height
                will cover the entire image including all planes.
*/
CV_EXPORT size_t CVPixelBufferGetBytesPerRow(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetDataSize
    @abstract   Returns the data size for contigous planes of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Data size used in CVPixelBufferCreateWithPlanarBytes.
*/
CV_EXPORT size_t CVPixelBufferGetDataSize(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferIsPlanar
    @abstract   Returns if the PixelBuffer is planar.
    @param      pixelBuffer Target PixelBuffer.
    @result     True if the PixelBuffer was created using CVPixelBufferCreateWithPlanarBytes.
*/
CV_EXPORT Boolean CVPixelBufferIsPlanar(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetPlaneCount
    @abstract   Returns number of planes of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @result     Number of planes.  Returns 0 for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetPlaneCount(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetWidthOfPlane
    @abstract   Returns the width of the plane at planeIndex in the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Width in pixels, or 0 for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetWidthOfPlane(CVPixelBufferRef pixelBuffer, size_t planeIndex) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetHeightOfPlane
    @abstract   Returns the height of the plane at planeIndex in the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Height in pixels, or 0 for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetHeightOfPlane(CVPixelBufferRef pixelBuffer, size_t planeIndex) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetBaseAddressOfPlane
    @abstract   Returns the base address of the plane at planeIndex in the PixelBuffer.
    @discussion Retrieving the base address for a PixelBuffer requires that the buffer base address be locked
                via a successful call to CVPixelBufferLockBaseAddress.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Base address of the plane, or NULL for non-planar CVPixelBufferRefs.
*/
CV_EXPORT void *CVPixelBufferGetBaseAddressOfPlane(CVPixelBufferRef pixelBuffer, size_t planeIndex) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetBytesPerRowOfPlane
    @abstract   Returns the row bytes of the plane at planeIndex in the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @param      planeIndex  Identifying the plane.
    @result     Row bytes of the plane, or NULL for non-planar CVPixelBufferRefs.
*/
CV_EXPORT size_t CVPixelBufferGetBytesPerRowOfPlane(CVPixelBufferRef pixelBuffer, size_t planeIndex) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferGetExtendedPixels
    @abstract   Returns the size of extended pixels of the PixelBuffer.
    @param      pixelBuffer Target PixelBuffer.
    @param      extraColumnsOnLeft Returns the pixel row padding to the left.  May be NULL.
    @param      extraRowsOnTop Returns the pixel row padding to the top.  May be NULL. 
    @param      extraColumnsOnRight Returns the pixel row padding to the right. May be NULL.
    @param      extraRowsOnBottom Returns the pixel row padding to the bottom. May be NULL.
*/
CV_EXPORT void CVPixelBufferGetExtendedPixels(CVPixelBufferRef pixelBuffer,
					      size_t *extraColumnsOnLeft,
					      size_t *extraColumnsOnRight,
					      size_t *extraRowsOnTop,
					      size_t *extraRowsOnBottom) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*!
    @function   CVPixelBufferFillExtendedPixels
    @abstract   Fills the extended pixels of the PixelBuffer with Zero.   This function replicates edge pixels to fill the entire extended region of the image.
    @param      pixelBuffer Target PixelBuffer.
*/
CV_EXPORT CVReturn CVPixelBufferFillExtendedPixels(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

#if COREVIDEO_SUPPORTS_IOSURFACE

/*!
	@function   CVPixelBufferGetIOSurface
	@abstract   Returns the IOSurface backing the pixel buffer, or NULL if it is not backed by an IOSurface.
	@param      pixelBuffer Target PixelBuffer.
*/
CV_EXPORT IOSurfaceRef CVPixelBufferGetIOSurface(CVPixelBufferRef pixelBuffer) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/*!
    @function   CVPixelBufferCreateWithIOSurface
    @abstract   Call to create a single CVPixelBuffer for a passed-in IOSurface.
    @discussion The CVPixelBuffer will retain the IOSurface.
    	IMPORTANT NOTE: If you are using IOSurface to share CVPixelBuffers between processes
    	and those CVPixelBuffers are allocated via a CVPixelBufferPool, it is important
    	that the CVPixelBufferPool does not reuse CVPixelBuffers whose IOSurfaces are still
    	in use in other processes.  
    	CoreVideo and IOSurface will take care of this for if you use IOSurfaceCreateMachPort 
    	and IOSurfaceLookupFromMachPort, but NOT if you pass IOSurfaceIDs.
    @param      surface		            The IOSurface to wrap.
    @param      pixelBufferAttributes   A dictionary with additional attributes for a a pixel buffer. This parameter is optional. See PixelBufferAttributes for more details.
    @param      pixelBufferOut          The new pixel buffer will be returned here
    @result     returns kCVReturnSuccess on success.
*/
CV_EXPORT CVReturn CVPixelBufferCreateWithIOSurface(
		CFAllocatorRef allocator,
		IOSurfaceRef surface,
		CFDictionaryRef pixelBufferAttributes,
		CVPixelBufferRef *pixelBufferOut) AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#endif // COREVIDEO_SUPPORTS_IOSURFACE

#if defined(__cplusplus)
}
#endif

#endif
