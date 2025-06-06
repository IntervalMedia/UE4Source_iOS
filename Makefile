ARCHS = arm64
TARGET = iphone:clang:latest:latest
include $(THEOS)/makefiles/common.mk

TWEAK_NAME = UE4SourceiOS
UE4SourceiOS_FILES = Tweak.xm Cheats.cpp classes.cpp
UE4SourceiOS_CFLAGS = -std=c++17 -fobjc-arc
include $(THEOS_MAKE_PATH)/tweak.mk
