package org.webrtc.audio;

import org.webrtc.JNINamespace;
import org.webrtc.MediaSource;


public class MyAudioSource extends MediaSource {
  public MyAudioSource(long nativeSource) {
    super(nativeSource);
  }

  public void OnData(byte[] audio_data, int bits_per_sample, int sample_rate,
            int number_of_channels, int number_of_frames) {
    OnData(getNativeAudioSource(), audio_data, bits_per_sample, sample_rate, number_of_channels, number_of_frames);
  }

  private static native void OnData(long nativeMyAudioSource, byte[] audio_data, int bits_per_sample, int sample_rate,
            int number_of_channels, int number_of_frames);

  /** Returns a pointer to webrtc::AudioSourceInterface. */
  long getNativeAudioSource() {
    return getNativeMediaSource();
  }
}