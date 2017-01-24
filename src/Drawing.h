#pragma once
#include <vector>
#include <string>
#include <osg/ref_ptr>
#include <osgViz/Object.h>

namespace vizkit3dDebugDrawings
{
    /**A named collection of drawables */
    class Drawing
    {
    public:
        
        using PrimitiveCollection = std::vector<osg::ref_ptr<osgviz::Object>>;
        
        void setName(const std::string& n)
        {
            name = n;
        }
        void addPrimitive(const osg::ref_ptr<osgviz::Object>& prim)
        {
            primitives.push_back(prim);
        }
        
        const std::string& getName() const
        {
            return name;
        }
        
        const PrimitiveCollection& getPrimitives() const
        {
            return primitives;
        }
        
    private:
        std::string name;
        PrimitiveCollection primitives;
    };
}
