/*
 *  Copyright (c) 2026 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <jni.h>

#include "api/audio/empty_audio_device.h"
#include "sdk/android/src/jni/jni_helpers.h"
#include "third_party/jni_zero/jni_zero.h"
#include "sdk/android/generated_peerconnection_jni/JavaMyAudioSource_jni.h"

namespace webrtc {
namespace jni {

static void JNI_JavaMyAudioSource_SendData(JNIEnv* env,
                                           jlong source,
                                           const jni_zero::JavaParamRef<jbyteArray>& audio_data,
                                           jint bits_per_sample,
                                           jint sample_rate,
                                           jint number_of_channels,
                                           jint number_of_frames) {
  // Get the MyAudioSource instance
  MyAudioSource* my_audio_source = reinterpret_cast<MyAudioSource*>(source);
  
  if (my_audio_source == nullptr) {
    return;
  }
  
  // Convert Java byte array to C++ pointer
  jbyte* audio_data_ptr = env->GetByteArrayElements(audio_data, nullptr);
  if (audio_data_ptr == nullptr) {
    return;
  }
  
  // Call the C++ OnData method
  my_audio_source->OnData(
      static_cast<const void*>(audio_data_ptr),
      static_cast<int>(bits_per_sample),
      static_cast<int>(sample_rate),
      static_cast<size_t>(number_of_channels),
      static_cast<size_t>(number_of_frames));
  
  // Release the byte array elements
  env->ReleaseByteArrayElements(audio_data, audio_data_ptr, JNI_ABORT);
}

}  // namespace jni
}  // namespace webrtc