/*
	File:		QTTrack.h

	Copyright:	(c)2004-2010 by Apple Inc., all rights reserved.

*/
/*!
    @class			QTTrack

    @abstract		A QTTrack object is an object that represents the ordering and other characteristics 
					of media data in a QTMovie object, such as a single video track or audio track.
 
	@discussion		A QTMovie object typically contains one or more streams of media data, which are represented by
					QTTrack objects. When a QTMovie object has been initialized with QTMovieOpenForPlaybackAttribute set to NO,
					a QTTrack object wraps the underlying QuickTime track (of type Track).
 
					A QTMovie object may have several QTTrack objects associated with it. By constrast, a QTTrack object has
					exactly one QTMedia object associated with it.
*/

#import <Foundation/Foundation.h>
#if !__LP64__
	#import <QuickTime/QuickTime.h>
#endif
#import <QTKit/QTKitDefines.h>
#import <QTKit/QTTime.h>
#import <QTKit/QTTimeRange.h>

@class QTMovie;
@class QTMedia;
@class NSImage;
@class QTTrackHelper;
@class QTInvalidationSet;

	// track attributes
/*!
	@constant		QTTrackBoundsAttribute
	@abstract		The bounding rectangle of a QTTrack object; the value for this key is of type NSValue, interpreted as an NSRect.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackBoundsAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSValue (NSRect)

/*!
	@constant		QTTrackCreationTimeAttribute
	@abstract		The creation time of a QTTrack object; the value for this key is of type NSDate.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackCreationTimeAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSDate

/*!
	@constant		QTTrackDimensionsAttribute
	@abstract		The dimensions of a QTTrack object; the value for this key is of type NSValue, interpreted as an NSSize.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackDimensionsAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSValue (NSSize)

/*!
	@constant		QTTrackDisplayNameAttribute
	@abstract		The display name of a QTTrack object; the value for this key is of type NSString.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackDisplayNameAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSString

/*!
	@constant		QTTrackEnabledAttribute
	@abstract		Whether a QTTrack object is enabled; the value for this key is of type NSNumber, interpreted as a BOOL.
	@discussion		This attribute can be read and written.
					This attribute can be read and written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackEnabledAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSNumber (BOOL)

/*!
	@constant		QTTrackFormatSummaryAttribute
	@abstract		A localized, human-readable string that summarizes a QTTrack object�s format; for example, �16-bit Integer (Big Endian), Stereo (L R), 48.000 kHz�.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackFormatSummaryAttribute					AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;      // NSString

/*!
	@constant		QTTrackIsChapterTrackAttribute
	@abstract		Whether a QTTrack object is a chapter track for some other QTTrack object; the value for this key is of type NSNumber, interpreted as a BOOL.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackIsChapterTrackAttribute				AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;      // NSNumber (BOOL)

/*!
	@constant		QTTrackHasApertureModeDimensionsAttribute
	@abstract		Whether aperture mode dimensions have been set on a QTTrack object; the value for this key is of type NSNumber, interpreted as a BOOL.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackHasApertureModeDimensionsAttribute		AVAILABLE_QTKIT_VERSION_7_2_AND_LATER;      // NSNumber (BOOL)

/*!
	@constant		QTTrackIDAttribute
	@abstract		The track ID of a QTTrack object; the value for this key is of type NSNumber, interpreted as a long.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackIDAttribute							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSNumber (long)

/*!
	@constant		QTTrackLayerAttribute
	@abstract		The track layer of a QTTrack object; the value for this key is of type NSNumber, interpreted as a short.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackLayerAttribute							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSNumber (short)

/*!
	@constant		QTTrackMediaTypeAttribute
	@abstract		The media type of a QTTrack object; the value for this key is of type NSString.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackMediaTypeAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSString

/*!
	@constant		QTTrackModificationTimeAttribute
	@abstract		The modification time of a QTTrack object; the value for this key is of type NSDate.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackModificationTimeAttribute				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSDate

/*!
	@constant		QTTrackRangeAttribute
	@abstract		The range of time occupied by a QTTrack object; the value for this key is of type NSValue, interpreted as a QTTimeRange.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackRangeAttribute							AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSValue (QTTimeRange)

/*!
	@constant		QTTrackTimeScaleAttribute
	@abstract		The time scale of a QTTrack object; the value for this key is of type NSNumber, interpreted as a long.
	@discussion		This attribute can be read but not written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackTimeScaleAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSNumber (long)

/*!
	@constant		QTTrackUsageInMovieAttribute
	@abstract		Whether a QTTrack object contributes data to the movie; the value for this key is of type NSNumber, interpreted as a BOOL.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackUsageInMovieAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSNumber (BOOL)

/*!
	@constant		QTTrackUsageInPosterAttribute
	@abstract		Whether a QTTrack object contributes data to the movie poster; the value for this key is of type NSNumber, interpreted as a BOOL.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackUsageInPosterAttribute					AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSNumber (BOOL)

/*!
	@constant		QTTrackUsageInPreviewAttribute
	@abstract		Whether a QTTrack object contributes data to the movie preview; the value for this key is of type NSNumber, interpreted as a BOOL.
	@discussion		This attribute can be read and written.
					This attribute can be read but not written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackUsageInPreviewAttribute				AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSNumber (BOOL)

/*!
	@constant		QTTrackVolumeAttribute
	@abstract		The volume of a QTTrack object; the value for this key is of type NSNumber, interpreted as a float.
	@discussion		This attribute can be read and written.
					This attribute can be read and written when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
 */
