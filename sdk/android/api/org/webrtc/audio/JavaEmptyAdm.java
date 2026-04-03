/*
 *  Copyright 2018 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

package org.webrtc.audio;

import android.content.Context;
import android.media.AudioAttributes;
import android.media.AudioDeviceInfo;
import android.media.AudioManager;
import android.os.Build;
import androidx.annotation.RequiresApi;
import java.nio.ByteBuffer;
import java.util.concurrent.ScheduledExecutorService;
import org.webrtc.JniCommon;
import org.webrtc.Logging;

/**
 * JavaEmptyAdm implemented using android.media.AudioRecord as input and
 * android.media.AudioTrack as output.
 */
public class JavaEmptyAdm implements AudioDeviceModule {
  private static final String TAG = "JavaEmptyAdm";

  private final Object nativeLock = new Object();
  private long nativeAudioDeviceModule;

  private JavaAudioDeviceModule(Context context) {
    this.context = context;
  }

  @Override
  public long getNativeAudioDeviceModulePointer() {
    synchronized (nativeLock) {
      if (nativeAudioDeviceModule == 0) {
        nativeAudioDeviceModule = nativeCreateJavaEmptyAdm(context);
      }
      return nativeAudioDeviceModule;
    }
  }

  @Override
  public void release() {
    synchronized (nativeLock) {
      if (nativeAudioDeviceModule != 0) {
        JniCommon.nativeReleaseRef(nativeAudioDeviceModule);
        nativeAudioDeviceModule = 0;
      }
    }
  }

  @Override
  public void setSpeakerMute(boolean mute) {
    Logging.d(TAG, "setSpeakerMute: " + mute);
  }

  @Override
  public void setMicrophoneMute(boolean mute) {
    Logging.d(TAG, "setMicrophoneMute: " + mute);
  }

  @Override
  public boolean setNoiseSuppressorEnabled(boolean enabled) {
    Logging.d(TAG, "setNoiseSuppressorEnabled: " + enabled);
    return enabled;
  }

  private static native long nativeCreateJavaEmptyAdm(Context context);
}
