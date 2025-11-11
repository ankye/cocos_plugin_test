#ifndef CC_PLUGIN_TP___H
#define CC_PLUGIN_TP___H

#include "THREE_LIB_TP__.h"
#include "IEventHandler.h"
#include "PluginPlus.h"

namespace ccp
{

    class CC_PLUGIN_TP__
    {
    private:
        std::string _version = "0.0.1";
        THREE_LIB_TP__ *_threeLib;

        u8 *rgbaBuf;
        u32 rgbaBufSize;

    public:
        CCPObject *jsObject;

        CC_PLUGIN_TP__();
        ~CC_PLUGIN_TP__();

        std::string version();
        int sendData(unsigned char *buff, int size);
        std::vector<u8> generateImageData(int width, int height);
        void setJSObject(CCPObject *v);
    };
}
#endif