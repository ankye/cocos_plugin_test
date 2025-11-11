#ifndef CC_PLUGIN_IEVENT_HANDLER_H
#define CC_PLUGIN_IEVENT_HANDLER_H

#include <utility>

namespace ccp
{
    const std::string PLUGIN_OPEN = std::string("onPluginOpen");
    const std::string PLUGIN_CLOSE = std::string("onPluginClose");
    const std::string PLUGIN_ON_DATA = std::string("onPluginData");
    const std::string PLUGIN_ON_DATA_WITH_BUFFER = std::string("onPluginDataWithBuffer");

}
#endif // CC_PLUGIN_IEVENT_HANDLER_H
