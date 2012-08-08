/*
 * Copyright (C) 2011, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "LatinIME: jni: ProximityInfo"

#include "com_android_inputmethod_keyboard_ProximityInfo.h"
#include "jni.h"
#include "jni_common.h"
#include "proximity_info.h"

namespace latinime {

static jlong latinime_Keyboard_setProximityInfo(JNIEnv *env, jobject object,
        jstring localeJStr, jint maxProximityCharsSize, jint displayWidth, jint displayHeight,
        jint gridWidth, jint gridHeight, jint mostCommonkeyWidth, jintArray proximityChars,
        jint keyCount, jintArray keyXCoordinates, jintArray keyYCoordinates,
        jintArray keyWidths, jintArray keyHeights, jintArray keyCharCodes,
        jfloatArray sweetSpotCenterXs, jfloatArray sweetSpotCenterYs, jfloatArray sweetSpotRadii) {
    const char *localeCStr = env->GetStringUTFChars(localeJStr, 0);
    ProximityInfo *proximityInfo = new ProximityInfo(env, localeCStr, maxProximityCharsSize,
            displayWidth, displayHeight, gridWidth, gridHeight, mostCommonkeyWidth, proximityChars,
            keyCount, keyXCoordinates, keyYCoordinates, keyWidths, keyHeights, keyCharCodes,
            sweetSpotCenterXs, sweetSpotCenterYs, sweetSpotRadii);
    env->ReleaseStringUTFChars(localeJStr, localeCStr);
    return reinterpret_cast<jlong>(proximityInfo);
}

static void latinime_Keyboard_release(JNIEnv *env, jobject object, jlong proximityInfo) {
    ProximityInfo *pi = reinterpret_cast<ProximityInfo*>(proximityInfo);
    if (!pi) return;
    delete pi;
}

static JNINativeMethod sKeyboardMethods[] = {
    {"setProximityInfoNative", "(Ljava/lang/String;IIIIII[II[I[I[I[I[I[F[F[F)J",
            (void*)latinime_Keyboard_setProximityInfo},
    {"releaseProximityInfoNative", "(J)V", (void*)latinime_Keyboard_release}
};

int register_ProximityInfo(JNIEnv *env) {
    const char *const kClassPathName = "com/android/inputmethod/keyboard/ProximityInfo";
    return registerNativeMethods(env, kClassPathName, sKeyboardMethods,
            sizeof(sKeyboardMethods) / sizeof(sKeyboardMethods[0]));
}
} // namespace latinime
