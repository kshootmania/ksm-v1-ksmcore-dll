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
    };

}
