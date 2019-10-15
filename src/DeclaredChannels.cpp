#include "DeclaredChannels.hpp"
#include <iostream>


using namespace std;

namespace vizkit3dDebugDrawings
{
    
shared_ptr<DeclaredChannels> DeclaredChannels::instance = nullptr;
mutex DeclaredChannels::newInstaceMutex;
    
shared_ptr<DeclaredChannels> DeclaredChannels::getInstance()
{
    if(instance != nullptr)
    {
        return instance;
    }
    
    lock_guard<mutex> lock(newInstaceMutex);
    //test again, another thread could have created the instance in the meantime
    if(instance == nullptr)
    {
        instance.reset(new DeclaredChannels());
    }
    return instance;
}


DeclaredChannels::DeclaredChannels(){}


void DeclaredChannels::declareChannel(const string& channel)
{
    lock_guard<mutex> lock(declareMutex);
    if(channels.find(channel) != channels.end())
    {
        cout << "WARNING: Debug drawing channel '" << channel << "' has been declared more than once" << endl;
        return;
    }
    channels.insert(channel);
}

unordered_set<string> DeclaredChannels::getChannels() const
{
    lock_guard<mutex> lock(declareMutex);
    return channels;
}







}
