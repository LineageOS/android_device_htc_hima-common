/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "light"

#include "Light.h"

#include <log/log.h>

namespace {
using android::hardware::light::V2_0::LightState;

static uint32_t rgbToBrightness(const LightState& state) {
    uint32_t color = state.color & 0x00ffffff;
    return ((77 * ((color >> 16) & 0xff)) + (150 * ((color >> 8) & 0xff)) +
            (29 * (color & 0xff))) >> 8;
}

static bool isLit(const LightState& state) {
    return (state.color & 0x00ffffff);
}
} // anonymous namespace

namespace android {
namespace hardware {
namespace light {
namespace V2_0 {
namespace implementation {

enum {
    LED_AMBER,
    LED_GREEN,
    LED_BLANK,
};

enum {
    PULSE_LENGTH_ALWAYS_ON = 1,
    PULSE_LENGTH_NORMAL = 2,
    PULSE_LENGTH_LONG = 3,
};

enum {
    BLINK_MODE_OFF = 0,
    BLINK_MODE_NORMAL = 1,
    BLINK_MODE_LONG = 4,
};

Light::Light(std::ofstream&& backlight, std::ofstream&& amber_led,
             std::ofstream&& green_led, std::ofstream&& amber_blink,
             std::ofstream&& green_blink) :
    mBacklight(std::move(backlight)),
    mAmberLed(std::move(amber_led)),
    mGreenLed(std::move(green_led)),
    mAmberBlink(std::move(amber_blink)),
    mGreenBlink(std::move(green_blink)) {
    auto attnFn(std::bind(&Light::setAttentionLight, this, std::placeholders::_1));
    auto backlightFn(std::bind(&Light::setBacklight, this, std::placeholders::_1));
    auto batteryFn(std::bind(&Light::setBatteryLight, this, std::placeholders::_1));
    auto notifFn(std::bind(&Light::setNotificationLight, this, std::placeholders::_1));
    mLights.emplace(std::make_pair(Type::ATTENTION, attnFn));
    mLights.emplace(std::make_pair(Type::BACKLIGHT, backlightFn));
    mLights.emplace(std::make_pair(Type::BATTERY, batteryFn));
    mLights.emplace(std::make_pair(Type::NOTIFICATIONS, notifFn));
}

// Methods from ::android::hardware::light::V2_0::ILight follow.
Return<Status> Light::setLight(Type type, const LightState& state) {
    auto it = mLights.find(type);

    if (it == mLights.end()) {
        return Status::LIGHT_NOT_SUPPORTED;
    }

    it->second(state);

    return Status::SUCCESS;
}

Return<void> Light::getSupportedTypes(getSupportedTypes_cb _hidl_cb) {
    std::vector<Type> types;

    for (auto const& light : mLights) {
        types.push_back(light.first);
    }

    _hidl_cb(types);

    return Void();
}

void Light::setAttentionLight(const LightState& state) {
    std::lock_guard<std::mutex> lock(mLock);
    mAttentionState = state;
    setSpeakerBatteryLightLocked();
}

void Light::setBacklight(const LightState& state) {
    std::lock_guard<std::mutex> lock(mLock);

    uint32_t brightness = rgbToBrightness(state);

    mBacklight << brightness << std::endl;
}

void Light::setBatteryLight(const LightState& state) {
    std::lock_guard<std::mutex> lock(mLock);
    mBatteryState = state;
    setSpeakerBatteryLightLocked();
}

void Light::setNotificationLight(const LightState& state) {
    std::lock_guard<std::mutex> lock(mLock);
    mNotificationState = state;
    setSpeakerBatteryLightLocked();
}

void Light::setSpeakerBatteryLightLocked() {
    if (isLit(mBatteryState) && isLit(mNotificationState)) {
        setSpeakerLightLockedDual(mBatteryState, mNotificationState);
    } else if (isLit(mNotificationState)) {
        setSpeakerLightLocked(mNotificationState);
    } else if (isLit(mAttentionState)) {
        setSpeakerLightLocked(mAttentionState);
    } else if (isLit(mBatteryState)) {
        setSpeakerLightLocked(mBatteryState);
    } else {
        /* Lights off */
        mAmberLed << 0 << std::endl;
        mGreenLed << 0 << std::endl;
        mAmberBlink << 0 << std::endl;
        mGreenBlink << 0 << std::endl;
    }
}

void Light::setSpeakerLightLocked(const LightState& state) {
    uint32_t colorRGB = state.color & 0x00ffffff;
    uint32_t color = LED_BLANK;
    uint32_t blinkMode = BLINK_MODE_OFF;
    LightState localState = state;

    if ((colorRGB >> 8) & 0xff) color = LED_GREEN;
    if ((colorRGB >> 16) & 0xff) color = LED_AMBER;
    if (((colorRGB >> 8) & 0xff) > ((colorRGB >> 16) & 0xff)) color = LED_GREEN;

    if (localState.flashMode == Flash::TIMED) {
        // make sure to blink by default regardless of timing
        blinkMode = BLINK_MODE_NORMAL;
    }

    switch (localState.flashOnMs) {
        case PULSE_LENGTH_ALWAYS_ON:
            localState.flashMode = Flash::NONE;
            break;
        case PULSE_LENGTH_NORMAL:
            blinkMode = BLINK_MODE_NORMAL;
            break;
        case PULSE_LENGTH_LONG:
            blinkMode = BLINK_MODE_LONG;
            break;
    }

    switch (localState.flashMode) {
        case Flash::TIMED:
            switch (color) {
                case LED_AMBER:
                    mAmberLed << 1;
                    mGreenLed << 0;
                    mAmberBlink << blinkMode;
                    mGreenBlink << 0;
                    break;
                case LED_GREEN:
                    mAmberLed << 0;
                    mGreenLed << 1;
                    mAmberBlink << 0;
                    mGreenBlink << blinkMode;
                    break;
                case LED_BLANK:
                    mAmberBlink << 0;
                    mGreenBlink << 0;
                    break;
                default:
                    break;
            }
            break;
        case Flash::NONE:
            switch (color) {
                case LED_AMBER:
                    mAmberLed << 1;
                    mGreenLed << 0;
                    mAmberBlink << 0;
                    mGreenBlink << 0;
                    break;
                case LED_GREEN:
                    mAmberLed << 0;
                    mGreenLed << 1;
                    mAmberBlink << 0;
                    mGreenBlink << 0;
                    break;
                case LED_BLANK:
                    mAmberLed << 0;
                    mGreenLed << 0;
                    break;
            }
            break;
        default:
            break;
    }

    mAmberLed << std::endl;
    mGreenLed << std::endl;
    mAmberBlink << std::endl;
    mGreenBlink << std::endl;
}

void Light::setSpeakerLightLockedDual(const LightState& batteryState,
                                      const LightState& notificationState __unused) {
    uint32_t colorRGB = batteryState.color & 0x00ffffff;
    uint32_t color = LED_BLANK;
    uint32_t blinkMode = BLINK_MODE_LONG;

    if ((colorRGB >> 8) & 0xff) color = LED_GREEN;
    if ((colorRGB >> 16) & 0xff) color = LED_AMBER;

    switch (color) {
        case LED_AMBER:
            mAmberBlink << 1 << std::endl;
            mGreenLed << 1 << std::endl;
            mAmberBlink << 4 << std::endl;
            break;
        case LED_GREEN:
            mGreenBlink << 1 << std::endl;
            mAmberLed << 1 << std::endl;
            mGreenBlink << 4 << std::endl;
            break;
        default:
            break;
    }
}

} // namespace implementation
}  // namespace V2_0
}  // namespace light
}  // namespace hardware
}  // namespace android
