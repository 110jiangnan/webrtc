/*
 *  Copyright 2016 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#import <Foundation/Foundation.h>

#import "RTCMediaSource.h"
#import "sdk/objc/base/RTCMacros.h"
#include "api/audio/empty_audio_device.h"

NS_ASSUME_NONNULL_BEGIN

RTC_OBJC_EXPORT
@interface RTC_OBJC_TYPE (RTCAudioSource) : RTC_OBJC_TYPE(RTCMediaSource)

- (instancetype)init NS_UNAVAILABLE;

// Sets the volume for the RTCMediaSource. `volume` is a gain value in the range
// [0, 10].
// Temporary fix to be able to modify volume of remote audio tracks.
// TODO(kthelgason): Property stays here temporarily until a proper volume-api
// is available on the surface exposed by webrtc.
@property(nonatomic, assign) double volume;
@property(nonatomic, assign) bool isCustomSource;

-(void) onAudioData:(NSData *)audioData (int):bits_per_sample (int):sample_rate (int):number_of_channels (int):number_of_frames;

@end

NS_ASSUME_NONNULL_END
