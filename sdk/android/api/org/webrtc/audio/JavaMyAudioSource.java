package org.webrtc.audio;

import org.webrtc.MediaSource;
import org.webrtc.AudioSource;

public class JavaMyAudioSource extends AudioSource {
  public JavaMyAudioSource(long nativeSource) {
    super(nativeSource);
  }

  public void OnData(byte[] audio_data, int bits_per_sample, int sample_rate,
            int number_of_channels, int number_of_frames) {
    nativeSendData(getNativeAudioSource(), audio_data, bits_per_sample, sample_rate, number_of_channels, number_of_frames);
  }

  private static native void nativeSendData(long source, byte[] audio_data, int bits_per_sample, int sample_rate, int number_of_channels, int number_of_frames);
}