set(SOURCES CocoaInterface.mm
            CPUInfoOsx.cpp
            HotKeyController.m
            PlatformDarwinOSX.cpp
            smc.c
            XBMCHelper.cpp)

set(HEADERS CocoaInterface.h
            CPUInfoOsx.h
            HotKeyController.h
            PlatformDarwinOSX.h
            smc.h
            XBMCHelper.h)

core_add_library(platform_osx)
