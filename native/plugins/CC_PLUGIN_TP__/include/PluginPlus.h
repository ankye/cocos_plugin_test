#ifndef PLUGIN_PLUS_H
#define PLUGIN_PLUS_H

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <variant>
#include <vector>

typedef unsigned char u8;
typedef signed char i8;
typedef unsigned short u16;
typedef signed short i16;
typedef unsigned int u32;

#include <iostream>
#include <map>

#include "simple_log.h"
#ifdef CC_PLUGIN_WASM
#include <sys/timeb.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#elif CC_PLUGIN_NATIVE
#include "bindings/sebind/sebind.h"
#include "plugins/bus/EventBus.h"
#include "plugins/Plugins.h"
#endif

#ifdef CC_PLUGIN_WASM
typedef u32 uCCPrt;
typedef emscripten::val CCPObject;
typedef emscripten::val CCPOutU8Arr;
typedef std::string CCPInU8Arr;
#elif CC_PLUGIN_NATIVE
typedef uint64_t uCCPrt;
typedef se::Object CCPObject;
typedef se::Object *CCPOutU8Arr;
typedef std::vector<uint8_t> &CCPInU8Arr;
#endif

#ifdef CC_PLUGIN_WASM
#define CCPLUGINBIND(cls, name) function(#name, &cls::name)

#define CCPLUGINPROP(name, type)          \
    type name;                            \
    emscripten::val get##name() const     \
    {                                     \
        return emscripten::val(name);     \
    }                                     \
    void set##name(emscripten::val value) \
    {                                     \
        name = value.as<type>();          \
    }

#define CCPLUGINPROPBIND(cls, name) property(#name, &cls::get##name, &cls::set##name)

#define CCP_CONSTRUCTOR(name)                             \
    CCPObject obj;                                        \
    name(CCPObject &&v) : obj(std::forward<CCPObject>(v)) \
    {                                                     \
        jsObject = &obj;                                  \
    }

#define CCP_UINT8ARRAY(data, size) \
    emscripten::val(emscripten::typed_memory_view(size, data))

#define CALL_JS(jsObject, eventName, ...)                           \
    do                                                              \
    {                                                               \
        if (jsObject)                                               \
        {                                                           \
            jsObject->call<void>(eventName.c_str(), ##__VA_ARGS__); \
        }                                                           \
    } while (0)

#define CC_PLUGIN_BINDING_BEGIN(name)   \
    EMSCRIPTEN_BINDINGS(name)           \
    {                                   \
        emscripten::class_<name>(#name) \
            .constructor<emscripten::val>()

#define CC_PLUGIN_BINDING_END(name) \
    }

#endif

#ifdef CC_PLUGIN_NATIVE
#define CCPLUGINBIND(cls, name) function(#name, &cls::name)

#define CCPLUGINPROP(name, type)               \
    type name;                                 \
    type get##name() const                     \
    {                                          \
        return name;                           \
    }                                          \
    void set##name(const se::Value value)      \
    {                                          \
        bool ok = false;                       \
        name = seval_to_type<type>(value, ok); \
    }

#define CCPLUGINPROPBIND(cls, name) property(#name, &cls::get##name, &cls::set##name)

#define CCP_CONSTRUCTOR(name) \
    name(CCPObject *val)      \
    {                         \
        jsObject = val;       \
    }

#define CCP_UINT8ARRAY(data, size) \
    se::Object::createTypedArray(se::Object::TypedArrayType::UINT8, data, size)

template <typename... Args>
se::ValueArray createValueVector(Args &&...args)
{
    return {se::Value(std::forward<Args>(args))...}; // 使用折叠表达式
}
#define CALL_JS(jsObject, eventName, ...)                         \
    do                                                            \
    {                                                             \
        if (jsObject)                                             \
        {                                                         \
            se::Value func;                                       \
            jsObject->getProperty(eventName.c_str(), &func);      \
            if (func.isObject() && func.toObject()->isFunction()) \
            {                                                     \
                se::ValueArray args;                              \
                args = createValueVector(__VA_ARGS__);            \
                func.toObject()->call(args, jsObject);            \
            }                                                     \
        }                                                         \
    } while (0)

#define CC_PLUGIN_BINDING_BEGIN(name)           \
    static bool register_##name(se::Object *ns) \
    {                                           \
        sebind::class_<name> klass(#name);      \
        klass.constructor<CCPObject *>()

#define CC_PLUGIN_BINDING_END(name)                        \
    klass.install(ns);                                     \
    return true;                                           \
    }                                                      \
    void add_##name##_class()                              \
    {                                                      \
        using namespace cc::plugin;                        \
        static Listener listener(BusType::SCRIPT_ENGINE);  \
        listener.receive([](ScriptEngineEvent event) { \
        if (event == ScriptEngineEvent::POST_INIT) { \
            se::ScriptEngine::getInstance()->addRegisterCallback(register_##name); \
        } }); \
    }                                                      \
    CC_PLUGIN_ENTRY(name##_glue, add_##name##_class);

#endif

#endif // CC_PLUGIN_TP___PLUGIN_PLUS_H