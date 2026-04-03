#include "api/audio/empty_audio_device.h"

namespace webrtc {

webrtc::scoped_refptr<MyAudioSource> MyAudioSource::Create(
    const webrtc::AudioOptions* audio_options) {
  auto source = webrtc::make_ref_counted<MyAudioSource>();
  source->Initialize(audio_options);
  return source;
}

void MyAudioSource::Initialize(const webrtc::AudioOptions* audio_options) {
  if (!audio_options) return;
  options_ = *audio_options;
}

}  // namespace webrtc
