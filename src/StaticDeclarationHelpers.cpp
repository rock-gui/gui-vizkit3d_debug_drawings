#include "StaticDeclarationHelpers.hpp"
#include "DeclaredChannels.hpp"

namespace vizkit3dDebugDrawings
{
    StaticDeclareChannel::StaticDeclareChannel(const std::string& name)
    {
        DeclaredChannels::getInstance()->declareChannel(name);
    }
}
