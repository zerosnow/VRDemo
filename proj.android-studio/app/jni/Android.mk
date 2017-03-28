LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)
$(call import-add-path,$(LOCAL_PATH)/../../../vrsdks)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   $(wildcard ../../../Classes/*.cpp) \
                   $(wildcard ../../../Classes/audio/*.cpp) \
                   $(wildcard ../../../Classes/controller/*.cpp) \
                   $(wildcard ../../../Classes/utils/*.cpp) \
                   $(wildcard ../../../Classes/render/*.cpp) \
                   $(wildcard ../../../Classes/render/background/*.cpp) \
                   $(wildcard ../../../Classes/render/lyric/*.cpp) \
                   $(wildcard ../../../Classes/render/sprite/*.cpp) \
                   $(wildcard ../../../Classes/render/weather/*.cpp)




LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../vrsdks

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

# _COCOS_VR_HEADER_ANDROID_BEGIN
LOCAL_SRC_FILES += ../../../vrsdks/gvr-sdk/CCVRGvrRenderer.cpp ../../../vrsdks/gvr-sdk/CCVRGvrHeadTracker.cpp ../../../vrsdks/gvr-sdk/CCVRGvrController.cpp
# _COCOS_VR_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

# _COCOS_VR_LIB_ANDROID_BEGIN
LOCAL_SHARED_LIBRARIES := gvr
# _COCOS_VR_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

LOCAL_LDLIBS += -lOpenSLES

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

# _COCOS_VR_LIB_IMPORT_ANDROID_BEGIN
$(call import-module, gvr-sdk/gvr/prebuild)
# _COCOS_VR_LIB_IMPORT_ANDROID_END


