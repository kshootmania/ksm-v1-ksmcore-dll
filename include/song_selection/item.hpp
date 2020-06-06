#pragma once
#include <filesystem>

namespace SongSelection
{
    namespace fs = std::filesystem;

    class AbstractItem
    {
    public:
        AbstractItem() = default;
        virtual ~AbstractItem() = 0;
        
        virtual std::string getDebugString() const = 0;
    };

}
