/*
	File:  AVCompositionTrack.h

	Framework:  AVFoundation
 
	Copyright 2010 Apple Inc. All rights reserved.

*/

#import <AVFoundation/AVBase.h>
#import <AVFoundation/AVAssetTrack.h>
#import <CoreMedia/CMTime.h>
#import <CoreMedia/CMTimeRange.h>

@class AVAsset;
@class AVComposition;

/*!
    @class			AVCompositionTrack

    @abstract		AVCompositionTrack offers the low-level representation of tracks of AVCompositions, comprising
    				a media type, a track identifier, and an array of AVCompositionTrackSegments, each comprising a URL,
    				and track identifier, and a time mapping.
*/

@class AVCompositionTrackInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVCompositionTrack : AVAssetTrack
{
@private
    AVCompositionTrackInternal    *_priv;
}

/* Provides access to the array of track segments, each an instance of AVCompositionTrackSegment.
  	Note that timeMapping.target.start of the first AVCompositionTrackSegment must be kCMTimeZero,
  	and the timeMapping.target.start of each subsequent AVCompositionTrackSegment must equal
  	CMTimeRangeGetEnd(the previous AVCompositionTrackSegment's timeMapping.target).
  	-validateTrackSegments:error: will perform a test to ensure that an array of AVCompositionTrackSegments
  	conforms to this rule.
*/
@property (nonatomic, readonly, copy) NSArray *segments;

@end


/*!
    @class			AVMutableCompositionTrack

    @abstract		AVMutableCompositionTrack provides a convenient interface for insertions, removals, and scaling
    				of track segments without direct manipulation of their low-level representation.
 */

@class AVMutableCompositionTrackInternal;

NS_CLASS_AVAILABLE(10_7, 4_0)
@interface AVMutableCompositionTrack : AVCompositionTrack
{
@private
    AVMutableCompositionTrackInternal    *_mutablePriv;
}

/* Indicates a timescale in which time values for the track can be operated upon without extraneous numerical conversion.
   If not set, returns the naturalTimeScale of the first non-empty edit, or 600 if there are no non-empty edits.
   Set to 0 to revert to default behavior. */
@property (nonatomic) CMTimeScale naturalTimeScale;

/* indicates the language associated with the track, as an ISO 639-2/T language code; if not set, returns nil */
@property (nonatomic, copy) NSString *languageCode;

/* indicates the language tag associated with the track, as an RFC 4646 language tag; if not set, returns nil */
@property (nonatomic, copy) NSString *extendedLanguageTag;

/* the preferred transformation of the visual media data for display purposes; if not set, returns CGAffineTransformIdentity */
@property (nonatomic) CGAffineTransform preferredTransform;

/* the preferred volume of the audible media data; if not set, returns 1.0 */
@property (nonatomic) float preferredVolume;

/* Provides read/write access to the array of track segments, each an instance of AVCompositionTrackSegment.
  	Note that timeMapping.target.start of the first AVCompositionTrackSegment must be kCMTimeZero,
  	and the timeMapping.target.start of each subsequent AVCompositionTrackSegment must equal
  	CMTimeRangeGetEnd(the previous AVCompositionTrackSegment's timeMapping.target).
  	-validateTrackSegments:error: will perform a test to ensure that an array of AVCompositionTrackSegments
  	conforms to this rule.
*/
@property (nonatomic, copy) NSArray *segments;

/*!
	@method			insertTimeRange:ofTrack:atTime:error:
	@abstract		Inserts a timeRange of a source track into a track of a composition.
	@param			timeRange
					Specifies the timeRange of the track to be inserted.
	@param			track
					Specifies the source track to be inserted.
	@param			startTime
					Specifies the time at which the inserted track is to be presented by the composition track.
					You may pass kCMTimeInvalid for startTime to indicate that the timeRange should be appended 
					to the end of the track.
	@param			error
					Describes failures that may be reported to the user, e.g. the asset
					that was selected for insertion in the composition is restricted by copy-protection.
	@result			A BOOL value indicating the success of the insertion.
	@discussion	
		You provide a reference to an AVAssetTrack and the timeRange within it that you want to insert.  
		You specify the start time in the target composition track at which the timeRange should be inserted.
		
		Note that the inserted track timeRange will be presented at its natural duration and rate. It can be
		scaled to a different duration (and presented at a different rate) via -scaleTimeRange:toDuration:.
*/
- (BOOL)insertTimeRange:(CMTimeRange)timeRange ofTrack:(AVAssetTrack *)track atTime:(CMTime)startTime error:(NSError **)error;

/*!
	@method			insertEmptyTimeRange:
	@abstract		Adds or extends an empty timeRange within the composition track.
	@param			timeRange
					Specifies the empty timeRange to be inserted.
	@discussion	
		If you insert an empty timeRange into the track, any media that was presented
		during that interval prior to the insertion will be presented instead immediately
		afterward.
		The exact meaning of the term "empty timeRange" depends upon the mediaType of the track.  
		For example, an empty timeRange in a sound track presents silence.
*/
- (void)insertEmptyTimeRange:(CMTimeRange)timeRange;

/*!
	@method			removeTimeRange:
	@abstract		Removes a specified timeRange from the track.
	@param			timeRange
					Specifies the timeRange to be removed.
	@discussion
		Removal of a timeRange does not cause the track to be removed from the composition.
		Instead it removes or truncates track segments that intersect with the timeRange.
*/
- (void)removeTimeRange:(CMTimeRange)timeRange;

/*!
	@method			scaleTimeRange:toDuration:
	@abstract		Changes the duration of a timeRange of the track.
	@param			timeRange
					Specifies the timeRange of the track to be scaled.
	@param			duration
					Specifies the new duration of the timeRange.
	@discussion
		Each trackSegment affected by the scaling operation will be presented at a rate equal to
		source.duration / target.duration of its resulting timeMapping.
*/
- (void)scaleTimeRange:(CMTimeRange)timeRange toDuration:(CMTime)duration;

/*!
	@method			validateTrackSegments:error:
	@abstract		Tests an array of AVCompositionTrackSegments to determine whether they conform
					to the timing rules noted above (see the property key @"trackSegments").
	@param			trackSegments
					The array of AVCompositionTrackSegments to be validated.
	@param			error
					If validation fais, returns information about the failure.
	@discussion
		The array is tested for suitability for setting as the value of the trackSegments property.
		If a portion of an existing trackSegments array is to be modified, the modification can
		be made via an instance of NSMutableArray, and the resulting array can be tested via
		-validateTrackSegments:error:.
*/
- (BOOL)validateTrackSegments:(NSArray *)trackSegments error:(NSError **)error;

@end
