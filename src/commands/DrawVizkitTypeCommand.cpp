#include "DrawVizkitTypeCommand.h"
#include <rtt/types/TypekitRepository.hpp>
#include <orocos_cpp/TypeRegistry.hpp>
#include <orocos_cpp/PluginHelper.hpp>
#include <rtt/typelib/TypelibMarshaller.hpp>
#include <vizkit3d_plugin_information/Vizkit3dPluginInformation.hpp>
#include "vizkit3d_debug_drawings/DrawingManager.h"
#include <base-logging/Logging.hpp>


vizkit3dDebugDrawings::DrawVizkitTypeCommand* vizkit3dDebugDrawings::DrawVizkitTypeCommand::clone() const
{
    return new DrawVizkitTypeCommand(*this);
}

vizkit3dDebugDrawings::DrawVizkitTypeCommand::DrawVizkitTypeCommand() : Command("default")
{

}



vizkit3dDebugDrawings::DrawVizkitTypeCommand::DrawVizkitTypeCommand(const std::string& drawingName,
                                                                    const base::Vector3d& position,
                                                                    const base::Quaterniond& orientation,
                                                                    const std::string& typeName,
                                                                    void* pData) :
    Command(drawingName), position(position), orientation(orientation), typeName(typeName)
{
    marshall(typeName, pData);
}

void vizkit3dDebugDrawings::DrawVizkitTypeCommand::marshall(const std::string& typeName, void* pData)
{

    //FIXME eplain!!!
    RTT::types::TypeInfo* info = RTT::types::TypeInfoRepository::Instance()->type(typeName);
    if(info == nullptr)
    {
        //load typekit if not loaded
        std::string typekitName;
        orocos_cpp::TypeRegistry reg;
        reg.loadTypelist();
        if(!reg.getTypekitDefiningType(typeName, typekitName))
        {
            LOG_ERROR_S << "vizkit3d_debug_drawings: Failed to load typekit for: " << typeName;
            return;
        }
        if(!orocos_cpp::PluginHelper::loadTypekitAndTransports(typekitName))
        {
            LOG_ERROR_S << "vizkit3d_debug_drawings: Failed to load typekit: " << typekitName;
            return;
        }
        info = RTT::types::TypeInfoRepository::Instance()->type(typeName);
    }
    
    assert(info != nullptr);
    orogen_transports::TypelibMarshallerBase* marshaller = dynamic_cast<orogen_transports::TypelibMarshallerBase*>(info->getProtocol(orogen_transports::TYPELIB_MARSHALLER_ID));
    
    if(marshaller == nullptr)
    {
        LOG_ERROR_S << "vizkit3d_debug_drawings: casting marshaller failed\n";
        return;
    }
    
    //FIXME handle should be buffered?
    orogen_transports::TypelibMarshallerBase::Handle* handle = marshaller->createHandle();
    marshaller->setOrocosSample(handle, pData);
    marshaller->marshal(data, handle); //store byte representation of pData in handle
    marshaller->deleteHandle(handle);
    //FIXME maybe memory leak? dont know how the deletion stuff works :D    
}

void* vizkit3dDebugDrawings::DrawVizkitTypeCommand::unmarshall() const
{
    //FIXME duplicate code!!
    //FIXME eplain!!!
    RTT::types::TypeInfo* info = RTT::types::TypeInfoRepository::Instance()->type(typeName);
    if(info == nullptr)
    {
        //load typekit if not loaded
        std::string typekitName;
        orocos_cpp::TypeRegistry reg;
        reg.loadTypelist();
        if(!reg.getTypekitDefiningType(typeName, typekitName))
        {
            LOG_ERROR_S << "vizkit3d_debug_drawings: Failed to load typekit for: " << typeName;
            return nullptr;
        }
        if(!orocos_cpp::PluginHelper::loadTypekitAndTransports(typekitName))
        {
            LOG_ERROR_S << "vizkit3d_debug_drawings: Failed to load typekit: " << typekitName;
            return nullptr;
        }
        info = RTT::types::TypeInfoRepository::Instance()->type(typeName);
    }
    
    assert(info != nullptr);
    orogen_transports::TypelibMarshallerBase* marshaller = dynamic_cast<orogen_transports::TypelibMarshallerBase*>(info->getProtocol(orogen_transports::TYPELIB_MARSHALLER_ID));
    
    if(marshaller == nullptr)
    {
        LOG_ERROR_S << "vizkit3d_debug_drawings: casting marshaller failed\n";
        return nullptr;
    }
    
    //FIXME handle should be buffered?
    orogen_transports::TypelibMarshallerBase::Handle* handle = marshaller->createSample();
    std::vector<uint8_t> dataCopy(data); //FIXME anoying hack to get around const correctnes
    marshaller->unmarshal(dataCopy, handle);
    void* pData = marshaller->getOrocosSample(handle);
    return pData;//FIXME memroy leak for sure!!!
//     marshaller->deleteHandle(handle);
    //FIXME maybe memory leak? dont know how the deletion stuff works :D    
}



void vizkit3dDebugDrawings::DrawVizkitTypeCommand::execute(vizkit3dDebugDrawings::DrawingManager* drawingManager) const
{
    vizkit3d::Vizkit3DWidget* widget = drawingManager->getVizkit3DWidget();
    vizkit3d::Vizkit3dPluginInformation infos(widget);//FIXME buffer somewhere
    const auto& updateMethodMap = infos.getTypeToUpdateMethodMapping();
    QString qTypeName(QString::fromStdString(typeName));
    
    //remove leading /
    //FIXME for some types the leading :: might be needed?
    if(qTypeName.startsWith("/"))
    {
        qTypeName.remove(0, 1);
    }
    //the orogen typename uses "/" as namespace sperator, the c++ types use "::"
    qTypeName.replace("/", "::");
    
    if(!updateMethodMap.contains(qTypeName))
    {
        LOG_ERROR_S << "Cannot find vizkit library for type: " << qTypeName.toStdString();
        return;
    }

    //FIXME this will load the last library that has been inserted (if multiple libs support this type)
    const QString libName = updateMethodMap.value(qTypeName).libName;
    LOG_INFO_S << "libname for type " << qTypeName.toStdString() << " is: " << libName.toStdString();    
    
    //use direct connection if same thread and blocking otherwise
    Qt::ConnectionType conType = Qt::BlockingQueuedConnection;
    if(QThread::currentThread() == widget->thread())
        conType = Qt::DirectConnection;

    QObject* plugin = nullptr;
    QMetaObject::invokeMethod(widget, "createPlugin", conType,
                              Q_RETURN_ARG(QObject*, plugin),
                              Q_ARG(QString, libName), Q_ARG(QString, ""));
    if(plugin == nullptr)
    {
        LOG_ERROR_S << "unable to load vizkit3d plugin: " << libName.toStdString();
    }
    
    const QMetaMethod& updateMethod = updateMethodMap.value(qTypeName).method;
    std::cout << "GOT METHOD: " << updateMethod.signature() << std::endl;
    void* pData = unmarshall();
    updateMethod.invoke(plugin, conType, QGenericArgument(qTypeName.toStdString().c_str(), pData));
    
}





vizkit3dDebugDrawings::DrawVizkitTypeCommand::~DrawVizkitTypeCommand()
{

}
