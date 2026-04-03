#ifndef API_EMPTY_AUDIO_AUDIO_DEVICE_H_
#define API_EMPTY_AUDIO_AUDIO_DEVICE_H_

#include <string>
#include <optional>
#include "api/audio/audio_device.h"
#include "api/make_ref_counted.h"
#include "api/audio_options.h"
#include "api/media_stream_interface.h"
#include "api/notifier.h"
#include "api/scoped_refptr.h"

namespace webrtc {

class EmptyAudioDeviceModule : public AudioDeviceModule {
 public:
  EmptyAudioDeviceModule() = default;
  
  // Retrieve the currently utilized audio layer
  int32_t ActiveAudioLayer(AudioLayer* audioLayer) const override {
    if (audioLayer) {
      *audioLayer = kDummyAudio;
    }
    return 0;
  }

  // Full-duplex transportation of PCM audio
  int32_t RegisterAudioCallback(AudioTransport* audioCallback) override {
    return 0;
  }

  // Main initialization and termination
  int32_t Init() override { return 0; }
  int32_t Terminate() override { return 0; }
  bool Initialized() const override { return true; }

  // Device enumeration
  int16_t PlayoutDevices() override { return 1; }
  int16_t RecordingDevices() override { return 1; }
  int32_t PlayoutDeviceName(uint16_t index, char name[kAdmMaxDeviceNameSize],
                            char guid[kAdmMaxGuidSize]) override {
    if (name) {
      name[0] = '\0';
    }
    if (guid) {
      guid[0] = '\0';
    }
    return 0;
  }
  int32_t RecordingDeviceName(uint16_t index, char name[kAdmMaxDeviceNameSize],
                              char guid[kAdmMaxGuidSize]) override {
    if (name) {
      name[0] = '\0';
    }
    if (guid) {
      guid[0] = '\0';
    }
    return 0;
  }

  // Device selection
  int32_t SetPlayoutDevice(uint16_t index) override { return 0; }
  int32_t SetPlayoutDevice(WindowsDeviceType device) override { return 0; }
  int32_t SetRecordingDevice(uint16_t index) override { return 0; }
  int32_t SetRecordingDevice(WindowsDeviceType device) override { return 0; }

  // Audio transport initialization
  int32_t PlayoutIsAvailable(bool* available) override {
    if (available) {
      *available = true;
    }
    return 0;
  }
  int32_t InitPlayout() override { return 0; }
  bool PlayoutIsInitialized() const override { return true; }
  int32_t RecordingIsAvailable(bool* available) override {
    if (available) {
      *available = true;
    }
    return 0;
  }
  int32_t InitRecording() override { return 0; }
  bool RecordingIsInitialized() const override { return true; }

  // Audio transport control
  int32_t StartPlayout() override { return 0; }
  int32_t StopPlayout() override { return 0; }
  bool Playing() const override { return false; }
  int32_t StartRecording() override { 
    recording_ = true;
    return 0; 
  }
  int32_t StopRecording() override { 
    recording_ = false;
    return 0; 
  }
  bool Recording() const override { return recording_; }

  // Audio mixer initialization
  int32_t InitSpeaker() override { return 0; }
  bool SpeakerIsInitialized() const override { return true; }
  int32_t InitMicrophone() override { return 0; }
  bool MicrophoneIsInitialized() const override { return true; }

  // Speaker volume controls
  int32_t SpeakerVolumeIsAvailable(bool* available) override {
    if (available) {
      *available = true;
    }
    return 0;
  }
  int32_t SetSpeakerVolume(uint32_t volume) override { return 0; }
  int32_t SpeakerVolume(uint32_t* volume) const override {
    if (volume) {
      *volume = 100;
    }
    return 0;
  }
  int32_t MaxSpeakerVolume(uint32_t* maxVolume) const override {
    if (maxVolume) {
      *maxVolume = 100;
    }
    return 0;
  }
  int32_t MinSpeakerVolume(uint32_t* minVolume) const override {
    if (minVolume) {
      *minVolume = 0;
    }
    return 0;
  }

  // Microphone volume controls
  int32_t MicrophoneVolumeIsAvailable(bool* available) override {
    if (available) {
      *available = true;
    }
    return 0;
  }
  int32_t SetMicrophoneVolume(uint32_t volume) override { return 0; }
  int32_t MicrophoneVolume(uint32_t* volume) const override {
    if (volume) {
      *volume = 100;
    }
    return 0;
  }
  int32_t MaxMicrophoneVolume(uint32_t* maxVolume) const override {
    if (maxVolume) {
      *maxVolume = 100;
    }
    return 0;
  }
  int32_t MinMicrophoneVolume(uint32_t* minVolume) const override {
    if (minVolume) {
      *minVolume = 0;
    }
    return 0;
  }

