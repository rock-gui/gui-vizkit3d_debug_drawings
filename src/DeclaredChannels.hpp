#pragma once
#include <memory>
#include <mutex>
#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace vizkit3dDebugDrawings
{
    
/** A collection of all drawing channels that have been declared so far 
    as well as the means to declare them. */
class DeclaredChannels
{
private:
    static std::shared_ptr<DeclaredChannels> instance; 
    static std::mutex newInstaceMutex;
    
    
    std::unordered_set<std::string> channels;
    mutable std::mutex declareMutex;
    
    DeclaredChannels();
    
    
public:
    /** @return The single instance of the DeclaredChannels.
    */
    static std::shared_ptr<DeclaredChannels> getInstance();
    
    /**Declare a new drawing group.
     * This method is thread safe.
     */
    void declareChannel(const std::string& channel);
    
    
    /**Returns a copy of all declared channels
     * This method is thread safe     */ 
    std::unordered_set<std::string> getChannels() const;
    
};

}
