/*
 * Copyright 2017 The LineageOS Project
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

#define LOG_TAG "android.hardware.light@2.0-service.hima"

#include <hidl/HidlTransportSupport.h>
#include <utils/Errors.h>

#include "Light.h"

// libhwbinder:
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

// Generated HIDL files
using android::hardware::light::V2_0::ILight;
using android::hardware::light::V2_0::implementation::Light;

const static std::string kBacklightPath = "/sys/class/leds/lcd-backlight/brightness";
const static std::string kAmberLedPath = "/sys/class/leds/amber/brightness";
const static std::string kGreenLedPath = "/sys/class/leds/green/brightness";
const static std::string kAmberBlinkPath = "/sys/class/leds/amber/blink";
const static std::string kGreenBlinkPath = "/sys/class/leds/green/blink";

int main() {
    std::ofstream backlight(kBacklightPath);
    if (!backlight) {
        int error = errno;
        ALOGE("Failed to open %s (%d): %s", kBacklightPath.c_str(), error, strerror(error));
        return -error;
    }

    std::ofstream amberLed(kAmberLedPath);
    if (!amberLed) {
        int error = errno;
        ALOGE("Failed to open %s (%d): %s", kAmberLedPath.c_str(), error, strerror(error));
        return -error;
    }

    std::ofstream greenLed(kGreenLedPath);
    if (!greenLed) {
        int error = errno;
        ALOGE("Failed to open %s (%d): %s", kGreenLedPath.c_str(), error, strerror(error));
        return -error;
    }

    std::ofstream amberBlink(kAmberBlinkPath);
    if (!amberBlink) {
        int error = errno;
        ALOGE("Failed to open %s (%d): %s", kAmberBlinkPath.c_str(), error, strerror(error));
        return -error;
    }

    std::ofstream greenBlink(kGreenBlinkPath);
    if (!greenBlink) {
        int error = errno;
        ALOGE("Failed to open %s (%d): %s", kGreenBlinkPath.c_str(), error, strerror(error));
        return -error;
    }

    android::sp<ILight> service = new Light(std::move(backlight),
                                            std::move(amberLed),
                                            std::move(greenLed),
                                            std::move(amberBlink),
                                            std::move(greenBlink));

    configureRpcThreadpool(1, true);

    android::status_t status = service->registerAsService();

    if (status != android::OK) {
        ALOGE("Cannot register Light HAL service");
        return 1;
    }

    ALOGI("Light HAL Ready.");
    joinRpcThreadpool();
    // Under normal cases, execution will not reach this line.
    ALOGE("Light HAL failed to join thread pool.");
    return 1;
}
