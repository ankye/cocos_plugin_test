
#ifndef PLUGIN_SIMPLE_LOG_H
#define PLUGIN_SIMPLE_LOG_H
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include <utility>
#include <iostream>
#ifdef CC_PLUGIN_WASM
#include <sys/time.h>
#include <sys/timeb.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#elif CC_PLUGIN_NATIVE
#include <sys/time.h>
#include "bindings/sebind/sebind.h"
#include "plugins/bus/EventBus.h"
#include "plugins/Plugins.h"
#ifdef ANDROID

#include <jni.h>
#include <android/log.h>
#define LOG_TAG "CC_PLUGIN_NATIVE"

#endif
#endif

// 定义日志级别
typedef enum
{
    kLogLevel_None, // 不记录日志
    kLogLevel_Core, // 只记录核心模块日志（不包含ffmpeg）
    kLogLevel_All   // 记录所有日志，包含ffmpeg
} LogLevel;
void getCurrentTime(char *buffer, size_t bufferSize);
void simpleLog(const char *format, ...);
#endif // PLUGIN_SIMPLE_LOG_H