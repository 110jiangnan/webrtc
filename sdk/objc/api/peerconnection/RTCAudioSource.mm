/*
 *  Copyright 2016 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#import "RTCAudioSource+Private.h"
#import "RTCPeerConnectionFactory+Private.h"

#include "rtc_base/checks.h"

@implementation RTC_OBJC_TYPE (RTCAudioSource) {
  webrtc::Thread *_signalingThread;
}

@synthesize volume = _volume;
@synthesize isCustomSource = _isCustomSource;
@synthesize nativeAudioSource = _nativeAudioSource;

- (instancetype)
      initWithFactory:(RTC_OBJC_TYPE(RTCPeerConnectionFactory) *)factory
    nativeAudioSource:
        (webrtc::scoped_refptr<webrtc::AudioSourceInterface>)nativeAudioSource {
  RTC_DCHECK(factory);
  RTC_DCHECK(nativeAudioSource);

  self = [super initWithFactory:factory
                  nativeMediaSource:nativeAudioSource
                               type:RTC_OBJC_TYPE(RTCMediaSourceTypeAudio)];
  if (self) {
    _nativeAudioSource = nativeAudioSource;
    _signalingThread = factory.signalingThread;
  }
  return self;
}

- (instancetype)
      initWithFactory:(RTC_OBJC_TYPE(RTCPeerConnectionFactory) *)factory
    nativeMediaSource:
        (webrtc::scoped_refptr<webrtc::MediaSourceInterface>)nativeMediaSource
                 type:(RTC_OBJC_TYPE(RTCMediaSourceType))type {
  RTC_DCHECK_NOTREACHED();
  return nil;
}

- (NSString *)description {
  NSString *stateString = [[self class] stringForState:self.state];
  return [NSString stringWithFormat:@"RTC_OBJC_TYPE(RTCAudioSource)( %p ): %@",
                                    self,
                                    stateString];
}

- (double)volume {
  if (!_signalingThread->IsCurrent()) {
    return _signalingThread->BlockingCall([self] { return [self volume]; });
  }

  return _nativeAudioSource->GetVolume();
}

- (void)setVolume:(double)volume {
  if (!_signalingThread->IsCurrent()) {
    _signalingThread->BlockingCall([self, volume] { [self setVolume:volume]; });
    return;
  }

  _nativeAudioSource->SetVolume(volume);
}

-(void) onAudioData:(NSData *)audioData (int):bits_per_sample (int):sample_rate (int):number_of_channels (int):number_of_frames {
  if (self.isCustomSource) {
    // 或者 static_cast<MyAudioSource*>
    MyAudioSource *myAudioSource = (MyAudioSource *)self.nativeAudioSource;
    myAudioSource->OnData(audioData.bytes, bits_per_sample, sample_rate, number_of_channels, number_of_frames);
  }
}

@end
