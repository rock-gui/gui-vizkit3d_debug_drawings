#include <string>

#define V3DD_INTERNAL_CONCAT_(x,y) x##y
#define V3DD_INTERNAL_CONCAT(x,y) V3DD_INTERNAL_CONCAT_(x,y)

namespace vizkit3dDebugDrawings
{
    class StaticDeclareChannel
    {
        public:
            StaticDeclareChannel(const std::string& name);
    };
    
}