QTKIT_EXTERN NSString * const QTTrackVolumeAttribute						AVAILABLE_QTKIT_VERSION_7_0_AND_LATER;      // NSNumber (float)

@interface QTTrack : NSObject
{
@private
	long				_flags;
	QTTrackHelper		*_trackHelper;
	QTMovie				*_movie;
	QTInvalidationSet	*_children;
	int32_t				_cachedTrackID;
	long				_reserved1;
	long				_reserved2;
	long				_reserved3;
	long				_reserved4;
}

#if !__LP64__
	// class/init methods
/*!
	@method			trackWithQuickTimeTrack:error:
	@abstract		Returns a QTTrack object associated with a QuickTime Track.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					In addition, this method cannot be called by 64-bit applications.
	@param			track
					A QuickTime Track with which to initialize the QTTrack object.
	@param			errorPtr
					A pointer to an NSError object; if a QTTrack object cannot be created, an NSError object is returned in this location.
*/
+ (id)trackWithQuickTimeTrack:(Track)track error:(NSError **)errorPtr;

/*!
	@method			initWithQuickTimeTrack:error:
	@abstract		Returns a QTTrack object associated with a QuickTime Track.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					In addition, this method cannot be called by 64-bit applications.
	@param			track
					A QuickTime Track with which to initialize the QTTrack object.
	@param			errorPtr
					A pointer to an NSError object; if a QTTrack object cannot be created, an NSError object is returned in this location.
*/
- (id)initWithQuickTimeTrack:(Track)track error:(NSError **)errorPtr;
#endif

	// parent/child
/*!
	@method			movie
	@abstract		Returns the QTMovie object associated with a QTTrack object.
	@discussion		This method can be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (QTMovie *)movie;

/*!
	@method			media
	@abstract		Returns the QTMedia object associated with a QTTrack object.
	@discussion		This method can be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (QTMedia *)media;

	// attributes
/*!
	@method			isEnabled
	@abstract		Returns YES if the QTTrack object is currently enabled, NO otherwise.
	@discussion		This method can be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (BOOL)isEnabled;

/*!
	@method			setEnabled:
	@abstract		Sets the enabled state of a QTTrack object.
	@discussion		This method can be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			enabled
					The desired track enabled state.
*/
- (void)setEnabled:(BOOL)enabled;

/*!
	@method			volume
	@abstract		Returns the current volume of a QTTrack object.
	@discussion		This method can be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (float)volume;

/*!
	@method			setVolume:
	@abstract		Sets the volume of a QTTrack object.
	@discussion		This method can be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			volume
					The desired track volume.
*/
- (void)setVolume:(float)volume;

/*!
	@method			trackAttributes
	@abstract		Returns a dictionary containing the current values of all public attributes of a QTTrack object.
	@discussion		This method can be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (NSDictionary *)trackAttributes;

/*!
	@method			setTrackAttributes:
	@abstract		Sets the attributes of a QTTrack object using the key-value pairs in a specified dictionary.
	@discussion		This method can be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					However, certain attributes may not be writable when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			attributes
					An NSDictionary object that specifies the attributes to set and their desired values.
*/
- (void)setTrackAttributes:(NSDictionary *)attributes;

/*!
	@method			attributeForKey:
	@abstract		Returns the current value of an attribute of a QTTrack object.
	@discussion		This method can be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			attributeKey
					An NSString object that specifies the attribute to be read; pass strings like QTTrackTimeScaleAttribute or QTTrackVolumeAttribute.
	@result			An NSObject that is the value of the specified attribute key.
*/
- (id)attributeForKey:(NSString *)attributeKey;

/*!
	@method			setAttribute:forKey:
	@abstract		Sets an attribute of a QTTrack object to a specified value.
	@discussion		This method can be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					However, certain attributes may not be writable when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			value
					An object that specifies the value of the attribute to be written.
	@param			attributeKey
					An NSString object that specifies the attribute to be written; pass strings like QTTrackTimeScaleAttribute or QTTrackVolumeAttribute.
*/
- (void)setAttribute:(id)value forKey:(NSString *)attributeKey;

#if !__LP64__
	// underlying QT object
/*!
	@method			quickTimeTrack
	@abstract		Returns the QuickTime Track associated with a QTTrack object.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					In addition, this method cannot be called by 64-bit applications.
*/
- (Track)quickTimeTrack;
#endif

	// track-level editing