  // Speaker mute control
  int32_t SpeakerMuteIsAvailable(bool* available) override {
    if (available) {
      *available = true;
    }
    return 0;
  }
  int32_t SetSpeakerMute(bool enable) override { return 0; }
  int32_t SpeakerMute(bool* enabled) const override {
    if (enabled) {
      *enabled = false;
    }
    return 0;
  }

  // Microphone mute control
  int32_t MicrophoneMuteIsAvailable(bool* available) override {
    if (available) {
      *available = true;
    }
    return 0;
  }
  int32_t SetMicrophoneMute(bool enable) override { return 0; }
  int32_t MicrophoneMute(bool* enabled) const override {
    if (enabled) {
      *enabled = false;
    }
    return 0;
  }

  // Stereo support
  int32_t StereoPlayoutIsAvailable(bool* available) const override {
    if (available) {
      *available = true;
    }
    return 0;
  }
  int32_t SetStereoPlayout(bool enable) override { return 0; }
  int32_t StereoPlayout(bool* enabled) const override {
    if (enabled) {
      *enabled = true;
    }
    return 0;
  }
  int32_t StereoRecordingIsAvailable(bool* available) const override {
    if (available) {
      *available = true;
    }
    return 0;
  }
  int32_t SetStereoRecording(bool enable) override { return 0; }
  int32_t StereoRecording(bool* enabled) const override {
    if (enabled) {
      *enabled = true;
    }
    return 0;
  }

  // Playout delay
  int32_t PlayoutDelay(uint16_t* delayMS) const override {
    if (delayMS) {
      *delayMS = 0;
    }
    return 0;
  }

  // Only supported on Android.
  bool BuiltInAECIsAvailable() const override { return false; }
  bool BuiltInAGCIsAvailable() const override { return false; }
  bool BuiltInNSIsAvailable() const override { return false; }

  // Enables the built-in audio effects. Only supported on Android.
  int32_t EnableBuiltInAEC(bool enable) override { return 0; }
  int32_t EnableBuiltInAGC(bool enable) override { return 0; }
  int32_t EnableBuiltInNS(bool enable) override { return 0; }

  // Play underrun count. Only supported on Android.
  int32_t GetPlayoutUnderrunCount() const override { return 0; }

  // Used to generate RTC stats. If not implemented, RTCAudioPlayoutStats will
  // not be present in the stats.
  std::optional<Stats> GetStats() const override { 
    Stats stats;
    return stats;
  }

  // Whether to stop recording when all streams are muted.
  bool IsStopOnMuteModeEnabled() const override { return true; }

#if defined(WEBRTC_IOS)
  int GetPlayoutAudioParameters(AudioParameters* params) const override { return 0; }
  int GetRecordAudioParameters(AudioParameters* params) const override { return 0; }
#endif  // WEBRTC_IOS

  int32_t SetObserver(AudioDeviceObserver* observer) override { return 0; }
  int32_t GetPlayoutDevice() const override { return 0; }
  int32_t GetRecordingDevice() const override { return 0; }

 private:
  bool recording_ = false;
};


class MyAudioSource : public Notifier<AudioSourceInterface> {
 public:
  // Creates an instance of MyAudioSource.
  static webrtc::scoped_refptr<MyAudioSource> Create(const webrtc::AudioOptions* audio_options);

  SourceState state() const override { return kLive; }
  bool remote() const override { return false; }

  const webrtc::AudioOptions options() const override { return options_; }

  void AddSink(AudioTrackSinkInterface* sink) override {
    webrtc::MutexLock lock(&sink_lock_);
    if (std::find(sinks_.begin(), sinks_.end(), sink) != sinks_.end()) {
      return;  // Already added.
    }
    sinks_.push_back(sink);
  }

  void RemoveSink(AudioTrackSinkInterface* sink) override {
    webrtc::MutexLock lock(&sink_lock_);
    auto it = std::remove(sinks_.begin(), sinks_.end(), sink);
    if (it != sinks_.end()) {
      sinks_.erase(it, sinks_.end());
    }
  }

  void OnData(const void* audio_data, int bits_per_sample, int sample_rate,
              size_t number_of_channels, size_t number_of_frames) {
    webrtc::MutexLock lock(&sink_lock_);
    for (auto* sink : sinks_) {
      sink->OnData(audio_data, bits_per_sample, sample_rate, number_of_channels,
                   number_of_frames);
    }
  }

protected:
  MyAudioSource() {
  }
  ~MyAudioSource() override {
    webrtc::MutexLock lock(&sink_lock_);
    sinks_.clear();
  }

 private:
  void Initialize(const webrtc::AudioOptions* audio_options);
  mutable webrtc::Mutex sink_lock_;
  std::vector<AudioTrackSinkInterface*> sinks_ RTC_GUARDED_BY(sink_lock_);
  webrtc::AudioOptions options_;
};

}  // namespace webrtc

#endif  // API_EMPTY_AUDIO_AUDIO_DEVICE_H_