
#include "CC_PLUGIN_TP__.h"
#include "IEventHandler.h"
#include "simple_log.h"
#include "PluginPlus.h"

#include <iostream>
using namespace ccp;
using namespace std;
namespace
{

    // CC_PLUGIN_TP__ *COCOS_CC_PLUGIN_TP__Constructor(se::Object *jsObject)
    // {
    //     CC_PLUGIN_TP__ *plugin = new CC_PLUGIN_TP__();
    //     plugin->setJSObject(jsObject);
    //     return plugin;
    // }
    // int openPlugin(CC_PLUGIN_TP__ *plugin, int logLv)
    // {

    //     CALL_JS(plugin->jsObject, PLUGIN_OPEN, (u32)logLv, PLUGIN_OPEN);
    //     return 0;
    // }

    // int closePlugin(CC_PLUGIN_TP__ *plugin)
    // {
    //     CALL_JS(plugin->jsObject, PLUGIN_CLOSE, PLUGIN_CLOSE);
    //     return 0;
    // }

    // int sendData(CC_PLUGIN_TP__ *plugin, const std::vector<uint8_t> &input, int size)
    // {
    //     plugin->sendData((unsigned char *)input.data(), size);
    //     return 0;
    // }

    // CCPObject *getBuffer(CC_PLUGIN_TP__ *plugin, uCCPrt ptr_val, u32 size)
    // {
    //     // std::vector<uint8_t> a(size);                  // 创建一个大小为 size 的向量
    //     char *ptr = reinterpret_cast<char *>(ptr_val); // 将数值表示转换回指针                                           // std::memcpy(a.data(), ptr, size);
    //     return CCP_UINT8ARRAY(ptr, size);
    // }

    class COCOS_CC_PLUGIN_TP__
    {
    public:
        CCPObject *jsObject;
        CCPLUGINPROP(attrInt, int)

        ccp::CC_PLUGIN_TP__ *plugin = NULL;

        CCP_CONSTRUCTOR(COCOS_CC_PLUGIN_TP__)

        virtual ~COCOS_CC_PLUGIN_TP__()
        {
        }

        int openPlugin(int logLv)
        {
            if (plugin)
            {
                closePlugin();
            }

            plugin = new ccp::CC_PLUGIN_TP__();
            plugin->setJSObject(jsObject);
            // simpleLog("openPlugin logLv=%d", logLv);
            // logLevel = (LogLevel)logLv;
            CALL_JS(plugin->jsObject, ccp::PLUGIN_OPEN, (int)logLv, string("openPlugin"));
            return 0;
        }
        int closePlugin()
        {
            CALL_JS(plugin->jsObject, ccp::PLUGIN_CLOSE, string("closePlugin"));

            if (plugin)
            {
                delete plugin;
                plugin = NULL;
            }

            return 0;
        }
        std::string version()
        {
            if (plugin)
            {
                return plugin->version();
            }
            return "0.0.0";
        }

        int sendData(CCPInU8Arr input, int size)
        {
            u8 *buff = (u8 *)(input.data());
            return plugin->sendData(buff, size);
        }

        CCPOutU8Arr generateImageData(int width, int height)
        {
            std::vector<uint8_t> data = plugin->generateImageData(width, height);
            return CCP_UINT8ARRAY(data.data(), data.size());
        }

        CCPOutU8Arr getBuffer(uCCPrt ptr_val, u32 size)
        {
            // std::vector<uint8_t> a(size);                  // 创建一个大小为 size 的向量
            char *ptr = reinterpret_cast<char *>(ptr_val); // 将数值表示转换回指针                                           // std::memcpy(a.data(), ptr, size);
            return CCP_UINT8ARRAY(ptr, size);
        }
    };

} // namespace

// export c++ methods to JS
CC_PLUGIN_BINDING_BEGIN(COCOS_CC_PLUGIN_TP__)
    .CCPLUGINPROPBIND(COCOS_CC_PLUGIN_TP__, attrInt)
    .CCPLUGINBIND(COCOS_CC_PLUGIN_TP__, openPlugin)
    .CCPLUGINBIND(COCOS_CC_PLUGIN_TP__, closePlugin)
    .CCPLUGINBIND(COCOS_CC_PLUGIN_TP__, sendData)
    .CCPLUGINBIND(COCOS_CC_PLUGIN_TP__, getBuffer)
    .CCPLUGINBIND(COCOS_CC_PLUGIN_TP__, generateImageData)
    .CCPLUGINBIND(COCOS_CC_PLUGIN_TP__, version);
CC_PLUGIN_BINDING_END(COCOS_CC_PLUGIN_TP__)