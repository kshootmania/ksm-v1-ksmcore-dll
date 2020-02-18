#pragma once
#include <memory>
#include <vector>
#include "item.hpp"

namespace SongSelection
{

    class List
    {
    private:
        std::vector<std::unique_ptr<AbstractItem>> m_songs;

    public:
        List() = default;
        ~List() = default;
    };

}
