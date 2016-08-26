#
# Copyright 2015 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)

ifneq ($(filter hima himaul himawl himawhl, $(TARGET_DEVICE)),)

include $(call all-makefiles-under,$(LOCAL_PATH))

include $(CLEAR_VARS)

WCD9320_IMAGES := \
    wcd9320_anc.bin wcd9320_mad_audio.bin wcd9320_mbhc.bin

WCD9320_SYMLINKS := $(addprefix $(TARGET_OUT_ETC)/firmware/wcd9320/,$(WCD9320_IMAGES))
$(WCD9320_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "wcd9320 firmware link: $@"
	@mkdir -p $(dir $@)
	@rm -rf $@
	tf=$(notdir $@); if [ "$$tf" = "wcd9320_mbhc.bin" ]; then tf="mbhc.bin"; fi; ln -sf /data/misc/audio/$$tf $@

ALL_DEFAULT_INSTALLED_MODULES += $(WCD9320_SYMLINKS)

MODEM_IMAGES := \
    mba.b00 mba.mbn mba.mdt modem.b00 modem.b01 modem.b02 modem.b03 modem.b04 modem.b05 \
    modem.b06 modem.b07 modem.b08 modem.b09 modem.b10 modem.b11 modem.b12 modem.b13 \
    modem.b14 modem.b15 modem.b16 modem.b17 modem.b18 modem.b19 modem.b20 modem.b21 \
    modem.b22 modem.b23 modem.b24 modem.b25 modem.b26 modem.b27 modem.b28 modem.mdt

MODEM_SYMLINKS := $(addprefix $(TARGET_ROOT_OUT)/firmware/image/,$(notdir $(MODEM_IMAGES)))
$(MODEM_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "Modem firmware link: $@"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -sf /firmware/radio/$(notdir $@) $@

ALL_DEFAULT_INSTALLED_MODULES += $(MODEM_SYMLINKS)

ADSP_IMAGES := \
    adsp.b00 adsp.b01 adsp.b02 adsp.b03 adsp.b04 adsp.b05 adsp.b06 adsp.b07 \
    adsp.b08 adsp.b09 adsp.b10 adsp.b11 adsp.b12 adsp.b13 adsp.b14 adsp.b15 adsp.mdt

ADSP_SYMLINKS := $(addprefix $(TARGET_ROOT_OUT)/firmware/image/,$(notdir $(ADSP_IMAGES)))
$(ADSP_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "ADSP firmware link: $@"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -sf /firmware/adsp/$(notdir $@) $@

ALL_DEFAULT_INSTALLED_MODULES += $(ADSP_SYMLINKS)

CPE_IMAGES := \
    cpe.b00 cpe.b01 cpe.b02 cpe.b03 cpe.b04 cpe.b05 \
    cpe.b06 cpe.b07 cpe.b08 cpe.b09 cpe.b10 cpe.b11 \
    cpe.b12 cpe.b13 cpe.b14 cpe.b15 cpe.b16 cpe.b17 \
    cpe.b18 cpe.b19 cpe.b20 cpe.b21 cpe.b22 cpe.mdt

CPE_SYMLINKS := $(addprefix $(TARGET_ROOT_OUT)/firmware/image/,$(notdir $(CPE_IMAGES)))
$(CPE_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "CPE firmware link: $@"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) ln -sf /firmware/cpe/$(notdir $@) $@

ALL_DEFAULT_INSTALLED_MODULES += $(CPE_SYMLINKS)

endif