/*!
	@method			insertSegmentOfTrack:timeRange:atTime:
	@abstract		Inserts into a QTTrack object the specified segment of another QTTrack object.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie containing this track is not editable, an exception will be raised.
	@param			track
					The QTTrack object from which the segment to be inserted is copied.
	@param			range
					A QTTimeRange structure that indicates the segment in track to be copied.
	@param			time
					A QTTime structure that indicates the time in the target track at which the copied segment is to be inserted.
*/
- (void)insertSegmentOfTrack:(QTTrack *)track timeRange:(QTTimeRange)range atTime:(QTTime)time;

/*!
	@method			insertSegmentOfTrack:fromRange:scaledToRange:
	@abstract		Inserts into a QTTrack object the specified segment of another QTTrack object, scaling that new segment to a specified start time and duration.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie containing this track is not editable, an exception will be raised.
	@param			track
					The QTTrack object from which the segment to be inserted is copied.
	@param			srcRange
					A QTTimeRange structure that indicates the segment in track to be copied.
	@param			dstRange
					A QTTimeRange structure that indicates the range in the target track into which the copied segment is to be inserted.
*/
- (void)insertSegmentOfTrack:(QTTrack *)track fromRange:(QTTimeRange)srcRange scaledToRange:(QTTimeRange)dstRange;

/*!
	@method			insertEmptySegmentAt:
	@abstract		Inserts an empty segment into a QTTrack object.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie containing this track is not editable, an exception will be raised.
	@param			range
					A QTTimeRange structure that indicates the segment in the target track at which an empty segment is to be inserted.
*/
- (void)insertEmptySegmentAt:(QTTimeRange)range;

/*!
	@method			deleteSegment:
	@abstract		Deletes a specified segment from a QTTrack object.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie containing this track is not editable, an exception will be raised.
	@param			segment
					A QTTimeRange structure that indicates the segment in the target track that is to be deleted.
*/
- (void)deleteSegment:(QTTimeRange)segment;

/*!
	@method			scaleSegment:newDuration:
	@abstract		Scales a segment of a QTTrack object to a new duration.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
					If the movie containing this track is not editable, an exception will be raised.
	@param			segment
					A QTTimeRange structure that indicates the segment in the target track that is to be scaled.
	@param			newDuration
					A QTTime structure that indicates the desired duration of the segment that is to be scaled.
*/
- (void)scaleSegment:(QTTimeRange)segment newDuration:(QTTime)newDuration;

/*!
	@method			addImage:forDuration:withAttributes:
	@abstract		Adds an image to a QTTrack object for the specified duration, using attributes specified in the attributes dictionary.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			image
					An NSImage that is to be appended to the target track.
	@param			duration
					A QTTime structure that indicates the desired duration of the appended image in the track.
	@param			attributes
					An NSDictionary object that specifies attributes of the appended image.
					Keys in this dictionary can be QTAddImageCodecType to select a codec type and QTAddImageCodecQuality to select a quality.
					Qualities are expected to be specified as NSNumbers, using the codec values like codecNormalQuality.
					(See ImageCompression.h for the complete list.)
*/
- (void)addImage:(NSImage *)image forDuration:(QTTime)duration withAttributes:(NSDictionary *)attributes;

@end

@interface QTTrack (QTTrack_VisualSupport)

#if QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2
/*!
	@method			apertureModeDimensionsForMode:
	@abstract		Returns an NSSize value that indicates the dimensions of a QTTrack object for the specified aperture mode.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			mode
					An NSString object that indicates the aperture mode whose dimensions are to be returned; pass values like QTMovieApertureModeClean.
*/
- (NSSize)apertureModeDimensionsForMode:(NSString *)mode;

/*!
	@method			setApertureModeDimensions:forMode:
	@abstract		Sets the aperture mode dimensions of a QTTrack object for the specified aperture mode.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
	@param			dimensions
					An NSSize structure that indicates the desired dimensions for the specified aperture mode.
	@param			mode
					An NSString object that indicates the aperture mode whose dimensions are to be set; pass values like QTMovieApertureModeClean.
*/
- (void)setApertureModeDimensions:(NSSize)dimensions forMode:(NSString *)mode;

/*!
	@method			generateApertureModeDimensions
	@abstract		Adds aperture mode dimensions information to a QTTrack object.
	@discussion		This method adds information to a QTTrack object needed to support aperture modes for movie created with
					applications and/or versions of QuickTime that did not support aperture mode dimensions.
					This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)generateApertureModeDimensions;

/*!
	@method			removeApertureModeDimensions
	@abstract		Removes aperture mode dimensions information from a QTTrack object.
	@discussion		This method cannot be called when the movie containing this track has been initialized with QTMovieOpenForPlaybackAttribute set to YES.
*/
- (void)removeApertureModeDimensions;
#endif /* QTKIT_VERSION_MAX_ALLOWED >= QTKIT_VERSION_7_2 */

@end
