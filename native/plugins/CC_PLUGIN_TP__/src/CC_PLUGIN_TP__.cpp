
#include "CC_PLUGIN_TP__.h"
#include "PluginPlus.h"
#include <iostream>

using namespace std;
namespace ccp
{
    CC_PLUGIN_TP__::CC_PLUGIN_TP__()
    {
        _threeLib = new THREE_LIB_TP__();
        rgbaBuf = 0;
        rgbaBufSize = 0;
    }

    CC_PLUGIN_TP__::~CC_PLUGIN_TP__()
    {
        simpleLog("CC_PLUGIN_TP__ destory: %s", _version.c_str());

        if (rgbaBuf)
        {
            free((void *)rgbaBuf);
            rgbaBuf = 0;
        }
        rgbaBufSize = 0;
    }

    void CC_PLUGIN_TP__::setJSObject(CCPObject *v)
    {
        simpleLog("CC_PLUGIN_TP__ setJSObject");
        jsObject = v;
    }

    std::string CC_PLUGIN_TP__::version()
    {
        simpleLog("CC_PLUGIN_TP__ version: %s", _version.c_str());
        _threeLib->version();
        return _version;
    }

    int CC_PLUGIN_TP__::sendData(unsigned char *buff, int size)
    {
        simpleLog("CC_PLUGIN_TP__ sendData size: %d", size);
        if (size != rgbaBufSize)
        {
            if (rgbaBuf)
            {
                free((void *)rgbaBuf);
                rgbaBuf = 0;
            }
            rgbaBufSize = size;
            rgbaBuf = (u8 *)malloc(rgbaBufSize * sizeof(u8));
        }
        srand(unsigned(time(0)));
        for (int i = 0; i < rgbaBufSize; i++)
        {
            ((u8 *)rgbaBuf)[i] = (u8)(buff[i] + rand() % 128); // 产生0到255之间的随机数
        }

        simpleLog("CC_PLUGIN_TP__ calljs buffer size: %d", rgbaBufSize);
        uintptr_t ptr_val = reinterpret_cast<uintptr_t>(rgbaBuf);
        CALL_JS(jsObject, PLUGIN_ON_DATA, (uCCPrt)ptr_val, (u32)rgbaBufSize);

        CALL_JS(jsObject, PLUGIN_ON_DATA_WITH_BUFFER, CCP_UINT8ARRAY(rgbaBuf, rgbaBufSize), (u32)rgbaBufSize);

        return 0;
    }

    std::vector<u8> CC_PLUGIN_TP__::generateImageData(int width, int height)
    {
        auto size = width * height * 4;
        std::vector<u8> imageData(size, 255); // 创建一个全白的图像
        for (int i = 0; i < size; i++)
        {
            imageData[i] = (u8)(rand() % 128); // 产生0到255之间的随机数
        }
        return imageData;
    }
}