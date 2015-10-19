/*
 * Copyright (C) 2015 The CyanogenMod Project
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

#define CAMERA_PARAMETERS_EXTRA_C \
const char CameraParameters::KEY_TIME_CONS_POST_PROCESSING[] = "time-cons-post-processing"; \
const char CameraParameters::KEY_OIS_MODE[] = "ois_mode"; \
const char CameraParameters::KEY_APP_OIS_SETTING[] = "ois-setting"; \
const char CameraParameters::KEY_OIS_SUPPORT[] = "ois_support"; \
const char CameraParameters::KEY_CONTIBURST_TYPE[] = "contiburst-type"; \
const char CameraParameters::KEY_CAPTURE_MODE[] = "capture-mode"; \
const char CameraParameters::CAPTURE_MODE_NORMAL[] = "normal"; \
const char CameraParameters::CAPTURE_MODE_CONTI_ZOE[] = "contizoe"; \
const char CameraParameters::CAPTURE_MODE_CONTI_BURST[] = "contiburst"; \
const char CameraParameters::CAPTURE_MODE_CONTI_BURST_ONE_SHOT[] = "contiburst-one-shot"; \
const char CameraParameters::CAPTURE_MODE_HDR[] = "hdr"; \
const char CameraParameters::CAPTURE_MODE_PANORAMA[] = "panorama"; \
const char CameraParameters::CAPTURE_MODE_ZOE[] = "zoe"; \
const char CameraParameters::CAPTURE_MODE_EIS[] = "eis"; \
const char CameraParameters::KEY_CONTI_BURST_STATE[] = "contiburst-state"; \
const char CameraParameters::KEY_SUPPORTED_CAPTURE_MODES[] = "capture-mode-values"; \
const char CameraParameters::KEY_MIN_CONTRAST[] = "contrast-min"; \
const char CameraParameters::KEY_DEF_CONTRAST[] = "contrast-def"; \
const char CameraParameters::KEY_MIN_SHARPNESS[] = "sharpness-min"; \
const char CameraParameters::KEY_DEF_SHARPNESS[] = "sharpness-def"; \
const char CameraParameters::KEY_MIN_SATURATION[] = "saturation-min"; \
const char CameraParameters::KEY_DEF_SATURATION[] = "saturation-def"; \
const char CameraParameters::KEY_SINGLE_ISP_OUTPUT_ENABLED[] = "single-isp-output-enabled"; \
const char CameraParameters::POST_PROCESSING_ENABLE[] = "enable"; \
const char CameraParameters::POST_PROCESSING_BYPASS[] = "bypass"; \
const char CameraParameters::POST_PROCESSING_DELAY[] = "delay"; \
const char CameraParameters::SCENE_MODE_OFF[] = "off"; \
const char CameraParameters::SCENE_MODE_TEXT[] = "text"; \
const char CameraParameters::BURST_MODE_LIMIT20[] = "limit-20"; \
const char CameraParameters::BURST_MODE_UNLIMITED[] = "unlimited"; \
const char CameraParameters::OIS_MODE_OFF[] = "off"; \
const char CameraParameters::OIS_MODE_ON[] = "on"; \
const char CameraParameters::CONTI_BURST_CAPTURING[] = "contiburst-capturing"; \
const char CameraParameters::CONTI_BURST_CAPTURE_DONE[] = "contiburst-done"; \
const char CameraParameters::APP_OIS_SETTING_FALSE[] = "false"; \
const char CameraParameters::APP_OIS_SETTING_TRUE[] = "true"; \
const char CameraParameters::KEY_GPU_EFFECT[] = "GPU-effect"; \
const char CameraParameters::KEY_GPU_EFFECT_PARAM_0[] = "GE-param0"; \
const char CameraParameters::KEY_GPU_EFFECT_PARAM_1[] = "GE-param1"; \
const char CameraParameters::KEY_GPU_EFFECT_PARAM_2[] = "GE-param2"; \
const char CameraParameters::KEY_GPU_EFFECT_PARAM_3[] = "GE-param3"; \
const char CameraParameters::KEY_FORCE_USE_AUDIO_ENABLED[] = "forceuseaudio"; \
const char CameraParameters::KEY_ZSL[] = "zsl"; \
const char CameraParameters::KEY_CAMERA_MODE[] = "camera-mode"; \
const char CameraParameters::KEY_SMILEINFO_BYFACE_SUPPORTED[] = "smileinfo-byface-supported"; \
const char CameraParameters::ZSL_OFF[] = "off"; \
void CameraParameters::getBrightnessLumaTargetSet(int *magic, int *sauce) const{}; \
void CameraParameters::setBrightnessLumaTargetSet(int brightness, int luma) { \
    char str[32]; \
    snprintf(str, sizeof(str),"%d,%d", brightness, luma); \
    set("brightness-luma-target-set", str); \
}; \
void CameraParameters::getRawSize(int *magic, int *sauce) const{}; \
void CameraParameters::setZsl(const char *sauce) { set("zsl",sauce);}; \
const char *CameraParameters::getZsl() const { return get("zsl");}; \
const char CameraParameters_EXT::SCENE_MODE_BURST[] = "burst"; \
const char CameraParameters_EXT::SCENE_MODE_MANUAL[] = "manual"; \
const char CameraParameters_EXT::SCENE_MODE_TEXT[] = "text" ; \
const char CameraParameters_EXT::SCENE_MODE_ZOE[] = "zoe" ; \
const char CameraParameters_EXT::SCENE_MODE_PANORAMA[] = "panorama" ; \
const char CameraParameters_EXT::SCENE_MODE_PANORAMA_360[] = "panorama360" ;\
const char CameraParameters_EXT::ISO_AUTO[] = "auto" ; \
const char CameraParameters_EXT::ISO_HJR[] = "ISO_HJR" ; \
const char CameraParameters_EXT::ISO_100[] = "ISO100" ; \
const char CameraParameters_EXT::ISO_200[] = "ISO200" ; \
const char CameraParameters_EXT::ISO_400[] = "ISO400" ; \
const char CameraParameters_EXT::ISO_800[] = "ISO800" ; \
const char CameraParameters_EXT::ISO_1600[] = "ISO1600" ; \
const char CameraParameters_EXT::VIDEO_HFR_OFF[] = "off" ; \
const char CameraParameters_EXT::VIDEO_HFR_2X[] = "60" ; \
const char CameraParameters_EXT::VIDEO_HFR_3X[] = "90" ; \
const char CameraParameters_EXT::VIDEO_HFR_4X[] = "120" ; \
const char CameraParameters_EXT::VIDEO_HFR_5X[] = "150" ; \
const char CameraParameters_EXT::KEY_FASTVIDEO_FPS60_1080P_SUPPORTED[] = "video-1080p60fps-supported" ; \
const char CameraParameters_EXT::KEY_SLOW_MOTION_SUPPORTED[] = "video-slow-motion-supported" ; \
const char CameraParameters_EXT::KEY_SLOW_MOTION_MULTIPLE[] = "slow-motion-x" ; \
const char CameraParameters_EXT::KEY_SLOW_MOTION_RES[] = "slow-motion-res" ; \
const char CameraParameters_EXT::KEY_FASTVIDEO_FPS60_SUPPORTED[] = "video-720p60fps-supported" ; \
const char CameraParameters_EXT::KEY_CONTIBURST_TAKE[] = "take" ; \
const char CameraParameters_EXT::KEY_CONTIBURST_SUPPORTED_MODE[] = "contiburst-support-mode" ; \
const char CameraParameters_EXT::KEY_NON_ZSL_MANUAL_MODE[] = "non-zsl-manual-mode" ; \
const char CameraParameters_EXT::KEY_VIDEO_MODE[] = "video-mode" ; \
const char CameraParameters_EXT::KEY_FORCE_USE_AUDIO_ENABLED[] = "force-use-audio-enabled" ; \
const char CameraParameters_EXT::KEY_SLOW_MOTION_VERSION[] = "slow-motion-version" ; \
const char CameraParameters_EXT::KEY_SAVE_MIRROR[] = "save-mirror" ; \
const char CameraParameters_EXT::DENOISE_ON[] = "denoise-on" ; \
const char CameraParameters_EXT::DENOISE_OFF[] = "denoise-off" ; \
void CameraParameters_EXT::check_flashlight_restriction() {}; \
void CameraParameters_EXT::getBrightnessLumaTargetSet(int *magic, int *sauce) const{}; \
void CameraParameters_EXT::setBrightnessLumaTargetSet(int brightness, int luma) { \
    char str[32]; \
    snprintf(str, sizeof(str),"%d,%d", brightness, luma); \
    set("brightness-luma-target-set", str); \
}; \
CameraParameters_EXT::CameraParameters_EXT(CameraParameters *parent) {}; \
CameraParameters_EXT::~CameraParameters_EXT() {};

#define CAMERA_PARAMETERS_EXTRA_H \
    static const char KEY_TIME_CONS_POST_PROCESSING[]; \
    static const char KEY_OIS_MODE[]; \
    static const char KEY_APP_OIS_SETTING[]; \
    static const char KEY_OIS_SUPPORT[]; \
    static const char KEY_CONTIBURST_TYPE[]; \
    static const char KEY_CAPTURE_MODE[]; \
    static const char CAPTURE_MODE_NORMAL[]; \
    static const char CAPTURE_MODE_CONTI_ZOE[]; \
    static const char CAPTURE_MODE_CONTI_BURST[]; \
    static const char CAPTURE_MODE_CONTI_BURST_ONE_SHOT[]; \
    static const char CAPTURE_MODE_HDR[]; \
    static const char CAPTURE_MODE_PANORAMA[]; \
    static const char CAPTURE_MODE_ZOE[]; \
    static const char CAPTURE_MODE_EIS[]; \
    static const char KEY_CONTI_BURST_STATE[]; \
    static const char KEY_SUPPORTED_CAPTURE_MODES[]; \
    static const char KEY_MIN_CONTRAST[]; \
    static const char KEY_DEF_CONTRAST[]; \
    static const char KEY_MIN_SHARPNESS[]; \
    static const char KEY_DEF_SHARPNESS[]; \
    static const char KEY_MIN_SATURATION[]; \
    static const char KEY_DEF_SATURATION[]; \
    static const char KEY_SINGLE_ISP_OUTPUT_ENABLED[]; \
    static const char POST_PROCESSING_ENABLE[]; \
    static const char POST_PROCESSING_BYPASS[]; \
    static const char POST_PROCESSING_DELAY[]; \
    static const char SCENE_MODE_OFF[]; \
    static const char SCENE_MODE_TEXT[]; \
    static const char BURST_MODE_LIMIT20[]; \
    static const char BURST_MODE_UNLIMITED[]; \
    static const char OIS_MODE_OFF[]; \
    static const char OIS_MODE_ON[]; \
    static const char CONTI_BURST_CAPTURING[]; \
    static const char CONTI_BURST_CAPTURE_DONE[]; \
    static const char APP_OIS_SETTING_FALSE[]; \
    static const char APP_OIS_SETTING_TRUE[]; \
    static const char KEY_GPU_EFFECT[]; \
    static const char KEY_GPU_EFFECT_PARAM_0[]; \
    static const char KEY_GPU_EFFECT_PARAM_1[]; \
    static const char KEY_GPU_EFFECT_PARAM_2[]; \
    static const char KEY_GPU_EFFECT_PARAM_3[]; \
    static const char KEY_FORCE_USE_AUDIO_ENABLED[]; \
    static const char KEY_ZSL[]; \
    static const char KEY_CAMERA_MODE[]; \
    static const char KEY_SMILEINFO_BYFACE_SUPPORTED[]; \
    static const char ZSL_OFF[]; \
    void getRawSize(int *magic, int *sauce) const; \
    void getBrightnessLumaTargetSet(int *magic, int *sauce) const; \
    void setBrightnessLumaTargetSet(int brightness, int luma); \
    void setZsl(const char *sauce); \
    const char *getZsl() const;

#define CAMERA_PARAMETERS_EXT_H \
    static const char SCENE_MODE_BURST[]; \
    static const char SCENE_MODE_MANUAL[]; \
    static const char SCENE_MODE_TEXT[]; \
    static const char SCENE_MODE_ZOE[]; \
    static const char SCENE_MODE_PANORAMA[]; \
    static const char SCENE_MODE_PANORAMA_360[]; \
    static const char ISO_AUTO[]; \
    static const char ISO_HJR[]; \
    static const char ISO_100[]; \
    static const char ISO_200[]; \
    static const char ISO_400[]; \
    static const char ISO_800[]; \
    static const char ISO_1600[]; \
    static const char VIDEO_HFR_OFF[]; \
    static const char VIDEO_HFR_2X[]; \
    static const char VIDEO_HFR_3X[]; \
    static const char VIDEO_HFR_4X[]; \
    static const char VIDEO_HFR_5X[]; \
    static const char KEY_FASTVIDEO_FPS60_1080P_SUPPORTED[]; \
    static const char KEY_SLOW_MOTION_SUPPORTED[]; \
    static const char KEY_SLOW_MOTION_MULTIPLE[]; \
    static const char KEY_SLOW_MOTION_RES[]; \
    static const char KEY_FASTVIDEO_FPS60_SUPPORTED[]; \
    static const char KEY_CONTIBURST_TAKE[]; \
    static const char KEY_CONTIBURST_SUPPORTED_MODE[]; \
    static const char KEY_NON_ZSL_MANUAL_MODE[]; \
    static const char KEY_VIDEO_MODE[]; \
    static const char KEY_FORCE_USE_AUDIO_ENABLED[]; \
    static const char KEY_SLOW_MOTION_VERSION[]; \
    static const char KEY_SAVE_MIRROR[]; \
    static const char DENOISE_ON[]; \
    static const char DENOISE_OFF[]; \
    void check_flashlight_restriction(); \
    void getBrightnessLumaTargetSet(int *magic, int *sauce) const; \
    void setBrightnessLumaTargetSet(int brightness, int luma);

#define CAMERA_PARAMETERS_EXTRA_H_PRIVATE \
    String8 lKeys [300]; \
    String8 lValues [300]; \
    size_t lSize;
