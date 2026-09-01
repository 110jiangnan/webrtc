/*
 *  Copyright (c) 2018 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include <memory>

#include "sdk/android/generated_java_audio_jni/JavaEmptyAdm_jni.h"
#include "sdk/android/src/jni/audio_device/audio_record_jni.h"
#include "sdk/android/src/jni/audio_device/audio_track_jni.h"
#include "sdk/android/src/jni/jni_helpers.h"
#include "third_party/jni_zero/jni_zero.h"

namespace webrtc {
namespace jni {

static jlong JNI_JavaEmptyAdm_CreateJavaEmptyAdm(
    JNIEnv* env,
    const jni_zero::JavaParamRef<jobject>& j_context) {
  return jlongFromPointer(CreateEmptyAdm().release());
}

}  // namespace jni
}  // namespace webrtc
