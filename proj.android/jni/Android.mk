LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/entities/Entity.cpp \
				   ../../Classes/entities/GroundEntity.cpp \
				   ../../Classes/entities/HazardEntity.cpp \
				   ../../Classes/entities/PlayerEntity.cpp \
				   ../../Classes/scenes/GameScene.cpp \
				   ../../Classes/scenes/InitialScene.cpp \
				   ../../Classes/scenes/LoginScene.cpp \
				   ../../Classes/scenes/RegisterScene.cpp \
				   ../../Classes/singletons/Analytics.cpp \
				   ../../Classes/singletons/Options.cpp \
				   ../../Classes/singletons/StringCache.cpp \
				   ../../Classes/singletons/User.cpp \
				   ../../Classes/ui_wrappers/ButtonWrapper.cpp \
				   ../../Classes/ui_wrappers/CheckBoxWrapper.cpp \
				   ../../Classes/ui_wrappers/LabelWrapper.cpp \
				   ../../Classes/ui_wrappers/TextBoxWrapper.cpp \
				   ../../Classes/helpers/SwipeAnalyticsHelper.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
